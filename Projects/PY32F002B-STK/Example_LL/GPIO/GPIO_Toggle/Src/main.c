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
#include "py32f002bxx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define LED_GPIO_PIN                   LED3_PIN
#define LED_GPIO_PORT                  LED3_GPIO_PORT
#define LED_GPIO_CLK_ENABLE()          LED3_GPIO_CLK_ENABLE()

/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_GpioConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Configure GPIO in output push-pull mode to drive external LEDs */
  APP_GpioConfig();

  /* LED off*/
  LL_GPIO_SetOutputPin(LED_GPIO_PORT, LED_GPIO_PIN);

  while (1)
  {
    /* Toggles the LED. */
    LL_mDelay(100);
    LL_GPIO_TogglePin(LED_GPIO_PORT, LED_GPIO_PIN);
  }
}

/**
  * @brief  Configure Systemclock
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  /* Enable HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB divider: HCLK = SYSCLK */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* HSISYS used as SYSCLK clock source  */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* Set APB1 divider */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(24000000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(24000000);
}

/**
  * @brief  GPIO configuration program
  * @param  None
  * @retval None
  */
static void APP_GpioConfig(void)
{
  /* Enable GPIOA clock */
  LED_GPIO_CLK_ENABLE();

  /* Configure GPIO in output mode */
  LL_GPIO_SetPinMode(LED_GPIO_PORT, LED_GPIO_PIN, LL_GPIO_MODE_OUTPUT);
  /* Default output type (after reset) is push-pull */
  /* LL_GPIO_SetPinOutputType(LED_GPIO_PORT, LED_GPIO_PIN, LL_GPIO_OUTPUT_PUSHPULL); */
  /* Configure GPIO speed in low speed */
  /* LL_GPIO_SetPinSpeed(LED_GPIO_PORT, LED_GPIO_PIN, LL_GPIO_SPEED_FREQ_LOW); */
  /* Default (after reset) is no pull */
  /* LL_GPIO_SetPinPull(LED_GPIO_PORT, LED_GPIO_PIN, LL_GPIO_PULL_NO); */
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
