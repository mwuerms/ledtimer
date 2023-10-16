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

uint16_t dispBuffer_AddRow(uint8_t row_data) {
	if((disp_buffer.wr_index + 1) >= DISP_BUFFER_SIZE)
			return RET_ERROR;
	disp_buffer.buffer[disp_buffer.wr_index++] = row_data;
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

