/*
 * encoder.c
 *
 *  Created on: Oct 22, 2025
 *      Author: martin
 */

#include "main.h"
#include "encoder.h"
#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_it.h"

#define TIM_ENC TIM22
#define ENC_A_EXTI_LINE LL_EXTI_LINE_0
#define ENC_B_EXTI_LINE LL_EXTI_LINE_1
#define ENC_BTN_EXTI_LINE LL_EXTI_LINE_3

void encoder_init(void) {
	// enable ENC_A + ENC_BTN interrupts
	LL_EXTI_ClearFlag_0_31(ENC_A_EXTI_LINE);
	LL_EXTI_EnableFallingTrig_0_31(ENC_A_EXTI_LINE);
	LL_EXTI_EnableRisingTrig_0_31(ENC_A_EXTI_LINE);
	LL_EXTI_EnableIT_0_31(ENC_A_EXTI_LINE);

	LL_EXTI_ClearFlag_0_31(ENC_BTN_EXTI_LINE);
	LL_EXTI_EnableFallingTrig_0_31(ENC_BTN_EXTI_LINE);
	LL_EXTI_EnableRisingTrig_0_31(ENC_BTN_EXTI_LINE);
	LL_EXTI_EnableIT_0_31(ENC_BTN_EXTI_LINE);


	//LL_GPIO_ResetOutputPin(ENC_BTN_GPIO_Port, ENC_BTN_Pin);
	//LL_GPIO_SetOutputPin(ENC_BTN_GPIO_Port, ENC_BTN_Pin);
}

void encoder_a_isr(void) {
	if(LL_GPIO_ReadInputPort(ENC_A_GPIO_Port) & (1 << ENC_A_Pin)) {
		if(LL_GPIO_ReadInputPort(ENC_B_GPIO_Port) & (1 << ENC_A_Pin)) {
			// A set, B set -> left
		}
		else {
			// A set, B reset -> right
		}
	}
	else {
		if(LL_GPIO_ReadInputPort(ENC_B_GPIO_Port) & (1 << ENC_A_Pin)) {
			// A reset, B set -> right
		}
		else {
			// A reset, B reset -> left
		}
	}
}
void encoder_b_isr(void) {
	// nothing to do for now
}
void encoder_btn_isr(void) {
	if(LL_GPIO_ReadInputPort(ENC_BTN_GPIO_Port) & (1 << ENC_BTN_Pin)) {
		// set -> released
	}
	else {
		// reset -> pressed
	}
}
