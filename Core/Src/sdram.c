/* Includes ------------------------------------------------------------------*/
#include "sdram.h"

/* Functions -----------------------------------------------------------------*/
HAL_StatusTypeDef SDRAM_Init(SDRAM_HandleTypeDef *hsdram)
{
  FMC_SDRAM_CommandTypeDef command;

  /* Step 1: Configure a clock configuration enable command */
  command.CommandMode            = FMC_SDRAM_CMD_CLK_ENABLE;
  command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  command.AutoRefreshNumber      = 1;
  command.ModeRegisterDefinition = 0;
  HAL_StatusTypeDef halState = HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);
  if (halState != HAL_OK)
  {
    return halState;
  }

  /* Step 2: Insert 100 us minimum delay */ 
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  HAL_Delay(1);

  /* Step 3: Configure a PALL (precharge all) command */ 
  command.CommandMode            = FMC_SDRAM_CMD_PALL;
  command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  command.AutoRefreshNumber      = 1;
  command.ModeRegisterDefinition = 0;
  halState = HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);
  if (halState != HAL_OK)
  {
    return halState;
  }

  /* Step 4: Configure an Auto Refresh command */ 
  command.CommandMode            = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  command.AutoRefreshNumber      = 8;
  command.ModeRegisterDefinition = 0;
  halState = HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);
  if (halState != HAL_OK)
  {
    return halState;
  }

  /* Step 5: Program the external memory mode register */
  __IO uint32_t tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1 | \
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   | \
                     SDRAM_MODEREG_CAS_LATENCY_2           | \
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD | \
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
  
  command.CommandMode            = FMC_SDRAM_CMD_LOAD_MODE;
  command.CommandTarget          = FMC_SDRAM_CMD_TARGET_BANK1;
  command.AutoRefreshNumber      = 1;
  command.ModeRegisterDefinition = tmpmrd;
  halState = HAL_SDRAM_SendCommand(hsdram, &command, SDRAM_TIMEOUT);
  if (halState != HAL_OK)
  {
    return halState;
  }

  /* Step 6: Set the refresh rate counter */
  /* Set the device refresh rate */
  halState = HAL_SDRAM_ProgramRefreshRate(hsdram, REFRESH_COUNT);

  return halState;
}
