/*
 * Fonts.h
 *
 *  Created on: Jan 11, 2021
 *      Author: Cameron
 */

#ifndef SRC_FONTS_H_
#define SRC_FONTS_H_
#include "stdint.h"


struct FONT_CHAR_INFO {
	uint16_t bitWidth;
	uint16_t bitHeight;
	uint32_t offset;
};

typedef struct FONT_CHAR_INFO FONT_CHAR_INFO;

typedef struct FONT_INFO {
	uint8_t height; 		// Character height
	uint8_t startChar;   	//  Start character
	uint8_t endChar; 		//  End character
	uint8_t spaceWidth; //  Width, in pixels, of space character
	FONT_CHAR_INFO *cInfo; //  Character descriptor array
	uint8_t *bitmap; //  Character bitmap array
} FONT_INFO;

/// Font data stored PER GLYPH
typedef struct {
  uint16_t bitmapOffset; ///< Pointer into GFXfont->bitmap
  uint8_t width;         ///< Bitmap dimensions in pixels
  uint8_t height;        ///< Bitmap dimensions in pixels
  uint8_t xAdvance;      ///< Distance to advance cursor (x axis)
  int8_t xOffset;        ///< X dist from cursor pos to UL corner
  int8_t yOffset;        ///< Y dist from cursor pos to UL corner
} GFXglyph;

/// Data stored for FONT AS A WHOLE
typedef struct {
  uint8_t *bitmap;  ///< Glyph bitmaps, concatenated
  GFXglyph *glyph;  ///< Glyph array
  uint16_t first;   ///< ASCII extents (first char)
  uint16_t last;    ///< ASCII extents (last char)
  uint8_t yAdvance; ///< Newline distance (y axis)
} GFXfont;

#endif /* SRC_FONTS_H_ */
