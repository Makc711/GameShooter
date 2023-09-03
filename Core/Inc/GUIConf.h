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
File        : GUIConf.h
Purpose     : Configuration of available features and default values
----------------------------------------------------------------------
*/

#ifndef GUICONF_H
#define GUICONF_H

/*********************************************************************
*
*       Multi layer/display support
*/
#define GUI_NUM_LAYERS      2   // Maximum number of available layers

/*********************************************************************
*
*       Multi tasking support
*/
#ifdef OS_SUPPORT
#define GUI_OS                    (1)  // Compile with multitasking support
#else
#define GUI_OS                    (0)
#endif

/*********************************************************************
*
*       Configuration of touch support
*/
#ifndef   GUI_SUPPORT_TOUCH
#define GUI_SUPPORT_TOUCH       (1)  // Support touchscreen
#endif

/*********************************************************************
*
*       Default font
*/
#define GUI_DEFAULT_FONT          &GUI_Font6x8

/*********************************************************************
*
*       Configuration of available packages
*/
#define GUI_SUPPORT_MOUSE             (1)  // Support a mouse
#define GUI_WINSUPPORT                (1)  // Window manager package available
#define GUI_SUPPORT_MEMDEV            (1)  // Memory devices available
#define GUI_SUPPORT_DEVICES           (1)  // Enable use of device pointers
#define GUI_USE_ARGB                  (1)
#define GUI_MEMDEV_SUPPORT_CUSTOMDRAW (1)

/*********************************************************************
*
*       Configuration of window manager
*/
#define WM_SUPPORT_NOTIFY_VIS_CHANGED (1) // Enable sending of WM_NOTIFY_VIS_CHANGED messages

#endif  /* Avoid multiple inclusion */

/*************************** End of file ****************************/
