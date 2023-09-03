/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2023  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V6.32 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only  be used  in accordance  with  a license  and should  not be  re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIConf.c
Purpose     : Display controller initialization
---------------------------END-OF-HEADER------------------------------
*/

#include "GUIConf.h"
#include "ExtraMemories.h"
#include "GUI.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
// GUI_MEMDEV_CreateFixed = 5x5x3 = 0,074 kB
// GUI_MEMDEV_CreateFixed = 25x25x3 = 1,832 kB
// GUI_MEMDEV_CreateFixed = 37x37x3 = 4,011 kB
// GUI_MEMDEV_CreateFixed = 480x272x3 = 382,5 kB
// GUI_MEMDEV_CopyToLCD = 480x272x3 = 382,5 kB - once
// 0,074 * 2 + 1,832 * 5 + 4,011 * 4 + 382,5 * 2 + 382,5 + 10% = 1290
// Define the available number of bytes available for the GUI
#define GUI_NUMBYTES  (1024 * 1290)

#if defined ( __ICCARM__ ) // !< IAR Compiler
#pragma location=0xC0300000
static __no_init U32 aMemory[GUI_NUMBYTES / 4];

#elif defined ( __CC_ARM ) //!< Keil Compiler
U32 aMemory[GUI_NUMBYTES / 4] __attribute__((at(0xC0300000)));

#elif defined ( __GNUC__ ) // !< GNU Compiler
U32 SDRAM_DATA aMemory[GUI_NUMBYTES / 4];
//U32 aMemory[GUI_NUMBYTES / 4] __attribute__((__section__(".GUI_NUMBYTES_section")));
#endif

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUI_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   available memory for the GUI.
*/
void GUI_X_Config(void)
{
  // 32 bit aligned memory area
//  static U32 aMemory[GUI_NUMBYTES / 4];

  // Assign memory to emWin
  GUI_ALLOC_AssignMemory(aMemory, GUI_NUMBYTES);

  // Set default font
  GUI_SetDefaultFont(GUI_DEFAULT_FONT);
}

/*************************** End of file ****************************/
