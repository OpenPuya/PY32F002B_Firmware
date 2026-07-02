/**
  ******************************************************************************
  * @file    main.h
  * @author  MCU Application Team
  * @brief   Header for main.c file.
  *          This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 Puya Semiconductor Co.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by Puya under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx_hal.h"
#include "py32f002bxx_Start_Kit.h"

/* Private includes ----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* External FLASH chip: P25Q64 */
#define P25Q64_WRITE_ENABLE             0x06
#define P25Q64_WRITE_DISABLE            0x04
#define P25Q64_PAGE_PROGRAM             0x02
#define P25Q64_SECTOR_ERASE             0x20
#define P25Q64_READ_DATA                0x03
#define P25Q64_READ_Status_Register     0x05

#define SPI_NSS                           GPIO_PIN_6

/* Exported variables prototypes ---------------------------------------------*/
extern SPI_HandleTypeDef Spi1Handle;

/* Exported functions prototypes ---------------------------------------------*/
void APP_ErrorHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
