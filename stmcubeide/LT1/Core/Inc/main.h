/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ALM0_Pin GPIO_PIN_0
#define ALM0_GPIO_Port GPIOH
#define ALM1_Pin GPIO_PIN_1
#define ALM1_GPIO_Port GPIOH
#define DISP_ROW0_Pin GPIO_PIN_0
#define DISP_ROW0_GPIO_Port GPIOA
#define DISP_ROW1_Pin GPIO_PIN_1
#define DISP_ROW1_GPIO_Port GPIOA
#define DISP_ROW2_Pin GPIO_PIN_2
#define DISP_ROW2_GPIO_Port GPIOA
#define DISP_ROW3_Pin GPIO_PIN_3
#define DISP_ROW3_GPIO_Port GPIOA
#define DISP_ROW4_Pin GPIO_PIN_4
#define DISP_ROW4_GPIO_Port GPIOA
#define DISP_ROW5_Pin GPIO_PIN_5
#define DISP_ROW5_GPIO_Port GPIOA
#define DISP_ROW6_Pin GPIO_PIN_6
#define DISP_ROW6_GPIO_Port GPIOA
#define DISP_COL_SER_Pin GPIO_PIN_7
#define DISP_COL_SER_GPIO_Port GPIOA
#define BTN_UP1_Pin GPIO_PIN_0
#define BTN_UP1_GPIO_Port GPIOB
#define BTN_UP2_Pin GPIO_PIN_1
#define BTN_UP2_GPIO_Port GPIOB
#define BTN_UP3_Pin GPIO_PIN_2
#define BTN_UP3_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_10
#define SW1_GPIO_Port GPIOB
#define SW2_Pin GPIO_PIN_11
#define SW2_GPIO_Port GPIOB
#define SW3_Pin GPIO_PIN_12
#define SW3_GPIO_Port GPIOB
#define SW4_Pin GPIO_PIN_13
#define SW4_GPIO_Port GPIOB
#define DISP_COL_SRCLK_Pin GPIO_PIN_8
#define DISP_COL_SRCLK_GPIO_Port GPIOA
#define DISP_COL_RCLK_Pin GPIO_PIN_9
#define DISP_COL_RCLK_GPIO_Port GPIOA
#define DISP_COL_SRCLR_Pin GPIO_PIN_10
#define DISP_COL_SRCLR_GPIO_Port GPIOA
#define DISP_COL_OE_Pin GPIO_PIN_15
#define DISP_COL_OE_GPIO_Port GPIOA
#define BTN_UP4_Pin GPIO_PIN_3
#define BTN_UP4_GPIO_Port GPIOB
#define BTN_PLAY_Pin GPIO_PIN_4
#define BTN_PLAY_GPIO_Port GPIOB
#define BTN_MODE_Pin GPIO_PIN_5
#define BTN_MODE_GPIO_Port GPIOB
#define BTN_STOP_Pin GPIO_PIN_6
#define BTN_STOP_GPIO_Port GPIOB
#define CH_STAT_Pin GPIO_PIN_7
#define CH_STAT_GPIO_Port GPIOB
#define USB_STAT_Pin GPIO_PIN_8
#define USB_STAT_GPIO_Port GPIOB
#define SW0_Pin GPIO_PIN_9
#define SW0_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#include "macros.h"

extern volatile uint32_t global_events;
#define EV_WAKEUP	BIT(0)
#define EV_DISPLAY_UPDATE BIT(1)
#define EV_BLINK	BIT(2)
#define EV_BLINK2	BIT(3)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
