/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "main.h"
#include "rtc.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "encoder.h"
#include "disp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static int8_t main_task_func(uint8_t event, void *data);
static task_t main_task = {.name = "main task", .task = main_task_func};
int8_t main_tid;

// states
#define MAIN_ST_OFF (0)
#define MAIN_ST_SET_TIMER (1)
#define MAIN_ST_RUNNING (2)
#define MAIN_ST_RUNNING_DISP_OFF (3)
#define MAIN_ST_PAUSE (4)
#define MAIN_ST_ALARM (5)
#define MAIN_ST_TEST (6)

static struct {
	uint16_t state;
	struct {
		uint8_t min, sec;
	} timer_set, timer_cnt;
	uint16_t disp_timeout;
	uint8_t disp_state;
} main_task_ctrl = {
		.state = MAIN_ST_OFF,
};
#define TIMER_SET_MAX_MINUTES (99)
#define TIMER_SET_MIN_MINUTES (01)
#define TIMER_SET_SECONDS (59)

#define TIMER_DISP_ON_TIMEOUT (20) // in s

uint8_t main_bright = 20;
uint8_t main_num = 0;
uint8_t main_cnt = 0;
uint32_t main_f = 0x00000001U;

static int8_t main_task_func(uint8_t event, void *data) {
	switch(main_task_ctrl.state) {
	// -------------------------------------------------------------------------
	case MAIN_ST_OFF:
		if( /*(event == EV_START) ||*/
			(event == EV_ENC_SINGLE_PRESSED)) {
			// was in off state
			power_mode_request(POWER_MODE_SLEEP); // to display time and timer functionalities
			main_task_ctrl.state = MAIN_ST_SET_TIMER;
			main_task_ctrl.timer_set.min = 1;
			main_task_ctrl.timer_set.sec = 0;
			disp_on();
			disp_show_number(main_task_ctrl.timer_set.min);
			main_task_ctrl.disp_timeout = TIMER_DISP_ON_TIMEOUT;
			rtc_start_1s_timing_event();
			encoder_btn_use_debounce();
		}
		break;

	// -------------------------------------------------------------------------
	case MAIN_ST_SET_TIMER:
		if(event == EV_TIMER_RTC) { // timeout--
			if(main_task_ctrl.disp_timeout) {
				main_task_ctrl.disp_timeout--;
				if(main_task_ctrl.disp_timeout == 0) {
					// expired
					main_task_ctrl.state = MAIN_ST_OFF;
					rtc_stop_timing_event();
				}
			}
		}
		if(event == EV_ENC_ROT_RIGHT) { // +
			main_task_ctrl.disp_timeout = TIMER_DISP_ON_TIMEOUT; // reset timeout
			if(main_task_ctrl.timer_set.min < TIMER_SET_MAX_MINUTES) {
				main_task_ctrl.timer_set.min++;
				disp_show_number(main_task_ctrl.timer_set.min);
			}
		}
		if(event == EV_ENC_ROT_LEFT) { // -
			main_task_ctrl.disp_timeout = TIMER_DISP_ON_TIMEOUT; // reset timeout
			if(main_task_ctrl.timer_set.min > TIMER_SET_MIN_MINUTES) {
				main_task_ctrl.timer_set.min--;
				disp_show_number(main_task_ctrl.timer_set.min);
			}
		}
		if(event == EV_ENC_SINGLE_PRESSED) { // start
			main_task_ctrl.state = MAIN_ST_RUNNING;
			main_task_ctrl.timer_cnt.min = main_task_ctrl.timer_set.min;
			main_task_ctrl.timer_cnt.sec = main_task_ctrl.timer_set.sec;
			disp_show_number(main_task_ctrl.timer_cnt.min);
			disp_activity_on();
			rtc_start_1s_timing_event();
		}
		if(event == EV_ENC_LONG_PRESSED) { // stop, off
			main_task_ctrl.state = MAIN_ST_OFF;
			rtc_stop_timing_event();
			encoder_btn_use_int_only();
		}
		break;

	// -------------------------------------------------------------------------
	case MAIN_ST_RUNNING:
		if(event == EV_TIMER_RTC) { // timeout--
			main_task_ctrl.disp_state = 1;
			if(main_task_ctrl.timer_cnt.sec == 0) {
				if(main_task_ctrl.timer_cnt.min == 0) {
					// expired: ALARM
					main_task_ctrl.state = MAIN_ST_ALARM;
					main_task_ctrl.disp_state = 0;
					disp_show_number(main_task_ctrl.timer_set.min);
				}
				else {
					main_task_ctrl.timer_cnt.sec = TIMER_SET_SECONDS;
					main_task_ctrl.timer_cnt.min--;
				}
			}
			else {
				main_task_ctrl.timer_cnt.sec--;
			}

			if(main_task_ctrl.timer_cnt.min) {
				disp_show_number(main_task_ctrl.timer_cnt.min);
			}
			else {
				disp_show_number(main_task_ctrl.timer_cnt.sec);
			}
			if(main_task_ctrl.disp_state) {
				if(main_task_ctrl.timer_cnt.sec & 0x01)
					disp_activity_on();
				else
					disp_activity_off();
			}
		}
		if(event == EV_ENC_SINGLE_PRESSED) { // pause
			main_task_ctrl.state = MAIN_ST_PAUSE;
			rtc_start_1s_timing_event();
			if(main_task_ctrl.timer_cnt.min) {
				disp_show_number(main_task_ctrl.timer_cnt.min);
			}
			else {
				disp_show_number(main_task_ctrl.timer_cnt.sec);
			}
			disp_activity_off();
			main_task_ctrl.disp_state = 0;
		}
		if(event == EV_ENC_LONG_PRESSED) { // stop, set time
			main_task_ctrl.state = MAIN_ST_SET_TIMER;
			disp_show_number(main_task_ctrl.timer_set.min);
			main_task_ctrl.disp_timeout = TIMER_DISP_ON_TIMEOUT;
			rtc_start_1s_timing_event();
		}
		break;

	// -------------------------------------------------------------------------
	case MAIN_ST_RUNNING_DISP_OFF:
		break;

	// -------------------------------------------------------------------------
	case MAIN_ST_PAUSE:
		if(event == EV_TIMER_RTC) { // blink time
			if(main_task_ctrl.disp_state == 0) {
				main_task_ctrl.disp_state = 1;
				disp_number_off();
			}
			else {
				main_task_ctrl.disp_state = 0;
				if(main_task_ctrl.timer_cnt.min) {
					disp_show_number(main_task_ctrl.timer_cnt.min);
				}
				else {
					disp_show_number(main_task_ctrl.timer_cnt.sec);
				}
			}
		}
		if(event == EV_ENC_SINGLE_PRESSED) { // resume
			main_task_ctrl.state = MAIN_ST_RUNNING;
			disp_show_number(main_task_ctrl.timer_cnt.min);
			disp_activity_on();
			rtc_start_1s_timing_event();
		}
		if(event == EV_ENC_LONG_PRESSED) { // stop, set time
			main_task_ctrl.state = MAIN_ST_SET_TIMER;
			disp_show_number(main_task_ctrl.timer_set.min);
			main_task_ctrl.disp_timeout = TIMER_DISP_ON_TIMEOUT;
			rtc_start_1s_timing_event();
		}
		break;

	// -------------------------------------------------------------------------// -------------------------------------------------------------------------
	case MAIN_ST_ALARM:
		if(event == EV_TIMER_RTC) { // blink time
			if(main_task_ctrl.disp_state == 0) {
				main_task_ctrl.disp_state = 1;
				disp_number_off();
			}
			else {
				main_task_ctrl.disp_state = 0;
				disp_show_number(main_task_ctrl.timer_set.min);
			}
		}
		if( (event == EV_ENC_SINGLE_PRESSED) ||
			(event == EV_ENC_LONG_PRESSED)) { // done, go back to set time
			main_task_ctrl.state = MAIN_ST_SET_TIMER;
			disp_show_number(main_task_ctrl.timer_set.min);
			main_task_ctrl.disp_timeout = TIMER_DISP_ON_TIMEOUT;
			rtc_start_1s_timing_event();
		}
		break;
	}

	return 1; // stay on
}

