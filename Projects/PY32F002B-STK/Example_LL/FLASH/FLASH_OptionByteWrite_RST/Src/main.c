/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
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
#define MODE_PC0 OB_SWD_PB6_GPIO_PC0
//#define MODE_PC0 OB_SWD_PB6_NRST_PC0


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_FlashOBProgram(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Initialize SysTick */
  HAL_Init();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  if(READ_BIT(FLASH->OPTR, OB_USER_SWD_NRST_MODE)!= MODE_PC0 )
  {
    /* Option byte program */
    APP_FlashOBProgram();
  }
  else
  {
    BSP_LED_On(LED_GREEN);
  }

  while(1)
  {
  }
}

/**
  * @brief  Option byte program
  * @param  None
  * @retval None
  */
static void APP_FlashOBProgram(void)
{
  FLASH_OBProgramInitTypeDef OBInitCfg;

  /* Unlock the Flash to enable the flash control register access */
  HAL_FLASH_Unlock();

  /* Unlock the Flash to enable access to the part of flash control register that is about option byte */
  HAL_FLASH_OB_Unlock();

  /* Initialize FLASH Option Bytes PROGRAM structure */
  OBInitCfg.OptionType = OPTIONBYTE_USER;
  OBInitCfg.USERType = OB_USER_BOR_EN | OB_USER_BOR_LEV | OB_USER_IWDG_SW | OB_USER_IWDG_STOP | OB_USER_SWD_NRST_MODE;
  OBInitCfg.USERConfig = OB_BOR_DISABLE | OB_BOR_LEVEL_3p1_3p2 | OB_IWDG_SW | OB_IWDG_STOP_ACTIVE | MODE_PC0 ;

  /* Execute option byte program */
  HAL_FLASH_OBProgram(&OBInitCfg);

  /* Lock the Flash to disable the flash control register access */
  HAL_FLASH_Lock();

  /* Lock the Flash to disable access to the part of flash control register that is about option byte */
  HAL_FLASH_OB_Lock();

  /* Generate a reset and let option byte reload */
  HAL_FLASH_OB_Launch();
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
