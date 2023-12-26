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
/*
static uint32_t timer45minapp_timer_nr;

static enum {
	welcome = 0,
	set_time,
	count_down_time,
	pause,
	alarm,
	alarm2
} timer45minapp_state;

static struct {
	uint32_t secs_total;
	uint8_t mins;
	uint8_t secs;
	uint8_t colon;
	uint8_t fill_dots;
} timer45minapp_time;
*/

static struct {
	uint32_t timer_nr;
	enum {
		welcome = 0,
		set_time,
		count_down_time,
		pause,
		alarm,
		alarm2
	} state;
	struct {
		uint32_t secs_total;
		uint8_t mins;
		uint8_t secs;
		uint8_t colon;
		uint8_t fill_dots;
	} time;
	uint16_t welcome_cnt;
} timer45minapp_ctrl;
#define TIMER1APP_FILL_DOTS_FULL	(28)

void timer45minapp_Init(void) {
	return;
}

void timer45minapp_Start(void) {
	timer45minapp_ctrl.state = welcome;
	dispBuffer_Clear();
	dispBuffer_AddString("45min");
	timer45minapp_ctrl.time.secs_total = 0;
	timer45minapp_ctrl.time.mins = 45;
	timer45minapp_ctrl.time.secs = 0;
	timer45minapp_ctrl.time.colon = 1;
	timer45minapp_ctrl.time.fill_dots = 0;
	timer45minapp_ctrl.welcome_cnt = 1;
	timer45minapp_ctrl.timer_nr = lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_TIMER1APP_TIME);
}

