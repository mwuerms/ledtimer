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

#define DISPLAY_NB_COLUMNS	30 // 6 elements
#define DISPLAY_NB_ROWS	(7)	// 1 byte
#define DISPLAY_ROW_MASK (0x7F)

// Shift Register GPIOs
// Output Enable, set = on
#define ShiftRegister_Output_disable()	HAL_GPIO_WritePin(DISP_COL_OE_GPIO_Port, DISP_COL_OE_Pin, GPIO_PIN_SET);
#define ShiftRegister_Output_enable()	HAL_GPIO_WritePin(DISP_COL_OE_GPIO_Port, DISP_COL_OE_Pin, GPIO_PIN_RESET);
// Clear, low = clear, reset
#define ShiftRegister_SRCLR_Set()	HAL_GPIO_WritePin(DISP_COL_SRCLR_GPIO_Port, DISP_COL_SRCLR_Pin, GPIO_PIN_SET);
#define ShiftRegister_SRCLR_Clr()	HAL_GPIO_WritePin(DISP_COL_SRCLR_GPIO_Port, DISP_COL_SRCLR_Pin, GPIO_PIN_RESET);
// Clock, rising edge = fetch SI
#define ShiftRegister_SRCLK_Set()	HAL_GPIO_WritePin(DISP_COL_SRCLK_GPIO_Port, DISP_COL_SRCLK_Pin, GPIO_PIN_SET);
#define ShiftRegister_SRCLK_Clr()	HAL_GPIO_WritePin(DISP_COL_SRCLK_GPIO_Port, DISP_COL_SRCLK_Pin, GPIO_PIN_RESET);
// Clock, rising edge = fetch SI
#define ShiftRegister_RCLK_Set()	HAL_GPIO_WritePin(DISP_COL_RCLK_GPIO_Port, DISP_COL_RCLK_Pin, GPIO_PIN_SET);
#define ShiftRegister_RCLK_Clr()	HAL_GPIO_WritePin(DISP_COL_RCLK_GPIO_Port, DISP_COL_RCLK_Pin, GPIO_PIN_RESET);
// SI, SER Serial Input
#define ShiftRegister_SER_Set()	HAL_GPIO_WritePin(DISP_COL_SER_GPIO_Port, DISP_COL_SER_Pin, GPIO_PIN_SET);
#define ShiftRegister_SER_Clr()	HAL_GPIO_WritePin(DISP_COL_SER_GPIO_Port, DISP_COL_SER_Pin, GPIO_PIN_RESET);

void display_ShowCol(uint32_t col_nr, uint32_t row_data) {
	ShiftRegister_Output_disable();
	GPIOA->ODR &= ~DISPLAY_ROW_MASK;

	if(col_nr == 0) {
		// start from to, reset
		ShiftRegister_SRCLR_Clr();
		// set data
		ShiftRegister_SER_Set();
	}
	ShiftRegister_SRCLR_Set();
	// SRCLK: rising edges: fetch data
	ShiftRegister_SRCLK_Set();
	ShiftRegister_SRCLK_Clr();
	// clear data now
	ShiftRegister_SER_Clr();
	// RCLK: rising edges: fetch data
	ShiftRegister_RCLK_Set();
	ShiftRegister_RCLK_Clr();

	GPIOA->ODR |= row_data & DISPLAY_ROW_MASK;
	ShiftRegister_Output_enable();
}

// - public -------------------------------------------------------------------------

void display_Init(void) {
	display_lptim_nr = 0;
	display_ctrl = 0;

	ShiftRegister_Output_disable();
	ShiftRegister_SRCLK_Clr();
	ShiftRegister_RCLK_Clr();

	dispBuffer_Init();
	display_buffer = dispBuffer_Get();
	dispBuffer_Clear();
	// gpios: see gpio.c

	// testing display
	//uint8_t test_data[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
	//dispBuffer_AddRows(test_data, sizeof(test_data));
}

void display_On(void) {
	//lptim_StartDisplayUpdate();
	//lptim_AddRepeatingEvent(10, EV_DISPLAY_UPDATE);
	lptim_AddRepeatingEvent(1, EV_DISPLAY_UPDATE);
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
	/*if(rd_index >= wr_index) {
		rd_index -= wr_index;
	}*/
	if(rd_index >= DISPLAY_NB_COLUMNS) {
		rd_index -= DISPLAY_NB_COLUMNS;
	}
	return rd_index;
}

static uint32_t display_Scroll(uint32_t rd_origin, uint32_t wr_origin) {
	return rd_origin;
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

