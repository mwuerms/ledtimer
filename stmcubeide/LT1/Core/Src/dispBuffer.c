/*
 * dispBuffer.c
 *
 *  Created on: 16.10.2023
 *      Author: Martin
 */

#include "main.h"
#include "dispBuffer.h"
#include "display.h"
#include "fontmonospace.h"
#include "string.h"

// - private ------------------------------------------------------------------------
static disp_buffer_t disp_buffer;

// - public -------------------------------------------------------------------------

void dispBuffer_Init(void) {
	return;
}

disp_buffer_t *dispBuffer_Get(void) {
	return &disp_buffer;
}

uint16_t dispBuffer_Clear(void) {
	for(disp_buffer.wr_index = 0; disp_buffer.wr_index < DISP_BUFFER_SIZE; disp_buffer.wr_index++) {
		disp_buffer.buffer[disp_buffer.wr_index] = 0;
	}
	disp_buffer.wr_index = 0;
	return RET_SUCCESS;
}

uint8_t corr_wr_index[] = {
	 4,  3,  2,  1,  0,
	 9,  8,  7,  6,  5,
	14, 13, 12, 11, 10,
	19, 18, 17, 16, 15,
	24, 23, 22, 21, 20,
	29, 28, 27, 26, 25,
	34, 33, 32, 31, 30,
	39, 38, 37, 36, 35,
	44, 43, 42, 41, 40,
	49, 48, 47, 46, 45,
	54, 53, 52, 51, 50,
	59, 58, 57, 56, 55,
	64, 63, 62, 61, 60,
};
uint16_t dispBuffer_AddRow(uint8_t row_data) {
	if((disp_buffer.wr_index + 1) >= DISP_BUFFER_SIZE)
			return RET_ERROR;
	// bugfix, 2023-12-12, ME: order row0 ... row6 is inverted -> fix: re-arange data
	uint8_t n, temp;
	temp = row_data;
	row_data = 0;
	for(n = 7; n; n--) {
		row_data <<= 1;
		row_data |= (temp & 0x01);
		temp >>= 1;
	}

	// bugfix, 2023-12-13, ME: order col0 ... col4 is also inverted ->
	// datasheet did not specify the correct order, I tried beforehand, but got it mixed up anyway ... such things happen :-)
	// not this simple way ,-( disp_buffer.buffer[disp_buffer.wr_index++] = row_data;
	uint8_t cwr_index = corr_wr_index[disp_buffer.wr_index++];
	disp_buffer.buffer[cwr_index] = row_data;
	return RET_SUCCESS;
}

uint16_t dispBuffer_AddRows(uint8_t *row_data, uint16_t nb_rows) {
	uint16_t n = 0;
	for(n = 0; n < nb_rows; n++) {
		if(dispBuffer_AddRow(row_data[n]) == RET_ERROR) {
			return RET_ERROR;
		}
	}
	return RET_SUCCESS;
}

uint16_t dispBuffer_ShowRows(uint8_t *row_data, uint16_t nb_rows) {
	dispBuffer_Clear();
	return dispBuffer_AddRows(row_data, nb_rows);
}

uint16_t dispBuffer_AddChar(char c) {
	if((disp_buffer.wr_index + 6) >= DISP_BUFFER_SIZE)
		return RET_ERROR;
	dispBuffer_AddRows((uint8_t *)(font[c-0x20]), 5);
	dispBuffer_AddRow(FONT_CHAR_SEPARATOR);
	return RET_SUCCESS;
}

uint16_t dispBuffer_AddString(char *str) {
	while(*str != 0) {
		if(dispBuffer_AddChar(*str) == RET_ERROR) {
			return RET_ERROR;
		}
		str++;
	}
	return RET_SUCCESS;
}

uint16_t dispBuffer_GetNbFreeRows(void) {
	return DISP_BUFFER_SIZE - disp_buffer.wr_index;
}

uint16_t dispBuffer_ChangeRow(uint8_t row_data, uint16_t pos) {
	if(pos >= disp_buffer.wr_index) {
		return RET_ERROR;
	}
	disp_buffer.buffer[pos] = row_data;
	return RET_SUCCESS;
}

uint16_t dispBuffer_ChangeRows(uint8_t *row_data, uint16_t nb_rows, uint16_t pos) {
	uint16_t n = 0;
	for(n = 0; n < nb_rows; n++, pos++) {
		if(dispBuffer_ChangeRow(row_data[n], pos) == RET_ERROR) {
			return RET_ERROR;
		}
	}
	return RET_SUCCESS;
}

uint16_t dispBuffer_ChangeChar(char c, uint16_t pos) {
	if((pos + 6) >= DISP_BUFFER_SIZE)
		return RET_ERROR;
	dispBuffer_ChangeRows((uint8_t *)(font[c-0x20]), 5, pos);
	dispBuffer_ChangeRow(FONT_CHAR_SEPARATOR, pos+5);
	return RET_SUCCESS;
}

uint16_t dispBuffer_ChangeString(char *str, uint16_t pos) {
	while(*str != 0) {
		if(dispBuffer_ChangeChar(*str, pos) == RET_ERROR) {
			return RET_ERROR;
		}
		str++;
		pos =+ 6;
	}
	return RET_SUCCESS;
}

uint16_t dispBuffer_ShowTime(uint8_t mins, uint8_t secs, uint8_t colon) {
	char str_buffer[4];
	dispBuffer_Clear();
	// fill dots
#warning "FILL DOTS HERE"
	// mins
	string_uint8_to_string_2digits(mins, str_buffer);
	dispBuffer_AddString(str_buffer);
	// colon
	dispBuffer_AddRow(FONT_CHAR_SEPARATOR);
	if(colon) {
		dispBuffer_AddRow(font[':'-0x20][2]);
	}
	else {
		dispBuffer_AddRow(FONT_CHAR_SEPARATOR);
	}
	dispBuffer_AddRow(FONT_CHAR_SEPARATOR);
	// secs
	string_uint8_to_string_2digits(secs, str_buffer);
	dispBuffer_AddString(str_buffer);

	return RET_SUCCESS;
}

uint16_t dispBuffer_UpdateTime(uint8_t mins, uint8_t secs, uint8_t colon) {
	char str_buffer[4];
	uint16_t pos = 0;
	//disp_buffer.wr_index = 0;
	// mins
	string_uint8_to_string_2digits(mins, str_buffer);
	dispBuffer_ChangeString(str_buffer, pos);
	pos += 2*6;
	// colon
	dispBuffer_ChangeRow(FONT_CHAR_SEPARATOR, pos);
	pos++;
	if(colon) {
		dispBuffer_ChangeRow(font[':'-0x20][2], pos);
	}
	else {
		dispBuffer_ChangeRow(FONT_CHAR_SEPARATOR, pos);
	}
	pos++;
	dispBuffer_ChangeRow(FONT_CHAR_SEPARATOR, pos);
	pos++;
	// secs
	string_uint8_to_string_2digits(secs, str_buffer);
	dispBuffer_ChangeString(str_buffer, pos);

	return RET_SUCCESS;
}
