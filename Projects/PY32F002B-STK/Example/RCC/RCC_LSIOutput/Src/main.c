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
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_EnbaleLSI(void);

/**
  * @brief   Main program.
  * @retval  int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();

  /* Initialization button */
  BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

  /* Wait for the button to be pressed */
  while (BSP_PB_GetState(BUTTON_KEY))
  {
  }
  
  /* Enable LSI */
  APP_EnbaleLSI();
  
  /* Configure PA07 pin as MCO function, output LSI clock */
  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCOSOURCE_LSI, RCC_MCODIV_1);

  while (1)
  {
  }
}

/**
  * @brief   System clock configuration function.
  * @param   None
  * @retval  None
  */
static void APP_EnbaleLSI(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Oscillator configuration */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI;         /* Select oscillator LSI */
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;                           /* Enable LSI */
  RCC_OscInitStruct.LSICalibrationValue = RCC_LSICALIBRATION_32768Hz;
  /* Configure oscillator */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief   Error executing function
  * @param   None
  * @retval  None
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
