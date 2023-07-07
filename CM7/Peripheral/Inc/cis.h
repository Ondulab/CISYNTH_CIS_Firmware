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
#include "arm_math.h"

typedef enum
{
	CIS_BUFFER_OFFSET_NONE = 0,
	CIS_BUFFER_OFFSET_HALF,
	CIS_BUFFER_OFFSET_FULL,
}CIS_BUFF_StateTypeDef;

typedef enum
{
	CIS_RED = 0,
	CIS_GREEN,
	CIS_BLUE,
}CIS_Color_TypeDef;

#define CIS_RED_LINE_OFFSET 		(CIS_START_OFFSET)
#define CIS_GREEN_LINE_OFFSET 		((CIS_LINE_SIZE) + (CIS_START_OFFSET))
#define CIS_BLUE_LINE_OFFSET  		((CIS_LINE_SIZE * 2)) + (CIS_START_OFFSET)

/* Includes ------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

void cis_Init(void);
void cis_GetRGBImage(float32_t *redLine, float32_t *greenLine, float32_t *blueLine, int32_t oversampling);
void cis_ImageProcessRGB(int32_t *cis_buff);
void cis_ImageProcessRGB_Calibration(float32_t *cisCalData, uint16_t iterationNb);
void cis_Start_capture(void);
void cis_Stop_capture(void);
void cis_LedsOn(void);
void cis_LedsOff(void);
void cis_LedPowerAdj(int32_t red_pwm, int32_t green_pwm, int32_t blue_pwm);

#endif /* __CIS_H__ */
