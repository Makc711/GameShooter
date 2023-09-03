#pragma once

// Include
#include <sys/_stdint.h>
#include <GUI.h>

typedef struct
{
  const GUI_BITMAP GUI_UNI_PTR* pBitmap;
  GUI_MEMDEV_Handle hMem;
  uint16_t width;
  uint16_t height;
} IMAGE;