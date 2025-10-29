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

struct {
	uint16_t state;
} main_task_ctrl = {
		.state = MAIN_ST_OFF,
};

uint8_t main_bright = 20;
uint8_t main_num = 0;
uint32_t main_f = 0x00000001U;
static int8_t main_task_func(uint8_t event, void *data) {
	switch(main_task_ctrl.state) {
	case MAIN_ST_OFF:
		if(event == EV_START) {
			// was in off state
			main_task_ctrl.state = MAIN_ST_TEST;
		}
		break;
	case MAIN_ST_SET_TIMER:
		break;
	case MAIN_ST_RUNNING:
		break;
	case MAIN_ST_RUNNING_DISP_OFF:
		break;
	case MAIN_ST_PAUSE:
		break;
	case MAIN_ST_ALARM:
		break;

	case MAIN_ST_TEST:
		if(event == EV_TIMER_RTC) {
			main_task_ctrl.state = MAIN_ST_TEST; // to set breakpoint

			if(main_num) {
				main_num--;
				if(main_num == 0) {
					// expired -> stop RTC WUT
					LL_RTC_DisableWriteProtection(RTC);
					LL_RTC_ClearFlag_WUT(RTC);
					LL_RTC_DisableIT_WUT(RTC);
					LL_RTC_WAKEUP_Disable(RTC);
					LL_RTC_EnableWriteProtection(RTC);
					LL_EXTI_DisableIT_0_31(LL_EXTI_LINE_20);  			// Enable interrupt for EXTI line 20 (RTC)
				}
			}
			disp_show_number(main_num);
		}

		if(event == EV_ENC_SINGLE_PRESSED) {
			main_task_ctrl.state = MAIN_ST_TEST; // to set breakpoint

			// RTC konfigurieren
/*		    LL_RTC_DisableWriteProtection(RTC);
		    LL_RTC_DisableInitMode(RTC);

		    LL_RTC_InitTypeDef RTC_InitStruct = {0};
		    RTC_InitStruct.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
		    RTC_InitStruct.AsynchPrescaler = 127;
		    RTC_InitStruct.SynchPrescaler = 255;
		    LL_RTC_Init(RTC, &RTC_InitStruct);
		    LL_RTC_EnableWriteProtection(RTC);
*/
		    // Wakeup Timer konfigurieren (1 Hz)
		    LL_RTC_DisableWriteProtection(RTC);
		    LL_RTC_WAKEUP_Disable(RTC);
	//	    while(!LL_RTC_IsActiveFlag_WUTW(RTC));
		    LL_RTC_WAKEUP_SetClock(RTC, LL_RTC_WAKEUPCLOCK_CKSPRE);
		    LL_RTC_WAKEUP_SetAutoReload(RTC, 0);
		    LL_RTC_ClearFlag_WUT(RTC);
		    LL_RTC_EnableIT_WUT(RTC);
		    LL_RTC_WAKEUP_Enable(RTC);
		    LL_RTC_EnableWriteProtection(RTC);

		    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_20);  			// Enable interrupt for EXTI line 20 (RTC)
		    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_20);  	// Trigger on rising edge for line 20 (RTC)

		    // NVIC konfigurieren
		    NVIC_SetPriority(RTC_IRQn, 0);
		    NVIC_EnableIRQ(RTC_IRQn);

			main_num = 25;
			disp_show_number(main_num);
		}
		if(event == EV_ENC_DOUBLE_PRESSED) {
			main_task_ctrl.state = MAIN_ST_TEST;
			disp_set_frame(0x007FF800U);
		}
		if(event == EV_ENC_LONG_PRESSED) {
			main_task_ctrl.state = MAIN_ST_TEST;
			disp_set_frame(0x000007FFU);
		}
		if(event == EV_ENC_ROT_LEFT) {
			main_task_ctrl.state = MAIN_ST_TEST;
			if(main_bright > 10)
				main_bright -= 10;
			disp_set_brightness(main_bright);
			main_num++;
			if(main_num > 99)
				main_num = 0;
			disp_show_number(main_num);
		}
		if(event == EV_ENC_ROT_RIGHT) {
			main_task_ctrl.state = MAIN_ST_TEST;
			if(main_bright < 100)
				main_bright += 10;
			disp_set_brightness(main_bright);
			main_num++;
			if(main_num > 99)
				main_num = 0;
			disp_show_number(main_num);
		}
		break;
	}

	return 1; // stay on
}


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
  /* USER CODE BEGIN 2 */
	scheduler_init();
	power_mode_request(POWER_MODE_RUN);

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
