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

static struct {
	uint32_t secs_total;
	uint8_t mins;
	uint8_t secs;
	uint8_t colon;
	uint8_t fill_dots;
} timer1app_time;
#define TIMER1APP_FILL_DOTS_FULL	(28)

void timer1app_Init(void) {
	return;
}

static uint16_t timer1app_welcome_cnt;
void timer1app_Start(void) {
	timer1app_state = welcome;
	dispBuffer_Clear();
	dispBuffer_AddString("timer1app");
	timer1app_welcome_cnt = 1;
	timer1app_timer_nr = lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_TIMER1APP_TIME);
}

void timer1app_Stop(void) {
	return;
}

static uint8_t _inc_max(uint8_t x, uint8_t max) {
	x++;
	if(x > max) {
		return 0;
	}
	return x;
}


static uint8_t _inc_10_max(uint8_t x, uint8_t max10) {
	uint8_t x10 = x / 10;
	uint8_t x1  = x  - (x10 * 10);
	x10 = _inc_max(x10, max10);
	return (x10 * 10) + x1;
}

static uint8_t _inc_1_max(uint8_t x, uint8_t max1) {
	uint8_t x10 = x / 10;
	uint8_t x1  = x  - (x10 * 10);
	x1 = _inc_max(x1, max1);
	return (x10 * 10) + x1;
}

static uint8_t gpio_states[GPIO_NB_INPUTS];
void timer1app_ProcessEvents(uint32_t events) {
	gpio_GetCopyOfInputStates(gpio_states);
	switch(timer1app_state) {
	case welcome:
		if(events & EV_TIMER1APP_TIME) {
			if(timer1app_welcome_cnt == 0) {
				timer1app_state = set_time;
				timer1app_time.secs_total = 0;
				timer1app_time.mins = 11;
				timer1app_time.secs = 11;
				timer1app_time.colon = 1;
				timer1app_time.fill_dots = 0;
				dispBuffer_ShowTime(timer1app_time.mins, timer1app_time.secs, timer1app_time.colon);
			}
			else {
				timer1app_welcome_cnt--;
				timer1app_timer_nr = lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_TIMER1APP_TIME);
			}
		}
		if(events & EV_BUTTON_PRESSED) {
			timer1app_state = set_time;
			lptim_RemoveEvent(timer1app_timer_nr);
			timer1app_time.secs_total = 0;
			timer1app_time.mins = 0;
			timer1app_time.secs = 0;
			timer1app_time.colon = 1;
			timer1app_time.fill_dots = 0;
			dispBuffer_ShowTime(timer1app_time.mins, timer1app_time.secs, timer1app_time.colon);
		}
		break;
	case set_time:
		if(events & EV_BUTTON_PRESSED) {
			if( (gpio_states[GPIO_INDEX_BTN_UP0] == GPIO_STATE_BTN_SHORT_PRESSED) ||
				(gpio_states[GPIO_INDEX_BTN_UP0] == GPIO_STATE_BTN_LONG_PRESSED)) {
				// mins +10
				timer1app_time.mins = _inc_10_max(timer1app_time.mins, 9);
			}
			if( (gpio_states[GPIO_INDEX_BTN_UP1] == GPIO_STATE_BTN_SHORT_PRESSED) ||
				(gpio_states[GPIO_INDEX_BTN_UP1] == GPIO_STATE_BTN_LONG_PRESSED)) {
				// mins +1
				timer1app_time.mins = _inc_1_max(timer1app_time.mins, 9);
			}
			if( (gpio_states[GPIO_INDEX_BTN_UP2] == GPIO_STATE_BTN_SHORT_PRESSED) ||
				(gpio_states[GPIO_INDEX_BTN_UP2] == GPIO_STATE_BTN_LONG_PRESSED)) {
				// secs +10
				timer1app_time.secs = _inc_10_max(timer1app_time.secs, 5);
			}
			if( (gpio_states[GPIO_INDEX_BTN_UP3] == GPIO_STATE_BTN_SHORT_PRESSED) ||
				(gpio_states[GPIO_INDEX_BTN_UP3] == GPIO_STATE_BTN_LONG_PRESSED)) {
				// secs +1
				timer1app_time.secs = _inc_1_max(timer1app_time.secs, 9);
			}
			if(gpio_states[GPIO_INDEX_BTN_PLAY] == GPIO_STATE_BTN_SHORT_PRESSED) {
				// start timer
				timer1app_time.secs_total = timer1app_time.mins * 60 + timer1app_time.secs;
				timer1app_time.colon = 1;
				timer1app_time.fill_dots = TIMER1APP_FILL_DOTS_FULL;
				timer1app_state = count_down_time;
				timer1app_timer_nr = lptim_AddRepeatingEvent(LPTIM_PERIODE_0_5S, EV_TIMER1APP_TIME);
			}
			if(gpio_states[GPIO_INDEX_BTN_STOP] == GPIO_STATE_BTN_LONG_PRESSED) {
				// reset set time
				timer1app_time.secs_total = 0;
				timer1app_time.mins = 0;
				timer1app_time.secs = 0;
				timer1app_time.colon = 1;
				timer1app_time.fill_dots = 0;
			}
			dispBuffer_UpdateTime(timer1app_time.mins, timer1app_time.secs, timer1app_time.colon);
		}
		break;
	case count_down_time:
		if(events & EV_TIMER1APP_TIME) {
			if(timer1app_time.colon == 0) {
				timer1app_time.colon = 1;
				timer1app_time.secs_total--;
				if(timer1app_time.secs == 0) {
					// secs done
					timer1app_time.secs = 59;
					if(timer1app_time.mins == 0) {
						// time is up!
						timer1app_time.mins = 0;
						timer1app_time.secs = 0;
					}
					else {
						timer1app_time.mins--;
					}
				}
				else {
					timer1app_time.secs--;
				}
			}
			else {
				timer1app_time.colon--;
			}
			dispBuffer_UpdateTime(timer1app_time.mins, timer1app_time.secs, timer1app_time.colon);
		}
		break;
	case pause:
		break;
	case alarm:
		break;
	case alarm2:
		break;
	}
}
