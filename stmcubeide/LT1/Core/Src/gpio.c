/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "lptim.h"

static uint32_t gpio_lptim_nr;
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if(GPIO_Pin == USR_BTN_Pin) {
		//global_events |= EV_WAKEUP;
	}

	if(global_events)
		HAL_PWR_DisableSleepOnExit();
}
/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOH, ALM0_Pin|ALM1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DISP_ROW0_Pin|DISP_ROW1_Pin|DISP_ROW2_Pin|DISP_ROW3_Pin
                          |DISP_ROW4_Pin|DISP_ROW5_Pin|DISP_ROW6_Pin|DISP_COL_SER_Pin
                          |DISP_COL_SRCLK_Pin|DISP_COL_RCLK_Pin|DISP_COL_SRCLR_Pin|DISP_COL_OE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = USR_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USR_BTN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PHPin PHPin */
  GPIO_InitStruct.Pin = ALM0_Pin|ALM1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin PAPin PAPin PAPin
                           PAPin PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = DISP_ROW0_Pin|DISP_ROW1_Pin|DISP_ROW2_Pin|DISP_ROW3_Pin
                          |DISP_ROW4_Pin|DISP_ROW5_Pin|DISP_ROW6_Pin|DISP_COL_SER_Pin
                          |DISP_COL_SRCLK_Pin|DISP_COL_RCLK_Pin|DISP_COL_SRCLR_Pin|DISP_COL_OE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = BTN_UP0_Pin|BTN_UP1_Pin|BTN_UP2_Pin|BTN_UP3_Pin
                          |BTN_PLAY_Pin|BTN_MODE_Pin|BTN_STOP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin PBPin PBPin
                           PBPin */
  GPIO_InitStruct.Pin = SW1_Pin|SW2_Pin|SW3_Pin|SW4_Pin
                          |SW0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = CH_STAT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(CH_STAT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = USB_STAT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_STAT_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 2 */

static uint8_t gpio_input_states[GPIO_NB_INPUTS];		// store GPIO_STATE_RELEASED, GPIO_STATE_SHORT_PRESSED, GPIO_STATE_LONG_PRESSED
static uint8_t gpio_input_states_old[GPIO_NB_INPUTS];	// store the old gpio_input_states to check for any change
static uint8_t gpio_input_values[GPIO_NB_INPUTS];
static uint8_t gpio_input_states_buffer[GPIO_NB_INPUTS]; // store all the HAL_GPIO_ReadPin()
static uint8_t gpio_input_value_cnt[GPIO_NB_INPUTS];	// count when it is pressed or low

typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} gpio_inputs_def_t;

static const gpio_inputs_def_t gpio_inputs[] = {
		{ .port = BTN_UP0_GPIO_Port, .pin = BTN_UP0_Pin},
		{ .port = BTN_UP1_GPIO_Port, .pin = BTN_UP1_Pin},
		{ .port = BTN_UP2_GPIO_Port, .pin = BTN_UP2_Pin},
		{ .port = BTN_UP3_GPIO_Port, .pin = BTN_UP3_Pin},
		{ .port = BTN_PLAY_GPIO_Port, .pin = BTN_PLAY_Pin},
		{ .port = BTN_MODE_GPIO_Port, .pin = BTN_MODE_Pin},
		{ .port = BTN_STOP_GPIO_Port, .pin = BTN_STOP_Pin},
		{ .port = CH_STAT_GPIO_Port, .pin = CH_STAT_Pin},
		{ .port = USB_STAT_GPIO_Port, .pin = USB_STAT_Pin},
		{ .port = USR_BTN_GPIO_Port, .pin = USR_BTN_Pin},
};

#define GPIO_CURRENT_VALUE_MASK	(0x01)
#define GPIO_BTN_STATE_MASK	(0xFF)

