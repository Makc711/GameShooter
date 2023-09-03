/* Includes ------------------------------------------------------------------*/
#include "LCDConf.h"
#include "GUI_Private.h"
#include "GUIDRV_Lin.h"
#include "ltdc.h"
#include "dma2d.h"

/* Private defines ----------------------------------------------------------*/
#define isDMA2D_Configurated 1
#define isLTDC_Configurated  1

/* Define the possible screen orientations  */
#define ROTATION_0   0
#define ROTATION_90  1
#define ROTATION_180 2
#define ROTATION_270 3

/* Define the possible color modes */
#define CMS_ARGB8888 1
#define CMS_RGB888   2
#define CMS_RGB565   3
#define CMS_ARGB1555 4
#define CMS_ARGB4444 5
#define CMS_L8       6
#define CMS_AL44     7
#define CMS_AL88     8

/* Define physical screen sizes */
#define XSIZE_PHYS 480
#define YSIZE_PHYS 272

/* Define the number of buffers to use (minimum 1) */
#define NUM_BUFFERS  2
/* Define the number of virtual buffers to use (minimum 1) */
#define NUM_VSCREENS 1

/* Redefine number of layers to be used, must be equal or less than in GUIConf.h */
#undef  GUI_NUM_LAYERS
#define GUI_NUM_LAYERS 1

/* Define Layer 0 color mode, orientation and sizes */
#define COLOR_MODE_0  CMS_RGB565
#define ORIENTATION_0 ROTATION_0
#define XSIZE_0       480
#define YSIZE_0       272

/* Define Layer 1 color mode, orientation and sizes */
#define COLOR_MODE_1  CMS_ARGB4444
#define ORIENTATION_1 ROTATION_0
#define XSIZE_1       480
#define YSIZE_1       272

/* Choose Layer 0 color conversion depending of the color mode choosed */
#if   (COLOR_MODE_0 == CMS_ARGB8888)
#define COLOR_CONVERSION_0 GUICC_M8888I
#elif (COLOR_MODE_0 == CMS_RGB888)
#define COLOR_CONVERSION_0 GUICC_M888
#elif (COLOR_MODE_0 == CMS_RGB565)
#define COLOR_CONVERSION_0 GUICC_M565
#elif (COLOR_MODE_0 == CMS_ARGB1555)
#define COLOR_CONVERSION_0 GUICC_M1555I
#elif (COLOR_MODE_0 == CMS_ARGB4444)
#define COLOR_CONVERSION_0 GUICC_M4444I
#elif (COLOR_MODE_0 == CMS_L8)
#define COLOR_CONVERSION_0 GUICC_8666
#elif (COLOR_MODE_0 == CMS_AL44)
#define COLOR_CONVERSION_0 GUICC_1616I
#elif (COLOR_MODE_0 == CMS_AL88)
#define COLOR_CONVERSION_0 GUICC_88666I
#else
#error Illegal color mode 0!
#endif

/* Choose Layer 0 gui driver depending of the color mode choosed */
#if   (COLOR_MODE_0 == CMS_ARGB8888)
#if   (ORIENTATION_0 == ROTATION_0)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_32
#elif (ORIENTATION_0 == ROTATION_90)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OSX_32
#elif (ORIENTATION_0 == ROTATION_180)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OXY_32
#elif (ORIENTATION_0 == ROTATION_270)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OSY_32
#endif
#elif (COLOR_MODE_0 == CMS_RGB888)
#if   (ORIENTATION_0 == ROTATION_0)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_24
#elif (ORIENTATION_0 == ROTATION_CW)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OSX_24
#elif (ORIENTATION_0 == ROTATION_180)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OXY_24
#elif (ORIENTATION_0 == ROTATION_CCW)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OSY_24
#endif
#elif (COLOR_MODE_0 == CMS_RGB565)   \
   || (COLOR_MODE_0 == CMS_ARGB1555) \
   || (COLOR_MODE_0 == CMS_ARGB4444) \
   || (COLOR_MODE_0 == CMS_AL88)
#if   (ORIENTATION_0 == ROTATION_0)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_16
#elif (ORIENTATION_0 == ROTATION_CW)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OSX_16
#elif (ORIENTATION_0 == ROTATION_180)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OXY_16
#elif (ORIENTATION_0 == ROTATION_CCW)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OSY_16
#endif
#elif (COLOR_MODE_0 == CMS_L8)   \
   || (COLOR_MODE_0 == CMS_AL44)
#if   (ORIENTATION_0 == ROTATION_0)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_8
#elif (ORIENTATION_0 == ROTATION_CW)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OSX_8
#elif (ORIENTATION_0 == ROTATION_180)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OXY_8
#elif (ORIENTATION_0 == ROTATION_CCW)
#define DISPLAY_DRIVER_0   GUIDRV_LIN_OSY_8
#endif
#endif

/* Choose Layer 1 color conversion depending of the color mode//orientation choosed */
#if (GUI_NUM_LAYERS > 1)
#if   (COLOR_MODE_1 == CMS_ARGB8888)
#define COLOR_CONVERSION_1 GUICC_M8888I
#elif (COLOR_MODE_1 == CMS_RGB888)
#define COLOR_CONVERSION_1 GUICC_M888
#elif (COLOR_MODE_1 == CMS_RGB565)
#define COLOR_CONVERSION_1 GUICC_M565
#elif (COLOR_MODE_1 == CMS_ARGB1555)
#define COLOR_CONVERSION_1 GUICC_M1555I
#elif (COLOR_MODE_1 == CMS_ARGB4444)
#define COLOR_CONVERSION_1 GUICC_M4444I
#elif (COLOR_MODE_1 == CMS_L8)
#define COLOR_CONVERSION_1 GUICC_8666
#elif (COLOR_MODE_1 == CMS_AL44)
#define COLOR_CONVERSION_1 GUICC_1616I
#elif (COLOR_MODE_1 == CMS_AL88)
#define COLOR_CONVERSION_1 GUICC_88666I
#else
#error Illegal color mode 0!
#endif

/* Choose Layer 1 gui driver depending of the color mode/orientation choosed */
#if   (COLOR_MODE_1 == CMS_ARGB8888)
#if   (ORIENTATION_1 == ROTATION_0)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_32
#elif (ORIENTATION_1 == ROTATION_CW)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OSX_32
#elif (ORIENTATION_1 == ROTATION_180)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OXY_32
#elif (ORIENTATION_1 == ROTATION_CCW)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OSY_32
#endif
#elif (COLOR_MODE_1 == CMS_RGB888)
#if   (ORIENTATION_1 == ROTATION_0)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_24
#elif (ORIENTATION_1 == ROTATION_CW)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OSX_24
#elif (ORIENTATION_1 == ROTATION_180)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OXY_24
#elif (ORIENTATION_1 == ROTATION_CCW)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OSY_24
#endif
#elif (COLOR_MODE_1 == CMS_RGB565)   \
   || (COLOR_MODE_1 == CMS_ARGB1555) \
   || (COLOR_MODE_1 == CMS_ARGB4444) \
   || (COLOR_MODE_1 == CMS_AL88)
#if   (ORIENTATION_1 == ROTATION_0)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_16
#elif (ORIENTATION_1 == ROTATION_90)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OSX_16
#elif (ORIENTATION_1 == ROTATION_180)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OXY_16
#elif (ORIENTATION_1 == ROTATION_270)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OSY_16
#endif
#elif (COLOR_MODE_1 == CMS_L8)   \
   || (COLOR_MODE_1 == CMS_AL44)
#if   (ORIENTATION_1 == ROTATION_0)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_8
#elif (ORIENTATION_1 == ROTATION_CW)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OSX_8
#elif (ORIENTATION_1 == ROTATION_180)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OXY_8
#elif (ORIENTATION_1 == ROTATION_CCW)
#define DISPLAY_DRIVER_1   GUIDRV_LIN_OSY_8
#endif
#endif

#else

/* Use complete display automatically in case of only one layer */
#undef XSIZE_0
#undef YSIZE_0
#define XSIZE_0 XSIZE_PHYS
#define YSIZE_0 YSIZE_PHYS
     
#endif

/* Check that the configuration used is OK */
#if NUM_BUFFERS > 3
#error More than 3 buffers make no sense and are not supported in this configuration file!
#endif
#ifndef   XSIZE_PHYS
#error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
#error Physical Y size of display is not defined!
#endif
#ifndef   NUM_BUFFERS
#define NUM_BUFFERS 1
#else
#if (NUM_BUFFERS <= 0)
#error At least one buffer needs to be defined!
#endif
#endif
#ifndef   NUM_VSCREENS
#define NUM_VSCREENS 1
#else
#if (NUM_VSCREENS <= 0)
#error At least one screeen needs to be defined!
#endif
#endif
#if (NUM_VSCREENS > 1) && (NUM_BUFFERS > 1)
#error Virtual screens together with multiple buffers are not allowed!
#endif
     
/* Define the offset of the frame to be used */
#define LCD_FRAME_BUFFER ((U32)0xC0000000)
     
