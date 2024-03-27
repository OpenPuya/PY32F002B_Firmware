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
TIM_OC_InitTypeDef   sConfig1,sConfig2,sConfig3;
__IO uint32_t uwStep = 0;

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
  TimHandle.Init.Period            = 100 - 1;                                     /* Period = 100 - 1 */
  TimHandle.Init.Prescaler         = 24 - 1;                                      /* Prescaler = 24 - 1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                      /* ClockDivision = 0 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                          /* Counter direction = Up */
  TimHandle.Init.RepetitionCounter = 1 - 1;                                       /* Repetition = 0 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;              /* Auto-reload register not buffered */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                    /* Initialize TIM1 */
  {
    APP_ErrorHandler();
  }

  /* PWM Config */
  sConfig1.OCMode       = TIM_OCMODE_TIMING;                                      /* Channel Mode: TIMING */
  sConfig1.OCPolarity   = TIM_OCPOLARITY_HIGH;                                    /* Channel effective polarity: high level */
  sConfig1.OCNPolarity  = TIM_OCNPOLARITY_HIGH;                                   /* Complementary channel effective polarity: high level */
  sConfig1.OCIdleState  = TIM_OCNIDLESTATE_RESET;                                 /* Channel idle state: low level */
  sConfig1.OCNIdleState = TIM_OCNIDLESTATE_RESET;                                 /* Complementary channel idle state: low level */
  sConfig1.OCFastMode   = TIM_OCFAST_DISABLE;                                     /* Disable OC Fast Mode */
  /* Configure Channel 1 Comparison Value 50 */
  sConfig1.Pulse        = 50 - 1;
  /* Configure TIM1 Channel1 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  sConfig2 = sConfig1;
  /* Configure Channel 2 Comparison Value 50 */
  sConfig2.Pulse        = 50 - 1;
  /* Configure TIM1 Channel2 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  sConfig3 = sConfig1;
  /* Configure Channel 3 Comparison Value 50 */
  sConfig3.Pulse        = 50 - 1;
  /* Configure TIM1 Channel3 */
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Configuring commutation events: software mode */
  HAL_TIMEx_ConfigCommutEvent_IT(&TimHandle, TIM_TS_NONE, TIM_COMMUTATION_SOFTWARE);
  
  while (1)
  {

  }
}

/**
  * @brief   Commutation interrupt callback function
  * @param   htim：TIM Handle
  * @retval  None
  */
void HAL_TIMEx_CommutCallback(TIM_HandleTypeDef *htim)
{
  if (uwStep == 0)
  {
    /* Step 1 Configuration */

    /* Channel 1 is configured as PWM1 */
    sConfig1.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);
    
    /* Start CH1 */
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);
    /* Stop CH1N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_1);

    /* Channel 3 is configured as PWM1 */
    sConfig3.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);
    
    /* Start CH3N */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3);
    /* Stop CH3 */
    HAL_TIM_PWM_Stop(&TimHandle, TIM_CHANNEL_3);

    /* Stop CH2 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_2);
    /* Stop CH2N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_2);
    
    uwStep = 1;
  }

  else if (uwStep == 1)
  {
    /* Step 2 Configuration */
    
    /* Channel 2 is configured as PWM1 */
    sConfig2.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2);
    
    /* Start CH2N */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_2);
    
    /* Stop CH3N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_3);

    uwStep++;
  }

  else if (uwStep == 2)
  {
    /* Step 3 Configuration */
    
    /* Channel 3 is configured as PWM1 */
    sConfig3.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);
    
    /* Start CH3 */ 
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_3);
    
    /* Stop CH1 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_1);

    uwStep++;
  }

  else if (uwStep == 3)
  {
    /* Step 4 Configuration */
    
    /* Stop CH2N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_2);
    
    /* Channel 1 is configured as PWM1 */
    sConfig1.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);
    
    /* Start CH1N */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_1);
    
    uwStep++;
  }
  else if (uwStep == 4)
  {
    /* Step 5 Configuration */
    
    /* Stop CH3 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_3);

    /* Channel 2 is configured as PWM1 */
    sConfig2.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig2, TIM_CHANNEL_2);
    
    /* Start CH2 */
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2);

    uwStep++;
  }

  else if (uwStep == 5)
  {
    /* Step 6 Configuration */
    
    /* Channel 3 is configured as PWM1 */
    sConfig3.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig3, TIM_CHANNEL_3);
    
    /* Start CH3N */
    HAL_TIMEx_OCN_Start(&TimHandle, TIM_CHANNEL_3);

    /* Stop CH1N */
    HAL_TIMEx_OCN_Stop(&TimHandle, TIM_CHANNEL_1);

    uwStep++;
  }

  else
  {
    /* Step 1 Configuration */
    
    /* Channel 1 is configured as PWM1 */
    sConfig1.OCMode     = TIM_OCMODE_PWM1;
    HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig1, TIM_CHANNEL_1);
    
    /* Start CH1 */
    HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_1);
    
    /* Stop CH2 */
    HAL_TIM_OC_Stop(&TimHandle, TIM_CHANNEL_2);

    uwStep = 1;
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
