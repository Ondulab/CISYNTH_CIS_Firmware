/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BSP_example.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define FDCAN2_RX_Pin GPIO_PIN_5
#define FDCAN2_RX_GPIO_Port GPIOB
#define SDIO1_D2_Pin GPIO_PIN_10
#define SDIO1_D2_GPIO_Port GPIOC
#define ARD_D1_Pin GPIO_PIN_6
#define ARD_D1_GPIO_Port GPIOB
#define ARD_D10_Pin GPIO_PIN_4
#define ARD_D10_GPIO_Port GPIOB
#define MII_TX_EN_Pin GPIO_PIN_11
#define MII_TX_EN_GPIO_Port GPIOG
#define LCD_DISP_Pin GPIO_PIN_15
#define LCD_DISP_GPIO_Port GPIOJ
#define ARD_D13_Pin GPIO_PIN_3
#define ARD_D13_GPIO_Port GPIOD
#define SDIO1_D3_Pin GPIO_PIN_11
#define SDIO1_D3_GPIO_Port GPIOC
#define ARD_D12_Pin GPIO_PIN_2
#define ARD_D12_GPIO_Port GPIOI
#define ARD_D9_Pin GPIO_PIN_15
#define ARD_D9_GPIO_Port GPIOH
#define FDCAN1_RX_Pin GPIO_PIN_14
#define FDCAN1_RX_GPIO_Port GPIOH
#define OSC32_OUT_Pin GPIO_PIN_15
#define OSC32_OUT_GPIO_Port GPIOC
#define OSC32_IN_Pin GPIO_PIN_14
#define OSC32_IN_GPIO_Port GPIOC
#define MII_TXD3_Pin GPIO_PIN_2
#define MII_TXD3_GPIO_Port GPIOE
#define ARD_D0_Pin GPIO_PIN_7
#define ARD_D0_GPIO_Port GPIOB
#define MII_TXD1_Pin GPIO_PIN_12
#define MII_TXD1_GPIO_Port GPIOG
#define LCD_DISPD7_Pin GPIO_PIN_7
#define LCD_DISPD7_GPIO_Port GPIOD
#define SDIO1_CK_Pin GPIO_PIN_12
#define SDIO1_CK_GPIO_Port GPIOC
#define ARD_D8_Pin GPIO_PIN_3
#define ARD_D8_GPIO_Port GPIOE
#define SDIO1_D5_Pin GPIO_PIN_9
#define SDIO1_D5_GPIO_Port GPIOB
#define SDIO1_D4_Pin GPIO_PIN_8
#define SDIO1_D4_GPIO_Port GPIOB
#define MII_TXD0_Pin GPIO_PIN_13
#define MII_TXD0_GPIO_Port GPIOG
#define SDIO1_CMD_Pin GPIO_PIN_2
#define SDIO1_CMD_GPIO_Port GPIOD
#define USB_OTG_FS2_ID_Pin GPIO_PIN_10
#define USB_OTG_FS2_ID_GPIO_Port GPIOA
#define VBUS_FS2_Pin GPIO_PIN_9
#define VBUS_FS2_GPIO_Port GPIOA
#define FDCAN1_TX_Pin GPIO_PIN_13
#define FDCAN1_TX_GPIO_Port GPIOH
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define ARD_D7_Pin GPIO_PIN_8
#define ARD_D7_GPIO_Port GPIOI
#define ARD_D6_Pin GPIO_PIN_6
#define ARD_D6_GPIO_Port GPIOE
#define SDIO1_D0_Pin GPIO_PIN_8
#define SDIO1_D0_GPIO_Port GPIOC
#define SDIO1_D1_Pin GPIO_PIN_9
#define SDIO1_D1_GPIO_Port GPIOC
#define ARD_D5_Pin GPIO_PIN_8
#define ARD_D5_GPIO_Port GPIOA
#define USB_OTG_FS2_P_Pin GPIO_PIN_12
#define USB_OTG_FS2_P_GPIO_Port GPIOA
#define USB_OTG_FS2_N_Pin GPIO_PIN_11
#define USB_OTG_FS2_N_GPIO_Port GPIOA
#define MII_RX_ER_Pin GPIO_PIN_10
#define MII_RX_ER_GPIO_Port GPIOI
#define SDIO1_D7_Pin GPIO_PIN_7
#define SDIO1_D7_GPIO_Port GPIOC
#define SDIO1_D6_Pin GPIO_PIN_6
#define SDIO1_D6_GPIO_Port GPIOC
#define LD2_Pin GPIO_PIN_13
#define LD2_GPIO_Port GPIOI
#define ARD_D2_Pin GPIO_PIN_3
#define ARD_D2_GPIO_Port GPIOG
#define LCD_INT_Pin GPIO_PIN_2
#define LCD_INT_GPIO_Port GPIOG
#define OSC_OUT_Pin GPIO_PIN_1
#define OSC_OUT_GPIO_Port GPIOH
#define OSC_IN_Pin GPIO_PIN_0
#define OSC_IN_GPIO_Port GPIOH
#define LCD_BL_Pin GPIO_PIN_0
#define LCD_BL_GPIO_Port GPIOK
#define ARD_D4_Pin GPIO_PIN_1
#define ARD_D4_GPIO_Port GPIOK
#define ARD_A1_Pin GPIO_PIN_8
#define ARD_A1_GPIO_Port GPIOF
#define ARD_A0_Pin GPIO_PIN_0
#define ARD_A0_GPIO_Port GPIOC
#define MII_MDC_Pin GPIO_PIN_1
#define MII_MDC_GPIO_Port GPIOC
#define MII_TXD2_Pin GPIO_PIN_2
#define MII_TXD2_GPIO_Port GPIOC
#define MII_TX_CLK_Pin GPIO_PIN_3
#define MII_TX_CLK_GPIO_Port GPIOC
#define MII_CRS_Pin GPIO_PIN_2
#define MII_CRS_GPIO_Port GPIOH
#define MII_MDIO_Pin GPIO_PIN_2
#define MII_MDIO_GPIO_Port GPIOA
#define MII_RX_CLK_Pin GPIO_PIN_1
#define MII_RX_CLK_GPIO_Port GPIOA
#define MII_COL_Pin GPIO_PIN_3
#define MII_COL_GPIO_Port GPIOH
#define VCP_TX_Pin GPIO_PIN_10
#define VCP_TX_GPIO_Port GPIOB
#define VCP_RX_Pin GPIO_PIN_11
#define VCP_RX_GPIO_Port GPIOB
#define OTG_FS2_OverCurrent_Pin GPIO_PIN_11
#define OTG_FS2_OverCurrent_GPIO_Port GPIOH
#define ARD_D3_Pin GPIO_PIN_6
#define ARD_D3_GPIO_Port GPIOA
#define MII_RX_DV_Pin GPIO_PIN_7
#define MII_RX_DV_GPIO_Port GPIOA
#define ARD_A2_Pin GPIO_PIN_0
#define ARD_A2_GPIO_Port GPIOA
#define OTG_FS2_PSO_Pin GPIO_PIN_5
#define OTG_FS2_PSO_GPIO_Port GPIOA
#define MII_RX_D3_Pin GPIO_PIN_1
#define MII_RX_D3_GPIO_Port GPIOB
#define LD1_Pin GPIO_PIN_2
#define LD1_GPIO_Port GPIOJ
#define LCD_RST_Pin GPIO_PIN_12
#define LCD_RST_GPIO_Port GPIOB
#define ARD_D11_Pin GPIO_PIN_15
#define ARD_D11_GPIO_Port GPIOB
#define MII_RX_D2_Pin GPIO_PIN_0
#define MII_RX_D2_GPIO_Port GPIOB
#define FDCAN2_TX_Pin GPIO_PIN_13
#define FDCAN2_TX_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
