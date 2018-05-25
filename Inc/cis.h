/**
  ******************************************************************************
  * @file           : cis.h
  * @brief          : Header for cis.c file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CIS_H__
#define __CIS_H__

#define HI_TIME_FREQ 		(1000000)
#define DAC_TIME_FREQ 		(500)
#define CIS_PIXELS			(10200)
#define ADC_CONVERTED_DATA_BUFFER_SIZE	(CIS_PIXELS + 4)

/* Includes ------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

void cisInit(void);

#endif /* __CIS_H__ */
