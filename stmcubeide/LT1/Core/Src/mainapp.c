/*
 * mainapp.c
 *
 *  Created on: 01.10.2023
 *      Author: Martin
 */

#include "mainapp.h"
#include "timer1app.h"
#include "gpio.h"
#include "dispBuffer.h"
#include "lptim.h"

static enum {
	mainapp = 0,
	timer1app
} mainapp_active_app;

void mainapp_Init(void) {
	mainapp_active_app = mainapp;
}

void mainapp_Start(void) {
	//dispBuffer_AddString("main_is_rolling!");
	//lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_MAINAPP_TIME);
}

uint8_t copy_gpio_states[GPIO_NB_INPUTS];
uint8_t display_gpio_states[GPIO_NB_INPUTS];
void mainapp_ProcessEvents(uint32_t events) {
	uint8_t n;
	switch(mainapp_active_app) {
	case mainapp:
		if(events & EV_MAINAPP_TIME) {
			static uint16_t delay_cnt = 10;
			if(delay_cnt == 0) {
				mainapp_active_app = timer1app;
				timer1app_Start();
			}
			else {
				delay_cnt--;
				lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_MAINAPP_TIME);
			}
		}
		if(events & EV_BUTTON_PRESSED) {
			// testing gpios
			gpio_GetCopyOfInputStates(copy_gpio_states);
			for(n = 0; n <= GPIO_INDEX_BTN_STOP; n++) {
				if(copy_gpio_states[n] == GPIO_STATE_BTN_PRESSED) {
					display_gpio_states[n] |= 0x02;
					dispBuffer_ChangeRow(display_gpio_states[n], n);
				}
				if(copy_gpio_states[n] == GPIO_STATE_BTN_RELEASED) {
					display_gpio_states[n] = 0x01;
					dispBuffer_ChangeRow(display_gpio_states[n], n);
				}
				if(copy_gpio_states[n] == GPIO_STATE_BTN_SHORT_PRESSED) {
					display_gpio_states[n] |= 0x04;
					dispBuffer_ChangeRow(display_gpio_states[n], n);
				}
				if(copy_gpio_states[n] == GPIO_STATE_BTN_LONG_PRESSED) {
					display_gpio_states[n] |= 0x08;
					dispBuffer_ChangeRow(display_gpio_states[n], n);
				}
			}
		}
		break;
	case timer1app:
		timer1app_ProcessEvents(events);
		break;
	}
}
