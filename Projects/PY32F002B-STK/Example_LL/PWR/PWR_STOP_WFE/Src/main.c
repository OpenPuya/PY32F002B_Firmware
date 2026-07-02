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
/* Private variables ---------------------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ExtiConfig(void);
static void APP_EnterStop(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Enable PWR clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize Button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* Initial EXTI Event */
  APP_ExtiConfig();

  /* Light up LED */
  BSP_LED_On(LED_GREEN);

  /* Wait for the BUTTON to be pressed */
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }

  /* LED off */
  BSP_LED_Off(LED_GREEN);

  /* Enter STOP mode */
  APP_EnterStop();

  while (1)
  {
    /* Toggle LED */
    BSP_LED_Toggle(LED_GREEN);

    /* Delay 200ms */
    LL_mDelay(200);
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

  /* Set AHB divider:HCLK = SYSCLK */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* HSISYS used as SYSCLK source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSISYS);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSISYS)
  {
  }

  /* Set APB1 divider */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(24000000);

  /* Update the system clock global variable SystemCoreClock (can also be updated by calling the SystemCoreClockUpdate() function) */
  LL_SetSystemCoreClock(24000000);
}

/**
  * @brief  Configure Exti
  * @param  None
  * @retval None
  */
static void APP_ExtiConfig(void)
{
   LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
   LL_EXTI_InitTypeDef EXTI_InitStruct = {0};

   /* Enable GPIOA clock */
   LL_IOP_GRP1_EnableClock (LL_IOP_GRP1_PERIPH_GPIOA);

   /* Choose PA06 Pin */
   GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
   /* Choose input mode */
   GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
   /* Choose pull up */
   GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
   /* Initialze GPIOA */
   LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   /* Configure PA6 as the EXTI6 interrupt input */
   LL_EXTI_SetEXTISource(LL_EXTI_CONFIG_PORTA,LL_EXTI_CONFIG_LINE6);

   /* Enable EXTI6 */
   EXTI_InitStruct.Line = LL_EXTI_LINE_6;

   EXTI_InitStruct.LineCommand = ENABLE;
   /* Event mode */
   EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
   /* Trigger Falling Mode */
   EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
   /* Initialize the EXTI registers according to the specified parameters in EXTI_InitStruct  */
   LL_EXTI_Init(&EXTI_InitStruct);
}

/**
  * @brief  Enter Stop mode
  * @param  None
  * @retval None
  */
static void APP_EnterStop(void)
{
  /* Enable PWR clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* STOP mode with low power regulator ON */
  LL_PWR_SetLprMode(LL_PWR_LPR_MODE_LPR);

  /* STOP mode with deep low power regulator ON (some devices may not be supported) */
  /* LL_PWR_SetLprMode(LL_PWR_LPR_MODE_DLPR); */

  /* SRAM retention voltage aligned with digital LDO output */
  LL_PWR_SetStopModeSramVoltCtrl(LL_PWR_SRAM_RETENTION_VOLT_CTRL_LDO);

  /* Enter DeepSleep mode */
  LL_LPM_EnableDeepSleep();

  /* Request Wait For Event */
   __SEV();
   __WFE();
   __WFE();

   LL_LPM_EnableSleep();
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
