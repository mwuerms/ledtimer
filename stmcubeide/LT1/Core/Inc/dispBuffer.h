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

#define DISPLAY_NB_COLUMNS	5 // 1 element only (5*6)
#define DISPLAY_NB_ROWS	(7)	// 1 byte
#define DISPLAY_ROW_MASK (0x7F)

#define DISP_BUFFER_SIZE	(32*2)
typedef struct {
	uint8_t buffer[DISP_BUFFER_SIZE];
	uint8_t wr_index;
	uint8_t rd_index, rd_origin;
} disp_buffer_t;

void dispBuffer_Init(void);
disp_buffer_t *dispBuffer_Get(void);
uint16_t dispBuffer_Clear(void);
uint16_t dispBuffer_AddRow(uint8_t row_data);
uint16_t dispBuffer_AddRows(uint8_t *row_data, uint16_t nb_rows);
uint16_t dispBuffer_ShowRows(uint8_t *row_data, uint16_t nb_rows);
uint16_t dispBuffer_AddChar(char c);
uint16_t dispBuffer_AddString(char *str);
uint16_t dispBuffer_GetNbFreeRows(void);
uint16_t dispBuffer_ChangeRow(uint8_t row_data, uint16_t pos);
uint16_t dispBuffer_ChangeRows(uint8_t *row_data, uint16_t nb_rows, uint16_t pos);

#endif /* INC_DISPBUFFER_H_ */
