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
	dispBuffer_AddString("main_is_rolling!");
	lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_MAINAPP_TIME);
}

void mainapp_ProcessEvents(uint32_t events) {
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
		break;
	case timer1app:
		timer1app_ProcessEvents(events);
		break;
	}
}
