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

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_TimConfig(void);

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
  
  /* Initialize Button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  
  /* Tim Config */
  APP_TimConfig();
  
  /* TIM Start and Enable IT */
  HAL_TIM_Base_Start_IT(&TimHandle);

  while (1)
  {
    
  }
}

/**
  * @brief  Tim Period Elaspsed Callback Function
  * @param  None
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* LED Toggle */
  BSP_LED_Toggle(LED_GREEN);
}

/**
  * @brief  TIM Config
  * @param  None
  * @retval None
  */
static void APP_TimConfig(void)
{ 
  /* TIM1 */
  TimHandle.Instance = TIM1;                                                  
  
  /* Period = 3000 - 1 */
  TimHandle.Init.Period            = 3000 - 1;                                     

  /* Prescaler = 8000 - 1 */
  TimHandle.Init.Prescaler         = 8000 - 1;                                 

  /* ClockDivision = 0 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  

  /* Counter direction = Up */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                      

  /* Repetition = 0 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                   

  /* Auto-reload register not buffered */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          

  /* Initialize TIM1 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                
  {
    APP_ErrorHandler();
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
