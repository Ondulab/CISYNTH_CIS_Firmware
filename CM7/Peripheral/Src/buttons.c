/**
 ******************************************************************************
 * @file           : buttons.c
 * @brief          : 5 key keybord driver
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
#include "buttons.h"
#include "ssd1362.h"
#include "config.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
buttonStateTypeDef  buttonState[5] = {0};

static GPIO_TypeDef* BUTTON_PORT[KEY_NUMBER] = {SW_1_GPIO_Port,
												    SW_2_GPIO_Port,
												    SW_3_GPIO_Port,
												    SW_4_GPIO_Port,
												    SW_5_GPIO_Port
                                                   };

static const uint16_t BUTTON_PIN[KEY_NUMBER] = {SW_1_Pin,
												    SW_2_Pin,
												    SW_3_Pin,
												    SW_4_Pin,
											        SW_5_Pin
                                                   };

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
 * @brief EXTI line detection callbacks
 * @param GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	switch (GPIO_Pin)
	{
	case SW_1_Pin:
		buttonState[SW1] = SWITCH_PRESSED;
		break;
	case SW_2_Pin:
		buttonState[SW2] = SWITCH_PRESSED;
		break;
	case SW_3_Pin:
		buttonState[SW3] = SWITCH_PRESSED;
		break;
	case SW_4_Pin:
		buttonState[SW4] = SWITCH_PRESSED;
		break;
	case SW_5_Pin:
		buttonState[SW5] = SWITCH_PRESSED;
		break;
	}
}
