/*
 * UGRScreen.cpp
 *
 *  Created on: 16 Nov 2021
 *      Author: camer
 */

#include "UGRScreen.h"


UGR_Screen::UGR_Screen(SPI_HandleTypeDef *spiLcdHandle, GPIO_TypeDef *csPORT,
		uint16_t csPIN, GPIO_TypeDef *dcPORT, uint16_t dcPIN,
		GPIO_TypeDef *resetPORT, uint16_t resetPIN) {

//	memcpy(&this->spiHandle, spiLcdHandle, sizeof(*spiLcdHandle));
	this->spiHandle = spiLcdHandle;
	this->csPORT 	= csPORT;
	this->csPIN		= csPIN;
	this->dcPORT	= dcPORT;
	this->dcPIN		= dcPIN;
	this->resetPORT	= resetPORT;
	this->resetPIN	= resetPIN;

	ILI9341_Init(spiLcdHandle, csPORT, csPIN, dcPORT, dcPIN, resetPORT, resetPIN);
	ILI9341_setRotation(4);
}

UGR_Screen::~UGR_Screen() {
	// TODO Auto-generated destructor stub
}

uint16_t UGR_Screen::getCsPin() const {
	return csPIN;
}

const GPIO_TypeDef* UGR_Screen::getCsPort() const {
	return csPORT;
}

uint16_t UGR_Screen::getDcPin() const {
	return dcPIN;
}

const GPIO_TypeDef* UGR_Screen::getDcPort() const {
	return dcPORT;
}

void UGR_Screen::setDataMode() {
	HAL_GPIO_WritePin(this->dcPORT, this->dcPIN, GPIO_PIN_SET);
}

bool UGR_Screen::checkSpiReady() {
	return HAL_SPI_GetState(this->spiHandle) == HAL_SPI_STATE_READY;
}

const GPIO_TypeDef* UGR_Screen::getResetPort() const {
	return resetPORT;
}
