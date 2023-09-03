/**
  ******************************************************************************
  * @file           : sdram.h
  * @author         : Rusanov M.N.
  * @version        : V1.0.0
  * @date           : 02-July-2023
  * @brief          : Header for sdram.c file.
  *                   SDRAM MT48LC4M32B2
  *                   This file is needed to initialize SDRAM.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDRAM_H_
#define SDRAM_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private defines -----------------------------------------------------------*/
#define SDRAM_TIMEOUT                            ((uint32_t)0xFFFF)
#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)
#define SDRAM_DEVICE_ADDR                        ((uint32_t)0xC0000000)
#define REFRESH_COUNT	                           ((uint32_t)0x0603) /*SDRAM refresh counter (100MHz SD Clock)*/

/* Exported functions prototypes ---------------------------------------------*/
HAL_StatusTypeDef SDRAM_Init(SDRAM_HandleTypeDef *hsdram);

#endif /* SDRAM_H_ */