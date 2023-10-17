/*
 * timer1app.c
 *
 *  Created on: 01.10.2023
 *      Author: Martin
 */

#include "timer1app.h"
#include "gpio.h"
#include "dispBuffer.h"
#include "lptim.h"
#include "gpio.h"

static uint32_t timer1app_timer_nr;

static enum {
	welcome = 0,
	set_time,
	count_down_time,
	pause,
	alarm,
	alarm2
} timer1app_state;

void timer1app_Init(void) {
	return;
}

static uint16_t timer1app_welcome_cnt;
void timer1app_Start(void) {
	timer1app_state = welcome;
	dispBuffer_Clear();
	dispBuffer_AddString("timer1app");
	timer1app_welcome_cnt = 2;
	timer1app_timer_nr = lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_TIMER1APP_TIME);
}

void timer1app_Stop(void) {
	return;
}

static uint32_t timer1app_cnt = 0;
static uint8_t timer1app_disp_buffer[20];
static uint8_t* gpio_states;
void timer1app_ProcessEvents(uint32_t events) {
	gpio_GetCopyOfInputStates(gpio_states);
	switch(timer1app_state) {
	case welcome:
		if(events & EV_TIMER1APP_TIME) {
			if(timer1app_welcome_cnt == 0) {
				timer1app_state = set_time;
				dispBuffer_ShowTime(23, 56, 1);
				timer1app_timer_nr = lptim_AddRepeatingEvent(LPTIM_PERIODE_0_5S, EV_TIMER1APP_TIME);
			}
			else {
				timer1app_welcome_cnt--;
				timer1app_timer_nr = lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_TIMER1APP_TIME);
			}
		}
		if(events & EV_BUTTON_PRESSED) {
			timer1app_state = set_time;
			lptim_RemoveEvent(timer1app_timer_nr);
			dispBuffer_ShowTime(12, 34, 1);
			timer1app_timer_nr = lptim_AddRepeatingEvent(LPTIM_PERIODE_0_5S, EV_TIMER1APP_TIME);
		}
		break;
	case set_time:
		break;
	case count_down_time:
		break;
	case pause:
		break;
	case alarm:
		break;
	case alarm2:
		break;
	}
}
