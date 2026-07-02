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
TIM_IC_InitTypeDef   sICConfig;

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
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);
    
  TimHandle.Instance = TIM1;                                            /* TIM1 */
  TimHandle.Init.Period            = 8000 - 1;                          /* Period = 8000 - 1 */
  TimHandle.Init.Prescaler         = 3000 - 1;                          /* Prescaler = 3000 - 1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;            /* ClockDivision = 0 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                /* Counter direction = Up */
  TimHandle.Init.RepetitionCounter = 1 - 1;                             /* Repetition = 0 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;    /* Auto-reload register not buffered */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                          /* Initialize TIM1 */
  {
    APP_ErrorHandler();
  }

  /* Select the edge of the active transition on the TI1 channel: rising edge */
  sICConfig.ICPolarity  = TIM_ICPOLARITY_RISING;                               
  /* Select the active input: IC1 = TI1FP1 */
  sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;                             
  /* Set input prescaler: prescaler is disabled */
  sICConfig.ICPrescaler = TIM_ICPSC_DIV1;                                      
  /* Configure the input filter duration: no filter needed */
  sICConfig.ICFilter    = 0;                                                    
  /* Configure the Input Capture of channel 1 */
  if (HAL_TIM_IC_ConfigChannel(&TimHandle, &sICConfig, TIM_CHANNEL_1) != HAL_OK) 
  {
    APP_ErrorHandler();
  }
  /* Start the Input Capture in interrupt mode */
  if (HAL_TIM_IC_Start_IT(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                    
  {
    APP_ErrorHandler();
  }
  while (1)
  {

  }
}

/**
  * @brief  TIM IC Capture Callback
  * @param  None
  * @retval None
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  /* LED Toggle */
  BSP_LED_Toggle(LED_GREEN);
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
