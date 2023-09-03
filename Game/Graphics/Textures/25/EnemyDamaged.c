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
* Source file: Enemy1                                                *
* Dimensions:  37 * 37                                               *
* NumColors:   65536 colors + 8 bit alpha channel                    *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmEnemyDamaged;

static GUI_CONST_STORAGE unsigned char _acEnemy1[] = {
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xD8,0x00,0x00, 0x8C,0x00,0x00, 0x7D,0x00,0x00, 0x8E,0x00,0x00, 0xE4,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFA,0x00,0x00, 0xCA,0x00,0x00, 0xAF,0x00,0x00, 0xCE,0x00,0x00, 
        0xBF,0x00,0x00, 0x12,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x1F,0x00,0x00, 0xCA,0x00,0x00, 0xFF,0x00,0x00, 0xFD,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xD6,0x00,0x00, 0x35,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x03,0x00,0x00, 
        0x06,0x00,0x00, 0x00,0x00,0x00, 0x00,0x90,0x00, 0x00,0xB8,0x00, 0x00,0x88,0x00, 0x00,0x00,0x00, 0x0D,0x00,0x00, 0x33,0x00,0x00, 0x31,0x00,0x00, 0x35,0x00,0x00, 0x85,0x00,0x00, 0xFD,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFC,0x00,0x00, 0x39,0x00,0x00, 0x00,0x00,0x00, 0x00,0x68,0x00, 0x00,0x98,0x00, 0x00,0x70,0x00, 
        0x00,0x58,0x00, 0x00,0xA0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xA8,0x00, 0x00,0x38,0x00, 0x00,0x30,0x00, 0x00,0x30,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x88,0x00,0x20, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xE9,0x00,0x00, 0x10,0x00,0x00, 0x00,0x48,0x00, 0x00,0xE8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xE8,0x00, 0x00,0xE8,0x00, 0x00,0xE8,0x00, 0x00,0xC8,0x00, 0x00,0x18,0xE3, 0x1A,0x00,0x00, 0xEE,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xE4,0x00,0x00, 0x10,0x00,0x00, 0x00,0x50,0x00, 0x00,0xF0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0x78,0x00, 0x00,0x00,0x00, 0xC3,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xA3,0x00,0x20, 0x2A,0x00,0x00, 0x00,0x00,0x00, 0x00,0x78,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xA8,0x00, 0x00,0x00,0x00, 0x2E,0x00,0x00, 0xA0,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xAD,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x68,0x00, 0x00,0xE0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xE0,0x00, 0x00,0x60,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x7C,0x08,0x21, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFE,0x00,0x00, 0x37,0x00,0x00, 0x00,0x00,0x00, 0x00,0xC0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF0,0x00, 0x00,0xC8,0x00, 0x00,0x48,0x00, 0x00,0x00,0x00, 
        0xC6,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xF3,0x00,0x00, 0x1B,0x00,0x00, 0x00,0x18,0xA3, 0x00,0xD8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xE8,0x00, 0x00,0x68,0x00, 0x00,0x00,0x00, 
        0xA0,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0x70,0x00,0x00, 0x00,0x00,0x00, 0x00,0x60,0x00, 0x00,0xF0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xA0,0x00, 0x00,0x00,0x00, 0x26,0x08,0x21, 
        0xEF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFE,0x00,0x20, 0x3C,0x00,0x00, 0x00,0x00,0x00, 0x00,0xD8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xB0,0x00, 0x00,0x00,0x00, 0x23,0x00,0x00, 
        0x6E,0x00,0x00, 0x63,0x00,0x00, 0x79,0x00,0x00, 0x97,0x00,0x00, 0xA8,0x00,0x00, 0x7F,0x00,0x00, 0x85,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xF3,0x00,0x00, 0x2D,0x00,0x00, 0x00,0x00,0x00, 0x00,0xD8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF0,0x00, 0x00,0x50,0x00, 0x00,0x00,0x00, 
        0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x1B,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0x65,0x00,0x20, 0x00,0x00,0x00, 0x00,0x78,0x00, 0x00,0xF0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF0,0x00, 0x00,0x58,0x00, 0x07,0x00,0x00, 
        0x89,0x00,0x00, 0xA8,0x00,0x00, 0x8F,0x00,0x00, 0x70,0x00,0x00, 0x61,0x00,0x00, 0x76,0x00,0x00, 0xBE,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xD9,0x00,0x00, 0x06,0x00,0x00, 0x00,0x48,0x00, 0x00,0xE8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF0,0x00, 0x00,0x90,0x00, 0x00,0x00,0x00, 0x2D,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xD0,0x00,0x00, 0x00,0x00,0x00, 0x00,0x38,0x00, 0x00,0xC0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xA8,0x00, 0x00,0x00,0x00, 0x17,0x00,0x00, 0xC1,0x00,0x20, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0x6F,0x08,0x21, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0xB8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0x90,0x00, 0x00,0x00,0x00, 0xAB,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xA4,0x00,0x20, 0x06,0x00,0x00, 0x00,0x50,0x00, 0x00,0xF0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0x88,0x00, 0x00,0x00,0x00, 0xC1,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFD,0x00,0x00, 0x26,0x00,0x00, 0x00,0x40,0x00, 0x00,0xF0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xD8,0x00, 0x00,0xC8,0x00, 0x00,0x60,0x00, 0x04,0x00,0x00, 0xD4,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFA,0x00,0x00, 0x27,0x00,0x00, 0x00,0x28,0x00, 0x00,0x90,0x00, 0x00,0x80,0x00, 0x00,0x90,0x00, 0x00,0xE0,0x00, 
        0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xA0,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x1A,0x00,0x20, 0xED,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0x7A,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x70,0x00, 
        0x00,0xF0,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xF8,0x00, 0x00,0xE0,0x00, 0x00,0x00,0x00, 0x13,0x00,0x00, 0x5F,0x00,0x00, 0x64,0x00,0x00, 0xC2,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFB,0x00,0x00, 0xB4,0x00,0x00, 0xA8,0x00,0x00, 0xC6,0x00,0x00, 0x33,0x00,0x00, 0x00,0x00,0x00, 
        0x00,0xB8,0x00, 0x00,0xF8,0x00, 0x00,0xF0,0x00, 0x00,0xB8,0x00, 0x00,0x90,0x00, 0x00,0xD0,0x00, 0x00,0xE8,0x00, 0x00,0x98,0x00, 0x00,0x00,0x00, 0x6D,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xBC,0x00,0x00, 0x00,0x00,0x00, 
        0x00,0x30,0x00, 0x00,0x88,0x00, 0x00,0x58,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x00,0x00, 0x00,0x38,0x00, 0x00,0x00,0x00, 0x10,0x00,0x00, 0xD1,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0x7E,0x08,0x21, 
        0x00,0x00,0x00, 0x00,0x00,0x00, 0x07,0x00,0x00, 0x4E,0x00,0x00, 0x82,0x00,0x20, 0x32,0x00,0x00, 0x16,0x00,0x00, 0x4C,0x00,0x00, 0xD3,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xCA,0x00,0x00, 0xBA,0x00,0x00, 0xD8,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFC,0x00,0x00, 0xEE,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00,
  0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 
        0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00, 0xFF,0x00,0x00
};

GUI_CONST_STORAGE GUI_BITMAP bmEnemyDamaged = {
  37, // xSize
  37, // ySize
  111, // BytesPerLine
  24, // BitsPerPixel
  (unsigned char *)_acEnemy1,  // Pointer to picture data
  NULL,  // Pointer to palette
  GUI_DRAW_BMPAM565
};

/*************************** End of file ****************************/