void timer45minapp_Stop(void) {
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
void timer45minapp_ProcessEvents(uint32_t events) {
	gpio_GetCopyOfInputStates(gpio_states);

	switch(timer45minapp_ctrl.state) {
	// ------------------------------------------------------------------------------
	case welcome:
		if(events & EV_TIMER1APP_TIME) {
			if(timer45minapp_ctrl.welcome_cnt == 0) {
				timer45minapp_ctrl.state = set_time;
				dispBuffer_ShowTime(timer45minapp_ctrl.time.mins, timer45minapp_ctrl.time.secs, timer45minapp_ctrl.time.colon);
			}
			else {
				timer45minapp_ctrl.welcome_cnt--;
				timer45minapp_ctrl.timer_nr = lptim_AddSingleEvent(LPTIM_PERIODE_1S, EV_TIMER1APP_TIME);
			}
		}
		if(events & EV_BUTTON_PRESSED) {
			timer45minapp_ctrl.state = set_time;
			lptim_RemoveEvent(timer45minapp_ctrl.timer_nr);
			dispBuffer_ShowTime(timer45minapp_ctrl.time.mins, timer45minapp_ctrl.time.secs, timer45minapp_ctrl.time.colon);
		}
		break;

	// ------------------------------------------------------------------------------
	case set_time:
		if(events & EV_BUTTON_PRESSED) {
			if( (gpio_states[GPIO_INDEX_BTN_UP0] == GPIO_STATE_BTN_SHORT_PRESSED) ||
				(gpio_states[GPIO_INDEX_BTN_UP0] == GPIO_STATE_BTN_LONG_PRESSED)) {
				// mins +10
				timer45minapp_ctrl.time.mins = _inc_10_max(timer45minapp_ctrl.time.mins, 9);
			}
			if( (gpio_states[GPIO_INDEX_BTN_UP1] == GPIO_STATE_BTN_SHORT_PRESSED) ||
				(gpio_states[GPIO_INDEX_BTN_UP1] == GPIO_STATE_BTN_LONG_PRESSED)) {
				// mins +1
				timer45minapp_ctrl.time.mins = _inc_1_max(timer45minapp_ctrl.time.mins, 9);
			}
			if( (gpio_states[GPIO_INDEX_BTN_UP2] == GPIO_STATE_BTN_SHORT_PRESSED) ||
				(gpio_states[GPIO_INDEX_BTN_UP2] == GPIO_STATE_BTN_LONG_PRESSED)) {
				// secs +10
				timer45minapp_ctrl.time.secs = _inc_10_max(timer45minapp_ctrl.time.secs, 5);
			}
			if( (gpio_states[GPIO_INDEX_BTN_UP3] == GPIO_STATE_BTN_SHORT_PRESSED) ||
				(gpio_states[GPIO_INDEX_BTN_UP3] == GPIO_STATE_BTN_LONG_PRESSED)) {
				// secs +1
				timer45minapp_ctrl.time.secs = _inc_1_max(timer45minapp_ctrl.time.secs, 9);
			}
			if(gpio_states[GPIO_INDEX_BTN_PLAY] == GPIO_STATE_BTN_SHORT_PRESSED) {
				// start timer
				timer45minapp_ctrl.time.secs_total = timer45minapp_ctrl.time.mins * 60 + timer45minapp_ctrl.time.secs;
				timer45minapp_ctrl.time.colon = 1;
				timer45minapp_ctrl.time.fill_dots = TIMER1APP_FILL_DOTS_FULL;
				timer45minapp_ctrl.state = count_down_time;
				timer45minapp_ctrl.timer_nr = lptim_AddRepeatingEvent(LPTIM_PERIODE_0_5S, EV_TIMER1APP_TIME);
			}
			if(gpio_states[GPIO_INDEX_BTN_STOP] == GPIO_STATE_BTN_LONG_PRESSED) {
				// reset set time
				timer45minapp_ctrl.time.secs_total = 0;
				timer45minapp_ctrl.time.mins = 0;
				timer45minapp_ctrl.time.secs = 0;
				timer45minapp_ctrl.time.colon = 1;
				timer45minapp_ctrl.time.fill_dots = 0;
			}
			dispBuffer_UpdateTime(timer45minapp_ctrl.time.mins, timer45minapp_ctrl.time.secs, timer45minapp_ctrl.time.colon);
		}
		break;

	// ------------------------------------------------------------------------------
	case count_down_time:
		if(events & EV_TIMER1APP_TIME) {
			if(timer45minapp_ctrl.time.colon == 0) {
				timer45minapp_ctrl.time.colon = 1;
				timer45minapp_ctrl.time.secs_total--;
				if(timer45minapp_ctrl.time.secs == 0) {
					// secs done
					timer45minapp_ctrl.time.secs = 59;
					if(timer45minapp_ctrl.time.mins == 0) {
						// time is up!
						timer45minapp_ctrl.time.mins = 0;
						timer45minapp_ctrl.time.secs = 0;
						timer45minapp_ctrl.time.secs_total = 10;

						timer45minapp_ctrl.state = alarm;
						dispBuffer_Clear();
						dispBuffer_AddString("ALARM");
					}
					else {
						timer45minapp_ctrl.time.mins--;
					}
				}
				else {
					timer45minapp_ctrl.time.secs--;
				}
			}
			else {
				timer45minapp_ctrl.time.colon--;
			}
			dispBuffer_UpdateTime(timer45minapp_ctrl.time.mins, timer45minapp_ctrl.time.secs, timer45minapp_ctrl.time.colon);
		}
		if(events & EV_BUTTON_PRESSED) {
			if(gpio_states[GPIO_INDEX_BTN_PLAY] == GPIO_STATE_BTN_SHORT_PRESSED) {
				timer45minapp_ctrl.state = pause;
				lptim_RemoveEvent(timer45minapp_ctrl.timer_nr);
			}
			if(gpio_states[GPIO_INDEX_BTN_STOP] == GPIO_STATE_BTN_LONG_PRESSED) {
				lptim_RemoveEvent(timer45minapp_ctrl.timer_nr);
				timer45minapp_Start();
			}
		}
		break;

	// ------------------------------------------------------------------------------
	case pause:
		if(events & EV_BUTTON_PRESSED) {
			if(gpio_states[GPIO_INDEX_BTN_PLAY] == GPIO_STATE_BTN_SHORT_PRESSED) {
				timer45minapp_ctrl.state = count_down_time;
				timer45minapp_ctrl.timer_nr = lptim_AddRepeatingEvent(LPTIM_PERIODE_0_5S, EV_TIMER1APP_TIME);
			}
			if(gpio_states[GPIO_INDEX_BTN_STOP] == GPIO_STATE_BTN_LONG_PRESSED) {
				lptim_RemoveEvent(timer45minapp_ctrl.timer_nr);
				timer45minapp_Start();
			}
		}

		break;

	// ------------------------------------------------------------------------------
	case alarm:
		if(events & EV_TIMER1APP_TIME) {
			timer45minapp_ctrl.time.secs_total--;
			if(timer45minapp_ctrl.time.secs_total & 0x0001) {
				dispBuffer_Clear();
				dispBuffer_AddString("-----");
			}
			else {
				dispBuffer_Clear();
				dispBuffer_AddString("alarm");
			}
		}
		if(events & EV_BUTTON_PRESSED) {
			if ((gpio_states[GPIO_INDEX_BTN_STOP] == GPIO_STATE_BTN_SHORT_PRESSED) ||
				(gpio_states[GPIO_INDEX_BTN_STOP] == GPIO_STATE_BTN_LONG_PRESSED)) {
				lptim_RemoveEvent(timer45minapp_ctrl.timer_nr);
				timer45minapp_Start();
			}
		}
		break;

	// ------------------------------------------------------------------------------
	case alarm2:
		break;
	}
}
