/**
  ******************************************************************************
  * @file    BSP/Src/mmc.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use the MMC Driver
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "BSP_example.h"

/** @addtogroup STM32H7xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BLOCK_START_ADDR         0     /* Block start address      */
#define NUM_OF_BLOCKS            5     /* Total number of blocks   */
#define BUFFER_WORDS_SIZE        ((MMC_BLOCKSIZE * NUM_OF_BLOCKS) >> 2) /* Total data size in bytes */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t aTxBuffer[BUFFER_WORDS_SIZE];
uint32_t aRxBuffer[BUFFER_WORDS_SIZE];
__IO uint32_t MMCWriteStatus = 0, MMCReadStatus = 0;
/* Private function prototypes -----------------------------------------------*/
static void MMC_SetHint(void);
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset);
static uint8_t Buffercmp(uint32_t* pBuffer1, uint32_t* pBuffer2, uint16_t BufferLength);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  MMC Demo
  * @param  None
  * @retval None
  */
void MMC_demo (void)
{
int32_t MMC_state ;
  MMC_SetHint();

  MMC_state = BSP_MMC_Init(0);

  GUI_SetTextColor(GUI_COLOR_BLACK);

  if(MMC_state != BSP_ERROR_NONE)
  {
    GUI_SetTextColor(GUI_COLOR_RED);
    GUI_DisplayStringAt(20, 100, (uint8_t *)"MMC INITIALIZATION : FAIL.", LEFT_MODE);
    GUI_DisplayStringAt(20, 115, (uint8_t *)"MMC Test Aborted.", LEFT_MODE);
  }
  else
  {
    GUI_DisplayStringAt(20, 100, (uint8_t *)"MMC INITIALIZATION : OK.", LEFT_MODE);

    MMC_state = BSP_MMC_Erase(0,BLOCK_START_ADDR, (MMC_BLOCKSIZE * NUM_OF_BLOCKS));
    while(BSP_MMC_GetCardState(0) != MMC_TRANSFER_OK)
    {
    }

    if(MMC_state != BSP_ERROR_NONE)
    {
      GUI_SetTextColor(GUI_COLOR_RED);
      GUI_DisplayStringAt(20, 115, (uint8_t *)"MMC ERASE : FAILED.", LEFT_MODE);
      GUI_DisplayStringAt(20, 130, (uint8_t *)"MMC Test Aborted.", LEFT_MODE);
    }
    else
    {
      GUI_DisplayStringAt(20, 115, (uint8_t *)"MMC ERASE : OK.", LEFT_MODE);

      /* Fill the buffer to write */
      Fill_Buffer(aTxBuffer, BUFFER_WORDS_SIZE, 0x22FF);
      MMC_state = BSP_MMC_WriteBlocks(0,(uint32_t *)aTxBuffer, BLOCK_START_ADDR, NUM_OF_BLOCKS);

      /* Wait until MMC cards are ready to use for new operation */
      while(BSP_MMC_GetCardState(0) != MMC_TRANSFER_OK)
      {
      }
      if(MMC_state != BSP_ERROR_NONE)
      {
        GUI_SetTextColor(GUI_COLOR_RED);
        GUI_DisplayStringAt(20, 130, (uint8_t *)"MMC WRITE : FAILED.", LEFT_MODE);
        GUI_DisplayStringAt(20, 145, (uint8_t *)"MMC Test Aborted.", LEFT_MODE);
      }
      else
      {
        GUI_DisplayStringAt(20, 130, (uint8_t *)"MMC WRITE : OK.", LEFT_MODE);
        MMC_state = BSP_MMC_ReadBlocks(0,(uint32_t *)aRxBuffer, BLOCK_START_ADDR, NUM_OF_BLOCKS);

        /* Wait until MMC cards are ready to use for new operation */
        while(BSP_MMC_GetCardState(0) != MMC_TRANSFER_OK)
        {
        }
        if(MMC_state != BSP_ERROR_NONE)
        {
          GUI_SetTextColor(GUI_COLOR_RED);
          GUI_DisplayStringAt(20, 145, (uint8_t *)"MMC READ : FAILED.", LEFT_MODE);
          GUI_DisplayStringAt(20, 160, (uint8_t *)"MMC Test Aborted.", LEFT_MODE);
        }
        else
        {
          GUI_DisplayStringAt(20, 145, (uint8_t *)"MMC READ : OK.", LEFT_MODE);
          if(Buffercmp(aTxBuffer, aRxBuffer, BUFFER_WORDS_SIZE) > 0)
          {
            GUI_SetTextColor(GUI_COLOR_RED);
            GUI_DisplayStringAt(20, 160, (uint8_t *)"MMC COMPARE : FAILED.", LEFT_MODE);
            GUI_DisplayStringAt(20, 175, (uint8_t *)"MMC Test Aborted.", LEFT_MODE);
          }
          else
          {
            GUI_SetTextColor(GUI_COLOR_GREEN);
            GUI_DisplayStringAt(20, 160, (uint8_t *)"MMC TEST : OK.", LEFT_MODE);
          }
        }
      }
    }
  }

  while (1)
  {

    if(CheckForUserInput() > 0)
    {
      return;
    }
  }
}