/* Private macro -------------------------------------------------------------*/
/* Redirect bulk conversion to DMA2D routines */
#define DEFINE_DMA2D_COLORCONVERSION(PFIX, PIXELFORMAT)                                                        \
static void _Color2IndexBulk_##PFIX##_DMA2D(LCD_COLOR * pColor, void * pIndex, U32 NumItems, U8 SizeOfIndex) { \
  _DMA_Color2IndexBulk(pColor, pIndex, NumItems, SizeOfIndex, PIXELFORMAT);                                    \
}                                                                                                              \
static void _Index2ColorBulk_##PFIX##_DMA2D(void * pIndex, LCD_COLOR * pColor, U32 NumItems, U8 SizeOfIndex) { \
  _DMA_Index2ColorBulk(pIndex, pColor, NumItems, SizeOfIndex, PIXELFORMAT);                                    \
}

/* Private typedef -----------------------------------------------------------*/
typedef struct
{
  const int32_t address;          
  __IO int32_t  pendingBuffer;   
  int32_t       bufferIndex;     
  int32_t       xSize;            
  int32_t       ySize;            
  int32_t       bytesPerPixel;
  const LCD_API_COLOR_CONV   *pColorConvAPI;
  const int32_t orientation;
}LCD_LayerPropTypedef;
  
/* Variables -----------------------------------------------------------------*/
/* Array for speeding up nibble conversion for A4 bitmaps */
static const U8 aMirror_[] = {
  0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90, 0xA0, 0xB0, 0xC0, 0xD0, 0xE0, 0xF0,
  0x01, 0x11, 0x21, 0x31, 0x41, 0x51, 0x61, 0x71, 0x81, 0x91, 0xA1, 0xB1, 0xC1, 0xD1, 0xE1, 0xF1,
  0x02, 0x12, 0x22, 0x32, 0x42, 0x52, 0x62, 0x72, 0x82, 0x92, 0xA2, 0xB2, 0xC2, 0xD2, 0xE2, 0xF2,
  0x03, 0x13, 0x23, 0x33, 0x43, 0x53, 0x63, 0x73, 0x83, 0x93, 0xA3, 0xB3, 0xC3, 0xD3, 0xE3, 0xF3,
  0x04, 0x14, 0x24, 0x34, 0x44, 0x54, 0x64, 0x74, 0x84, 0x94, 0xA4, 0xB4, 0xC4, 0xD4, 0xE4, 0xF4,
  0x05, 0x15, 0x25, 0x35, 0x45, 0x55, 0x65, 0x75, 0x85, 0x95, 0xA5, 0xB5, 0xC5, 0xD5, 0xE5, 0xF5,
  0x06, 0x16, 0x26, 0x36, 0x46, 0x56, 0x66, 0x76, 0x86, 0x96, 0xA6, 0xB6, 0xC6, 0xD6, 0xE6, 0xF6,
  0x07, 0x17, 0x27, 0x37, 0x47, 0x57, 0x67, 0x77, 0x87, 0x97, 0xA7, 0xB7, 0xC7, 0xD7, 0xE7, 0xF7,
  0x08, 0x18, 0x28, 0x38, 0x48, 0x58, 0x68, 0x78, 0x88, 0x98, 0xA8, 0xB8, 0xC8, 0xD8, 0xE8, 0xF8,
  0x09, 0x19, 0x29, 0x39, 0x49, 0x59, 0x69, 0x79, 0x89, 0x99, 0xA9, 0xB9, 0xC9, 0xD9, 0xE9, 0xF9,
  0x0A, 0x1A, 0x2A, 0x3A, 0x4A, 0x5A, 0x6A, 0x7A, 0x8A, 0x9A, 0xAA, 0xBA, 0xCA, 0xDA, 0xEA, 0xFA,
  0x0B, 0x1B, 0x2B, 0x3B, 0x4B, 0x5B, 0x6B, 0x7B, 0x8B, 0x9B, 0xAB, 0xBB, 0xCB, 0xDB, 0xEB, 0xFB,
  0x0C, 0x1C, 0x2C, 0x3C, 0x4C, 0x5C, 0x6C, 0x7C, 0x8C, 0x9C, 0xAC, 0xBC, 0xCC, 0xDC, 0xEC, 0xFC,
  0x0D, 0x1D, 0x2D, 0x3D, 0x4D, 0x5D, 0x6D, 0x7D, 0x8D, 0x9D, 0xAD, 0xBD, 0xCD, 0xDD, 0xED, 0xFD,
  0x0E, 0x1E, 0x2E, 0x3E, 0x4E, 0x5E, 0x6E, 0x7E, 0x8E, 0x9E, 0xAE, 0xBE, 0xCE, 0xDE, 0xEE, 0xFE,
  0x0F, 0x1F, 0x2F, 0x3F, 0x4F, 0x5F, 0x6F, 0x7F, 0x8F, 0x9F, 0xAF, 0xBF, 0xCF, 0xDF, 0xEF, 0xFF,
};

static LCD_LayerPropTypedef layerProp_[GUI_NUM_LAYERS] =
{
  {
    .address = LCD_FRAME_BUFFER,
    .pendingBuffer = -1,
    .bufferIndex = 0,
    .xSize = XSIZE_PHYS,
    .ySize = YSIZE_PHYS,
    .bytesPerPixel = 0,
    .pColorConvAPI = COLOR_CONVERSION_0,
    .orientation = ORIENTATION_0
  },
#if GUI_NUM_LAYERS > 1
  {
    .address = LCD_FRAME_BUFFER + XSIZE_PHYS * YSIZE_PHYS * sizeof(U32) * NUM_VSCREENS * NUM_BUFFERS,
    .pendingBuffer = -1,
    .bufferIndex = 0,
    .xSize = XSIZE_PHYS,
    .ySize = YSIZE_PHYS,
    .bytesPerPixel = 0,
    .pColorConvAPI = COLOR_CONVERSION_1,
    .orientation = ORIENTATION_1
  }
  #endif
};

static U32 aBuffer_[XSIZE_PHYS * sizeof(U32) * 3];
static U32 *pBufferDma2D_ = &aBuffer_[XSIZE_PHYS * sizeof(U32) * 0];
static volatile char transferInProgress_  = 0;

/* Private function prototypes -----------------------------------------------*/
static void _DMA_Index2ColorBulk(void *pIndex, LCD_COLOR *pColor, U32 numItems, U8 sizeOfIndex, U32 pixelFormat);
static void _DMA_Color2IndexBulk(LCD_COLOR *pColor, void *pIndex, U32 numItems, U8 sizeOfIndex, U32 pixelFormat);

/* Color conversion routines using DMA2D */
DEFINE_DMA2D_COLORCONVERSION(M8888I, LTDC_PIXEL_FORMAT_ARGB8888)
/* Internal pixel format of emWin is 32 bit, because of that ARGB8888 */
DEFINE_DMA2D_COLORCONVERSION(M888, LTDC_PIXEL_FORMAT_ARGB8888) 
DEFINE_DMA2D_COLORCONVERSION(M565, LTDC_PIXEL_FORMAT_RGB565)
DEFINE_DMA2D_COLORCONVERSION(M1555I, LTDC_PIXEL_FORMAT_ARGB1555)
DEFINE_DMA2D_COLORCONVERSION(M4444I, LTDC_PIXEL_FORMAT_ARGB4444)

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  Get the used pixel format
  * @param  layerIndex - Layer index used 
  * @retval LTDC pixel format
  */
static U32 _GetPixelformat(const int layerIndex) 
{
  if (layerIndex >= GUI_NUM_LAYERS) 
  {
    return 0;
  }
  const LCD_API_COLOR_CONV* pColorConvAPI = layerProp_[layerIndex].pColorConvAPI;
  if (pColorConvAPI == GUICC_M8888I) 
  {
    return LTDC_PIXEL_FORMAT_ARGB8888;
  }
  if (pColorConvAPI == GUICC_M888) 
  {
    return LTDC_PIXEL_FORMAT_RGB888;
  }
  if (pColorConvAPI == GUICC_M565) 
  {
    return LTDC_PIXEL_FORMAT_RGB565;
  }
  if (pColorConvAPI == GUICC_M1555I)
  {
    return LTDC_PIXEL_FORMAT_ARGB1555;
  }
  if (pColorConvAPI == GUICC_M4444I) 
  {
    return LTDC_PIXEL_FORMAT_ARGB4444;
  }
  if (pColorConvAPI == GUICC_8666) 
  {
    return LTDC_PIXEL_FORMAT_L8;
  }
  if (pColorConvAPI == GUICC_1616I) 
  {
    return LTDC_PIXEL_FORMAT_AL44;
  }
  if (pColorConvAPI == GUICC_88666I) 
  {
    return LTDC_PIXEL_FORMAT_AL88;
  }
  /* We'll hang in case of bad configuration */
  while (1){}
}

#if (!isDMA2D_Configurated)
/**
  * @brief  Enable/Disable the DMA2D interrupt
  * @param  DMA2D_IT - DM2D interrupt to enable
  * @param  newState - ENABLE/DISABLE
  * @retval LTDC pixel format
  */
