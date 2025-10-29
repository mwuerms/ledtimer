/*
 * disp.c
 *
 *  Created on: Oct 22, 2025
 *      Author: martin
 */

#include "main.h"
#include "disp.h"

// - private functions ---------------------------------------------------------

#define DISP_TIM TIM22
#define DISP_NB_LEDS (23)
#define DISP_MAX_BRIGHTNESS (99) // 0 ... 99

static volatile struct {
	uint32_t led_mask;
	uint32_t frame, out_frame;
	uint8_t led_index;
	uint8_t brightness;
} disp_ctrl;

static inline void disp_disable_all_leds(void) {
	LL_GPIO_SetPinMode(P1_GPIO_Port, P1_Pin, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(P2_GPIO_Port, P2_Pin, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(P3_GPIO_Port, P3_Pin, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(P4_GPIO_Port, P4_Pin, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(P5_GPIO_Port, P5_Pin, LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(P6_GPIO_Port, P6_Pin, LL_GPIO_MODE_INPUT);
}

// all GPIOs on same port -> easier
static const uint32_t disp_gpios[] = {P1_Pin, P2_Pin, P3_Pin, P4_Pin, P5_Pin, P6_Pin};
static const uint8_t led_index_to_disp_gpio[DISP_NB_LEDS][2] = {
// out high, out low
		{0, 1},
		{0, 2},
		{0, 3},
		{0, 4},
		{0, 5},
		{1, 0},
		{1, 2},
		{1, 3},
		{1, 4},
		{1, 5},
		{2, 0},
		{2, 1},
		{2, 3},
		{2, 4},
		{2, 5},
		{3, 0},
		{3, 1},
		{3, 2},
		{3, 4},
		{3, 5},
		{4, 0},
		{4, 1},
		{4, 2},
};

static inline void disp_enable_led(uint8_t led_index) {
	if(led_index >= DISP_NB_LEDS) {
		// invalid LED
		return;
	}
	LL_GPIO_SetOutputPin(P1_GPIO_Port,   disp_gpios[(led_index_to_disp_gpio[led_index][0])]);
	LL_GPIO_SetPinMode(P1_GPIO_Port,     disp_gpios[(led_index_to_disp_gpio[led_index][0])], LL_GPIO_MODE_OUTPUT);
	LL_GPIO_ResetOutputPin(P1_GPIO_Port, disp_gpios[(led_index_to_disp_gpio[led_index][1])]);
	LL_GPIO_SetPinMode(P1_GPIO_Port,     disp_gpios[(led_index_to_disp_gpio[led_index][1])], LL_GPIO_MODE_OUTPUT);
}

static inline void disp_disable_led(uint8_t led_index) {
	if(led_index >= DISP_NB_LEDS) {
		// invalid LED
		return;
	}
	LL_GPIO_SetPinMode(P1_GPIO_Port, disp_gpios[(led_index_to_disp_gpio[led_index][0])], LL_GPIO_MODE_INPUT);
	LL_GPIO_SetPinMode(P1_GPIO_Port, disp_gpios[(led_index_to_disp_gpio[led_index][0])], LL_GPIO_MODE_INPUT);
}

static inline void disp_clear_frame(void) {
	// TODO was ist mit der D23 -> "Aktivity"
	disp_ctrl.frame = 0;
}

static const uint32_t led_frame_for_digit[] = {
	0x000007DFU, // 0
	0x00000780U, // 1
	0x000005FDU, // 2
	0x000007F9U, // 3
	0x000007A3U, // 4
	0x000006DBU, // 5
	0x000006FFU, // 6
	0x00000791U, // 7
	0x000007FFU, // 8
	0x000007FBU, // 9
};

static inline void disp_add_digit_to_frame(uint8_t digit, uint8_t pos) {
	uint32_t f;
	if(digit > 9) {
		// error, invalid digit
		return;
	}
	f = led_frame_for_digit[digit];
	if(pos == 0) {
		// 1er
		disp_ctrl.frame &= ~(0x000007FFU << 11);
		disp_ctrl.frame |=  (f << 11);
	}
	else {
		// 10er
		disp_ctrl.frame &= ~(0x000007FFU);
		disp_ctrl.frame |=  (f);
	}
}

static inline void disp_set_act_in_frame(uint8_t act) {
	if(act) {
		// set on
		disp_ctrl.frame |=  (1 << 22);
	}
	else {
		// set off
		disp_ctrl.frame &= ~(1 << 22);
	}
}

// - public functions ----------------------------------------------------------

void disp_init(void) {
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
	disp_off();
	disp_ctrl.led_index = 0;
	disp_set_brightness(100);
	disp_show_number(12);
	disp_activity_on();
	disp_on();
	LL_TIM_EnableCounter(DISP_TIM);
}

void disp_set_brightness(uint8_t bright) {
	if(bright > DISP_MAX_BRIGHTNESS) {
		bright = DISP_MAX_BRIGHTNESS;
	}
	disp_ctrl.brightness = bright;
	LL_TIM_OC_SetCompareCH1(DISP_TIM, (uint32_t)disp_ctrl.brightness);
}

void disp_on(void) {
	// set_gpio
	LL_TIM_ClearFlag_UPDATE(DISP_TIM);
	LL_TIM_EnableIT_UPDATE(DISP_TIM);
	// reset gpio
	LL_TIM_ClearFlag_CC1(DISP_TIM);
	LL_TIM_EnableIT_CC1(DISP_TIM);
	return;
}
void disp_off(void) {
	disp_disable_all_leds();
	LL_TIM_ClearFlag_UPDATE(DISP_TIM);
	LL_TIM_DisableIT_UPDATE(DISP_TIM);
	// reset gpio
	LL_TIM_ClearFlag_CC1(DISP_TIM);
	LL_TIM_DisableIT_CC1(DISP_TIM);
}

void disp_show_number(uint8_t num) {
	disp_clear_frame();
	// 10er
	uint8_t digit = num / 10;
	disp_add_digit_to_frame(digit, 1);
	// 1er
	digit = num - digit * 10;
	disp_add_digit_to_frame(digit, 0);
	disp_ctrl.out_frame = disp_ctrl.frame;
	if(disp_ctrl.out_frame == 0) {
		// nothing to display -> disp_off
		disp_off();
	}
	else {
		disp_on();
	}
}

void disp_set_frame(uint32_t f) {
	disp_ctrl.frame = f;
	disp_ctrl.out_frame = disp_ctrl.frame;
}

// disp_hide_number

void disp_activity_on(void) {
	disp_set_act_in_frame(1);
	disp_ctrl.out_frame = disp_ctrl.frame;
}

void disp_activity_off(void) {
	disp_set_act_in_frame(0);
	disp_ctrl.out_frame = disp_ctrl.frame;
}


void disp_timer_isr_gpio_set(void) {
	if(disp_ctrl.led_index >= DISP_NB_LEDS) {
		disp_ctrl.led_index = 0;
		disp_ctrl.led_mask = 0x00000001;
	}
	else {
		disp_ctrl.led_index++;
		disp_ctrl.led_mask <<= 1;
	}
	if(disp_ctrl.out_frame & disp_ctrl.led_mask) {
		disp_enable_led(disp_ctrl.led_index);
	}
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2);
	return;
}

void disp_timer_isr_gpio_reset(void) {
	disp_disable_led(disp_ctrl.led_index);
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
	return;
}
