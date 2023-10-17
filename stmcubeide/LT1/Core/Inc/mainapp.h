/*
 * mainapp.h
 *
 *  Created on: 01.10.2023
 *      Author: Martin
 */

#ifndef INC_MAINAPP_H_
#define INC_MAINAPP_H_

#include <stdint.h>
#include "main.h"

void mainapp_Init(void);
void mainapp_Start(void);
void mainapp_ProcessEvents(uint32_t events);

#endif /* INC_MAINAPP_H_ */
