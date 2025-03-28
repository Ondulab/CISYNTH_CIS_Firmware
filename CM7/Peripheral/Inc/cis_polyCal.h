/**
 ******************************************************************************
 * @file           : cis_polyCal.h
 ******************************************************************************
 * @attention
 *
 * Copyright (C) 2018-present Reso-nance Numerique.
 * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CIS_POLYCAL_H__
#define __CIS_POLYCAL_H__

#include "cis.h"

/* Structure pour une ligne de couleur */
struct ColorLine{
    float32_t* line;
    struct CalibrationCoefficients* coeff;
};

/*
struct RGB_CalibrationCoefficients{
     struct CalibrationCoefficients redCoeff;
     struct CalibrationCoefficients greenCoeff;
     struct CalibrationCoefficients blueCoeff;
};
*/

/* Includes ------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

void cis_convertRAWImageToRGBImage(struct RAWImage* RAWImage, int32_t* RGBimage);
void cis_startPolyCalibration(uint16_t iterationNb);
void cis_calibrate(struct RAWImage* rawImage);
void cis_applyCalibration(struct RAWImage* RAWImage, struct cisRGB_Calibration* rgbCalibration);
void cis_calibrateLeds(void);

#endif /* __CIS_POLYCAL_H__ */