/*
 * power modes, cases
 *
 * 1. case 0: nothing to do, no data to preserve
 *   + available power modes: **stop**
 *   + all power down,
 *   + wakeup by rotary encoder, press or rotate -> EXTI, GPIO only
 *   + available power modes:
 *     + GPIO + EXTI: run; sleep; low-power run; low-power-sleep; stop; wake up from standby:
 *       + PA0: WKUP1: ENC_A_Pin -> rotate knob to wake
 *       + PA2: WKUP3: unused (UART2_TX)
 * 2. case 1: display, setup time, count down time
 *   + use power mode: **sleep**
 *   + active: rotary encoder + button -> 16-bit timers
 *   + RTC timer
 *   + display -> 16-bit timers
 *   + CPU may be off, when there is nothing to do
 *   + available power modes:
 *     + 16-bit timers: run; **sleep**; low-power run; low-power-sleep; - ; -
 *     + RTC: run; sleep; low-power run; low-power-sleep; stop; standby
 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, 3);

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_RTC_Init();
  MX_TIM22_Init();
  MX_TIM2_Init();
  MX_TIM21_Init();
  /* USER CODE BEGIN 2 */
	scheduler_init();
	//power_mode_request(POWER_MODE_SLEEP); // to display time and timer functionalities
	power_mode_request(POWER_MODE_STOP); // no to do: power down everything, but generate INT on encoder input

	encoder_init();
	disp_init();

	scheduler_add_task(&main_task);
	main_tid = main_task.tid;
	scheduler_start_task(main_tid);


	// stay in scheduler
	scheduler_run();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
  {
  }
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  while (LL_PWR_IsActiveFlag_VOS() != 0)
  {
  }
  LL_RCC_HSI_Enable();

   /* Wait till HSI is ready */
  while(LL_RCC_HSI_IsReady() != 1)
  {

  }
  LL_RCC_HSI_SetCalibTrimming(16);
  LL_PWR_EnableBkUpAccess();
  if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSE)
  {
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
  }
  LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);
  LL_RCC_LSE_Enable();

   /* Wait till LSE is ready */
  while(LL_RCC_LSE_IsReady() != 1)
  {

  }
  if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSE)
  {
    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
  }
  LL_RCC_EnableRTC();
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
  {

  }

  LL_Init1msTick(16000000);

  LL_SetSystemCoreClock(16000000);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
