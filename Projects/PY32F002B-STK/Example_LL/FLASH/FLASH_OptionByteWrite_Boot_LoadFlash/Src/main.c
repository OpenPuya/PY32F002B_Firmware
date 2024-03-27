/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  FLASH_OBBootProgramInitTypeDef OBootInitCfg={0};

  /* Initialize SysTick */
  HAL_Init();

  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* Initialize USART(for printf use) */
  BSP_USART_Config();

  /* Wait for the BUTTON to be pressed */
  while(BSP_PB_GetState(BUTTON_KEY) == 1);

  /* Unlock the Flash to enable the flash control register access */
  HAL_FLASH_Unlock();

  /* Unlock the Flash to enable access to the part of flash control register that is about option byte */
  HAL_FLASH_OB_Unlock();

  /* Initialize FLASH Option Bytes PROGRAM structure */
  OBootInitCfg.BOOTType= OB_BOOT_MODE_LOADFLASH;
  OBootInitCfg.BOOTSize= OB_BOOT_SIZE_3K;

  /* Execute option byte program */
  HAL_FLASH_OBBOOTProgram(&OBootInitCfg);

  /* Lock the Flash to disable the flash control register access */
  HAL_FLASH_Lock();

  /* Lock the Flash to disable access to the part of flash control register that is about option byte */
  HAL_FLASH_OB_Lock();

  /* Generate a reset and let option byte reload */
  HAL_FLASH_OB_Launch();

  while (1)
  {
  }
}

/**
  * @brief  Error handling function
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  /* Infinite loop */
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file：Pointer to the source file name
  * @param  line：assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add His own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