/**
  * @brief Tx Transfer completed callbacks
  * @param None
  * @retval None
  */
void BSP_MMC_WriteCpltCallback(uint32_t Instance)
{
  MMCWriteStatus = 1;

}

/**
  * @brief Rx Transfer completed callbacks
  * @param None
  * @retval None
  */
void BSP_MMC_ReadCpltCallback(uint32_t Instance)
{
  MMCReadStatus = 1;
}

/**
  * @brief  Display MMC Demo Hint
  * @param  None
  * @retval None
  */
static void MMC_SetHint(void)
{
  uint32_t x_size, y_size;

  BSP_LCD_GetXSize(0, &x_size);
  BSP_LCD_GetYSize(0, &y_size);
  /* Clear the LCD */
  GUI_Clear(GUI_COLOR_WHITE);

  /* Set LCD Demo description */
  GUI_SetTextColor(GUI_COLOR_BLUE);
  GUI_FillRect(0, 0, x_size, 80, GUI_COLOR_BLUE);
  GUI_SetTextColor(GUI_COLOR_WHITE);
  GUI_SetBackColor(GUI_COLOR_BLUE);
  GUI_SetFont(&Font24);
  GUI_DisplayStringAt(0, 0, (uint8_t *)"MMC", CENTER_MODE);
  GUI_SetFont(&Font12);
  GUI_DisplayStringAt(0, 30, (uint8_t *)"This example shows how to write", CENTER_MODE);
  GUI_DisplayStringAt(0, 45, (uint8_t *)"and read data on the microMMC and also", CENTER_MODE);
  GUI_DisplayStringAt(0, 60, (uint8_t *)"how to detect the presence of the card", CENTER_MODE);

  /* Set the LCD Text Color */
  GUI_SetTextColor(GUI_COLOR_BLUE);
  GUI_DrawRect(10, 90, x_size - 20, y_size - 100, GUI_COLOR_BLUE);
  GUI_DrawRect(11, 91, x_size - 22, y_size - 102, GUI_COLOR_BLUE);

  GUI_SetTextColor(GUI_COLOR_BLACK);
  GUI_SetBackColor(GUI_COLOR_WHITE);
 }

/**
  * @brief  Fills buffer with user predefined data.
  * @param  pBuffer: pointer on the buffer to fill
  * @param  uwBufferLenght: size of the buffer to fill
  * @param  uwOffset: first value to fill on the buffer
  * @retval None
  */
static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset)
{
  uint32_t tmpIndex = 0;

  /* Put in global buffer different values */
  for (tmpIndex = 0; tmpIndex < uwBufferLenght; tmpIndex++ )
  {
    pBuffer[tmpIndex] = tmpIndex + uwOffset;
  }
}

/**
  * @brief  Compares two buffers.
  * @param  pBuffer1, pBuffer2: buffers to be compared.
  * @param  BufferLength: buffer's length
  * @retval 1: pBuffer identical to pBuffer1
  *         0: pBuffer differs from pBuffer1
  */
static uint8_t Buffercmp(uint32_t* pBuffer1, uint32_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
