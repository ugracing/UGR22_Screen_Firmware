/*
 * S25FL.h
 *
 *  Created on: Nov 8, 2020
 *      Author: Cameron
 */

#ifndef SRC_S25FL_H_
#define SRC_S25FL_H_

#include "stm32l4xx_hal.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FL_READ_ID            0x90
#define FL_WRITE_DISABLE      0X04
#define FL_WRITE_ENABLE       0X06

#define FL_READ_STATREG1      0X05

#define FL_READ               0X13

#define FL_PAGE_PROG          0x12

#define FL_SECTOR_ERASE       0XDC
#define FL_BULK_ERASE         0X60
#define FS_RESET              0xFF

class S25FL {
public:
	S25FL(SPI_HandleTypeDef *spiFlashHandle, GPIO_TypeDef *csPORT, uint16_t csPIN);
	S25FL();
	virtual ~S25FL();
    int begin();
    void reset();                                               //Resets the chip
    void transfer(uint8_t * txBuf, uint8_t * rxBuf, uint32_t len);                       //Acts as SPI.transfer specific to flash. The buffer will be written with the recieved data.
    uint8_t transfer(uint8_t buf);                                    //Acts as SPI.transfer specific to flash. Will return recieved character.
    void write_disable();                                       //Disables Write ability on the flash chip.
    void write_enable();                                        //Enables Write ability on the flash chip (will re-disable after any write command).
    char check_WIP();                                           //Returns the Write In Progress bit from flash.
    void block_WIP();                                           //Only returns once a write cycle has completed on the flash chip.
    void read(uint32_t add, uint8_t * buf, uint32_t len);       //Read from address add into buf for byte length len (no size limit).
    void program(uint32_t add, uint8_t * buf, uint32_t len);    //Program from address add from buf for byte length len (size limit is end of address program page)
    void sector_erase(uint32_t add);
    void bulk_erase();

	uint32_t getMaxAddress() const {
		return _maxAddress;
	}

private:
	char HWNSS = true;
    GPIO_TypeDef *_csPORT;
    uint16_t _csPIN;
    SPI_HandleTypeDef * _SPIhandle;
    uint32_t _maxAddress;
};

#endif /* SRC_S25FL_H_ */
