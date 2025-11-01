/*
 * disp.c
 *
 *  Created on: Oct 22, 2025
 *      Author: martin
 */

#ifndef INC_DISP_C_
#define INC_DISP_C_

void disp_init(void);
void disp_on(void);
void disp_off(void);
void disp_set_brightness(uint8_t bright);

void disp_show_number(uint8_t num);
void disp_number_on();
void disp_number_off();
void disp_activity_on(void);
void disp_activity_off(void);

void disp_timer_isr_gpio_set(void);
void disp_timer_isr_gpio_reset(void);

#endif /* INC_DISP_C_ */
