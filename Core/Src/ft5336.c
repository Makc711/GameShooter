/* Includes ------------------------------------------------------------------*/
#include "ft5336.h"
#include "i2c.h"

/* Private variables ---------------------------------------------------------*/
static ft5336_handle_TypeDef ft5336_handle = { FT5336_I2C_NOT_INITIALIZED, 0, 0 };

/* Functions -----------------------------------------------------------------*/
/**
  * @brief  Reads a single data.
  * @param  addr - I2C address
  * @param  reg - Reg address
  * @retval Data to be read
  */
static uint8_t TS_IO_Read(const uint8_t addr, const uint8_t reg)
{
  uint8_t read_value = 0;
  HAL_I2C_Mem_Read(&hi2c3, addr, reg, I2C_MEMADD_SIZE_8BIT, &read_value, 1, 0x1000);
  return read_value;
}

/**
  * @brief  Writes a single data.
  * @param  addr - I2C address
  * @param  reg - Reg address
  * @param  value - Data to be written
  */
static void TS_IO_Write(const uint8_t addr, const uint8_t reg, uint8_t value)
{
  const HAL_StatusTypeDef status = HAL_I2C_Mem_Write(&hi2c3, addr, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 0x1000);
  if (status != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief  Get the last touch gesture identification (zoom, move up/down...).
  * @param  deviceAddr - Device address on communication Bus (I2C slave address of FT5336).
  * @param  pGestureId - Pointer to get last touch gesture Identification.
  */
static void ft5336_TS_GetGestureID(const uint8_t deviceAddr, uint32_t *pGestureId)
{
  const volatile uint8_t ucReadData = TS_IO_Read(deviceAddr, FT5336_GEST_ID_REG);
  *pGestureId = ucReadData;
}

/**
  * @brief  Get the touch detailed informations on touch number 'touchIdx' (0..1)
  *         This touch detailed information contains :
  *         - weight that was applied to this touch
  *         - sub-area of the touch in the touch panel
  *         - event of linked to the touch (press down, lift up, ...)
  * @param  deviceAddr - Device address on communication Bus (I2C slave address of FT5336).
  * @param  touchIdx - Passed index of the touch (0..1) on which we want to get the
  *                    detailed information.
  * @param  pWeight - Pointer to to get the weight information of 'touchIdx'.
  * @param  pArea   - Pointer to to get the sub-area information of 'touchIdx'.
  * @param  pEvent  - Pointer to to get the event information of 'touchIdx'.
  */
static void TS_GetTouchInfo(const uint8_t deviceAddr,
  const uint32_t touchIdx,
  uint32_t *pWeight,
  uint32_t *pArea,
  uint32_t *pEvent)
{
  if (touchIdx < ft5336_handle.currActiveTouchNb)
  {
    uint8_t regAddressXHigh = 0;
    uint8_t regAddressPWeight = 0;
    uint8_t regAddressPMisc = 0;
    switch (touchIdx)
    {
    case 0 :
      regAddressXHigh   = FT5336_P1_XH_REG;
      regAddressPWeight = FT5336_P1_WEIGHT_REG;
      regAddressPMisc   = FT5336_P1_MISC_REG;
      break;

    case 1 :
      regAddressXHigh   = FT5336_P2_XH_REG;
      regAddressPWeight = FT5336_P2_WEIGHT_REG;
      regAddressPMisc   = FT5336_P2_MISC_REG;
      break;

    case 2 :
      regAddressXHigh   = FT5336_P3_XH_REG;
      regAddressPWeight = FT5336_P3_WEIGHT_REG;
      regAddressPMisc   = FT5336_P3_MISC_REG;
      break;

    case 3 :
      regAddressXHigh   = FT5336_P4_XH_REG;
      regAddressPWeight = FT5336_P4_WEIGHT_REG;
      regAddressPMisc   = FT5336_P4_MISC_REG;
      break;

    case 4 :
      regAddressXHigh   = FT5336_P5_XH_REG;
      regAddressPWeight = FT5336_P5_WEIGHT_REG;
      regAddressPMisc   = FT5336_P5_MISC_REG;
      break;

    case 5 :
      regAddressXHigh   = FT5336_P6_XH_REG;
      regAddressPWeight = FT5336_P6_WEIGHT_REG;
      regAddressPMisc   = FT5336_P6_MISC_REG;
      break;

    case 6 :
      regAddressXHigh   = FT5336_P7_XH_REG;
      regAddressPWeight = FT5336_P7_WEIGHT_REG;
      regAddressPMisc   = FT5336_P7_MISC_REG;
      break;

    case 7 :
      regAddressXHigh   = FT5336_P8_XH_REG;
      regAddressPWeight = FT5336_P8_WEIGHT_REG;
      regAddressPMisc   = FT5336_P8_MISC_REG;
      break;

    case 8 :
      regAddressXHigh   = FT5336_P9_XH_REG;
      regAddressPWeight = FT5336_P9_WEIGHT_REG;
      regAddressPMisc   = FT5336_P9_MISC_REG;
      break;

    case 9 :
      regAddressXHigh   = FT5336_P10_XH_REG;
      regAddressPWeight = FT5336_P10_WEIGHT_REG;
      regAddressPMisc   = FT5336_P10_MISC_REG;
      break;

    default :
      break;
    }

    /* Read Event Id of touch index */
    volatile uint8_t ucReadData = TS_IO_Read(deviceAddr, regAddressXHigh);
    *pEvent = (ucReadData & FT5336_TOUCH_EVT_FLAG_MASK) >> FT5336_TOUCH_EVT_FLAG_SHIFT;

    /* Read weight of touch index */
    ucReadData = TS_IO_Read(deviceAddr, regAddressPWeight);
    *pWeight = (ucReadData & FT5336_TOUCH_WEIGHT_MASK) >> FT5336_TOUCH_WEIGHT_SHIFT;

    /* Read area of touch index */
    ucReadData = TS_IO_Read(deviceAddr, regAddressPMisc);
    *pArea = (ucReadData & FT5336_TOUCH_AREA_MASK) >> FT5336_TOUCH_AREA_SHIFT;
  }
}

/**
  * @brief  Read the ft5336 device ID, pre initialize I2C in case of need to be
  *         able to read the FT5336 device ID, and verify this is a FT5336.
  * @param  deviceAddr - I2C FT5336 Slave address.
  * @retval The Device ID.
  */
static uint8_t Touch_ReadID(const uint8_t deviceAddr)
{
  volatile uint8_t ucReadId = 0;
  int8_t bFoundDevice = 0;

  /* At maximum 4 attempts to read ID : exit at first finding of the searched device ID */
  for (uint8_t nbReadAttempts = 0; ((nbReadAttempts < 3) && !(bFoundDevice)); nbReadAttempts++)
  {
    HAL_Delay(10);
    /* Read register FT5336_CHIP_ID_REG as DeviceID detection */
    ucReadId = TS_IO_Read(deviceAddr, FT5336_CHIP_ID_REG);

    /* Found the searched device ID ? */
    if (ucReadId == FT5336_ID_VALUE)
    {
      bFoundDevice = 1; // Set device as found
    }
  }
  return ucReadId; // Return the device ID value
}

/**
  * @brief  Return if there is touches detected or not.
  *         Try to detect new touches and forget the old ones (reset internal global
  *         variables).
  * @param  deviceAddr - Device address on communication Bus.
  * @retval Number of active touches detected (can be 0, 1 or 2).
  */
static uint8_t TS_DetectTouch(const uint8_t deviceAddr)
{
  /* Read register FT5336_TD_STAT_REG to check number of touches detection */
  volatile uint8_t nbTouch = TS_IO_Read(deviceAddr, FT5336_TD_STAT_REG);
  nbTouch &= FT5336_TD_STAT_MASK;

  if (nbTouch > FT5336_MAX_DETECTABLE_TOUCH)
  {
    /* If invalid number of touch detected, set it to zero */
    nbTouch = 0;
  }

  /* Update ft5336 driver internal global : current number of active touches */
  ft5336_handle.currActiveTouchNb = nbTouch;

  /* Reset current active touch index on which to work on */
  ft5336_handle.currActiveTouchIdx = 0;
  return nbTouch;
}

/**
  * @brief  Get the touch screen X and Y positions values
  *         Manage multi touch thanks to touch Index global
  *         variable 'ft5336_handle.currActiveTouchIdx'.
  * @param  deviceAddr - Device address on communication Bus.
  * @param  x - Pointer to X position value
  * @param  y - Pointer to Y position value
  */
static void TS_GetXY(const uint8_t deviceAddr, uint16_t *x, uint16_t *y)
{
  if (ft5336_handle.currActiveTouchIdx < ft5336_handle.currActiveTouchNb)
  {
    uint8_t regAddressXLow = 0;
    uint8_t regAddressXHigh = 0;
    uint8_t regAddressYLow = 0;
    uint8_t regAddressYHigh = 0;
    switch (ft5336_handle.currActiveTouchIdx)
    {
    case 0 :
      regAddressXLow  = FT5336_P1_XL_REG;
      regAddressXHigh = FT5336_P1_XH_REG;
      regAddressYLow  = FT5336_P1_YL_REG;
      regAddressYHigh = FT5336_P1_YH_REG;
      break;

    case 1 :
      regAddressXLow  = FT5336_P2_XL_REG;
      regAddressXHigh = FT5336_P2_XH_REG;
      regAddressYLow  = FT5336_P2_YL_REG;
      regAddressYHigh = FT5336_P2_YH_REG;
      break;

    case 2 :
      regAddressXLow  = FT5336_P3_XL_REG;
      regAddressXHigh = FT5336_P3_XH_REG;
      regAddressYLow  = FT5336_P3_YL_REG;
      regAddressYHigh = FT5336_P3_YH_REG;
      break;

    case 3 :
      regAddressXLow  = FT5336_P4_XL_REG;
      regAddressXHigh = FT5336_P4_XH_REG;
      regAddressYLow  = FT5336_P4_YL_REG;
      regAddressYHigh = FT5336_P4_YH_REG;
      break;

    case 4 :
      regAddressXLow  = FT5336_P5_XL_REG;
      regAddressXHigh = FT5336_P5_XH_REG;
      regAddressYLow  = FT5336_P5_YL_REG;
      regAddressYHigh = FT5336_P5_YH_REG;
      break;

    case 5 :
      regAddressXLow  = FT5336_P6_XL_REG;
      regAddressXHigh = FT5336_P6_XH_REG;
      regAddressYLow  = FT5336_P6_YL_REG;
      regAddressYHigh = FT5336_P6_YH_REG;
      break;

    case 6 :
      regAddressXLow  = FT5336_P7_XL_REG;
      regAddressXHigh = FT5336_P7_XH_REG;
      regAddressYLow  = FT5336_P7_YL_REG;
      regAddressYHigh = FT5336_P7_YH_REG;
      break;

    case 7 :
      regAddressXLow  = FT5336_P8_XL_REG;
      regAddressXHigh = FT5336_P8_XH_REG;
      regAddressYLow  = FT5336_P8_YL_REG;
      regAddressYHigh = FT5336_P8_YH_REG;
      break;

    case 8 :
      regAddressXLow  = FT5336_P9_XL_REG;
      regAddressXHigh = FT5336_P9_XH_REG;
      regAddressYLow  = FT5336_P9_YL_REG;
      regAddressYHigh = FT5336_P9_YH_REG;
      break;

    case 9 :
      regAddressXLow  = FT5336_P10_XL_REG;
      regAddressXHigh = FT5336_P10_XH_REG;
      regAddressYLow  = FT5336_P10_YL_REG;
      regAddressYHigh = FT5336_P10_YH_REG;
      break;

    default :
      break;
    }

    /* Read low part of X position */
    volatile uint8_t ucReadData = TS_IO_Read(deviceAddr, regAddressXLow);
    uint16_t coordinate = (ucReadData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

    /* Read high part of X position */
    ucReadData = TS_IO_Read(deviceAddr, regAddressXHigh);
    coordinate |= ((ucReadData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

    /* Send back ready X position to caller */
    *x = coordinate;

    /* Read low part of Y position */
    ucReadData = TS_IO_Read(deviceAddr, regAddressYLow);
    coordinate = (ucReadData & FT5336_TOUCH_POS_LSB_MASK) >> FT5336_TOUCH_POS_LSB_SHIFT;

    /* Read high part of Y position */
    ucReadData = TS_IO_Read(deviceAddr, regAddressYHigh);
    coordinate |= ((ucReadData & FT5336_TOUCH_POS_MSB_MASK) >> FT5336_TOUCH_POS_MSB_SHIFT) << 8;

    /* Send back ready Y position to caller */
    *y = coordinate;

    ft5336_handle.currActiveTouchIdx++; /* next call will work on next touch */
  }
}

/**
  * @brief  Update gesture Id following a touch detected.
  * @param  tsState - Pointer to touch screen current state structure
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
static uint8_t TS_GetGestureId(TS_StateTypeDef *tsState)
{
  uint32_t gestureId = 0;
  uint8_t tsStatus = TS_OK;
  ft5336_TS_GetGestureID(TS_I2C_ADDRESS, &gestureId);
  switch (gestureId)
  {
  case FT5336_GEST_ID_NO_GESTURE :
    tsState->gestureId = GEST_ID_NO_GESTURE;
    break;
  case FT5336_GEST_ID_MOVE_UP :
    tsState->gestureId = GEST_ID_MOVE_UP;
    break;
  case FT5336_GEST_ID_MOVE_RIGHT :
    tsState->gestureId = GEST_ID_MOVE_RIGHT;
    break;
  case FT5336_GEST_ID_MOVE_DOWN :
    tsState->gestureId = GEST_ID_MOVE_DOWN;
    break;
  case FT5336_GEST_ID_MOVE_LEFT :
    tsState->gestureId = GEST_ID_MOVE_LEFT;
    break;
  case FT5336_GEST_ID_ZOOM_IN :
    tsState->gestureId = GEST_ID_ZOOM_IN;
    break;
  case FT5336_GEST_ID_ZOOM_OUT :
    tsState->gestureId = GEST_ID_ZOOM_OUT;
    break;
  default :
    tsStatus = TS_ERROR;
    break;
  }
  return tsStatus;
}

/**
  * @brief  Initializes and configures the touchscreen functionality.
  */
void Touch_Init(void)
{
  if (Touch_ReadID(TS_I2C_ADDRESS) != FT5336_ID_VALUE)
  {
    Error_Handler();
  }
  const uint8_t regValue = (FT5336_G_MODE_INTERRUPT_POLLING & (FT5336_G_MODE_INTERRUPT_MASK >> FT5336_G_MODE_INTERRUPT_SHIFT))
    << FT5336_G_MODE_INTERRUPT_SHIFT;
  TS_IO_Write(TS_I2C_ADDRESS, FT5336_GMODE_REG, regValue);
  ft5336_handle.i2cInitialized = FT5336_I2C_INITIALIZED;
}

/**
  * @brief  Returns status and positions of the touch screen.
  * @param  tsState - Pointer to touch screen current state structure
  * @retval TS_OK if all initializations are OK. Other value if error.
  */
uint8_t TS_GetState(TS_StateTypeDef *tsState)
{
#if (USE_SLIP_PROTECTION)
  static uint16_t _x[TS_MAX_NB_TOUCH] = { 0 };
  static uint16_t _y[TS_MAX_NB_TOUCH] = { 0 };
#endif

#if (USE_TOUCH_INFO)
  uint32_t weight = 0;
  uint32_t area = 0;
  uint32_t event = 0;
#endif

  uint8_t tsStatus = TS_OK;

  /* Check and update the number of touches active detected */
  tsState->touchDetected = TS_DetectTouch(TS_I2C_ADDRESS);

  if (tsState->touchDetected)
  {
    uint16_t x[TS_MAX_NB_TOUCH];
    uint16_t y[TS_MAX_NB_TOUCH];
    for (uint32_t index = 0; index < tsState->touchDetected; index++)
    {
      uint16_t bruteX[TS_MAX_NB_TOUCH];
      uint16_t bruteY[TS_MAX_NB_TOUCH];

      /* Get each touch coordinates */
      TS_GetXY(TS_I2C_ADDRESS, &(bruteX[index]), &(bruteY[index]));
      
#if (TS_SWAP_XY)
      x[index] = bruteY[index];
      y[index] = bruteX[index];
#else
      x[index] = bruteX[index];
      y[index] = bruteY[index];
#endif

#if (TS_SWAP_X)
      x[index] = TS_WIDTH - 1 - x[index];
#endif

#if (TS_SWAP_Y)
      y[index] = TS_HEIGHT - 1 - y[index];
#endif

#if (IS_CALIBRATION_COMPLETE)
      x[index] = (uint16_t)((float)x[index] * (TS_WIDTH - 1) / MAX_FACT_X + 0.5001f);
      y[index] = (uint16_t)((float)y[index] * (TS_HEIGHT - 1) / MAX_FACT_Y + 0.5001f);
      if (x[index] >= TS_WIDTH)
      {
        x[index] = tsState->touchX[index];
      }
      if (y[index] >= TS_HEIGHT)
      {
        y[index] = tsState->touchY[index];
      }
#endif 
      
#if (USE_SLIP_PROTECTION)
      const uint16_t xDiff = (x[index] > _x[index])
                            ? (x[index] - _x[index])
                            : (_x[index] - x[index]);
      const uint16_t yDiff = (y[index] > _y[index])
                            ? (y[index] - _y[index])
                            : (_y[index] - y[index]);
      if ((xDiff + yDiff) > 5)
      {
        _x[index] = x[index];
        _y[index] = y[index];
        tsState->touchX[index] = x[index];
        tsState->touchY[index] = y[index];
      }
#else
      tsState->touchX[index] = x[index];
      tsState->touchY[index] = y[index];
#endif

#if (USE_TOUCH_INFO)
      /* Get touch info related to the current touch */
      TS_GetTouchInfo(TS_I2C_ADDRESS, index, &weight, &area, &event);

      /* Update tsState structure */
      tsState->touchWeight[index] = weight;
      tsState->touchArea[index] = area;
      switch (event)
      {
      case FT5336_TOUCH_EVT_FLAG_PRESS_DOWN :
        tsState->touchEventId[index] = TOUCH_EVENT_PRESS_DOWN;
        break;
      case FT5336_TOUCH_EVT_FLAG_LIFT_UP :
        tsState->touchEventId[index] = TOUCH_EVENT_LIFT_UP;
        break;
      case FT5336_TOUCH_EVT_FLAG_CONTACT :
        tsState->touchEventId[index] = TOUCH_EVENT_CONTACT;
        break;
      case FT5336_TOUCH_EVT_FLAG_NO_EVENT :
        tsState->touchEventId[index] = TOUCH_EVENT_NO_EVT;
        break;
      default:
        tsStatus = TS_ERROR;
        return tsStatus;
      }
#endif
    }
#if (USE_GESTURE_DETECT)
    tsStatus = TS_GetGestureId(tsState);
#endif
  }
  return tsStatus;
}
