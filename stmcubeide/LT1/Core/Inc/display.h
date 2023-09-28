/*
 * display.h
 *
 *  Created on: Sep 27, 2023
 *      Author: Martin
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

// - public ----------------------------------
#include <stdint.h>

void display_Init(void);
void display_On(void);
void display_Off(void);
void display_Update(void);

void display_ShowString(char *str);

#endif /* INC_DISPLAY_H_ */