static void _DMA2D_ITConfig(const U32 DMA2D_IT, const int newState)
{
  if (newState != DISABLE) 
  {    
    DMA2D->CR |= DMA2D_IT;    
  }
  else 
  {    
    DMA2D->CR &= ~DMA2D_IT;    
  }
}

/**
  * @brief  DM2D Msp initialisation
  * @param  hdma2d - DM2D handle
  * @retval None
  */
void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef *hdma2d)
{  
  /* Enable dma2d clock */
  __HAL_RCC_DMA2D_CLK_ENABLE();   
}

/**
  * @brief  DM2D Msp de-initialisation
  * @param  hdma2d - DM2D handle
  * @retval None
  */
void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef *hdma2d)
{
  /* Enable DMA2D reset state */
  __HAL_RCC_DMA2D_FORCE_RESET();
  
  /* Release DMA2D from reset state */ 
  __HAL_RCC_DMA2D_RELEASE_RESET();
}
#endif // isDMA2D_Configurated

#if (!isLTDC_Configurated)
/**
  * @brief  LTDC Msp initialisation
  * @param  hltdc - LTDC handle
  * @retval None
  */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef *hltdc)
{
  GPIO_InitTypeDef gpio_init_structure;
  static RCC_PeriphCLKInitTypeDef periphClkInitStruct;
  
  /* Enable the LTDC clocks */
  __HAL_RCC_LTDC_CLK_ENABLE();  
  
  /* LCD clock configuration */
  /* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
  /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 192 Mhz */
  /* PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 192/5 = 38.4 Mhz */
  /* LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_4 = 38.4/4 = 9.6Mhz */
  periphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  periphClkInitStruct.PLLSAI.PLLSAIN = 192;
  periphClkInitStruct.PLLSAI.PLLSAIR = 5;
  periphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_4;
  HAL_RCCEx_PeriphCLKConfig(&periphClkInitStruct);  
  
  /* Enable GPIOs clock */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOJ_CLK_ENABLE();
  __HAL_RCC_GPIOK_CLK_ENABLE();
  
  /*** LTDC Pins configuration ***/
  /* GPIOE configuration */
  gpio_init_structure.Pin       = GPIO_PIN_4;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_NOPULL;
  gpio_init_structure.Speed     = GPIO_SPEED_FAST;
  gpio_init_structure.Alternate = GPIO_AF14_LTDC;  
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);

  /* GPIOG configuration */
  gpio_init_structure.Pin       = GPIO_PIN_12;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Alternate = GPIO_AF9_LTDC;
  HAL_GPIO_Init(GPIOG, &gpio_init_structure);

  /* GPIOI LTDC alternate configuration */
  gpio_init_structure.Pin       = GPIO_PIN_9 | GPIO_PIN_10 | \
                                  GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOI, &gpio_init_structure);

  /* GPIOJ configuration */  
  gpio_init_structure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
                                  GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | \
                                  GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | \
                                  GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOJ, &gpio_init_structure);  

  /* GPIOK configuration */  
  gpio_init_structure.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | \
                                  GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Alternate = GPIO_AF14_LTDC;
  HAL_GPIO_Init(GPIOK, &gpio_init_structure);
  
  /* LCD_DISP GPIO configuration */
  gpio_init_structure.Pin       = GPIO_PIN_12; /* LCD_DISP pin has to be manually controlled */
  gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(GPIOI, &gpio_init_structure);

  /* LCD_BL_CTRL GPIO configuration */
  gpio_init_structure.Pin       = GPIO_PIN_3; /* LCD_BL_CTRL pin has to be manually controlled */
  gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
  HAL_GPIO_Init(GPIOK, &gpio_init_structure);

  /* Set LTDC Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(LTDC_IRQn, 0xE, 0);  
  /* Enable LTDC Interrupt */
  HAL_NVIC_EnableIRQ(LTDC_IRQn);
  
  /* Set DMA2D Interrupt to the lowest priority */
  HAL_NVIC_SetPriority(DMA2D_IRQn, 0xE, 0x0);
  /* Enable DMA2D Interrupt */
  HAL_NVIC_EnableIRQ(DMA2D_IRQn);
  /* Enable DMA2D transfer complete Interrupt */
  _DMA2D_ITConfig(DMA2D_CR_TCIE, ENABLE);
}

/**
  * @brief  LTDC Msp de-initialisation
  * @param  hltdc - LTDC handle
  * @retval None
  */
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef *hltdc)
{
  /* Enable LTDC reset state */
  __HAL_RCC_LTDC_FORCE_RESET();
  
  /* Release LTDC from reset state */ 
  __HAL_RCC_LTDC_RELEASE_RESET();
}
#endif // isLTDC_Configurated

/**
  * @brief  Initialise the LCD Controller
  * @param  layerIndex - layer Index.
  */
static void LCD_LL_LayerInit(const int layerIndex) 
{  
  LTDC_LayerCfgTypeDef layerCfg;

  if (layerIndex < GUI_NUM_LAYERS)
  {
    /* Layer configuration */
    layerCfg.WindowX0 = 0;
    layerCfg.WindowX1 = XSIZE_PHYS;
    layerCfg.WindowY0 = 0;
    layerCfg.WindowY1 = YSIZE_PHYS;
    layerCfg.PixelFormat = _GetPixelformat(layerIndex);
    layerCfg.FBStartAdress = layerProp_[layerIndex].address;
    layerCfg.Alpha = 255;
    layerCfg.Alpha0 = 0;
    layerCfg.Backcolor.Blue = 0;
    layerCfg.Backcolor.Green = 0;
    layerCfg.Backcolor.Red = 0;
    layerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    layerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    layerCfg.ImageWidth = XSIZE_PHYS;
    layerCfg.ImageHeight = YSIZE_PHYS;
    HAL_LTDC_ConfigLayer(&hltdc, &layerCfg, layerIndex);

    /* Enable LUT on demand */
    if (LCD_GetBitsPerPixelEx((int)layerIndex) <= 8)
    {
      /* Enable usage of LUT for all modes with <= 8bpp*/
      HAL_LTDC_EnableCLUT(&hltdc, layerIndex);
    }
    else
    {
      /* Optional CLUT initialization for AL88 mode (16bpp)*/
      if (layerProp_[layerIndex].pColorConvAPI == GUICC_88666I)
      {
        static uint32_t LUT[256];
        HAL_LTDC_EnableCLUT(&hltdc, layerIndex);

        for (uint32_t i = 0; i < GUI_COUNTOF(LUT); i++)
        {
          LUT[i] = LCD_API_ColorConv_8666.pfIndex2Color(i);
        }
        HAL_LTDC_ConfigCLUT(&hltdc, LUT, GUI_COUNTOF(LUT), layerIndex);
      }
    }
  }  
}
  
/**
  * @brief  LCD Low layer initialisation
  */
