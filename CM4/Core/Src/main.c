/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "mdma.h"
#include "tim.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "ssd1362.h"
#include "pictures.h"
#include "gui.h"
#include "leds.h"

#include "usart.h"

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
/* USER CODE BEGIN PFP */
void HSEM4_Init(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

/* USER CODE BEGIN Boot_Mode_Sequence_1 */

/* USER CODE END Boot_Mode_Sequence_1 */
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_DMA_Init();
  MX_GPIO_Init();
  MX_MDMA_Init();
  MX_FMC_Init();
  MX_TIM12_Init();
  /* USER CODE BEGIN 2 */
  HSEM4_Init();

#ifdef PRINTF_CM4
  MX_USART1_UART_Init();
#endif

    printf("CM4 BOOT\n");

	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("@@@       @=  @*       @   @@   @  @@@  @@       @   @@@  @@@\n");
	printf("@@        @=  @*       @   @@   @   @@  @@           @@@  *@@\n");
	printf("@@   @@@@@@=  @=  @@@@@@   @@   @   @@  @@@@   @@@   @@@  @@@\n");
	printf("@@   @@@@@@=  @@    @@@@   @@   @    @  @@@@   @@@        @@@\n");
	printf("@@   @@@@@@=  @@@@.    @@      @@  .    @@@@   @@@        @@@\n");
	printf("@@   @@-  @=  @@@@@@   @@@@  @@@@  @    @@@@   @@@   @@@  @@@\n");
	printf("@@@       @=  @@@      @@@@  @@@@  @@   @@@@   @@@   @@@  @@@\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@  @@@\n");
	printf("\n");

	// Initialize oled display and print logo
	ssd1362_init();
	ssd1362_clearBuffer();
	ssd1362_writeFullBuffer();

    char shortVersion[8];
    strcpy(shortVersion, FW_VERSION);

    // Locate the first dot
    char *p = strchr(shortVersion, '.');
    if (p != NULL)
    {
        // From there, look for the second dot
        p = strchr(p + 1, '.');
        if (p != NULL)
        {
            // Truncate at the second dot
            *p = '\0';
        }
    }

#ifndef SKIP_SPLASH
	for (uint8_t i = 0; i < 16; i++)
	{
		ssd1362_drawBmp(CISYNTH_img, 2, 0, 250, 64, i, 0);
	    ssd1362_drawString(230, 56, (signed char *)shortVersion, 4, 8);
		ssd1362_writeFullBuffer();

		if (i == 0)
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		if (i == 2)
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		if (i == 4)
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
		if (i == 6)
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		if (i == 8)
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		if (i == 10)
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);

		HAL_Delay(50);
	}
#endif

	//led_test();

    leds_timerInit();

	gui_mainLoop();

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
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SPI2|RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.PLL3.PLL3M = 5;
  PeriphClkInitStruct.PLL3.PLL3N = 160;
  PeriphClkInitStruct.PLL3.PLL3P = 10;
  PeriphClkInitStruct.PLL3.PLL3Q = 16;
  PeriphClkInitStruct.PLL3.PLL3R = 16;
  PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_2;
  PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
  PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
  PeriphClkInitStruct.Spi123ClockSelection = RCC_SPI123CLKSOURCE_PLL3;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_PLL3;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HSEM4_Init(void)
{
    // Enable HSEM clock for CM4
    __HAL_RCC_HSEM_CLK_ENABLE();

    // Enable notification on semaphore 1 to receive IRQ on CM4
    HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(1));

    // Set IRQ priority and enable HSEM IRQ for CM4
    HAL_NVIC_SetPriority(HSEM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(HSEM2_IRQn);
}

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
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		for(volatile uint32_t i = 0; i < 0xFFFFFF; i++);
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
