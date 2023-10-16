/*
 * timer1app.h
 *
 *  Created on: 01.10.2023
 *      Author: Martin
 */

#ifndef INC_TIMER1APP_H_
#define INC_TIMER1APP_H_

#include "mainapp.h"

void timer1app_Init(void);
void timer1app_Start(void);
void timer1app_Stop(void);
void timer1app_ProcessGPIOEvents(uint8_t *gpio_events, uint32_t size);
void timer1app_TimerEvents(uint32_t events);

#endif /* INC_TIMER1APP_H_ */
