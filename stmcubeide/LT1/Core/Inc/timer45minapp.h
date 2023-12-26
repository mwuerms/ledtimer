/*
 * timer1app.h
 *
 *  Created on: 01.10.2023
 *      Author: Martin
 */

#ifndef INC_TIMER1APP_H_
#define INC_TIMER1APP_H_

#include "mainapp.h"

void timer45minapp_Init(void);
void timer45minapp_Start(void);
void timer45minapp_Stop(void);

void timer45minapp_ProcessEvents(uint32_t events);

#endif /* INC_TIMER1APP_H_ */
