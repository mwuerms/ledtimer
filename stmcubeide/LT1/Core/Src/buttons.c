/*
 * buttons.c
 *
 *  Created on: Sep 28, 2023
 *      Author: Martin
 */

#include "main.h"
#include "buttons.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if(GPIO_Pin == USR_BTN_Pin) {
		global_events |= EV_BUTTON;
	}

	if(global_events)
		HAL_PWR_DisableSleepOnExit();
}

void buttons_Init(void) {
	return;
}
