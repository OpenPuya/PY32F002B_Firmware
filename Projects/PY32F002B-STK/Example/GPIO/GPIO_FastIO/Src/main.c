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
#define APP_GpioToggle()  {GPIOA->BSRR = u32High;\
                            GPIOA->BSRR = u32Low; \
                            GPIOA->BSRR = u32High;\
                            GPIOA->BSRR = u32Low; \
                            GPIOA->BSRR = u32High;\
                            GPIOA->BSRR = u32Low; \
                            GPIOA->BSRR = u32High;\
                            GPIOA->BSRR = u32Low; \
                            GPIOA->BSRR = u32High;\
                            GPIOA->BSRR = u32Low;}

/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_GpioInit(void);
static void APP_SystemClockConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  uint32_t u32High = 0x00000002;
  uint32_t u32Low  = 0x00020000;

  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();

  /* Initialize pin PA1 */
  APP_GpioInit();

  /* Configure System Clock */
  APP_SystemClockConfig();

  while (1)
  {
    /* LED flip output approximately 12MHz */
    APP_GpioToggle();
    APP_GpioToggle();
    APP_GpioToggle();
    APP_GpioToggle();
    APP_GpioToggle();
    APP_GpioToggle();
    APP_GpioToggle();
    APP_GpioToggle();
    APP_GpioToggle();
    APP_GpioToggle();
  }
}

/**
  * @brief  GPIO initialization.
  * @param  None
  * @retval None
  */
static void APP_GpioInit()
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();                          /* GPIOA clock enable */

  /* Initialize pin PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;            /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLUP;                    /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     /* GPIO speed */

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);                /* GPIO initialization */
}

/**
  * @brief  Clock configuration function.
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Oscillator configuration */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE; /* Select oscillator HSE, HSI, LSI, LSE */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                           /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                           /* HSI 1 frequency division */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz;  /* Configure the HSI clock to 24MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DISABLE;               /* Close HSE bypass */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                          /* Close LSI */
  /*RCC_OscInitStruct.LSICalibrationValue = RCC_LSICALIBRATION_32768Hz;*/
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;                          /* Close LSE */
  /*RCC_OscInitStruct.LSEDriver = RCC_LSEDRIVE_MEDIUM;*/
  /* Configure oscillator */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Clock source configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* Choose to configure clock HCLK, SYSCLK, PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSISYS; /* Select HSISYS as the system clock */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;        /* AHB clock 1 division */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;         /* APB clock 1 division */
  /* Configure clock source */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    APP_ErrorHandler();
  }
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
