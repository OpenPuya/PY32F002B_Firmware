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
#define  PERIOD_VALUE       (uint32_t)(2000 - 1)
#define  PULSE1_VALUE       400
#define  PULSE2_VALUE       800
#define  PULSE3_VALUE       1200
#define  PULSE4_VALUE       1600

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef    TimHandle;
TIM_OC_InitTypeDef   sConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_TimConfig(void);
static void APP_TimPwmConfig(void);


/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */ 
  HAL_Init();
  
  /* TIM Config */
  APP_TimConfig();

  /* TIM PWM Config */
  APP_TimPwmConfig();

  /* Channel1 Start PWM */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  /* Channel2 Start PWM */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  /* Channel3 Start PWM */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }

  /* Channel4 Start PWM */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_4) != HAL_OK)                  
  {
    APP_ErrorHandler();
  }
  while (1)
  {
    
  }
}

/**
  * @brief  TIM Configure
  * @param  None
  * @retval None
  */
static void APP_TimConfig(void)
{
  /* TIM1 */
  TimHandle.Instance = TIM1;                                                  
  
  /* Period = 2000 - 1  */
  TimHandle.Init.Period            = 2000-1;                                     

  /* Prescaler = 1200 - 1 */
  TimHandle.Init.Prescaler         = 1200 - 1;                                 

  /* ClockDivision = 0  */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  

  /* Counter direction = Up */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                      

  /* Repetition = 0 */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                   

  /* Auto-reload register not buffered  */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;          

  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                
  {
    APP_ErrorHandler();
  }

}
/**
  * @brief  TIM1 PWM Configure
  * @param  None
  * @retval None
  */
static void APP_TimPwmConfig(void)
{
  /* Set output compare mode: PWM1 */
  sConfig.OCMode       = TIM_OCMODE_PWM1;                                     

  /* OC channel output high level effective */
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;                                 

  /* Disable OC FastMode */
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;                                  

  /* OCN channel output high level effective */
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                

  /* Idle state OC1N output low level */
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;                              

  /* Idle state OC1 output low level*/
  sConfig.OCIdleState  = TIM_OCIDLESTATE_RESET;                               

  sConfig.Pulse = PULSE1_VALUE;                                              

  /* Channel 1 configuration */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sConfig.Pulse = PULSE2_VALUE;                                               

  /* Channel 2 configuration */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sConfig.Pulse = PULSE3_VALUE;                                              

  /* Channel 3 configuration */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_3) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  sConfig.Pulse = PULSE4_VALUE;                                               

  /* Channel 4 configuration */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_4) != HAL_OK)
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
