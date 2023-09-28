/*
 * macros.h
 *
 *  Created on: Sep 28, 2023
 *      Author: Martin
 */

#ifndef INC_MACROS_H_
#define INC_MACROS_H_

#define BIT(n)	(1 << n)
#define RET_SUCCESS	0
#define RET_ERROR	1

#define ENTER_ATOMIC_NVIC_IRQn(irqn, restore) do { \
			restore = NVIC_GetEnableIRQ(irqn); \
			HAL_NVIC_DisableIRQ(irqn); \
		} while (0)

#define LEAVE_ATOMIC_NVIC_IRQn(irqn, restore) do { \
			if(restore) \
				HAL_NVIC_EnableIRQ(irqn); \
		} while(0)
#endif /* INC_MACROS_H_ */
