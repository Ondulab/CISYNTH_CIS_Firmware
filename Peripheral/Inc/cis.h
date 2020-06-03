/**
  ******************************************************************************
  * @file           : cis.h
  * @brief          : Header for cis.c file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CIS_H__
#define __CIS_H__

#include "config.h"
#include "main.h"

#define CIS_LED_R_GPIO_Port ARD_D4_GPIO_Port
#define CIS_LED_G_GPIO_Port ARD_D7_GPIO_Port
#define CIS_LED_B_GPIO_Port ARD_D8_GPIO_Port

#define CIS_LED_R_Pin ARD_D4_Pin
#define CIS_LED_G_Pin ARD_D7_Pin
#define CIS_LED_B_Pin ARD_D8_Pin

enum color { RED, GREEN, BLUE };

__IO uint32_t cis_adc_data[CIS_PIXELS_NB];

#ifdef DEBUG_CIS
extern __IO uint32_t cis_dbg_cnt;
extern __IO uint32_t cis_dbg_data_cal;
extern __IO uint32_t cis_dbg_data;
#endif

/* Includes ------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

void cisInit(void);

#endif /* __CIS_H__ */