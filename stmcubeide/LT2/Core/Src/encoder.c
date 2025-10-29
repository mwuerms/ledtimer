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

#define TIM_ENC TIM21
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
	if(LL_GPIO_ReadInputPort(ENC_A_GPIO_Port) & ENC_A_Pin) {
		if(LL_GPIO_ReadInputPort(ENC_B_GPIO_Port) & ENC_B_Pin) {
			// A set, B set -> right
			scheduler_send_event(main_tid, EV_ENC_ROT_RIGHT, NULL);
		}
		else {
			// A set, B reset -> left
			scheduler_send_event(main_tid, EV_ENC_ROT_LEFT, NULL);
		}
	}
	else {
		if(LL_GPIO_ReadInputPort(ENC_B_GPIO_Port) & ENC_B_Pin) {
			// A reset, B set -> left
			scheduler_send_event(main_tid, EV_ENC_ROT_LEFT, NULL);
		}
		else {
			// A reset, B reset -> right
			scheduler_send_event(main_tid, EV_ENC_ROT_RIGHT, NULL);
		}
	}
}

void encoder_b_isr(void) {
	// nothing to do for now
}

#define ENC_BTN_CTRL_PRESSED_TIMER_DELAY_MAX (73) // should be 50 ms
#define ENC_BTN_CTRL_LONG_PRESSED_TIMER_DELAY_MAX (727) // 500 ms
#define ENC_BTN_CTRL_STATE_PRESSED  (0)
#define ENC_BTN_CTRL_STATE_RELEASED (1)
static volatile struct {
	uint8_t btn_state;
	struct {
		uint16_t timer_delay;
		uint8_t cnt;
	} pressed;
	struct {
		uint16_t timer_delay;
	} long_pressed;
} enc_btn_ctrl = {
	.btn_state = ENC_BTN_CTRL_STATE_RELEASED,
	.pressed.timer_delay = 0, // inactive
	.pressed.cnt = 0,
	.long_pressed.timer_delay = 0, // inactive
};

void encoder_btn_isr(void) {
	if(LL_GPIO_ReadInputPort(ENC_BTN_GPIO_Port) & ENC_BTN_Pin) {
		// set -> released
		enc_btn_ctrl.btn_state = ENC_BTN_CTRL_STATE_RELEASED;
		enc_btn_ctrl.long_pressed.timer_delay = 0;
	}
	else {
		// reset -> pressed
		enc_btn_ctrl.btn_state = ENC_BTN_CTRL_STATE_PRESSED;
		if(enc_btn_ctrl.pressed.timer_delay == 0) {
			// timer expired = idle -> start
			enc_btn_ctrl.pressed.timer_delay = ENC_BTN_CTRL_PRESSED_TIMER_DELAY_MAX;
			enc_btn_ctrl.pressed.cnt = 1;
		}
		else {
			enc_btn_ctrl.pressed.cnt++;
		}
		if(enc_btn_ctrl.long_pressed.timer_delay == 0) {
			// timer expired = idle -> start
			enc_btn_ctrl.long_pressed.timer_delay = ENC_BTN_CTRL_LONG_PRESSED_TIMER_DELAY_MAX;
		}
	}
}

void encoder_timer_isr(void) {
	if(enc_btn_ctrl.pressed.timer_delay) {
		enc_btn_ctrl.pressed.timer_delay--;
		if(enc_btn_ctrl.pressed.timer_delay == 0) {
			// expired
			if(LL_GPIO_ReadInputPort(ENC_BTN_GPIO_Port) & ENC_BTN_Pin) {
				// btn is released, if btn is still pressed -> skip
				if(enc_btn_ctrl.pressed.cnt == 1) {
					scheduler_send_event(main_tid, EV_ENC_SINGLE_PRESSED, NULL);
				}
				else {
					// don't care how many, more than 1
					scheduler_send_event(main_tid, EV_ENC_DOUBLE_PRESSED, NULL);
				}
			}
		}
	}
	if(enc_btn_ctrl.long_pressed.timer_delay) {
		enc_btn_ctrl.long_pressed.timer_delay--;
		if(enc_btn_ctrl.long_pressed.timer_delay == 0) {
			// expired
			scheduler_send_event(main_tid, EV_ENC_LONG_PRESSED, NULL);
			// once for now
		}
	}
}
