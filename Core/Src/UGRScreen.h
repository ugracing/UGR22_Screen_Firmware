/*
 * UGRScreen.h
 *
 *  Created on: 16 Nov 2021
 *      Author: camer
 */

#ifndef SRC_UGRSCREEN_H_
#define SRC_UGRSCREEN_H_

#define ILI_STREAMBUF_SIZE	2048


#include "stm32l4xx_hal.h"
#include "string.h"

extern "C" {
#include "MY_ILI9341.h"
}


class UGR_Screen {
public:
	UGR_Screen(SPI_HandleTypeDef *spiLcdHandle, GPIO_TypeDef *csPORT, uint16_t csPIN, GPIO_TypeDef *dcPORT, uint16_t dcPIN, GPIO_TypeDef *resetPORT, uint16_t resetPIN);
	virtual ~UGR_Screen();
	void setDataMode();
	bool checkSpiReady();

	uint16_t getCsPin() const;
	const GPIO_TypeDef* getCsPort() const;
	uint16_t getDcPin() const;
	const GPIO_TypeDef* getDcPort() const;
	const GPIO_TypeDef* getResetPort() const;


	uint32_t ILI9341StreamBufIndex;
	uint8_t ILI9341StreamBuf[ILI_STREAMBUF_SIZE];

	SPI_HandleTypeDef *spiHandle;
	GPIO_TypeDef *csPORT;
	uint16_t csPIN;
	GPIO_TypeDef *dcPORT;
	uint16_t dcPIN;
	GPIO_TypeDef *resetPORT;
	uint16_t resetPIN;
};

#endif /* SRC_UGRSCREEN_H_ */
