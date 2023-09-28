/*
 * display.c
 *
 *  Created on: Sep 27, 2023
 *      Author: Martin
 */

// - private ------------------------------
#include "display.h"
#include "lptim.h"
#include "fontmonospace.h"

#warning "__DISPLAY: 1 element only"

#define DISPLAY_NB_COLUMNS	5 // 1 element only (5*6)
#define DISPLAY_NB_ROWS	(7)	// 1 byte
#define DISPLAY_ROW_MASK (0x7F)

#define DISPLAY_BUFFER_SIZE	(32*2)
typedef struct {
	uint8_t buffer[DISPLAY_BUFFER_SIZE];
	uint8_t wr_index;
	uint8_t rd_index, rd_origin;
} display_buffer_t;

static display_buffer_t display_buffer;


static uint32_t display_lptim_nr = 0;






void display_ShowCol(uint32_t col_nr, uint32_t row_data) {
	GPIOA->ODR = 0;
	switch(col_nr) {
	case 0:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		break;
	}
	GPIOA->ODR = row_data & DISPLAY_ROW_MASK;
}


// - public ----------------------------
void display_Init(void) {
	display_lptim_nr = 0;
}

void display_On(void) {
	//lptim_StartDisplayUpdate();
	lptim_AddRepeatingEvent(10, EV_DISPLAY_UPDATE);
	return;
}

void display_Off(void) {
	//lptim_StopDisplayUpdate();
	lptim_RemoveEvent(display_lptim_nr);
	return;
}

void display_ScrollingOn(void) {
	return;
}
void display_ScrollingOff(void) {
	return;
}


static uint32_t _next(uint32_t rd_origin, uint32_t wr_index, uint32_t col_nr) {
	uint32_t rd_index = rd_origin + col_nr;
	if(rd_index >= wr_index) {
		rd_index -= wr_index;
	}
	return rd_index;
}

static uint32_t _scroll(uint32_t rd_origin, uint32_t wr_origin) {
	static uint32_t cnt_scroll = 32768/8/8/10;
	uint32_t next_rd_origin = rd_origin;
	if(cnt_scroll == 0) {
		cnt_scroll = 32768/8/8/10;
		next_rd_origin++;
		if(next_rd_origin >= wr_origin) {
			next_rd_origin = 0;
		}
	}
	else {
		cnt_scroll--;
	}
	return next_rd_origin;
}

// call in background from timer (LPTIM1)
void display_Update(void) {
	static uint32_t col_cnt = 0;

	display_buffer.rd_origin = _scroll(display_buffer.rd_origin, display_buffer.wr_index);
	display_buffer.rd_index = _next(display_buffer.rd_origin, display_buffer.wr_index, col_cnt);

	display_ShowCol(col_cnt, display_buffer.buffer[display_buffer.rd_index]);
	col_cnt++;
	if(col_cnt >= DISPLAY_NB_COLUMNS) {
		col_cnt = 0;
	}
}



static void display_ClearDisplayBuffer(void) {
	for(display_buffer.wr_index = 0; display_buffer.wr_index < DISPLAY_BUFFER_SIZE; display_buffer.wr_index++) {
		display_buffer.buffer[display_buffer.wr_index] = 0;
	}
	display_buffer.wr_index = 0;
}

static uint32_t display_AddCharToDisplayBuffer(char c) {
	uint8_t n;
	if((display_buffer.wr_index + 6) >= DISPLAY_BUFFER_SIZE)
		return RET_ERROR;
	for(n = 0; n < 5; n++) {
		display_buffer.buffer[display_buffer.wr_index++] = font[c-0x20][n];
	}
	display_buffer.buffer[display_buffer.wr_index++] = FONT_CHAR_SEPARATOR;
	return RET_SUCCESS;
}

void display_ShowString(char *str) {
	display_ClearDisplayBuffer();
	while(*str != 0) {
		if(display_AddCharToDisplayBuffer(*str) == RET_ERROR) {
			break;
		}
		str++;
	}
}
