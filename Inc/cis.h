/**
  ******************************************************************************
  * @file           : cis.h
  * @brief          : Header for cis.c file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CIS_H__
#define __CIS_H__

#define HI_TIME_FREQ 		(600000)
#define DAC_TIME_FREQ 		(100) // 1Hz to 1Khz
#define CIS_PIXELS_NB		(1275)

/* Includes ------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

void cisInit(void);

#endif /* __CIS_H__ */
