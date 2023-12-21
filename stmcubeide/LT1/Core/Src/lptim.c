/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    lptim.c
  * @brief   This file provides code for the configuration
  *          of the LPTIM instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "lptim.h"

/* USER CODE BEGIN 0 */
/* Includes ------------------------------------------------------------------*/
#include "macros.h"
#include "main.h"
#include "lptim.h"
#include "display.h"

/* USER CODE END 0 */

LPTIM_HandleTypeDef hlptim1;
LPTIM_HandleTypeDef hlptim2;

/* LPTIM1 init function */
void MX_LPTIM1_Init(void)
{

  /* USER CODE BEGIN LPTIM1_Init 0 */

  /* USER CODE END LPTIM1_Init 0 */

  /* USER CODE BEGIN LPTIM1_Init 1 */

  /* USER CODE END LPTIM1_Init 1 */
  hlptim1.Instance = LPTIM1;
  hlptim1.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
  hlptim1.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV1;
  hlptim1.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
  hlptim1.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
  hlptim1.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
  hlptim1.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
  hlptim1.Init.Input1Source = LPTIM_INPUT1SOURCE_GPIO;
  hlptim1.Init.Input2Source = LPTIM_INPUT2SOURCE_GPIO;
  hlptim1.Init.RepetitionCounter = 0;
  if (HAL_LPTIM_Init(&hlptim1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPTIM1_Init 2 */

  /* USER CODE END LPTIM1_Init 2 */

}
/* LPTIM2 init function */
void MX_LPTIM2_Init(void)
{

  /* USER CODE BEGIN LPTIM2_Init 0 */

  /* USER CODE END LPTIM2_Init 0 */

  /* USER CODE BEGIN LPTIM2_Init 1 */

  /* USER CODE END LPTIM2_Init 1 */
  hlptim2.Instance = LPTIM2;
  hlptim2.Init.Clock.Source = LPTIM_CLOCKSOURCE_APBCLOCK_LPOSC;
  hlptim2.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV1;
  hlptim2.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
  hlptim2.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
  hlptim2.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
  hlptim2.Init.CounterSource = LPTIM_COUNTERSOURCE_INTERNAL;
  hlptim2.Init.Input1Source = LPTIM_INPUT1SOURCE_GPIO;
  hlptim2.Init.Input2Source = LPTIM_INPUT2SOURCE_GPIO;
  hlptim2.Init.RepetitionCounter = 0;
  if (HAL_LPTIM_Init(&hlptim2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LPTIM2_Init 2 */

  /* USER CODE END LPTIM2_Init 2 */

}

void HAL_LPTIM_MspInit(LPTIM_HandleTypeDef* lptimHandle)
{

  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(lptimHandle->Instance==LPTIM1)
  {
  /* USER CODE BEGIN LPTIM1_MspInit 0 */

  /* USER CODE END LPTIM1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPTIM1;
    PeriphClkInit.Lptim1ClockSelection = RCC_LPTIM1CLKSOURCE_LSI;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* LPTIM1 clock enable */
    __HAL_RCC_LPTIM1_CLK_ENABLE();

    /* LPTIM1 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPTIM1_IRQn);
  /* USER CODE BEGIN LPTIM1_MspInit 1 */

  /* USER CODE END LPTIM1_MspInit 1 */
  }
  else if(lptimHandle->Instance==LPTIM2)
  {
  /* USER CODE BEGIN LPTIM2_MspInit 0 */

  /* USER CODE END LPTIM2_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_LPTIM2;
    PeriphClkInit.Lptim2ClockSelection = RCC_LPTIM2CLKSOURCE_PCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    /* LPTIM2 clock enable */
    __HAL_RCC_LPTIM2_CLK_ENABLE();

    /* LPTIM2 interrupt Init */
    HAL_NVIC_SetPriority(LPTIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(LPTIM2_IRQn);
  /* USER CODE BEGIN LPTIM2_MspInit 1 */

  /* USER CODE END LPTIM2_MspInit 1 */
  }
}

void HAL_LPTIM_MspDeInit(LPTIM_HandleTypeDef* lptimHandle)
{

  if(lptimHandle->Instance==LPTIM1)
  {
  /* USER CODE BEGIN LPTIM1_MspDeInit 0 */

  /* USER CODE END LPTIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPTIM1_CLK_DISABLE();

    /* LPTIM1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(LPTIM1_IRQn);
  /* USER CODE BEGIN LPTIM1_MspDeInit 1 */

  /* USER CODE END LPTIM1_MspDeInit 1 */
  }
  else if(lptimHandle->Instance==LPTIM2)
  {
  /* USER CODE BEGIN LPTIM2_MspDeInit 0 */

  /* USER CODE END LPTIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LPTIM2_CLK_DISABLE();

    /* LPTIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(LPTIM2_IRQn);
  /* USER CODE BEGIN LPTIM2_MspDeInit 1 */

  /* USER CODE END LPTIM2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
// - private ---------------------------------
typedef struct {
	uint32_t ctrl;
	uint32_t periode_reload;
	uint32_t periode_cnt;
	uint32_t events;
} lptim_events_t;
#define LPTIM_EVENTS_CTRL_ACTIVE	BIT(31)
#define LPTIM_EVENTS_CTRL_REPEATE	BIT(30)

static volatile lptim_events_t lptim_events[LPTIM_NB_EVENTS];

static uint32_t lptim_Find_Free_Event(void){
	uint32_t n;
	for(n = 0; n < LPTIM_NB_EVENTS; n++) {
		if((lptim_events[n].ctrl & LPTIM_EVENTS_CTRL_ACTIVE) == 0) {
			// unused
			return n;
		}
	}
	return LPTIM_NB_EVENTS;
}

static volatile lptim_display_ctrl = 0;
#define LPTIM_DISPLAY_CTRL_ON	BIT(0)

static volatile uint32_t lptim2_event;
void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim) {
	if(hlptim == &hlptim1) {
		uint8_t n;
		for(n = 0; n < LPTIM_NB_EVENTS; n++) {
			if((lptim_events[n].ctrl & LPTIM_EVENTS_CTRL_ACTIVE)) {
				if(lptim_events[n].periode_cnt == 0) {
					global_events |= lptim_events[n].events;
					if((lptim_events[n].ctrl & LPTIM_EVENTS_CTRL_REPEATE)) {
						lptim_events[n].periode_cnt = lptim_events[n].periode_reload;
					}
					else {
						lptim_events[n].ctrl &= ~LPTIM_EVENTS_CTRL_ACTIVE;
					}
				}
				else {
					lptim_events[n].periode_cnt--;
				}
			}
		}
	}
	else {
		global_events |= lptim2_event;
		//display_Update();
	}
	if(global_events)
		HAL_PWR_DisableSleepOnExit();
}
// - public ---------------------------------
void lptim_Start(void) {
	HAL_LPTIM_Counter_Start_IT(&hlptim1, LPTIM_CLK_INTERVAL);
}

uint32_t lptim_AddSingleEvent(uint32_t periode, uint32_t event) {
	if(event == 0) {
		// error, cannot add event, there is none given
		// else this could result in a possible dead lock
		return LPTIM_COULD_NOT_ADD_EVENT;
	}

	// ATOMIC
	uint32_t restore_irq;
	ENTER_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);

	// find 1st free lptim_events
	uint32_t ret = LPTIM_COULD_NOT_ADD_EVENT;	// default: no free lptim_event
	uint32_t lptim_event_nr = lptim_Find_Free_Event();
	if(lptim_event_nr < LPTIM_NB_EVENTS) {
		// found free lptim_event
		ret = lptim_event_nr;
		lptim_events[lptim_event_nr].periode_cnt = periode;
		lptim_events[lptim_event_nr].periode_reload = periode;
		lptim_events[lptim_event_nr].events = event;
		lptim_events[lptim_event_nr].ctrl = LPTIM_EVENTS_CTRL_ACTIVE;
	}

	LEAVE_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);
	return ret;
}

uint32_t lptim_AddRepeatingEvent(uint32_t periode, uint32_t event) {
	if(event == 0) {
		// error, cannot add event, there is none given
		// else this could result in a possible dead lock
		return LPTIM_COULD_NOT_ADD_EVENT;
	}

	// ATOMIC
	uint32_t restore_irq;
	ENTER_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);

	// find 1st free lptim_events
	uint32_t ret = LPTIM_COULD_NOT_ADD_EVENT;	// default: no free lptim_event
	uint32_t lptim_event_nr = lptim_Find_Free_Event();
	if(lptim_event_nr < LPTIM_NB_EVENTS) {
		// found free lptim_event
		ret = lptim_event_nr;
		lptim_events[lptim_event_nr].periode_cnt = periode;
		lptim_events[lptim_event_nr].periode_reload = periode;
		lptim_events[lptim_event_nr].events = event;
		lptim_events[lptim_event_nr].ctrl = LPTIM_EVENTS_CTRL_ACTIVE | LPTIM_EVENTS_CTRL_REPEATE;
	}

	LEAVE_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);
	return ret;
}

uint32_t lptim_RemoveEvent(uint32_t lptim_event_nr) {
	if(lptim_event_nr >= LPTIM_NB_EVENTS) {
		return RET_ERROR;
	}

	// ATOMIC
	uint32_t restore_irq;
	ENTER_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);

	lptim_events[lptim_event_nr].ctrl = 0;

	LEAVE_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);
	return RET_SUCCESS;
}

static uint32_t lptim_display_nr = 0;
void lptim_StartDisplayUpdate(void) {
	// ATOMIC
	uint32_t restore_irq;
	ENTER_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);

	lptim_display_nr = lptim_AddRepeatingEvent(1, EV_DISPLAY_UPDATE);

	LEAVE_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);
}

void lptim_StopDisplayUpdate(void) {
	// ATOMIC
	uint32_t restore_irq;
	ENTER_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);

	lptim_RemoveEvent(lptim_display_nr);

	LEAVE_ATOMIC_NVIC_IRQn(LPTIM1_IRQn, restore_irq);
}

uint32_t lptim2_StartRepeating(uint32_t event) {
	lptim2_event = event;
	/* 2 MHz: 0.5 us
	 * 200: 438 us   (row5)
	 * 2000: 1000 us (row5): this is more like it
	 * 20000: 10 ms  (row5)
	 */
	/* 16 MHz: 62.5 ns = 0.0625 us
	 * 10666 = 0.66 us = 1500 Hz = 50 Hz * 30 (row5), measured 650 us: OK
	 * 20000 = 1.25 ms (row5), measured: 1.23 ms: OK
	 */
	HAL_LPTIM_Counter_Start_IT(&hlptim2, 10666);
	return RET_SUCCESS;
}

uint32_t lptim2_Stop(void) {
	HAL_LPTIM_Counter_Stop_IT(&hlptim2);
}

/* USER CODE END 1 */
