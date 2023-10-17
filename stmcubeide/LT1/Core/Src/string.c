/*
 * string.c
 *
 *  Created on: 17.10.2023
 *      Author: Martin
 */
#include "string.h"

void string_uint8_to_string(uint8_t value, char *str) {
	uint8_t digit_pos, use_char;
	int8_t digits[] = {100, 10, 1};
	uint8_t digit_value;
	use_char = 0;
	// no sign
	if(value == 0) {
		// only append '0', and done here
		*str++ = '0';
		*str++ = 0;
		return;
	}
	for(digit_pos = 0; digit_pos < (sizeof(digits)/sizeof(digits[0])); digit_pos++) {
		digit_value = (uint8_t)(value/digits[digit_pos]);
		if((digit_value != 0) || (use_char != 0)) {
			use_char = 1;
			*str++ = '0' + digit_value;
			value -= digit_value * digits[digit_pos];
		}
	}
	*str++ = 0;
}

void string_uint8_to_string_2digits(uint8_t value, char *str) {
	uint8_t digit_value;
	// no sign
	if(value == 0) {
		// only append '0', and done here
		*str++ = '0';
		*str++ = '0';
		*str++ = 0;
		return;
	}
	if(value > 99) {
		// max, set to '99'
		*str++ = '9';
		*str++ = '9';
		*str++ = 0;
		return;
	}
	digit_value = (uint8_t)(value/10);
	*str++ = '0' + digit_value;
	value -= digit_value * 10;

	digit_value = (uint8_t)(value/1);
	*str++ = '0' + digit_value;
	value -= digit_value * 1;
	*str++ = 0;
}

void string_buffer_append_int16(int16_t value) {
	return;
#if 0
	uint16_t digit_pos, use_char;
	int16_t digits[] = {10000, 1000, 100, 10, 1};
	uint8_t digit_value;
	use_char = 0;
	// sign
	if(value < 0) {
		value *= -1;
		if(string_buffer_append_char('-') == 0) {
			// buffer full, stop
			return;
		}
	}
	if(value == 0) {
		// only append '0', and done here
		string_buffer_append_char('0');
		return;
	}
	for(digit_pos = 0; digit_pos < (sizeof(digits)/sizeof(digits[0])); digit_pos++) {
		digit_value = (uint8_t)(value/digits[digit_pos]);
		if((digit_value != 0) || (use_char != 0)) {
			use_char = 1;
			if(string_buffer_append_char('0'+digit_value) == 0) {
				// buffer full, stop
				return;
			}
			value -= digit_value * digits[digit_pos];
		}
	}
#endif
}
