/*
 * encoder.h
 *
 *  Created on: Oct 22, 2025
 *      Author: martin
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

void encoder_init(void);
void encoder_a_isr(void);
void encoder_b_isr(void);
void encoder_btn_isr(void);
void encoder_btn_timer_pressed_isr(void);
void encoder_btn_timer_long_pressed_isr(void);
void encoder_btn_use_int_only(void);
void encoder_btn_use_debounce(void);

#endif /* INC_ENCODER_H_ */
