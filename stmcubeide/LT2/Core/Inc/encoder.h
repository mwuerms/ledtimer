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
void encoder_timer_isr(void);

#endif /* INC_ENCODER_H_ */
