/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */
#define GPIO_STATE_LOW			 (0)
#define GPIO_STATE_HIGH			 (1)
#define GPIO_STATE_BTN_PRESSED		 (2)
#define GPIO_STATE_BTN_RELEASED		 (3)
#define GPIO_STATE_BTN_SHORT_PRESSED (4)
#define GPIO_STATE_BTN_LONG_PRESSED	 (5)

#define GPIO_OLD_STATE_HIGH	(1 << 2)
#define GPIO_OLD_STATE_LOW	(0)

#define GPIO_STATE_CNT_SHORT (5)	//  5 * 2 ms =  10 ms
#define GPIO_STATE_CNT_LONG (250)	// 250 * 2 ms = 500 ms

#define GPIO_INDEX_BTN_UP0	(0)
#define GPIO_INDEX_BTN_UP1	(1)
#define GPIO_INDEX_BTN_UP2	(2)
#define GPIO_INDEX_BTN_UP3	(3)
#define GPIO_INDEX_BTN_PLAY	(4)
#define GPIO_INDEX_BTN_MODE	(5)
#define GPIO_INDEX_BTN_STOP	(6)
#define GPIO_INDEX_CH_STAT	(7)
#define GPIO_INDEX_USB_STAT	(8)
#define GPIO_INDEX_USR_BTN	(9)
#define GPIO_NB_INPUTS	(9+1)

void gpio_PollInputs(void);

void gpio_GetCopyOfInputStates(uint8_t* copy_states);
uint32_t gpio_IsAnyButtonPressed(void);
uint32_t gpio_hasAnyButtonChanged(void);

void gpio_StartPolling(void);
void gpio_StopPolling(void);

void gpio_EnableButtonInterrupts(void);
void gpio_DisableButtonInterrupts(void);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

