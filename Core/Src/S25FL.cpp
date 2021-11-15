/*
 * S25FL.cpp
 *
 *  Created on: Nov 8, 2020
 *      Author: Cameron
 */



#include "S25FL.h"

/**
 * @brief constructor for flash class, assuming software CS control
 * @param spiFlashHandle the HAL flash definition for the SPI interface
 * @param csPORT the GPIO port on which the CS pin is connected
 * @param csPIN the pin number of the CS port
 */
S25FL::S25FL(SPI_HandleTypeDef *spiFlashHandle, GPIO_TypeDef *csPORT, uint16_t csPIN) {
	// TODO Auto-generated constructor stub
	_SPIhandle = spiFlashHandle;
	_csPORT = csPORT;
	_csPIN  = csPIN;
	HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_SET);
	HWNSS = false;
}

S25FL::S25FL(){

}

S25FL::~S25FL() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief initialises the flash chip and confirms its ID
 * @return fail or success of initialisation
 */
int S25FL::begin() {
	this->reset();
	HAL_Delay(1);
	uint8_t txBuf[6] = {FL_READ_ID,0,0,0,0,0};
	uint8_t rxBuf[6];
	this->transfer(txBuf, rxBuf, sizeof(txBuf));
	if(rxBuf[4] == 0x01 && rxBuf[5] == 0x17){             //Manufacturer ID confirmed (128Mbit)
	_maxAddress = 0x00FFFFFF;
	}else if(rxBuf[4] == 0x01 && rxBuf[5] == 0x18){       //Manufacturer ID confirmed (256Mbit)
	_maxAddress = 0x01FFFFFF;
	}else{
	  return 1;
	}
	return 0;
}

/**
 * @brief sends a reset command to the flash chip
 */
void S25FL::reset() {
	this->transfer(FS_RESET);
}

/**
 * @brief transfers/receives an amount of bytes to/from a transmit and receive buffer
 * @note Both buffers must be of the same size
 * @param txBuf transmit buffer
 * @param rxBuf receiver buffer
 * @param len   number of bytes to transfer
 */
void S25FL::transfer(uint8_t *txBuf, uint8_t *rxBuf, uint32_t len) {
	if(!HWNSS) HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(_SPIhandle, txBuf, rxBuf, len, HAL_MAX_DELAY);
	if(!HWNSS) HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_SET);
}

/**
 * @brief transfers/receives a single byte. Useful for simple commands
 * @param buf the byte to send
 * @return the single byte received
 */
uint8_t S25FL::transfer(uint8_t buf) {
	if(!HWNSS) HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_RESET);
	uint8_t rx;
	HAL_SPI_TransmitReceive(_SPIhandle, &buf, &rx, 1, HAL_MAX_DELAY);
	if(!HWNSS) HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_SET);
	return rx;
}

/**
 * @brief un-sets the write enable bit if it is set.
 */
void S25FL::write_disable() {
	this->transfer(FL_WRITE_DISABLE);
}

/**
 * @brief sets the write enable bit on the flash IC so that a write command can be used.
 * 		  This bit is reset after each write command.
 */
void S25FL::write_enable() {
	this->transfer(FL_WRITE_ENABLE);
}

/**
 * @brief checks the flash IC for writes in progress
 * @return if write in progress (busy)
 */
char S25FL::check_WIP() {
	uint8_t rxBuf[2];
	uint8_t txBuf[2] = {FL_READ_STATREG1, 0};
	this->transfer(txBuf, rxBuf, 2);
	return rxBuf[1] & 0x01;             //Return Write in Progress bit
}

/**
 * @brief blocking function that only returns when the flash chip is no longer writing data/busy
 */
void S25FL::block_WIP() {
	while(this->check_WIP());
}

/**
 * @brief from a starting address, move bytes from flash into the given buffer. No size limit.
 * @param add Address to start reading from
 * @param buf The buffer where the read data will be moved to
 * @param len The amount of data (bytes) to be transfered
 */
void S25FL::read(uint32_t add, uint8_t *buf, uint32_t len) {
	this->block_WIP();
	HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_RESET);
	add = __builtin_bswap32(add);
	uint8_t com = FL_READ;
	HAL_SPI_Transmit(_SPIhandle, &com, 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(_SPIhandle, (uint8_t*)&add, 4, HAL_MAX_DELAY);
	HAL_SPI_Receive(_SPIhandle, buf, len, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_SET);
}

/**
 * @brief move up to 512 bytes of data into the page program buffer. The data is programmed onto the chip after transfer has ended.
 * @param add Address to start programming from
 * @param buf The buffer pointer to be copied to the flash buffer
 * @param len The length of data to be copied to the flash buffer
 */
void S25FL::program(uint32_t add, uint8_t *buf, uint32_t len) {
	this->block_WIP();
	this->write_enable();
	HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_RESET);
	add = __builtin_bswap32(add);
	uint8_t com = FL_PAGE_PROG;
	HAL_SPI_Transmit(_SPIhandle, &com, 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(_SPIhandle, (uint8_t*)&add, 4, HAL_MAX_DELAY);
	HAL_SPI_Transmit(_SPIhandle, buf, len, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_SET);
}

/**
 * @brief Erases one page (64KB or 256KB)
 * @param add
 */
void S25FL::sector_erase(uint32_t add) {
	add = __builtin_bswap32(add);
	this->block_WIP();
	this->write_enable();
	HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_RESET);
	uint8_t com = FL_SECTOR_ERASE;
	HAL_SPI_Transmit(_SPIhandle, &com, 1, HAL_MAX_DELAY);
	HAL_SPI_Transmit(_SPIhandle, (uint8_t*)&add, 4, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(_csPORT, _csPIN, GPIO_PIN_SET);
}

void S25FL::bulk_erase() {
	this->block_WIP();
	this->write_enable();
	this->transfer(FL_BULK_ERASE);
}


