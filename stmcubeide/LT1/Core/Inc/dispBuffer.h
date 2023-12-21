/*
 * dispBuffer.h
 *
 *  Created on: 16.10.2023
 *      Author: Martin
 */

#ifndef INC_DISPBUFFER_H_
#define INC_DISPBUFFER_H_

// - public ----------------------------------
#include <stdint.h>

#define DISP_BUFFER_SIZE	(32*2)
typedef struct {
	uint8_t buffer[DISP_BUFFER_SIZE];
	uint8_t wr_index;
	uint8_t rd_index, rd_origin;
} disp_buffer_t;

void dispBuffer_Init(void);
disp_buffer_t *dispBuffer_Get(void);
uint16_t dispBuffer_Clear(void);
uint16_t dispBuffer_AddColumn(uint8_t col_data);
uint16_t dispBuffer_AddColumns(uint8_t *col_data, uint16_t nb_col);
uint16_t dispBuffer_ShowColumns(uint8_t *col_data, uint16_t nb_col);
uint16_t dispBuffer_AddChar(char c);
uint16_t dispBuffer_AddString(char *str);
uint16_t dispBuffer_GetNbFreeColumns(void);
uint16_t dispBuffer_ChangeRow(uint8_t col_data, uint16_t pos);
uint16_t dispBuffer_ChangeRows(uint8_t *col_data, uint16_t nb_col, uint16_t pos);

uint16_t dispBuffer_ShowTime(uint8_t mins, uint8_t secs, uint8_t colon);

#endif /* INC_DISPBUFFER_H_ */
