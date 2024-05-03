
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_filex.c
  * @author  MCD Application Team
  * @brief   FileX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_filex.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* Main thread stack size */
#define FX_APP_THREAD_STACK_SIZE         2*1024
/* Main thread priority */
#define FX_APP_THREAD_PRIO               10

/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* Main thread global data structures.  */
TX_THREAD       fx_app_thread;

/* Buffer for FileX FX_MEDIA sector cache. */
ALIGN_32BYTES (uint32_t fx_nor_qspi_media_memory[FX_NOR_QSPI_SECTOR_SIZE / sizeof(uint32_t)]);
/* Define FileX global data structures.  */
FX_MEDIA        nor_qspi_flash_disk;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* Main thread entry function.  */
void fx_app_thread_entry(ULONG thread_input);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/**
  * @brief  Application FileX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT MX_FileX_Init(VOID *memory_ptr)
{
  UINT ret = FX_SUCCESS;

  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;
  VOID *pointer;

  /* USER CODE BEGIN MX_FileX_MEM_POOL */

  /* USER CODE END MX_FileX_MEM_POOL */

  /* USER CODE BEGIN 0 */

  /* USER CODE END 0 */

  /*Allocate memory for the main thread's stack*/
  ret = tx_byte_allocate(byte_pool, &pointer, FX_APP_THREAD_STACK_SIZE, TX_NO_WAIT);

  /* Check FX_APP_THREAD_STACK_SIZE allocation*/
  if (ret != FX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the main thread.  */
  ret = tx_thread_create(&fx_app_thread, FX_APP_THREAD_NAME, fx_app_thread_entry, 0, pointer, FX_APP_THREAD_STACK_SIZE,
                         FX_APP_THREAD_PRIO, FX_APP_PREEMPTION_THRESHOLD, FX_APP_THREAD_TIME_SLICE, FX_APP_THREAD_AUTO_START);

  /* Check main thread creation */
  if (ret != FX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }
  /* USER CODE BEGIN MX_FileX_Init */

  /* USER CODE END MX_FileX_Init */

  /* Initialize FileX.  */
  fx_system_initialize();

  /* USER CODE BEGIN MX_FileX_Init 1*/

  /* USER CODE END MX_FileX_Init 1*/

  return ret;
}

 /**
 * @brief  Main thread entry.
 * @param thread_input: ULONG user argument used by the thread entry
 * @retval none
 */
void fx_app_thread_entry(ULONG thread_input)
{
  UINT nor_qspi_status = FX_SUCCESS;
  /* USER CODE BEGIN fx_app_thread_entry 0 */

  /* USER CODE END fx_app_thread_entry 0 */

  /* Format the QUAD-SPI NOR flash as FAT */
  nor_qspi_status =  fx_media_format(&nor_qspi_flash_disk,                                                               // nor_qspi_flash_disk pointer
                                     fx_stm32_levelx_nor_driver,                                                         // Driver entry
                                     (VOID *)LX_NOR_QSPI_DRIVER_ID,                                                      // Device info pointer
                                     (UCHAR *) fx_nor_qspi_media_memory,                                                 // Media buffer pointer
                                     sizeof(fx_nor_qspi_media_memory),                                                   // Media buffer size
                                     FX_NOR_QSPI_VOLUME_NAME,                                                            // Volume Name
                                     FX_NOR_QSPI_NUMBER_OF_FATS,                                                         // Number of FATs
                                     32,                                                                                 // Directory Entries
                                     FX_NOR_QSPI_HIDDEN_SECTORS,                                                         // Hidden sectors
                                     ((LX_STM32_QSPI_FLASH_SIZE - LX_STM32_QSPI_SECTOR_SIZE) / FX_NOR_QSPI_SECTOR_SIZE), // Total sectors minus one
                                     FX_NOR_QSPI_SECTOR_SIZE,                                                            // Sector size
                                     8,                                                                                  // Sectors per cluster
                                     1,                                                                                  // Heads
                                     1);                                                                                 // Sectors per track

  /* Check the format nor_qspi_status */
  if (nor_qspi_status != FX_SUCCESS)
  {
    /* USER CODE BEGIN QUAD-SPI NOR format error */
    while(1);
    /* USER CODE END QUAD-SPI NOR format error */
  }

  /* Open the QUAD-SPI NOR driver */
  nor_qspi_status =  fx_media_open(&nor_qspi_flash_disk, FX_NOR_QSPI_VOLUME_NAME, fx_stm32_levelx_nor_driver, (VOID *)LX_NOR_QSPI_DRIVER_ID, (VOID *) fx_nor_qspi_media_memory, sizeof(fx_nor_qspi_media_memory));

  /* Check the media open nor_qspi_status */
  if (nor_qspi_status != FX_SUCCESS)
  {
    /* USER CODE BEGIN QUAD-SPI NOR open error */
    while(1);
    /* USER CODE END QUAD-SPI NOR open error */
  }

  /* USER CODE BEGIN fx_app_thread_entry 1 */

  /* USER CODE END fx_app_thread_entry 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
