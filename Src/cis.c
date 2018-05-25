
/**
 ******************************************************************************
 * @file           : cis.c
 * @brief          :
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

#include "tim.h"
#include "cis.h"

/* Extern variables ---------------------------------------------------------*/
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
extern HRTIM_HandleTypeDef hhrtim;
extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac1;

/* Private variables ---------------------------------------------------------*/
__IO uint16_t aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE] = {0};
const uint16_t aEscalator16bit[32] = {0x1100, 0x3322, 0x5544, 0x7766, 0x9988, 0xBBAA, 0xDDCC, 0xFFEE, 0xDDEE, 0xBBCC, 0x99AA, 0x7788, 0x5566, 0x3344, 0x1122};
static __IO uint32_t pixel_cnt = 0;
static __IO uint16_t color_selector = 3;

static DAC_ChannelConfTypeDef sConfig;

/* Private function prototypes -----------------------------------------------*/
void timesBaseInit(void);

void cisInit(void)
{
	//	/* ### - 4 - Start conversion in DMA mode ################################# */
	//	if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)aADCxConvertedData, ADC_CONVERTED_DATA_BUFFER_SIZE) != HAL_OK)
	//	{
	//		Error_Handler();
	//	}

	/* ### -6 - Start ADC conversion ############################################################ */
	if (HAL_ADC_Start_IT(&hadc1) != HAL_OK)
	{
		Error_Handler();
	}

	static DAC_ChannelConfTypeDef sConfig;

	/*##-1- Initialize the DAC peripheral ######################################*/
	if (HAL_DAC_Init(&hdac1) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/*##-1- DAC channel1 Configuration #########################################*/
	sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
	sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

	if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
	{
		/* Channel configuration Error */
		Error_Handler();
	}

	//	if (HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t *)aEscalator16bit, 32, DAC_ALIGN_12B_R) != HAL_OK)
	//	{
	//		/* Start DMA Error */
	//		Error_Handler();
	//	}


	/*##-2- Enable DAC selected channel and associated DMA #############################*/
	if (HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t *)aADCxConvertedData + 100, 1500/*ADC_CONVERTED_DATA_BUFFER_SIZE - 4*/, DAC_ALIGN_12B_R) != HAL_OK)
	{
		/* Start DMA Error */
		Error_Handler();
	}

	//	/*##-2- Enable DAC selected channel and associated DMA #############################*/
	//	if (HAL_DAC_Start_DMA(&hdac1, DAC1_CHANNEL_1, (uint32_t *)aADCxConvertedData, ADC_CONVERTED_DATA_BUFFER_SIZE, DAC_ALIGN_12B_R) != HAL_OK)
	//	{
	//		/* Start DMA Error */
	//		Error_Handler();
	//	}

	//		HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);

	timesBaseInit();

	while(1)
	{
		printf("ADC_Buf = ");
		for(int cnt = 2; cnt < ADC_CONVERTED_DATA_BUFFER_SIZE; cnt += 500)
		{
			printf("%d  ", (int)aADCxConvertedData[cnt]);
		}
		printf("\n");
		HAL_Delay(100);
	}
}

