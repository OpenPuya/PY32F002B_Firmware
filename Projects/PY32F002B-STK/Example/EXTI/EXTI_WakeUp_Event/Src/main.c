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
EXTI_HandleTypeDef exti_handle;

/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_ConfigureEXTI(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();
  
  /* LED initialization */
  BSP_LED_Init(LED_GREEN);

  /* Initialization button */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  
  /* Configure external events */
  APP_ConfigureEXTI();
  
  /* Pause systick */
  HAL_SuspendTick();
  
  /* Turn on LED */
  BSP_LED_On(LED_GREEN);
  
  /* Waiting for the user to press the button */
  while (BSP_PB_GetState(BUTTON_KEY) == 1)
  {
  }
  
  /* Turn off LED */
  BSP_LED_Off(LED_GREEN);
  
  /* Entering STOP mode */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFE);
  
  /* Restore systick */
  HAL_ResumeTick();
  
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(500);
  }
}

/**
  * @brief  Configure event pins
  * @param  None
  * @retval None
  */
static void APP_ConfigureEXTI(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  __HAL_RCC_GPIOA_CLK_ENABLE();                  /* Enable GPIOA clock */
  GPIO_InitStruct.Mode  = GPIO_MODE_EVT_FALLING; /* GPIO mode is a falling edge event */
  GPIO_InitStruct.Pull  = GPIO_PULLUP;           /* pull up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;  /* The speed is high */
  GPIO_InitStruct.Pin = GPIO_PIN_6;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
  * @brief  Error executing function.
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
  /* Users can add their own printing information as needed,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
