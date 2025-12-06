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


static inline void encoder_setup_btn_timer(void) {
	LL_TIM_OC_SetCompareCH1(TIM_ENC, 250); // in ms
	LL_TIM_ClearFlag_CC1(TIM_ENC);
	LL_TIM_EnableIT_CC1(TIM_ENC);
	LL_TIM_OC_SetCompareCH2(TIM_ENC, 950); // in ms
	LL_TIM_ClearFlag_CC2(TIM_ENC);
	LL_TIM_EnableIT_CC2(TIM_ENC);
}

//static inline void encoder_restart_single_btn_timer(void) {
static inline void encoder_restart_btn_timer(void) {
	LL_TIM_SetAutoReload(TIM_ENC, 65535);
	LL_TIM_SetCounter(TIM_ENC, 0);
	LL_TIM_EnableCounter(TIM_ENC);
}

static inline void encoder_stop_btn_timer(void) {
	LL_TIM_DisableCounter(TIM_ENC);
}


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

	encoder_btn_use_int_only();

	//LL_GPIO_ResetOutputPin(ENC_BTN_GPIO_Port, ENC_BTN_Pin);
	//LL_GPIO_SetOutputPin(ENC_BTN_GPIO_Port, ENC_BTN_Pin);
}

void encoder_a_isr(void) {
	if(LL_GPIO_ReadInputPort(ENC_A_GPIO_Port) & ENC_A_Pin) {
		if(LL_GPIO_ReadInputPort(ENC_B_GPIO_Port) & ENC_B_Pin) {
			// A set, B set -> left
			scheduler_send_event(main_tid, EV_ENC_ROT_LEFT, NULL);
		}
		else {
			// A set, B reset -> right
			scheduler_send_event(main_tid, EV_ENC_ROT_RIGHT, NULL);
		}
	}
	else {
		if(LL_GPIO_ReadInputPort(ENC_B_GPIO_Port) & ENC_B_Pin) {
			// A reset, B set -> right
			scheduler_send_event(main_tid, EV_ENC_ROT_RIGHT, NULL);
		}
		else {
			// A reset, B reset -> left
			scheduler_send_event(main_tid, EV_ENC_ROT_LEFT, NULL);
		}
	}
}

void encoder_b_isr(void) {
	// nothing to do for now
}

#define ENC_BTN_CTRL_TYPE_SIMPLE (0)
#define ENC_BTN_CTRL_TYPE_TIMER (1)
#define ENC_BTN_CTRL_STATE_PRESSED  (0)
#define ENC_BTN_CTRL_STATE_RELEASED (1)
static volatile struct {
	uint8_t type;
	uint8_t btn_state;
	uint8_t pressed_cnt;
	uint8_t long_pressed_cnt;
} enc_btn_ctrl = {
	.type = ENC_BTN_CTRL_TYPE_SIMPLE,
	.btn_state = ENC_BTN_CTRL_STATE_RELEASED,
	.pressed_cnt = 0,
	.long_pressed_cnt = 0,
};

static uint16_t abc = 0;
void encoder_btn_isr(void) {
	if(enc_btn_ctrl.type == ENC_BTN_CTRL_TYPE_SIMPLE) {
		// simple, send only EV_ENC_SINGLE_PRESSED on press
		if((LL_GPIO_ReadInputPort(ENC_BTN_GPIO_Port) & ENC_BTN_Pin) == 0) {
			// btn is pressed
			scheduler_send_event(main_tid, EV_ENC_SINGLE_PRESSED, NULL);
		}
	}
	else {
		// more comples, use timing to debounce for EV_ENC_SINGLE_PRESSED
		// and create EV_ENC_DOUBLE_PRESSED and EV_ENC_LONG_PRESSED events as well
		if(LL_GPIO_ReadInputPort(ENC_BTN_GPIO_Port) & ENC_BTN_Pin) {
			// set -> released
			enc_btn_ctrl.btn_state = ENC_BTN_CTRL_STATE_RELEASED;
		}
		else {
			// reset -> pressed
			enc_btn_ctrl.btn_state = ENC_BTN_CTRL_STATE_PRESSED;
			enc_btn_ctrl.pressed_cnt++;
			encoder_restart_btn_timer();
			LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2);
		}
	}
}

void encoder_btn_timer_pressed_isr(void) {
	// expired
	if(LL_GPIO_ReadInputPort(ENC_BTN_GPIO_Port) & ENC_BTN_Pin) {
		// btn is released, if btn is still pressed -> skip
		if(enc_btn_ctrl.pressed_cnt == 1) {
			encoder_stop_btn_timer();
			scheduler_send_event(main_tid, EV_ENC_SINGLE_PRESSED, NULL);
		}
		else {
			// don't care how many, more than 1
			encoder_stop_btn_timer();
			scheduler_send_event(main_tid, EV_ENC_DOUBLE_PRESSED, NULL);
		}
	}
	enc_btn_ctrl.pressed_cnt = 0;
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2);
}

void encoder_btn_timer_long_pressed_isr(void){
	// expired
	if((LL_GPIO_ReadInputPort(ENC_BTN_GPIO_Port) & ENC_BTN_Pin) == 0) {
		// is still pressed
		scheduler_send_event(main_tid, EV_ENC_LONG_PRESSED, NULL);
	}
	encoder_stop_btn_timer();
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
}

void encoder_btn_use_int_only(void) {
	enc_btn_ctrl.type = ENC_BTN_CTRL_TYPE_SIMPLE;
}

void encoder_btn_use_debounce(void) {
	encoder_setup_btn_timer();
	enc_btn_ctrl.type = ENC_BTN_CTRL_TYPE_TIMER;
}
