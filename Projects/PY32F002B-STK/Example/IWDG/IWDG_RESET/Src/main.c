/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
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
IWDG_HandleTypeDef   IwdgHandle;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */ 
  HAL_Init();

  IwdgHandle.Instance = IWDG;                     /* IWDG */
  IwdgHandle.Init.Prescaler = IWDG_PRESCALER_32;  /* Prescaler DIV 32 */
  IwdgHandle.Init.Reload = (1000);                /* IWDG Reload value 1000 */

  if (HAL_IWDG_Init(&IwdgHandle) != HAL_OK)       /* Initialize the IWDG */
  {
    APP_ErrorHandler();
  }

  while (1)
  {

    HAL_Delay(900);                               /* Feed the dog every 900ms to ensure normal operation */
    
    /* HAL_Delay(1100);*/                         /* Feed the dog every 1.1 seconds, unable to function properly */
    
    BSP_LED_Toggle(LED_GREEN);                    /* LED Toggle */
    /* Refresh the Iwdg */
    if (HAL_IWDG_Refresh(&IwdgHandle) != HAL_OK)
    {
      APP_ErrorHandler();
    }
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
