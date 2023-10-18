/*
 * display.c
 *
 *  Created on: Sep 27, 2023
 *      Author: Martin
 */

// - private ------------------------------------------------------------------------

#include "display.h"
#include "dispBuffer.h"
#include "lptim.h"

static uint32_t display_lptim_nr = 0;

static disp_buffer_t *display_buffer;
static uint32_t display_ctrl;
#define DISPLAY_CTRL_SCROLL_ON	BIT(0)

#if 1
#warning "__DISPLAY: 1 element -> 5 columns only"

#define DISPLAY_NB_COLUMNS	5 // 1 element only (5*6)
#define DISPLAY_NB_ROWS	(7)	// 1 byte
#define DISPLAY_ROW_MASK (0x7F)

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
#else
#warning "__DISPLAY: 6 elements -> 30 columns"

#define DISPLAY_NB_COLUMNS	30 // 6 elements
#define DISPLAY_NB_ROWS	(7)	// 1 byte
#define DISPLAY_ROW_MASK (0x7F)

#endif

// - public -------------------------------------------------------------------------

void display_Init(void) {
	display_lptim_nr = 0;
	display_ctrl = 0;

	dispBuffer_Init();
	display_buffer = dispBuffer_Get();
	dispBuffer_Clear();
	// gpios: see gpio.c
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
	display_ctrl |=  DISPLAY_CTRL_SCROLL_ON;
}
void display_ScrollingOff(void) {
	display_ctrl &= ~DISPLAY_CTRL_SCROLL_ON;
}


static uint32_t display_NextRow(uint32_t rd_origin, uint32_t wr_index, uint32_t col_nr) {
	uint32_t rd_index = rd_origin + col_nr;
	if(rd_index >= wr_index) {
		rd_index -= wr_index;
	}
	return rd_index;
}

static uint32_t display_Scroll(uint32_t rd_origin, uint32_t wr_origin) {
	if((display_ctrl & DISPLAY_CTRL_SCROLL_ON) == 0) {
		// scroll off, nothing to do
		return rd_origin;
	}
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
	display_buffer->rd_origin = display_Scroll(display_buffer->rd_origin, display_buffer->wr_index);
	display_buffer->rd_index  = display_NextRow(display_buffer->rd_origin, display_buffer->wr_index, col_cnt);

	display_ShowCol(col_cnt, display_buffer->buffer[display_buffer->rd_index]);
	col_cnt++;
	if(col_cnt >= DISPLAY_NB_COLUMNS) {
		col_cnt = 0;
	}
}

