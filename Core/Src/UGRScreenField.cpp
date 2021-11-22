/*
 * UGRScreenField.cpp
 *
 *  Created on: 16 Nov 2021
 *      Author: camer
 */

#include "UGRScreenField.h"

UGR_ScreenField::UGR_ScreenField(int startx, int starty, char *str, GFXfont font, UGR_Screen *screen) {
	this->startx = startx;
	this->starty = starty;
	this->font	= font;
	this->screen = screen;
	this->currentString = (char*)malloc(33); //TODO allow different sizes

	this->update(str);
}

UGR_ScreenField::~UGR_ScreenField() {
	free(this->currentString);
}

void UGR_ScreenField::update(char *str) {
	//Write new string
	uint16_t localStartX = this->startx;
	uint16_t localStartY = this->starty;
	for (int i = 0; i < strlen(str); i++) {

			//get font bitmap pointer
			int offset = str[i] - font.first;
			GFXglyph * cInfo = &(font.glyph[offset]);
			uint8_t *fontChar = &(font.bitmap[cInfo->bitmapOffset]);
			uint16_t fontColour = COLOR_ORANGE;

			//calculate width to nearest byte
			int width = cInfo->width/ 8;
			if (cInfo->width - width * 8 > 0) {
				width += 1;
			}
			width = width * 8;


		    uint16_t bo = (cInfo->bitmapOffset);
		    uint8_t w = (cInfo->width), h = (cInfo->height), ad = cInfo->xAdvance;
		    int8_t xo = (cInfo->xOffset),
		           yo = (cInfo->yOffset);
		    uint8_t xx, yy, bits = 0, bit = 0;
		    int16_t xo16 = 0, yo16 = 0;

			xo16 = xo;
			yo16 = yo;

			//init DMA buffer
			screen->ILI9341StreamBufIndex = 0;
			while(HAL_SPI_GetState(this->screen->spiHandle) != HAL_SPI_STATE_READY){
				//TODO find better way or checking, also timeout code?
			}
			ILI9341_SetCursorPosition(localStartX, localStartY, localStartX + w -1, localStartY + h - 1);
			this->screen->setDataMode();


		    for (yy = 0; yy < h; yy++) {
		      for (xx = 0; xx < w; xx++) {
		        if (!(bit++ & 7)) {
		          bits = (font.bitmap[bo++]);
		        }
		        if (bits & 0x80) {
		        	screen->ILI9341StreamBuf[screen->ILI9341StreamBufIndex++] = fontColour>>8;
		        	screen->ILI9341StreamBuf[screen->ILI9341StreamBufIndex++] = fontColour;
		        } else {
		        	screen->ILI9341StreamBuf[screen->ILI9341StreamBufIndex++] = COLOR_BLACK>>8;
		        	screen->ILI9341StreamBuf[screen->ILI9341StreamBufIndex++] = COLOR_BLACK;
		        }


		        bits <<= 1;


		        //check buffer fullness
		        if(screen->ILI9341StreamBufIndex == ILI_STREAMBUF_SIZE/2){
		        	//check if DMA in progress, if so, wait for completion
		        	while(HAL_SPI_GetState(this->screen->spiHandle) != HAL_SPI_STATE_READY){
		        		//TODO find better way or checking, also timeout code?
		        	}
		        	//Otherwise, start DMA transfer
		        	HAL_SPI_Transmit_DMA(this->screen->spiHandle, screen->ILI9341StreamBuf, ILI_STREAMBUF_SIZE/2);
		        } else if(screen->ILI9341StreamBufIndex == ILI_STREAMBUF_SIZE){
		        	//check if DMA in progress, if so, wait for completion
		        	while(HAL_SPI_GetState(this->screen->spiHandle) != HAL_SPI_STATE_READY){
		        		//TODO find better way or checking, also timeout code?
		        	}
		        	//Otherwise, start DMA transfer
		        	HAL_SPI_Transmit_DMA(this->screen->spiHandle, screen->ILI9341StreamBuf + ILI_STREAMBUF_SIZE/2, ILI_STREAMBUF_SIZE/2);
		        	screen->ILI9341StreamBufIndex = 0;
		        }
		      }
		    }

			//Check if anything is left in the buffer after pixel generation
			if(screen->ILI9341StreamBufIndex > 0){
				//check if DMA in progress, if so, wait for completion
				while(HAL_SPI_GetState(this->screen->spiHandle) != HAL_SPI_STATE_READY){
					//TODO find better way or checking, also timeout code?
				}
				//Otherwise, start DMA transfer
				if(screen->ILI9341StreamBufIndex > ILI_STREAMBUF_SIZE/2){
					HAL_SPI_Transmit_DMA(this->screen->spiHandle, screen->ILI9341StreamBuf + ILI_STREAMBUF_SIZE/2, screen->ILI9341StreamBufIndex - ILI_STREAMBUF_SIZE/2);
				} else {
					HAL_SPI_Transmit_DMA(this->screen->spiHandle, screen->ILI9341StreamBuf, screen->ILI9341StreamBufIndex);
				}
			}

			const char* teststr = "10";
			if(strcmp(str, teststr) == 0){
				while(HAL_SPI_GetState(this->screen->spiHandle) != HAL_SPI_STATE_READY){
									//TODO find better way or checking, also timeout code?
								}
			}

		//compare max dimensions, blanking extra space from prev. string
			if(i < strlen(this->currentString)){
				offset = this->currentString[i] - font.first;
				cInfo = &(font.glyph[offset]);
				//if there isnt full overlap on the right, blank it out
				if(cInfo->width > w){
					//TODO dont use slow function for this
					while(HAL_SPI_GetState(this->screen->spiHandle) != HAL_SPI_STATE_READY){
						//TODO find better way or checking, also timeout code?
					}
					if(cInfo->height > h){
						ILI9341_Fill_Rect(localStartX + w , localStartY, localStartX + cInfo->width -1, localStartY + cInfo->height -1, COLOR_BLACK);
					} else {
						ILI9341_Fill_Rect(localStartX + w , localStartY, localStartX + cInfo->width -1, localStartY + h -1, COLOR_BLACK);
					}
				}
				//if there isnt full overlap on the bottom (and a little bit on the corner)l blank it out
				if(cInfo->height > h){
					//TODO dont use slow function for this
					while(HAL_SPI_GetState(this->screen->spiHandle) != HAL_SPI_STATE_READY){
						//TODO find better way or checking, also timeout code?
					}
					if(cInfo->width > w){
						ILI9341_Fill_Rect(localStartX, localStartY + h, localStartX + cInfo->width -1, localStartY + cInfo->height -1, COLOR_BLACK);
					} else {
						ILI9341_Fill_Rect(localStartX, localStartY + h, localStartX + w -1, localStartY + cInfo->height -1, COLOR_BLACK);
					}
				}
			}

			localStartX += ad;
		}

	strncpy(this->currentString, str, 32);

}



void UGR_ScreenField::clear() {
}

uint16_t UGR_ScreenField::getStartx() const {
	return startx;
}

uint16_t UGR_ScreenField::getStarty() const {
	return starty;
}

uint16_t UGR_ScreenField::getColour() const {
	return colour;
}

void UGR_ScreenField::setColour(uint16_t colour) {
	this->colour = colour;
}

const GFXfont& UGR_ScreenField::getFont() const {
	return font;
}