void gpio_PollInputs(void) {
	uint32_t n;
	// shift all to store old values
	for(n = 0; n < GPIO_NB_INPUTS; n++) {
		gpio_input_values[n] <<= 1;
		gpio_input_values[n] |= HAL_GPIO_ReadPin(gpio_inputs[n].port, gpio_inputs[n].pin);
	}

	// eval inputs
	if((gpio_input_values[GPIO_INDEX_USR_BTN] & GPIO_CURRENT_VALUE_MASK) == 0x00000000) {
		gpio_input_states[GPIO_INDEX_USR_BTN] = GPIO_STATE_BTN_RELEASED;
		gpio_input_value_cnt[GPIO_INDEX_USR_BTN] = 0;
	}
	else {
		gpio_input_states[GPIO_INDEX_USR_BTN] = GPIO_STATE_BTN_PRESSED;
	}

	if(gpio_input_value_cnt[GPIO_INDEX_USR_BTN] == 0) {
		if((gpio_input_values[GPIO_INDEX_USR_BTN] & GPIO_BTN_STATE_MASK) == 0x000F) {
			gpio_input_states[GPIO_INDEX_USR_BTN] = GPIO_STATE_BTN_SHORT_PRESSED;
			gpio_input_value_cnt[GPIO_INDEX_USR_BTN] = GPIO_STATE_CNT_LONG;
		}
	}
	else {
		if(gpio_input_value_cnt[GPIO_INDEX_USR_BTN] == 1) {
			gpio_input_states[GPIO_INDEX_USR_BTN] = GPIO_STATE_BTN_LONG_PRESSED;
			gpio_input_value_cnt[GPIO_INDEX_USR_BTN] = GPIO_STATE_CNT_LONG;
		}
		gpio_input_value_cnt[GPIO_INDEX_USR_BTN]--;
	}

	// eval inputs
	for(n = 0; n < GPIO_INDEX_USB_STAT; n++) {
		switch(gpio_input_states[n]) {
		case GPIO_STATE_BTN_RELEASED:
			if(gpio_input_values[n] == 0xF0) {
				// 1st button press
				gpio_input_states[n] = GPIO_STATE_BTN_SHORT_PRESSED;
			}
			break;
		case GPIO_STATE_BTN_SHORT_PRESSED:
		case GPIO_STATE_BTN_LONG_PRESSED:
			gpio_input_states[n] = GPIO_STATE_BTN_PRESSED;
			gpio_input_value_cnt[n] = 250;
			break;
		case GPIO_STATE_BTN_PRESSED:
			if((gpio_input_values[n] & 0x0F) == 0x0F) {
				// button was released
				gpio_input_states[n] = GPIO_STATE_BTN_RELEASED;
			}
			else {
				// still pressed
				if(gpio_input_value_cnt[n] == 0) {
					gpio_input_states[n] = GPIO_STATE_BTN_LONG_PRESSED;
				}
				else {
					gpio_input_value_cnt[n]--;
				}
			}
			break;
		}
	}
}

void gpio_GetCopyOfInputStates(uint8_t* copy_states) {
	uint32_t n;
	for(n = 0; n < GPIO_NB_INPUTS; n++) {
		copy_states[n] = gpio_input_states[n];
	}
}

uint32_t gpio_IsAnyButtonPressed(void) {
	uint32_t n;
	for(n = 0; n <= GPIO_INDEX_BTN_STOP; n++) {
		if(gpio_input_states[n] == GPIO_STATE_BTN_SHORT_PRESSED) {
			return TRUE;
		}
		if(gpio_input_states[n] == GPIO_STATE_BTN_LONG_PRESSED) {
			return TRUE;
		}
	}
	if(gpio_input_states[GPIO_INDEX_USR_BTN] == GPIO_STATE_BTN_PRESSED) {
		return TRUE;
	}
	return FALSE;
}

uint32_t gpio_hasAnyButtonChanged(void) {
	uint32_t n;
	uint32_t cnt_change = 0;
	// check states for any change, also copy to old states
	for(n = 0; n <= GPIO_INDEX_BTN_STOP; n++) {
		if(gpio_input_states[n] != gpio_input_states_old[n]) {
			// change detected
			cnt_change++;
		}
		gpio_input_states_old[n] = gpio_input_states[n];
	}
	if(cnt_change == 0) {
		// no change detected
		return FALSE;
	}
	return TRUE;
}

void gpio_StartPolling(void) {
	uint32_t n;
	for(n = 0; n < GPIO_NB_INPUTS; n++) {
		gpio_input_values[n] = 0xFF;
		gpio_input_states[n] = GPIO_STATE_BTN_RELEASED;
		gpio_input_states_old[n] = GPIO_STATE_BTN_RELEASED;
	}
	gpio_lptim_nr = lptim_AddRepeatingEvent(LPTIM_PERIODE_2MS, EV_GPIO_POLL);
}

void gpio_StopPolling(void) {
	lptim_RemoveEvent(gpio_lptim_nr);
}

void gpio_enablebuttoninterrupts(void) {
	return;
}

void gpio_disablebuttoninterrupts(void) {
	return;
}

#if 0
__HAL_RCC_GPIOC_CLK_ENABLE();

#warning "_DISPLAY GPIOC"
  /*Configure GPIO pins : PBPin PBPin */
	GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SW4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif
/* USER CODE END 2 */
