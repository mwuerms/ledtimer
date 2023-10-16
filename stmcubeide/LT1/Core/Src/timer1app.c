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

static uint32_t timer1app_rep_timer_nr;

void timer1app_Init(void) {
	return;
}

void timer1app_Start(void) {
	dispBuffer_AddString("main_is_rolling!");
	timer1app_rep_timer_nr = lptim_AddRepeatingEvent(LPTIM_PERIODE_0_5S, EV_TIMER1APP_TIME);
}
void timer1app_Stop(void) {

}

static uint32_t timer1app_cnt = 0;
static uint8_t timer1app_disp_buffer[20];
void timer1app_ProcessGPIOEvents(uint8_t *gpio_events, uint32_t size) {
	return;
}

void timer1app_TimerEvents(uint32_t events) {
	timer1app_cnt++;
	uint32_t dd = timer1app_cnt/10;
	timer1app_disp_buffer[0] = '0';
	timer1app_disp_buffer[1] = '1';
	if(timer1app_cnt & 0x00000001)
		timer1app_disp_buffer[2] = ':';
	else
		timer1app_disp_buffer[2] = '_';
	timer1app_disp_buffer[3] = '0'+dd;
	timer1app_disp_buffer[3] = '0'+timer1app_cnt - dd*10;
	//display_ShowString("00:01");
	dispBuffer_ShowRows(timer1app_disp_buffer, 6);
	return;
}

