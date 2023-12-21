/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    lptim.h
  * @brief   This file contains all the function prototypes for
  *          the lptim.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LPTIM_H__
#define __LPTIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern LPTIM_HandleTypeDef hlptim1;

extern LPTIM_HandleTypeDef hlptim2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_LPTIM1_Init(void);
void MX_LPTIM2_Init(void);

/* USER CODE BEGIN Prototypes */
#define LPTIM_SOURCE_CLK (32768UL)
#define LPTIM_CLK_INTERVAL (8)	// 8/32768 Hz = 244 us
#define LPTIM_NB_EVENTS	(4)

#define LPTIM_PERIODE_2MS	(10)	// 10 * 244 us = 2.44 ms
#define LPTIM_PERIODE_1S	(LPTIM_SOURCE_CLK/LPTIM_CLK_INTERVAL)
#define LPTIM_PERIODE_0_5S	(LPTIM_PERIODE_1S/2)


void lptim_Start(void);

#define LPTIM_COULD_NOT_ADD_EVENT (0xFFFFFFFF)
uint32_t lptim_AddSingleEvent(uint32_t periode, uint32_t event);
uint32_t lptim_AddRepeatingEvent(uint32_t periode, uint32_t event);
uint32_t lptim_RemoveEvent(uint32_t lptim_event_nr);

uint32_t lptim2_StartRepeating(uint32_t event);
uint32_t lptim2_Stop(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __LPTIM_H__ */

