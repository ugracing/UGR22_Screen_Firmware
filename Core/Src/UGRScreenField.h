/*
 * UGRScreenField.h
 *
 *  Created on: 16 Nov 2021
 *      Author: camer
 */

#ifndef SRC_UGRSCREENFIELD_H_
#define SRC_UGRSCREENFIELD_H_

#include "Fonts.h"
#include "string.h"
#include "UGRScreen.h"

class UGR_ScreenField {
public:
	UGR_ScreenField(int startx, int starty, char *str, GFXfont font, UGR_Screen *screen);
	virtual ~UGR_ScreenField();
	void update(char *str);
	void clear();

	uint16_t getStartx() const;
	uint16_t getStarty() const;
	uint16_t getColour() const;
	void setColour(uint16_t colour);
	const GFXfont& getFont() const;

	GFXfont font;
	uint16_t startx;
	uint16_t starty;
	uint16_t colour;
	uint16_t lastWidth;
	uint16_t lastHeight;
	char *currentString;

	UGR_Screen *screen;
};

#endif /* SRC_UGRSCREENFIELD_H_ */
