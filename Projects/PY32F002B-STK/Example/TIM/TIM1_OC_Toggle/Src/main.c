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
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef   sConfig;

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
      
  TimHandle.Instance = TIM1;                                                      /* TIM1 */
  TimHandle.Init.Period            = 8000 - 1;                                    /* Period = 8000 - 1 */
  TimHandle.Init.Prescaler         = 3000 - 1;                                    /* Prescaler = 3000 - 1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                      /* ClockDivision = 0 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                          /* Counter direction = Up */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                       /* Repetition = 0 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;              /* Auto-reload register not buffered */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                    /* Initialize TIM1 */
  {
    APP_ErrorHandler();
  }

  sConfig.OCMode       = TIM_OCMODE_TOGGLE;                                       /* Set output compare mode: TOGGLE */
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                                     /* OC Polarity High */
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;                                      /* Disable OC Fast Mode */
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                    /* OCN Polarity High */
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                                  /* OCN Idle state reset */
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;                                   /* OC Idle state reset */
  
  sConfig.Pulse = 2000;                                                           /* OC1 value 2000 */
  if (HAL_TIM_OC_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)    /* OC1 Channel Config */
  {
    APP_ErrorHandler();
  }

  if (HAL_TIM_OC_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                      /* TIM OC1 Start */
  {
    APP_ErrorHandler();
  }

  while (1)
  {

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
