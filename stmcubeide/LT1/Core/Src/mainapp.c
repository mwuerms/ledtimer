/*
 * mainapp.c
 *
 *  Created on: 01.10.2023
 *      Author: Martin
 */

#include "mainapp.h"
#include "gpio.h"
#include "dispBuffer.h"
#include "lptim.h"

void mainapp_Init(void) {
	return;
}

void mainapp_Start(void) {
	dispBuffer_AddString("main_is_rolling!");
	lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_MAINAPP_TIME);
}

void mainapp_ProcessGPIOEvents(uint8_t *gpio_events, uint32_t size) {
	return;
}

void mainapp_TimerEvents(uint32_t events) {
	timer1app_Start();
}
