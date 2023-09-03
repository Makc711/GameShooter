/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter (ST) for emWin V5.44.                      *
*        Compiled Nov 10 2017, 08:52:20                              *
*                                                                    *
*        (c) 1998 - 2017 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: Speed                                                 *
* Dimensions:  25 * 25                                               *
* NumColors:   65536 colors + 8 bit alpha channel                    *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmSpeed;

static GUI_CONST_STORAGE unsigned char _acSpeed[] = {
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xB1,0x00,0x00, 0x64,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFB,0x00,0x00, 0x32,0x84,0x51, 0x00,0xB5,0xD7, 0xA6,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xA1,0x00,0x00, 0x00,0xC6,0x58, 0x00,0xF7,0xFF, 0x1D,0x73,0xCE, 0xEC,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFE,0x00,0x00, 0xFE,0x00,0x00, 0xFF,0x00,0x00, 0xFB,0x00,0x00, 0x31,0x3B,0x0E, 0x00,0x9D,0x97, 0x00,0xB5,0xF7, 0x00,0x75,0x37, 0x79,0x2A,0x09, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFE,0x00,0x00, 0xF5,0x00,0x00, 0xF5,0x00,0x00, 0xFF,0x00,0x00, 0xB6,0x00,0x00, 0x00,0x75,0x16, 0x00,0x8E,0x5C, 0x00,0x8E,0x3C, 0x00,0x9F,0x1F, 0x12,0x64,0xB5, 
        0xE7,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFE,0x00,0x00, 0xFC,0x00,0x00, 0xFD,0x00,0x00, 0xFF,0x00,0x00, 0x5A,0x3A,0x8B, 0x00,0x85,0xDA, 0x00,0x8E,0x3B, 0x00,0x9E,0xFF, 0x00,0x9F,0x1F, 0x00,0x8E,0x3C, 
        0x72,0x29,0x87, 0xE6,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFD,0x00,0x00, 0xF5,0x00,0x00, 0xF9,0x00,0x21, 0xE5,0x00,0x00, 0x17,0x5C,0x53, 0x00,0x6C,0xD5, 0x00,0xBD,0xD6, 0x00,0x95,0xFA, 0x00,0x9F,0x1F, 0x00,0x96,0xBE, 
        0x00,0x94,0xB3, 0x15,0xB5,0xB6, 0xE4,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFE,0x00,0x00, 0xFD,0x00,0x00, 0xFD,0x00,0x00, 0xFE,0x00,0x00, 0xFE,0x00,0x00, 0xFF,0x00,0x00, 0xBE,0x00,0x00, 0x00,0x75,0x37, 0x00,0x7D,0x58, 0x00,0xAD,0x96, 0x00,0x8E,0x1B, 0x00,0x9F,0x1F, 0x00,0x96,0xDE, 
        0x00,0x8C,0xF5, 0x34,0x9C,0xF3, 0xEF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xF9,0x00,0x00, 0xF4,0x00,0x00, 0xF5,0x00,0x00, 0xF6,0x00,0x00, 0xF8,0x00,0x00, 0xFF,0x00,0x00, 0x8D,0x19,0x46, 0x00,0x7D,0xB9, 0x00,0x96,0xBD, 0x00,0x96,0xDE, 0x00,0x96,0xDE, 0x00,0x75,0x58, 0x00,0x85,0xDA, 
        0x00,0x86,0x1B, 0xA0,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0x6D,0x00,0xA4, 0x00,0x75,0x37, 0x00,0x96,0xDE, 0x00,0x9F,0x1F, 0x00,0x9E,0xFF, 0x00,0x9E,0xFF, 0x00,0x9F,0x1F, 
        0x00,0x96,0x9D, 0x7B,0x3A,0xAC, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFB,0x00,0x00, 0xFD,0x00,0x00, 0x61,0x62,0x81, 0x00,0x8B,0xC9, 0x00,0x7D,0xDA, 0x00,0x9F,0x1F, 0x00,0x9E,0xFF, 0x00,0x9F,0x1F, 0x00,0x9E,0xFF, 
        0x00,0x7D,0x78, 0x68,0x29,0xC8, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFE,0x00,0x00, 0xF7,0x00,0x00, 0xF8,0x00,0x00, 0xF9,0x00,0x00, 0xFF,0x00,0x00, 0x73,0x62,0xA5, 0x00,0xDD,0xEA, 0x00,0x94,0x4A, 0x00,0x8E,0x7D, 0x00,0x9F,0x1F, 0x00,0x9E,0xFF, 0x00,0x7D,0x57, 
        0x00,0xA5,0xB7, 0x6A,0x63,0x4D, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFE,0x00,0x00, 0xFA,0x00,0x00, 0xFA,0x00,0x00, 0xFB,0x00,0x00, 0xFF,0x00,0x00, 0x91,0x4A,0x23, 0x00,0xBD,0x08, 0x00,0x8D,0x35, 0x00,0x9E,0xFF, 0x00,0x9F,0x1F, 0x00,0x9F,0x1F, 0x00,0x8D,0xD9, 
        0x00,0xB6,0x39, 0x7C,0x5B,0x2D, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFB,0x00,0x00, 0xFB,0x00,0x00, 0xB7,0x00,0x00, 0x00,0x53,0x8F, 0x00,0x8E,0x7D, 0x00,0x9F,0x1F, 0x00,0x9E,0xFF, 0x00,0x9F,0x1F, 0x00,0x9E,0xFF, 
        0x00,0x7C,0xD5, 0x9F,0x39,0x84, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xED,0x00,0x00, 0x18,0x53,0x0C, 0x00,0x6C,0x93, 0x00,0x86,0x1B, 0x00,0x9E,0xFF, 0x00,0x96,0xDE, 0x00,0x85,0xB9, 
        0x01,0x63,0x6C, 0xCD,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xF9,0x00,0x00, 0xF5,0x00,0x00, 0xF7,0x00,0x00, 0xF7,0x00,0x00, 0xF9,0x00,0x00, 0xFF,0x00,0x00, 0x5A,0x74,0x0F, 0x00,0xC6,0xB9, 0x00,0x8C,0xF3, 0x00,0x8E,0x7D, 0x00,0x8D,0x13, 0x00,0xD5,0xA8, 
        0x26,0xA4,0x67, 0xF7,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFD,0x00,0x00, 0xFB,0x00,0x00, 0xFC,0x00,0x00, 0xFD,0x31,0xA6, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xC5,0x00,0x00, 0x00,0xB6,0x17, 0x00,0x95,0x76, 0x00,0x96,0xFF, 0x00,0x95,0xD9, 0x00,0xD5,0xC9, 
        0x74,0x7B,0x66, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xCC,0x00,0x00, 0x8B,0x94,0x92, 0x57,0xB5,0xB6, 0x06,0x8C,0x71, 0x00,0x75,0x37, 0x00,0x9E,0xFF, 0x00,0x96,0xDE, 0x08,0x84,0x2D, 
        0xD7,0x18,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xF2,0x18,0xC3, 0x57,0xBD,0xF7, 0x00,0xDE,0xFB, 0x00,0xEF,0x9D, 0x00,0xFF,0xFF, 0x00,0xE7,0x1B, 0x00,0x75,0x57, 0x00,0x96,0x9D, 0x00,0x96,0xDE, 0x6A,0x33,0x71, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xBB,0xAD,0x55, 0x00,0xE7,0x5C, 0x2C,0xA5,0x14, 0x5F,0x9C,0xD3, 0x4C,0xB5,0xB6, 0x68,0xDE,0xFB, 0x7F,0x63,0xD0, 0x00,0x85,0xFA, 0x1D,0x75,0x58, 0x84,0xE7,0x1C, 
        0x5F,0xC6,0x18, 0xFC,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xF6,0x18,0xC3, 0x39,0x8C,0x51, 0x8F,0x21,0x24, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0x6A,0x4B,0xB0, 0x85,0x6B,0xD0, 0x11,0xEF,0x9D, 
        0x00,0xF7,0xBE, 0x62,0x8C,0x51, 0xE0,0x00,0x00, 0x84,0x10,0x62, 0xF3,0x20,0xE4, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xF4,0x00,0x00, 0xF3,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xA3,0x7B,0xEF, 
        0x0F,0xD6,0xBA, 0x00,0xE7,0x3C, 0x0B,0xB5,0xB6, 0x0A,0xB5,0xD6, 0xEC,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFB,0x00,0x00, 0xF5,0x00,0x00, 0xF3,0x00,0x00, 0xEE,0x00,0x00, 0xEC,0x00,0x00, 0xEA,0x00,0x00, 0xE9,0x00,0x00, 0xE8,0x00,0x00, 0xE7,0x18,0xC3, 0xEF,0x00,0x00, 
        0xC5,0x00,0x00, 0x53,0xA5,0x34, 0x11,0xDE,0xDB, 0x70,0xCE,0x79, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFA,0x00,0x00, 0xE7,0x00,0x00, 0xE3,0x00,0x00, 0xE3,0x00,0x00, 0xE3,0x00,0x00, 0xE4,0x00,0x00, 0xE4,0x00,0x00, 0xE4,0x00,0x00, 0xE5,0x00,0x00, 0xE5,0x08,0x41, 
        0xEA,0x00,0x00, 0xEA,0x00,0x00, 0xDB,0x00,0x00, 0xFB,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFD,0x00,0x00, 0xF8,0x00,0x00, 0xF2,0x00,0x00, 0xEE,0x00,0x00, 0xEB,0x00,0x00, 0xE9,0x00,0x00, 0xE7,0x00,0x00, 0xE5,0x00,0x00, 0xE5,0x00,0x00, 
        0xE5,0x00,0x00, 0xE8,0x00,0x00, 0xF5,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00
};

GUI_CONST_STORAGE GUI_BITMAP bmSpeed = {
  25, // xSize
  25, // ySize
  75, // BytesPerLine
  24, // BitsPerPixel
  (unsigned char *)_acSpeed,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMPAM565
};

/*************************** End of file ****************************/
