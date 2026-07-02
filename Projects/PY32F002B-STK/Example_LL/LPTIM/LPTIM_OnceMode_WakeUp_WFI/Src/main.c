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
#define Delay             40*4

/* Private variables ---------------------------------------------------------*/
LL_LPTIM_InitTypeDef LPTIM_InitStruct = {0};
__IO uint32_t RatioNops = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigLptimClock(void);
static void APP_ConfigLptim(void);
static void APP_EnterStop(void);
static void APP_DelayNops(uint32_t Nops);
static void APP_GpioConfig(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);
  
  /* Initialize PA3 */
  APP_GpioConfig();

  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* Configure EXTI Line29 corresponding to LPTIM as interrupt wake-up mode */
  LL_EXTI_EnableIT(LL_EXTI_LINE_29);   /* Enable EXTI Line 29 interrupt wakeup */
  LL_EXTI_DisableEvent(LL_EXTI_LINE_29); /* Disable EXTI Line 29 event wakeup */

  /* Set LSI as LPTIM clcok source */
  APP_ConfigLptimClock();

  /* Initialize LPTIM */
  LPTIM_InitStruct.Prescaler = LL_LPTIM_PRESCALER_DIV128;        /* prescaler: 128 */
  LPTIM_InitStruct.UpdateMode = LL_LPTIM_UPDATE_MODE_IMMEDIATE;  /* registers are updated after each APB bus write access */
  if (LL_LPTIM_Init(LPTIM, &LPTIM_InitStruct) != SUCCESS)
  {
    APP_ErrorHandler();
  }

  /* LED ON */
  BSP_LED_On(LED_GREEN);

  /* Wait for the button to be pressed */
  while (BSP_PB_GetState(BUTTON_USER))
  {
  }

  /* LED off */
  BSP_LED_Off(LED_GREEN);

  /* Need to wait three LSI Time before enter the Stop Mode */ 
  RatioNops = Delay * (SystemCoreClock / 1000000U) / 4;  

  /* Configure LPTIM for continuous mode and enable interrupt */
  APP_ConfigLptim();
  
  while (1)
  {
    /* LPTIM must be disabled to restore internal state before next time enter stop mode */
    LL_LPTIM_Disable(LPTIM);
    
    /* Wait at least three LSI times for the completion of the disable operation */
    APP_DelayNops(RatioNops);    
    
    /* Enable LPTIM */
    LL_LPTIM_Enable(LPTIM);
    
    /* Set auto-reload value */
    LL_LPTIM_SetAutoReload(LPTIM, 51); 

    /* Start in once mode */
    LL_LPTIM_StartCounter(LPTIM, LL_LPTIM_OPERATING_MODE_ONESHOT);
    
    /* Enable STOP mode */
    APP_EnterStop();

    /* PA3 toggle */
    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_3);
  }
}

/**
  * @brief  Configure LPTIM clock
  * @param  None
  * @retval None
  */
static void APP_ConfigLptimClock(void)
{
  /* Enable LSI */
  LL_RCC_LSI_Enable();
  while(LL_RCC_LSI_IsReady() != 1)
  {
  }
  
  /* Select LTPIM clock source as LSI */
  LL_RCC_SetLPTIMClockSource(LL_RCC_LPTIM1_CLKSOURCE_LSI);
  
  /* Enable LPTIM clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPTIM1);
}

/**
  * @brief  Delayed by NOPS
  * @param  None
  * @retval None
  */
static void APP_DelayNops(uint32_t Nops)
{
  for(uint32_t i=0; i<Nops;i++)
  {
    __NOP();
  }
}

/**
  * @brief  GPIO configuration program
  * @param  None
  * @retval None
  */
static void APP_GpioConfig(void)
{
  /* Enable GPIOA clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* Configure PA3 in output mode */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_OUTPUT);
  /* Default output type (after reset) is push-pull */
  /* LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_3, LL_GPIO_OUTPUT_PUSHPULL); */
  /* Configure GPIO speed in low speed */
  /* LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_3, LL_GPIO_SPEED_FREQ_LOW); */
  /* Default (after reset) is no pull */
  /* LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_3, LL_GPIO_PULL_NO); */
}

/**
  * @brief  Configure LPTIM
  * @param  None
  * @retval None
  */
static void APP_ConfigLptim(void)
{   
  /* Enable LPTIM1 interrupt */
  NVIC_SetPriority(LPTIM1_IRQn, 0);
  NVIC_EnableIRQ(LPTIM1_IRQn);
  
  /* Enable LPTIM ARR match interrupt */
  LL_LPTIM_EnableIT_ARRM(LPTIM);
}

/**
  * @brief  Enable Stop mode
  * @param  None
  * @retval None
  */
static void APP_EnterStop(void)
{
  /* Enable PWR clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* STOP mode with low power regulator ON */
  LL_PWR_SetLprMode(LL_PWR_LPR_MODE_LPR);

  /* SRAM retention voltage aligned with digital LDO output */
  LL_PWR_SetStopModeSramVoltCtrl(LL_PWR_SRAM_RETENTION_VOLT_CTRL_LDO);

  /* Enter DeepSleep mode */
  LL_LPM_EnableDeepSleep();

  /* Request Wait For interrupt */
  __WFI();

   LL_LPM_EnableSleep();
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
  * @brief  LPTIM interrupt callback program
  * @param  None
  * @retval None
  */
void APP_LptimIRQCallback(void)
{
  if((LL_LPTIM_IsActiveFlag_ARRM(LPTIM) == 1) && (LL_LPTIM_IsEnabledIT_ARRM(LPTIM) == 1))
  {   
    /* Clear autoreload match flag */
    LL_LPTIM_ClearFLAG_ARRM(LPTIM);
 
    /* LED Toggle */
    BSP_LED_Toggle(LED_GREEN);
  }
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