/**
 * @brief  End of conversion callback in non blocking mode
 * @param  hadc : hadc handle
 * @retval None
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	static uint16_t aADCxConvertedValue = 0;
	static uint8_t colorIsSet = 0;

	/* Read the converted value */
	aADCxConvertedValue = HAL_ADC_GetValue(&hadc1);

	__HAL_HRTIM_SETCOMPARE(&hhrtim, 0, HRTIM_COMPAREUNIT_1, aADCxConvertedValue);

	if (!colorIsSet)
	{
		if (color_selector == 0)
		{
			HAL_GPIO_WritePin(CIS_LED_B_GPIO_Port, CIS_LED_B_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CIS_LED_R_GPIO_Port, CIS_LED_R_Pin, GPIO_PIN_RESET);
			colorIsSet = 1;
		}
		else if (color_selector == 1)
		{
			HAL_GPIO_WritePin(CIS_LED_R_GPIO_Port, CIS_LED_R_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CIS_LED_G_GPIO_Port, CIS_LED_G_Pin, GPIO_PIN_RESET);
			colorIsSet = 1;
		}
		else if (color_selector == 2)
		{
			HAL_GPIO_WritePin(CIS_LED_G_GPIO_Port, CIS_LED_G_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CIS_LED_B_GPIO_Port, CIS_LED_B_Pin, GPIO_PIN_RESET);
			colorIsSet = 1;
		}
		else if (color_selector == 3)
		{
			HAL_GPIO_WritePin(CIS_LED_R_GPIO_Port, CIS_LED_R_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CIS_LED_G_GPIO_Port, CIS_LED_G_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(CIS_LED_B_GPIO_Port, CIS_LED_B_Pin, GPIO_PIN_SET);
			colorIsSet = 1;
		}
		else if (color_selector == 4)
		{
			HAL_GPIO_WritePin(CIS_LED_R_GPIO_Port, CIS_LED_R_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CIS_LED_G_GPIO_Port, CIS_LED_G_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(CIS_LED_B_GPIO_Port, CIS_LED_B_Pin, GPIO_PIN_RESET);
			colorIsSet = 1;
		}
	}

	if (pixel_cnt == 0)
	{
		HAL_GPIO_WritePin(CIS_SP_GPIO_Port, CIS_SP_Pin, GPIO_PIN_SET);
	}
	else if (pixel_cnt == 4)
	{
		HAL_GPIO_WritePin(CIS_SP_GPIO_Port, CIS_SP_Pin, GPIO_PIN_RESET);;
	}
	else if (pixel_cnt > 4)
	{
		aADCxConvertedData[pixel_cnt] = aADCxConvertedValue;
	}

	pixel_cnt++;
	if (pixel_cnt > (ADC_CONVERTED_DATA_BUFFER_SIZE - 1))
	{
		pixel_cnt = 0;
		color_selector++;
		if (color_selector > 2)
		{
			color_selector = 0;
		}
		colorIsSet = 0;
	}
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @param  htim : TIM handle
 * @retval None
 */
void timesBaseInit(void)
{
	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;

	uint32_t uwPrescalerValue = 0;

	/* Compute the prescaler value */
	uwPrescalerValue = (uint32_t) ((SystemCoreClock / 2) / (DAC_TIME_FREQ * 2));

	/*##-1- Configure the TIM peripheral #######################################*/
	/* Time base configuration */
	htim6.Instance = TIM6;

	htim6.Init.Period            = uwPrescalerValue;
	htim6.Init.Prescaler         = 0;
	htim6.Init.ClockDivision     = 0;
	htim6.Init.CounterMode       = TIM_COUNTERMODE_UP;
	htim6.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&htim6);

	/* TIM6 TRGO selection */
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

	HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig);

	/*##-2- Enable TIM peripheral counter ######################################*/
	HAL_TIM_Base_Start(&htim6);

	/* Compute the prescaler value */
	uwPrescalerValue = (uint32_t) ((SystemCoreClock / 2) / (HI_TIME_FREQ * 2));

	htim15.Instance = TIM15;
	htim15.Init.Prescaler = 0;
	htim15.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim15.Init.Period = uwPrescalerValue;
	htim15.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
	htim15.Init.RepetitionCounter = 0;
	htim15.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_OC_Init(&htim15) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
	sConfigOC.Pulse = uwPrescalerValue / 2;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_OC_ConfigChannel(&htim15, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//	//	/* Start channel 1 in Output compare mode */
	//	if(HAL_TIM_OC_Start_IT(&htim15, TIM_CHANNEL_1) != HAL_OK)
	//	{
	//		/* Starting Error */
	//		Error_Handler();
	//	}
	//
	//	HAL_TIM_Base_Start_IT(&htim15);

	/* Compute the prescaler value */
	uwPrescalerValue = (uint32_t) ((SystemCoreClock / 2) / (HI_TIME_FREQ * 8));

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 0;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = uwPrescalerValue;;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	sConfigOC.OCMode = TIM_OCMODE_TOGGLE;
	sConfigOC.Pulse = uwPrescalerValue/2;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

//	/* Start channel 1 in Output compare mode */
//	if(HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_1) != HAL_OK)
//	{
//		/* Starting Error */
//		Error_Handler();
//	}
//
//	HAL_TIM_Base_Start_IT(&htim1);

	HRTIM_TimeBaseCfgTypeDef pTimeBaseCfg;
	HRTIM_SimplePWMChannelCfgTypeDef pSimplePWMChannelCfg;

	uwPrescalerValue = (uint32_t) ((SystemCoreClock / 2) / (HI_TIME_FREQ * 4));

	pTimeBaseCfg.Period = uwPrescalerValue;
	pTimeBaseCfg.RepetitionCounter = 0x00;
	pTimeBaseCfg.PrescalerRatio = HRTIM_PRESCALERRATIO_DIV1;
	pTimeBaseCfg.Mode = HRTIM_MODE_CONTINUOUS;
	if (HAL_HRTIM_TimeBaseConfig(&hhrtim, HRTIM_TIMERINDEX_TIMER_A, &pTimeBaseCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	pSimplePWMChannelCfg.Pulse = uwPrescalerValue / 2;
	pSimplePWMChannelCfg.Polarity = HRTIM_OUTPUTPOLARITY_HIGH;
	pSimplePWMChannelCfg.IdleLevel = HRTIM_OUTPUTIDLELEVEL_INACTIVE;
	if (HAL_HRTIM_SimplePWMChannelConfig(&hhrtim, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1, &pSimplePWMChannelCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	HAL_HRTIM_SimplePWMStart(&hhrtim, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1);
	//	  		HAL_HRTIM_SimpleOCStart(&hhrtim, HRTIM_TIMERINDEX_TIMER_A, HRTIM_OUTPUT_TA1);
	//	  		HAL_HRTIM_SimpleBaseStart_IT(&hhrtim, HRTIM_TIMERINDEX_TIMER_A);
	//	HAL_HRTIM_SimplePWMStart(&hhrtim, HRTIM_TIMERINDEX_TIMER_B, HRTIM_OUTPUT_TB1);
}

/* TIM callback --------------------------------------------------------------*/
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
//void HAL_HRTIM_Compare1EventCallback(HRTIM_HandleTypeDef *htim, uint32_t timerIdx)
//{
//	if (htim == &hhrtim) //ADC time freq
//	{
//		//		if (cnt % (int)(HI_TIME_FREQ / SAMPLE_TIME_FREQ) == 0)
//		//		{
//		//		}
//		if (color_selector == 0)
//		{
//			HAL_GPIO_WritePin(CIS_LED_B_GPIO_Port, CIS_LED_B_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(CIS_LED_R_GPIO_Port, CIS_LED_R_Pin, GPIO_PIN_RESET);
//		}
//		else if (color_selector == 1)
//		{
//			HAL_GPIO_WritePin(CIS_LED_R_GPIO_Port, CIS_LED_R_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(CIS_LED_G_GPIO_Port, CIS_LED_G_Pin, GPIO_PIN_RESET);
//		}
//		else if (color_selector == 2)
//		{
//			HAL_GPIO_WritePin(CIS_LED_G_GPIO_Port, CIS_LED_G_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(CIS_LED_B_GPIO_Port, CIS_LED_B_Pin, GPIO_PIN_RESET);
//		}
//		else
//		{
//			HAL_GPIO_WritePin(CIS_LED_R_GPIO_Port, CIS_LED_R_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(CIS_LED_G_GPIO_Port, CIS_LED_G_Pin, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(CIS_LED_B_GPIO_Port, CIS_LED_B_Pin, GPIO_PIN_RESET);
//		}
//
//		if (pixel_cnt == 0)
//		{
//			HAL_GPIO_WritePin(CIS_SP_GPIO_Port, CIS_SP_Pin, GPIO_PIN_SET);
//		}
//		else if (pixel_cnt == 4)
//		{
//			HAL_GPIO_WritePin(CIS_SP_GPIO_Port, CIS_SP_Pin, GPIO_PIN_RESET);;
//		}
//
//		pixel_cnt++;
//		if (pixel_cnt > (ADC_CONVERTED_DATA_BUFFER_SIZE * 2))
//		{
//			pixel_cnt = 0;
//			color_selector++;
//			if (color_selector > 2)
//			{
//				color_selector = 0;
//			}
//		}
//	}
//}

///**
// * @brief  Conversion complete callback in non-blocking mode
// * @param  hadc: ADC handle
// * @retval None
// */
//void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
//{
//	/* Invalidate Data Cache to get the updated content of the SRAM on the first half of the ADC converted data buffer: 32 bytes */
//	SCB_InvalidateDCache_by_Addr((uint32_t *) &aADCxConvertedData[0], ADC_CONVERTED_DATA_BUFFER_SIZE);
//}
//
///**
// * @brief  Conversion DMA half-transfer callback in non-blocking mode
// * @param  hadc: ADC handle
// * @retval None
// */
//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
//{
//	/* Invalidate Data Cache to get the updated content of the SRAM on the second half of the ADC converted data buffer: 32 bytes */
//	SCB_InvalidateDCache_by_Addr((uint32_t *) &aADCxConvertedData[ADC_CONVERTED_DATA_BUFFER_SIZE/2], ADC_CONVERTED_DATA_BUFFER_SIZE);
//}