static void LCD_LL_Init(void) 
{
  /* LTDC DeInit */
  if (HAL_LTDC_DeInit(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Set LCD Timings */
  hltdc.Init.HorizontalSync = 40;
  hltdc.Init.VerticalSync = 9;
  hltdc.Init.AccumulatedHBP = 53;
  hltdc.Init.AccumulatedVBP = 11;
  hltdc.Init.AccumulatedActiveH = 283;
  hltdc.Init.AccumulatedActiveW = 533;
  hltdc.Init.TotalHeigh = 285;
  hltdc.Init.TotalWidth = 565;
  
  /* background value */
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;  
  
  /* Polarity */
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL; 
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;  
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Instance = LTDC;
  
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_LTDC_ProgramLineEvent(&hltdc, 0);
  
  /* Enable dithering */
  HAL_LTDC_EnableDither(&hltdc);

#if (!isDMA2D_Configurated)
  /* DMA2D DeInit */
  if (HAL_DMA2D_DeInit(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
    
  /* Configure the DMA2D default mode */ 
  hdma2d.Init.Mode         = DMA2D_R2M;
  hdma2d.Init.ColorMode    = DMA2D_RGB565;
  hdma2d.Init.OutputOffset = 0x0;
  hdma2d.Instance          = DMA2D;

  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
#endif // isDMA2D_Configurated

  /* Assert display enable LCD_DISP pin */
  HAL_GPIO_WritePin(LCD_DISP_GPIO_Port, LCD_DISP_Pin, GPIO_PIN_SET);

  /* Assert backlight LCD_BL_CTRL pin */
  HAL_GPIO_WritePin(LCD_BL_CTRL_GPIO_Port, LCD_BL_CTRL_Pin, GPIO_PIN_SET);
}

/**
  * @brief  DMA2D interrupt handler
  */
void DMA2D_InterruptHandler(void) 
{
  /* Clear the Transfer complete interrupt */
  DMA2D->IFCR = (U32)DMA2D_IFSR_CTCIF;
  DMA2D->IFCR = (U32)DMA2D_IFCR_CCTCIF;
  /* Release the DMA2D for the next transfer */
  transferInProgress_ = 0;
}

/**
  * @brief  DMA2D wait for interrupt
  */
static void _DMA2D_ExecOperation(void) 
{  
  /* If no concurent operation, do not wait */
  if (transferInProgress_ == 0)
  {
    return;
  }
  
  /* Wait until the transfer is done */
  while (transferInProgress_) {}
}

/**
  * @brief  DMA2D Copy buffers
  * @param  layerIndex - Layer index
  * @param  pSrc       - Source buffer pointer
  * @param  pDst       - Destination buffer pointer
  * @param  xSize      - Horizontal size
  * @param  ySize      - Vertical size
  * @param  offLineSrc - Source Line offset
  * @param  offLineDst - Destination Line offset
  */
static void _DMA_Copy(const int layerIndex, void *pSrc, void *pDst, 
  const int xSize, const int ySize, const int offLineSrc, const int offLineDst) 
{
  /* Wait if there is a transfer in progress */
  _DMA2D_ExecOperation();  
  
  /* Take the TransferInProgress flag */
  transferInProgress_ = 1;
  
  /* Get the layer pixel format used */
  const U32 pixelFormat = _GetPixelformat(layerIndex);
  
  /* Setup DMA2D Configuration */  
  DMA2D->CR      = 0x00000000UL | (1 << 9);
  DMA2D->FGMAR   = (U32)pSrc;
  DMA2D->OMAR    = (U32)pDst;
  DMA2D->FGOR    = offLineSrc;
  DMA2D->OOR     = offLineDst;
  DMA2D->FGPFCCR = pixelFormat;
  DMA2D->NLR     = (U32)(xSize << 16) | (U16)ySize;
  
  /* Start the transfer, and enable the transfer complete IT */  
  DMA2D->CR     |= (1 | DMA2D_IT_TC);
  
  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation();
}

/**
  * @brief  DMA2D Copy RGB 565 buffer
  * @param  pSrc       - Source buffer pointer
  * @param  pDst       - Destination buffer pointer
  * @param  xSize      - Horizontal size
  * @param  ySize      - Vertical size
  * @param  offLineSrc - Source Line offset
  * @param  offLineDst - Destination Line offset
  */
static void _DMA_CopyRGB565(const void *pSrc, void *pDst, 
  const int xSize, const int ySize, const int offLineSrc, const int offLineDst)
{
  /* Wait if there is a transfer in progress */
  _DMA2D_ExecOperation();
  
  /* Take the TransferInProgress flag */ 
  transferInProgress_ = 1;

  /* Setup DMA2D Configuration */  
  DMA2D->CR      = 0x00000000UL | (1 << 9);
  DMA2D->FGMAR   = (U32)pSrc;
  DMA2D->OMAR    = (U32)pDst;
  DMA2D->FGOR    = offLineSrc;
  DMA2D->OOR     = offLineDst;
  DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_RGB565;
  DMA2D->NLR     = (U32)(xSize << 16) | (U16)ySize;
  
  /* Start the transfer, and enable the transfer complete IT */
  DMA2D->CR     |= (1 | DMA2D_IT_TC);
  
  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation(); 
}

/**
  * @brief  DMA2D Fill buffer
  * @param  layerIndex - Layer index
  * @param  pDst       - Destination buffer pointer
  * @param  xSize      - Horizontal size
  * @param  ySize      - Vertical size
  * @param  offLine    - Line offset
  * @param  colorIndex - Color to be used for the Fill operation
  */
static void _DMA_Fill(const int layerIndex, void *pDst, 
  const int xSize, const int ySize, const int offLine, const U32 colorIndex) 
{
  /* Wait if there is a transfer in progress */
  _DMA2D_ExecOperation();
  
  /* Take the TransferInProgress flag */
  transferInProgress_ = 1;

  /* Get the layer pixel format used */
  const U32 pixelFormat = _GetPixelformat(layerIndex);

  /* Setup DMA2D Configuration */  
  DMA2D->CR      = 0x00030000UL | (1 << 9);
  DMA2D->OCOLR   = colorIndex;
  DMA2D->OMAR    = (U32)pDst;
  DMA2D->OOR     = offLine;
  DMA2D->OPFCCR  = pixelFormat;
  DMA2D->NLR     = (U32)(xSize << 16) | (U16)ySize;
  
  /* Start the transfer, and enable the transfer complete IT */
  DMA2D->CR     |= (1 | DMA2D_IT_TC);
  
  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation(); 
}

/**
  * @brief  DMA2D Alpha blending bulk
  * @param  pColorFG  - Foregroung color
  * @param  pColorBG  - Backgroung color
  * @param  pColorDst - Destination color
  * @param  numItems  - Number of lines
  */
static void _DMA_AlphaBlendingBulk(LCD_COLOR *pColorFG, LCD_COLOR *pColorBG, LCD_COLOR *pColorDst, const U32 numItems) 
{  
  /* Wait if there is a transfer in progress */
  _DMA2D_ExecOperation();
  
  /* Take the TransferInProgress flag */
  transferInProgress_ = 1;
  
  /* Setup DMA2D Configuration */  
  DMA2D->CR      = 0x00020000UL | (1 << 9);
  DMA2D->FGMAR   = (U32)pColorFG;
  DMA2D->BGMAR   = (U32)pColorBG;
  DMA2D->OMAR    = (U32)pColorDst;
  DMA2D->FGOR    = 0;
  DMA2D->BGOR    = 0;
  DMA2D->OOR     = 0;
  DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888;
  DMA2D->BGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888;
  DMA2D->OPFCCR  = LTDC_PIXEL_FORMAT_ARGB8888;
  DMA2D->NLR     = (U32)(numItems << 16) | 1;
  
  /* Start the transfer, and enable the transfer complete IT */
  DMA2D->CR     |= (1 | DMA2D_IT_TC);
  
  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation(); 
}

/**
  * @brief  Mixing bulk colors
  * @param  pColorFG  - Foregroung color
  * @param  pColorBG  - Backgroung color
  * @param  pColorDst - Destination color
  * @param  intens    - Color intensity
  * @param  numItems  - Number of lines
  */
static void _DMA_MixColorsBulk(LCD_COLOR *pColorFG, LCD_COLOR *pColorBG, LCD_COLOR *pColorDst, const U8 intens, const U32 numItems) 
{
  /* Wait if there is a transfer in progress */
  _DMA2D_ExecOperation();
  
  /* Take the TransferInProgress flag */
  transferInProgress_ = 1;

  /* Setup DMA2D Configuration */
  DMA2D->CR      = 0x00020000UL | (1 << 9);
  DMA2D->FGMAR   = (U32)pColorFG;
  DMA2D->BGMAR   = (U32)pColorBG;
  DMA2D->OMAR    = (U32)pColorDst;
  DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888
                 | (1UL << 16)
                 | ((U32)intens << 24);
  DMA2D->BGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888
                 | (0UL << 16)
                 | ((U32)(255 - intens) << 24);
  DMA2D->OPFCCR  = LTDC_PIXEL_FORMAT_ARGB8888;
  DMA2D->NLR     = (U32)(numItems << 16) | 1;
  
  /* Start the transfer, and enable the transfer complete IT */
  DMA2D->CR     |= (1 | DMA2D_IT_TC);

  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation();
}

/**
  * @brief  Color conversion
  * @param  pSrc           - Source buffer
  * @param  pDst           - Destination buffer
  * @param  pixelFormatSrc - Source pixel format
  * @param  pixelFormatDst - Destination pixel format
  * @param  numItems       - Number of lines
  */
static void _DMA_ConvertColor(void *pSrc, void *pDst, 
  const U32 pixelFormatSrc, const U32 pixelFormatDst, const U32 numItems) 
{
  /* Wait if there is a transfer in progress */
  _DMA2D_ExecOperation();
  
  /* Take the TransferInProgress flag */
  transferInProgress_ = 1;

  /* Setup DMA2D Configuration */
  DMA2D->CR      = 0x00010000UL | (1 << 9);
  DMA2D->FGMAR   = (U32)pSrc;
  DMA2D->OMAR    = (U32)pDst;
  DMA2D->FGOR    = 0;
  DMA2D->OOR     = 0;
  DMA2D->FGPFCCR = pixelFormatSrc;
  DMA2D->OPFCCR  = pixelFormatDst;
  DMA2D->NLR     = (U32)(numItems << 16) | 1;
  
  /* Start the transfer, and enable the transfer complete IT */
  DMA2D->CR     |= (1 | DMA2D_IT_TC);
  
  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation();  
}

/**
  * @brief  Draw L8 picture
  * @param  pSrc           - Source buffer
  * @param  pDst           - Destination buffer
  * @param  offSrc         - Source Offset
  * @param  offDst         - Destination Offset
  * @param  pixelFormatDst - Destination pixel format
  * @param  xSize          - Picture horizontal size
  * @param  ySize          - Picture vertical size
  */
static void _DMA_DrawBitmapL8(void *pSrc, void *pDst, const U32 offSrc, const U32 offDst, 
  const U32 pixelFormatDst, const U32 xSize, const U32 ySize) 
{
  /* Wait if there is a transfer in progress */
  _DMA2D_ExecOperation();
  
  /* Take the TransferInProgress flag */
  transferInProgress_ = 1;

  /* Setup DMA2D Configuration */
  DMA2D->CR      = 0x00010000UL | (1 << 9);
  DMA2D->FGMAR   = (U32)pSrc;
  DMA2D->OMAR    = (U32)pDst;
  DMA2D->FGOR    = offSrc;
  DMA2D->OOR     = offDst;
  DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_L8;
  DMA2D->OPFCCR  = pixelFormatDst;
  DMA2D->NLR     = (U32)(xSize << 16) | ySize;
  
  /* Start the transfer, and enable the transfer complete IT */
  DMA2D->CR     |= (1 | DMA2D_IT_TC);
  
  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation(); 
}

/**
  * @brief  Draw A4 picture
  * @param  pSrc           - Source buffer
  * @param  pDst           - Destination buffer
  * @param  offSrc         - Source Offset
  * @param  offDst         - Destination Offset
  * @param  pixelFormatDst - Destination pixel format
  * @param  xSize          - Picture horizontal size
  * @param  ySize          - Picture vertical size
  * @retval 1 - numBytes incorrect, 0 - OK
  */
static int _DMA_DrawBitmapA4(void *pSrc, void *pDst, const U32 offSrc, const U32 offDst, 
  const U32 pixelFormatDst, const U32 xSize, const U32 ySize) 
{
  /* Check size of conversion buffer */
  U32 numBytes = ((xSize + 1) & ~1) * ySize;
  if ((numBytes > sizeof(aBuffer_)) || (numBytes == 0)) 
  {
    return 1;
  }
  
  /* Wait if there is a transfer in progress */ 
  _DMA2D_ExecOperation();
  
  /* Take the TransferInProgress flag */
  transferInProgress_ = 1;

  /* Conversion (swapping nibbles) */
  U8* pWR = (U8*)aBuffer_;
  U8* pRD = (U8*)pSrc;
  do 
  {
    *pWR++ = aMirror_[*pRD++];
  } while (--numBytes);
  
  /* Get current drawing color (ARGB) */
  const int index = LCD_GetColorIndex();
  const U32 color = LCD_Index2Color(index);

  /* Setup DMA2D Configuration */
  DMA2D->CR = 0x00020000UL;
  DMA2D->FGCOLR  = color;
  DMA2D->FGMAR   = (U32)aBuffer_;
  DMA2D->FGOR    = 0;
  DMA2D->FGPFCCR = 0xA;
  DMA2D->NLR     = (U32)((xSize + offSrc) << 16) | ySize;
  DMA2D->BGMAR   = (U32)pDst;
  DMA2D->BGOR    = offDst - offSrc;
  DMA2D->BGPFCCR = pixelFormatDst;
  DMA2D->OMAR    = DMA2D->BGMAR;
  DMA2D->OOR     = DMA2D->BGOR;
  DMA2D->OPFCCR  = DMA2D->BGPFCCR;
  
  /* Start the transfer, and enable the transfer complete IT */
  DMA2D->CR     |= (1 | DMA2D_IT_TC);
  
  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation(); 
  
  return 0;
}

/**
  * @brief  Draw alpha bitmap
  * @param  pDst        - Destination buffer
  * @param  pSrc        - Source buffer
  * @param  xSize       - Picture horizontal size
  * @param  ySize       - Picture vertical size
  * @param  offLineSrc  - Source line offset
  * @param  offLineDst  - Destination line offset
  * @param  pixelFormat - Pixel format
  */
static void _DMA_DrawAlphaBitmap(void *pDst, const void *pSrc, const int xSize, const int ySize, 
  const int offLineSrc, const int offLineDst, const int pixelFormat) 
{
  /* Wait if there is a transfer in progress */ 
  _DMA2D_ExecOperation();
  
  /* Take the TransferInProgress flag */
  transferInProgress_ = 1;
  
  /* Setup DMA2D Configuration */ 
  DMA2D->CR      = 0x00020000UL | (1 << 9);
  DMA2D->FGMAR   = (U32)pSrc;
  DMA2D->BGMAR   = (U32)pDst;
  DMA2D->OMAR    = (U32)pDst;
  DMA2D->FGOR    = offLineSrc;
  DMA2D->BGOR    = offLineDst;
  DMA2D->OOR     = offLineDst;
  DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888;
  DMA2D->BGPFCCR = pixelFormat;
  DMA2D->OPFCCR  = pixelFormat;
  DMA2D->NLR     = (U32)(xSize << 16) | (U16)ySize;

  /* Start the transfer, and enable the transfer complete IT */
  DMA2D->CR     |= (1 | DMA2D_IT_TC);
  
  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation();
}

/**
  * @brief  Load LUT
  * @param  pColor   - CLUT address
  * @param  numItems - Number of items to load
  */
static void _DMA_LoadLUT(LCD_COLOR *pColor, const U32 numItems)
{
  /* Wait if there is a transfer in progress */ 
  _DMA2D_ExecOperation();
  
  /* Take the TransferInProgress flag */
  transferInProgress_ = 1;
  /* Setup DMA2D Configuration */
  DMA2D->FGCMAR  = (U32)pColor;
  DMA2D->FGPFCCR  = LTDC_PIXEL_FORMAT_ARGB8888
                  | ((numItems - 1) & 0xFF) << 8;
  
  DMA2D->CR     |= DMA2D_IT_CTC;
    
  /* Start loading */
  DMA2D->FGPFCCR |= (1 << 5);
  
  /* Wait for the end of the transfer */
  _DMA2D_ExecOperation();
}

/**
  * @brief  DMA2D Alpha blending
  * @param  pColorFG  - Foreground color
  * @param  pColorBG  - Background color
  * @param  pColorDst - Destination color
  * @param  numItems  - Number of items
  */
static void _DMA_AlphaBlending(LCD_COLOR *pColorFG, LCD_COLOR *pColorBG, LCD_COLOR *pColorDst, const U32 numItems) 
{
  _DMA_AlphaBlendingBulk(pColorFG, pColorBG, pColorDst, numItems);
}

/**
  * @brief  Converts the given index values to 32 bit colors.
  * @param  pIndex      - Index value
  * @param  pColor      - Color relative to the index
  * @param  numItems    - Number of items
  * @param  sizeOfIndex - Size of index color
  * @param  pixelFormat - Pixel format
  */
static void _DMA_Index2ColorBulk(void *pIndex, LCD_COLOR *pColor, 
  const U32 numItems, const U8 sizeOfIndex, const U32 pixelFormat) 
{
  _DMA_ConvertColor(pIndex, pColor, pixelFormat, LTDC_PIXEL_FORMAT_ARGB8888, numItems);
}

/**
  * @brief  Converts a 32 bit colors to an index value.
  * @param  pColor      - Color relative to the index
  * @param  pIndex      - Index value
  * @param  numItems    - Number of items
  * @param  sizeOfIndex - Size of index color
  * @param  pixelFormat - Pixel format
  */
static void _DMA_Color2IndexBulk(LCD_COLOR *pColor, void *pIndex, 
  const U32 numItems, const U8 sizeOfIndex, const U32 pixelFormat)
{
  _DMA_ConvertColor(pColor, pIndex, LTDC_PIXEL_FORMAT_ARGB8888, pixelFormat, numItems);
}

/**
  * @brief  LCD Mix color bulk.
  * @param  pFG     - Foreground buffer
  * @param  pBG     - Background buffer
  * @param  pDst    - Destination buffer
  * @param  offFg   - Foreground offset
  * @param  offBg   - Background offset
  * @param  offDest - Destination offset
  * @param  xSize   - Horizontal size
  * @param  ySize   - Vertical size
  * @param  intens  - Color Intensity
  */
static void _LCD_MixColorsBulk(U32 *pFG, U32 *pBG, U32 *pDst, const unsigned offFg, 
  const unsigned offBg, const unsigned offDest, const unsigned xSize, const unsigned ySize, const U8 intens) 
{
  GUI_USE_PARA(offFg);
  GUI_USE_PARA(offDest);
   
  /* Do the same operation for all the lines */
  for (unsigned y = 0; y < ySize; y++) 
  {
    /* Use DMA2D for mixing up */
    _DMA_MixColorsBulk(pFG, pBG, pDst, intens, xSize);
    pFG  += xSize + offFg;
    pBG  += xSize + offBg;
    pDst += xSize + offDest;
  }
}

/**
  * @brief  Get buffer size.
  * @param  layerIndex - Layer index
  * @retval U32        - Buffer size 
  */
static U32 _GetBufferSize(const int layerIndex) 
{
  const U32 bufferSize = layerProp_[layerIndex].xSize * layerProp_[layerIndex].ySize * layerProp_[layerIndex].bytesPerPixel;
  return bufferSize;
}

/**
  * @brief  LCD Copy buffer
  * @param  layerIndex - Layer index
  * @param  indexSrc   - Source index
  * @param  indexDst   - Destination index
  */
static void _LCD_CopyBuffer(const int layerIndex, const int indexSrc, const int indexDst) 
{
  const U32 bufferSize = _GetBufferSize(layerIndex);
  const U32 addrSrc = layerProp_[layerIndex].address + bufferSize * indexSrc;
  const U32 addrDst = layerProp_[layerIndex].address + bufferSize * indexDst;
  _DMA_Copy(layerIndex, (void *)addrSrc, (void *)addrDst, layerProp_[layerIndex].xSize, layerProp_[layerIndex].ySize, 0, 0);
  /* After this function has been called all drawing operations are routed to Buffer[IndexDst] */
  layerProp_[layerIndex].bufferIndex = indexDst;
}

/**
  * @brief  LCD Copy rectangle
  * @param  layerIndex - Layer index
  * @param  x0         - Horizontal rect origin
  * @param  y0         - Vertical rect origin
  * @param  x1         - Horizontal rect end
  * @param  y1         - Vertical rect end
  * @param  xSize      - Rectangle width
  * @param  ySize      - Rectangle height
  */
static void _LCD_CopyRect(const int layerIndex, const int x0, const int y0, 
  const int x1, const int y1, const int xSize, const int ySize)
{
  const U32 bufferSize = _GetBufferSize(layerIndex);
  const U32 addrSrc = layerProp_[layerIndex].address + bufferSize * layerProp_[layerIndex].bufferIndex + 
    (y0 * layerProp_[layerIndex].xSize + x0) * layerProp_[layerIndex].bytesPerPixel;
  const U32 addrDst = layerProp_[layerIndex].address + bufferSize * layerProp_[layerIndex].bufferIndex + 
    (y1 * layerProp_[layerIndex].xSize + x1) * layerProp_[layerIndex].bytesPerPixel;
  const int offLine = layerProp_[layerIndex].xSize - xSize;
  _DMA_Copy(layerIndex, (void *)addrSrc, (void *)addrDst, xSize, ySize, offLine, offLine);
}

/**
  * @brief  LCD fill rectangle
  * @param  layerIndex - Layer index
  * @param  x0         - Horizontal rect origin
  * @param  y0         - Vertical rect origin
  * @param  x1         - Horizontal rect end
  * @param  y1         - Vertical rect end
  * @param  pixelIndex - Color to be used for the Fill operation
  */
static void _LCD_FillRect(const int layerIndex, const int x0, const int y0, 
  const int x1, const int y1, const U32 pixelIndex) 
{
  /* Depending on the draw mode, do it differently */
  if (GUI_GetDrawMode() == GUI_DM_XOR) 
  {
    /* Use SW Fill rectangle */
    LCD_SetDevFunc(layerIndex, LCD_DEVFUNC_FILLRECT, NULL);
    LCD_FillRect(x0, y0, x1, y1);
    /* Then set custom callback function for fillrect operation */
    LCD_SetDevFunc(layerIndex, LCD_DEVFUNC_FILLRECT, (void(*)(void))_LCD_FillRect);
  }
  else
  {
    const int xSize = x1 - x0 + 1;
    const int ySize = y1 - y0 + 1;
    const U32 bufferSize = _GetBufferSize(layerIndex);
    const U32 addrDst = layerProp_[layerIndex].address + bufferSize * layerProp_[layerIndex].bufferIndex + 
      (y0 * layerProp_[layerIndex].xSize + x0) * layerProp_[layerIndex].bytesPerPixel;
    _DMA_Fill(layerIndex, (void *)addrDst, xSize, ySize, layerProp_[layerIndex].xSize - xSize, pixelIndex);
  }
}

/**
  * @brief  Draw 16/32 bits per pixel bitmap
  * @param  layerIndex   - Layer index
  * @param  x            - start horizontal position on the screen
  * @param  y            - start vertical position on the screen
  * @param  p            - Source buffer
  * @param  xSize        - Horizontal bitmap size
  * @param  ySize        - Vertical bitmap size
  * @param  bytesPerLine - Number of bytes per Line
  * @param  bpp          - Number of bytes per pixel
  */
static void _LCD_DrawBitmap16_32bpp(const int layerIndex, const int x, const int y, 
  U16 const *p, const int xSize, const int ySize, const int bytesPerLine, const int bpp) 
{
  const U32 bufferSize = _GetBufferSize(layerIndex);
  const U32 addrDst = layerProp_[layerIndex].address + bufferSize * layerProp_[layerIndex].bufferIndex + 
    (y * layerProp_[layerIndex].xSize + x) * layerProp_[layerIndex].bytesPerPixel;
  const int offLineSrc = (bytesPerLine / bpp) - xSize;
  const int offLineDst = layerProp_[layerIndex].xSize - xSize;
  _DMA_Copy(layerIndex, (void *)p, (void *)addrDst, xSize, ySize, offLineSrc, offLineDst);
}

/**
  * @brief  Draw 32 bits per pixel bitmap
  * @param  layerIndex   - Layer index
  * @param  x            - start horizontal position on the screen
  * @param  y            - start vertical position on the screen
  * @param  p            - Source buffer
  * @param  xSize        - Horizontal bitmap size
  * @param  ySize        - Vertical bitmap size
  * @param  bytesPerLine - Number of bytes per Line
  */
static void _LCD_DrawBitmap32bpp(const int layerIndex, const int x, const int y, 
  U16 const *p, const int xSize, const int ySize, const int bytesPerLine) 
{
  _LCD_DrawBitmap16_32bpp(layerIndex, x, y, p, xSize, ySize, bytesPerLine, sizeof(U32));
}

/**
  * @brief  Draw 16 bits per pixel bitmap
  * @param  layerIndex   - Layer index
  * @param  x            - start horizontal position on the screen
  * @param  y            - start vertical position on the screen
  * @param  p            - Source buffer
  * @param  xSize        - Horizontal bitmap size
  * @param  ySize        - Vertical bitmap size
  * @param  bytesPerLine - Number of bytes per Line
  */
static void _LCD_DrawBitmap16bpp(const int layerIndex, const int x, const int y, 
  U16 const *p, const int xSize, const int ySize, const int bytesPerLine) 
{
  _LCD_DrawBitmap16_32bpp(layerIndex, x, y, p, xSize, ySize, bytesPerLine, sizeof(U16));
}

/**
  * @brief  Draw 8 bits per pixel bitmap
  * @param  layerIndex   - Layer index
  * @param  x            - start horizontal position on the screen
  * @param  y            - start vertical position on the screen
  * @param  p            - Source buffer
  * @param  xSize        - Horizontal bitmap size
  * @param  ySize        - Vertical bitmap size
  * @param  bytesPerLine - Number of bytes per Line
  */
static void _LCD_DrawBitmap8bpp(const int layerIndex, const int x, const int y, 
  U8 const *p, const int xSize, const int ySize, const int bytesPerLine)
{
  const U32 pixelFormat = _GetPixelformat(layerIndex);
  const U32 bufferSize = _GetBufferSize(layerIndex);
  const U32 addrDst = layerProp_[layerIndex].address + bufferSize * layerProp_[layerIndex].bufferIndex + 
    (y * layerProp_[layerIndex].xSize + x) * layerProp_[layerIndex].bytesPerPixel;
  const int offLineSrc = bytesPerLine - xSize;
  const int offLineDst = layerProp_[layerIndex].xSize - xSize;
  _DMA_DrawBitmapL8((void *)p, (void *)addrDst, offLineSrc, offLineDst, pixelFormat, xSize, ySize);
}

/**
  * @brief  Draw 4 bits per pixel bitmap
  * @param  layerIndex   - Layer index
  * @param  x            - start horizontal position on the screen
  * @param  y            - start vertical position on the screen
  * @param  p            - Source buffer
  * @param  xSize        - Horizontal bitmap size
  * @param  ySize        - Vertical bitmap size
  * @param  bytesPerLine - Number of bytes per Line
  * @retval 1 - param values incorrect, 0 - OK
  */
static int _LCD_DrawBitmap4bpp(const int layerIndex, const int x, const int y, 
  U8 const *p, const int xSize, const int ySize, const int bytesPerLine)
{
  if (x < 0) 
  {
    return 1;
  }
  if ((x + xSize) >= layerProp_[layerIndex].xSize) 
  {
    return 1;
  }
  if (y < 0) 
  {
    return 1;
  }
  if ((y + ySize) >= layerProp_[layerIndex].ySize) 
  {
    return 1;
  }
  const U32 pixelFormat = _GetPixelformat(layerIndex);
  
  /* Check if destination has direct color mode */
  if (pixelFormat > LTDC_PIXEL_FORMAT_ARGB4444) 
  {
    return 1;
  }
  const U32 bufferSize = _GetBufferSize(layerIndex);
  const U32 addrDst = layerProp_[layerIndex].address + bufferSize * layerProp_[layerIndex].bufferIndex + 
    (y * layerProp_[layerIndex].xSize + x) * layerProp_[layerIndex].bytesPerPixel;
  const int offLineSrc = (bytesPerLine * 2) - xSize;
  const int offLineDst = layerProp_[layerIndex].xSize - xSize;
  return _DMA_DrawBitmapA4((void *)p, (void *)addrDst, offLineSrc, offLineDst, pixelFormat, xSize, ySize);
}

/**
  * @brief  Draw 16 bits per pixel memory device
  * @param  pDst            - Destination buffer
  * @param  pSrc            - Source buffer
  * @param  xSize           - Horizontal memory device size
  * @param  ySize           - Vertical memory device size
  * @param  bytesPerLineDst - Destination number of bytes per Line
  * @param  bytesPerLineSrc - Source number of bytes per Line
  */
static void _LCD_DrawMemdev16bpp(void *pDst, const void *pSrc, 
  const int xSize, const int ySize, const int bytesPerLineDst, const int bytesPerLineSrc) 
{
  const int offLineSrc = (bytesPerLineSrc / (int)sizeof(U16)) - xSize;
  const int offLineDst = (bytesPerLineDst / (int)sizeof(U16)) - xSize;
  _DMA_CopyRGB565(pSrc, pDst, xSize, ySize, offLineSrc, offLineDst);
}

/**
  * @brief  Draw alpha memory device
  * @param  pDst            - Destination buffer
  * @param  pSrc            - Source buffer
  * @param  xSize           - Horizontal memory device size
  * @param  ySize           - Vertical memory device size
  * @param  bytesPerLineDst - Destination number of bytes per Line
  * @param  bytesPerLineSrc - Source number of bytes per Line
  */
static void _LCD_DrawMemdevAlpha(void *pDst, const void *pSrc, 
  const int xSize, const int ySize, const int bytesPerLineDst, const int bytesPerLineSrc) 
{
  const int offLineSrc = (bytesPerLineSrc / (int)sizeof(U32)) - xSize;
  const int offLineDst = (bytesPerLineDst / (int)sizeof(U32)) - xSize;
  _DMA_DrawAlphaBitmap(pDst, pSrc, xSize, ySize, offLineSrc, offLineDst, LTDC_PIXEL_FORMAT_ARGB8888);
}

/**
  * @brief  Draw alpha Bitmap
  * @param  layerIndex   - Layer index
  * @param  x            - Horizontal position on the screen
  * @param  y            - vertical position on the screen
  * @param  xSize        - Horizontal bitmap size
  * @param  ySize        - Vertical bitmap size
  * @param  bytesPerLine - Bytes per Line
  */
static void _LCD_DrawBitmapAlpha(const int layerIndex, const int x, const int y, 
  const void *p, const int xSize, const int ySize, const int bytesPerLine) 
{
  const int pixelFormat = (int)_GetPixelformat(layerIndex);
  const U32 bufferSize = _GetBufferSize(layerIndex);
  const U32 addrDst = layerProp_[layerIndex].address + bufferSize * layerProp_[layerIndex].bufferIndex + 
    (y * layerProp_[layerIndex].xSize + x) * layerProp_[layerIndex].bytesPerPixel;
  const int offLineSrc = (bytesPerLine / (int)sizeof(U32)) - xSize;
  const int offLineDst = layerProp_[layerIndex].xSize - xSize;
  _DMA_DrawAlphaBitmap((void *)addrDst, p, xSize, ySize, offLineSrc, offLineDst, pixelFormat);
}

/**
  * @brief  Translates the given colors into index values for the display controller
  * @param  pLogPal    - Palette 
  * @param  pBitmap    - Bitmap
  * @param  layerIndex - Layer index
  * @retval LCD_PIXELINDEX 
  */
static LCD_PIXELINDEX * _LCD_GetpPalConvTable(const LCD_LOGPALETTE GUI_UNI_PTR *pLogPal, 
  const GUI_BITMAP GUI_UNI_PTR *pBitmap, const int layerIndex) 
{
  int doDefault = 0;

  /* Check if we have a non transparent device independent bitmap */
  if (pBitmap->BitsPerPixel == 8) 
  {
    void (* pFunc)(void) = LCD_GetDevFunc(layerIndex, LCD_DEVFUNC_DRAWBMP_8BPP);
    if (pFunc) 
    {
      if (pBitmap->pPal) 
      {
        if (pBitmap->pPal->HasTrans) 
        {
          doDefault = 1;
        }
      }
      else
      {
        doDefault = 1;
      }
    }
    else
    {
      doDefault = 1;
    }
  }
  else 
  {
    doDefault = 1;
  }
  
  /* Default palette management for other cases */
  if (doDefault) 
  {
    /* Return a pointer to the index values to be used by the controller */
    return LCD_GetpPalConvTable(pLogPal);
  }

  /* Load LUT using DMA2D */
  _DMA_LoadLUT((U32 *)pLogPal->pPalEntries, pLogPal->NumEntries);
  
  /* Return something not NULL */
  return pBufferDma2D_;
}

/**
  * @brief  End of frame interrupt for managing multiple buffering
  * @param  hltdc - ltdc handle 
  */
void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc)
{
  for (int i = 0; i < GUI_NUM_LAYERS; i++) 
  {
    if (layerProp_[i].pendingBuffer >= 0) 
    {
      /* Calculate address of buffer to be used  as visible frame buffer */
      const U32 addr = layerProp_[i].address + layerProp_[i].xSize * layerProp_[i].ySize * layerProp_[i].pendingBuffer * layerProp_[i].bytesPerPixel;
      
      /* Store address into the LTDC regs */	  
      __HAL_LTDC_LAYER(hltdc, i)->CFBAR = addr;     
      __HAL_LTDC_RELOAD_CONFIG(hltdc);   
      
      /* Tell emWin that buffer is used */
      GUI_MULTIBUF_ConfirmEx(i, layerProp_[i].pendingBuffer);
      
      /* Clear pending buffer flag of layer */
      layerProp_[i].pendingBuffer = -1;
    }
  }
  HAL_LTDC_ProgramLineEvent(hltdc, 0);
}


/**
  * @brief  Function is called by the display driver for several purposes
  * @param  LayerIndex - Index of layer to be configured
  * @param  Cmd        - Commands
  * @param  pData      - Pointer to a LCD_X_DATA structure
  * @retval -1 - error, 0 - OK.
  */
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void *pData) 
{
  int result = 0;

  switch (Cmd) 
  {
  case LCD_X_INITCONTROLLER: 
    {
      /* Called during the initialization process in order to set up the display controller and put it into operation */
      LCD_LL_LayerInit((int)LayerIndex);
      break;
    }
  case LCD_X_SETORG: 
    {
      /* Required for setting the display origin which is passed in the 'xPos' and 'yPos' element of p */
      const LCD_X_SETORG_INFO *p = (LCD_X_SETORG_INFO *)pData;
      const U32 addr = layerProp_[LayerIndex].address + p->yPos * layerProp_[LayerIndex].xSize * layerProp_[LayerIndex].bytesPerPixel;
      HAL_LTDC_SetAddress(&hltdc, addr, LayerIndex);
      break;
    }
  case LCD_X_SHOWBUFFER: 
    {
      /* Required if multiple buffers are used. The 'Index' element of p contains the buffer index. */
      const LCD_X_SHOWBUFFER_INFO *p = (LCD_X_SHOWBUFFER_INFO *)pData;
      layerProp_[LayerIndex].pendingBuffer = p->Index;
      break;
    }
  case LCD_X_SETLUTENTRY: 
    {
      /* Required for setting a lookup table entry which is passed in the 'Pos' and 'Color' element of p */
      const LCD_X_SETLUTENTRY_INFO *p = (LCD_X_SETLUTENTRY_INFO *)pData;
      HAL_LTDC_ConfigCLUT(&hltdc, (uint32_t*)p->Color, p->Pos, LayerIndex);
      break;
    }
  case LCD_X_ON: 
    {
      /* Required if the display controller should support switching on and off */
      __HAL_LTDC_ENABLE(&hltdc);
      break;
    }
  case LCD_X_OFF: 
    {
      /* Required if the display controller should support switching on and off */
      __HAL_LTDC_DISABLE(&hltdc);
      break;
    }
  case LCD_X_SETVIS: 
    {
      /* Required for setting the layer visibility which is passed in the 'OnOff' element of pData */
      const LCD_X_SETVIS_INFO *p = (LCD_X_SETVIS_INFO *)pData;
      if (p->OnOff == ENABLE)
      {
        __HAL_LTDC_LAYER_ENABLE(&hltdc, LayerIndex); 
      }
      else
      {
        __HAL_LTDC_LAYER_DISABLE(&hltdc, LayerIndex);
      }
      __HAL_LTDC_RELOAD_CONFIG(&hltdc);
      break;
    }
  case LCD_X_SETPOS:
    {
      /* Required for setting the layer position which is passed in the 'xPos' and 'yPos' element of pData */
      const LCD_X_SETPOS_INFO *p = (LCD_X_SETPOS_INFO *)pData;
      HAL_LTDC_SetWindowPosition(&hltdc, p->xPos, p->yPos, LayerIndex);
      break;
    }
  case LCD_X_SETSIZE:
    {
      /* Required for setting the layer position which is passed in the 'xPos' and 'yPos' element of pData */
      int xPos, yPos;
      GUI_GetLayerPosEx(LayerIndex, &xPos, &yPos);
      const LCD_X_SETSIZE_INFO *p = (LCD_X_SETSIZE_INFO *)pData;
      if (LCD_GetSwapXYEx((int)LayerIndex))
      {
        layerProp_[LayerIndex].xSize = p->ySize;
        layerProp_[LayerIndex].ySize = p->xSize;
      }
      else
      {
        layerProp_[LayerIndex].xSize = p->xSize;
        layerProp_[LayerIndex].ySize = p->ySize;
      }
      HAL_LTDC_SetWindowPosition(&hltdc, xPos, yPos, LayerIndex);
      break;
    }
  case LCD_X_SETALPHA: 
    {
      /* Required for setting the alpha value which is passed in the 'Alpha' element of pData */
      LCD_X_SETALPHA_INFO *p = (LCD_X_SETALPHA_INFO *)pData;
      HAL_LTDC_SetAlpha(&hltdc, p->Alpha, LayerIndex);
      break;
    }
  case LCD_X_SETCHROMAMODE: 
    {
      /* Required for setting the chroma mode which is passed in the 'ChromaMode' element of pData */
      const LCD_X_SETCHROMAMODE_INFO *p = (LCD_X_SETCHROMAMODE_INFO *)pData;
      if (p->ChromaMode != 0)
      {
        HAL_LTDC_EnableColorKeying(&hltdc, LayerIndex);
      }
      else
      {
        HAL_LTDC_DisableColorKeying(&hltdc, LayerIndex);      
      }
      break;
    }
  case LCD_X_SETCHROMA: 
    {
      /* Required for setting the chroma value which is passed in the 'ChromaMin' and 'ChromaMax' element of pData */
      const LCD_X_SETCHROMA_INFO *p = (LCD_X_SETCHROMA_INFO *)pData;
      const U32 color = ((p->ChromaMin & 0xFF0000) >> 16) | (p->ChromaMin & 0x00FF00) | ((p->ChromaMin & 0x0000FF) << 16);
      HAL_LTDC_ConfigColorKeying(&hltdc, color, LayerIndex);
      break;
    }
  default:
    result = -1;
    break;
  }
  
  return result;
}

/**
  * @brief  Called during the initialization process in order to set up the
  *         display driver configuration
  */
void LCD_X_Config(void) 
{
  /* Call the Low level Init */
  LCD_LL_Init();
  
  /* At first initialize use of multiple buffers on demand */
#if (NUM_BUFFERS > 1)
  for (int i = 0; i < GUI_NUM_LAYERS; i++) 
  {
    GUI_MULTIBUF_ConfigEx(i, NUM_BUFFERS);
  }
#endif
  
  /* Set display driver and color conversion for 1st layer */
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER_0, COLOR_CONVERSION_0, 0, 0);
  
  /* Set size of 1st layer */
  if (LCD_GetSwapXYEx(0)) 
  {
    LCD_SetSizeEx(0, YSIZE_0, XSIZE_0);
    LCD_SetVSizeEx(0, YSIZE_0 * NUM_VSCREENS, XSIZE_0);
  }
  else
  {
    LCD_SetSizeEx(0, XSIZE_0, YSIZE_0);
    LCD_SetVSizeEx(0, XSIZE_0, YSIZE_0 * NUM_VSCREENS);
  }
#if (GUI_NUM_LAYERS > 1)
  /* Set display driver and color conversion for 2nd layer */
  GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER_1, COLOR_CONVERSION_1, 0, 1);
    
  /* Set size of 2nd layer */
  if (LCD_GetSwapXYEx(1)) 
  {
    LCD_SetSizeEx(1, YSIZE_0, XSIZE_1);
    LCD_SetVSizeEx(1, YSIZE_1 * NUM_VSCREENS, XSIZE_1);
  }
  else 
  {
    LCD_SetSizeEx(1, XSIZE_1, YSIZE_1);
    LCD_SetVSizeEx(1, XSIZE_1, YSIZE_1 * NUM_VSCREENS);
  }
#endif
  /* Setting up VRam address and get the pixel size */
  for (int i = 0; i < GUI_NUM_LAYERS; i++) 
  {
    /* Setting up VRam address */
    LCD_SetVRAMAddrEx(i, (void *)(layerProp_[i].address));
    /* Get the pixel size */
    layerProp_[i].bytesPerPixel = LCD_GetBitsPerPixelEx(i) >> 3;
  }
  /* Setting up custom functions */
  for (int i = 0; i < GUI_NUM_LAYERS; i++) 
  {
    const U32 pixelFormat = _GetPixelformat(i);
    /* Set custom function for copying complete buffers (used by multiple buffering) using DMA2D */
    LCD_SetDevFunc(i, LCD_DEVFUNC_COPYBUFFER, (void(*)(void))_LCD_CopyBuffer);
    if (pixelFormat <= LTDC_PIXEL_FORMAT_ARGB4444) 
    {
      /* Set custom function for filling operations using DMA2D */
      LCD_SetDevFunc(i, LCD_DEVFUNC_FILLRECT, (void(*)(void))_LCD_FillRect);
    }
    if (layerProp_[i].orientation == ROTATION_0)
    {
      /* Set custom function for copy recxtangle areas (used by GUI_CopyRect()) using DMA2D */
      LCD_SetDevFunc(i, LCD_DEVFUNC_COPYRECT, (void(*)(void))_LCD_CopyRect);
      
      /* Set functions for direct color mode layers. Won't work with indexed color modes because of missing LUT for DMA2D destination */
      if (pixelFormat <= LTDC_PIXEL_FORMAT_ARGB4444) 
      {
        /* Set up custom drawing routine for index based bitmaps using DMA2D */
        LCD_SetDevFunc(i, LCD_DEVFUNC_DRAWBMP_8BPP, (void(*)(void))_LCD_DrawBitmap8bpp);
      }
      
      /* Set up drawing routine for 16bpp bitmap using DMA2D */
      if (pixelFormat == LTDC_PIXEL_FORMAT_RGB565) 
      {
        /* Set up drawing routine for 16bpp bitmap using DMA2D. Makes only sense with RGB565 */
        LCD_SetDevFunc(i, LCD_DEVFUNC_DRAWBMP_16BPP, (void(*)(void))_LCD_DrawBitmap16bpp);
      }
      
      /* Set up drawing routine for 32bpp bitmap using DMA2D */
      if (pixelFormat == LTDC_PIXEL_FORMAT_ARGB8888) 
      {
        /* Set up drawing routine for 32bpp bitmap using DMA2D. Makes only sense with ARGB8888 */
        LCD_SetDevFunc(i, LCD_DEVFUNC_DRAWBMP_32BPP, (void(*)(void))_LCD_DrawBitmap32bpp);
      }
    }
  }
  
  /* Set up custom color conversion using DMA2D, works only for direct color modes because of missing LUT for DMA2D destination */

  /* Set up custom bulk color conversion using DMA2D for ARGB1555 */
  GUICC_M1555I_SetCustColorConv(_Color2IndexBulk_M1555I_DMA2D, _Index2ColorBulk_M1555I_DMA2D);

  /* Set up custom bulk color conversion using DMA2D for RGB565 */  
  GUICC_M565_SetCustColorConv(_Color2IndexBulk_M565_DMA2D, _Index2ColorBulk_M565_DMA2D);

  /* Set up custom bulk color conversion using DMA2D for ARGB4444 */
  GUICC_M4444I_SetCustColorConv(_Color2IndexBulk_M4444I_DMA2D, _Index2ColorBulk_M4444I_DMA2D);

  /* Set up custom bulk color conversion using DMA2D for RGB888 */
  GUICC_M888_SetCustColorConv(_Color2IndexBulk_M888_DMA2D, _Index2ColorBulk_M888_DMA2D);

  /* Set up custom bulk color conversion using DMA2D for ARGB8888 */
  GUICC_M8888I_SetCustColorConv(_Color2IndexBulk_M8888I_DMA2D, _Index2ColorBulk_M8888I_DMA2D);
  
  /* Set up custom alpha blending function using DMA2D */
  GUI_SetFuncAlphaBlending(_DMA_AlphaBlending);
  
  /* Set up custom function for translating a bitmap palette into index values.
   * Required to load a bitmap palette into DMA2D CLUT in case of a 8bpp indexed bitmap
   */
  GUI_SetFuncGetpPalConvTable(_LCD_GetpPalConvTable);
  
  /* Set up custom function for mixing up arrays of colors using DMA2D */
  GUI_SetFuncMixColorsBulk(_LCD_MixColorsBulk);
  
  /* Set up custom function for drawing AA4 characters */
  GUI_AA_SetpfDrawCharAA4(_LCD_DrawBitmap4bpp);
  
  /* Set up custom function for drawing 16bpp memory devices */
  GUI_MEMDEV_SetDrawMemdev16bppFunc(_LCD_DrawMemdev16bpp);
  
  /* Set up custom function for Alpha drawing operations */
//  GUI_SetFuncDrawAlpha(_LCD_DrawMemdevAlpha, _LCD_DrawBitmapAlpha); //TODO
}
