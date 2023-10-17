/*
 * string.h
 *
 *  Created on: 17.10.2023
 *      Author: Martin
 */

#ifndef INC_STRING_H_
#define INC_STRING_H_

#include "stdint.h"

void string_uint8_to_string(uint8_t value, char *str);
void string_uint8_to_string_2digits(uint8_t value, char *str);
void string_buffer_append_int16(int16_t value);

#endif /* INC_STRING_H_ */
