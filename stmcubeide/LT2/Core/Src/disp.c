/*
 * disp.c
 *
 *  Created on: Oct 22, 2025
 *      Author: martin
 */

#include "main.h"
#include "disp.h"

#define TIM_DISP TIM22

void disp_init(void) {
	return;
}

void disp_set_brightness(uint8_t bright) {
	return;
}

void disp_on(void) {
	// set_gpio
	LL_TIM_ClearFlag_UPDATE(TIM_DISP);
	LL_TIM_EnableIT_UPDATE(TIM_DISP);
	// reset gpio
	LL_TIM_ClearFlag_CC1(TIM_DISP);
	LL_TIM_EnableIT_CC1(TIM_DISP);
	return;
}
void disp_off(void) {
	return;
}

void disp_timer_isr_gpio_set(void) {
	return;
}

void disp_timer_isr_gpio_reset(void) {
	return;
}
