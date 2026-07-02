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
static void APP_ConfigInputCapture(void);
static void APP_ConfigTIM1(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Enable TIM1 peripheral clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  /* Enabel GPIOA clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* Initialize LED */
  BSP_LED_Init(LED3);

  /* Configure the TIM1 input capture channels */
  APP_ConfigInputCapture();

  /* Configure the TIM1*/
  APP_ConfigTIM1();

  while (1)
  {
  }
}

/**
  * @brief  Configure the TIM1 input capture channels
  * @param  None
  * @retval int
  */
static void APP_ConfigInputCapture(void)
{
  LL_TIM_IC_InitTypeDef InputCaptureInit ={0};
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};

  /* Configure PA0 as input capture channel */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_0;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2;
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_NO;

  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);

  /* Configure the capture channel using the parameters defined by InputCaptureInit structure */
  InputCaptureInit.ICActiveInput  = LL_TIM_ACTIVEINPUT_DIRECTTI;
  InputCaptureInit.ICPrescaler    = LL_TIM_ICPSC_DIV1;
  InputCaptureInit.ICPolarity     = LL_TIM_IC_POLARITY_FALLING;
  InputCaptureInit.ICFilter       = LL_TIM_IC_FILTER_FDIV1;

  LL_TIM_IC_Init(TIM1,LL_TIM_CHANNEL_CH1,&InputCaptureInit);

  /* Enable input capture channel 1 interrupt */
  LL_TIM_EnableIT_CC1(TIM1);

  /* Enable TIM1 interrupt request */
  NVIC_EnableIRQ(TIM1_CC_IRQn);
  NVIC_SetPriority(TIM1_CC_IRQn,0);
}

/**
  * @brief  TIM1 input capture interrupt callback
  * @param  None
  * @retval None
  */
void APP_InputcaptureCallback(void)
{
  /* Toggle LED */
  BSP_LED_Toggle(LED3);
}

/**
  * @brief  Configure TIM1 .
  * @param  None
  * @retval int
  */
static void APP_ConfigTIM1(void)
{
  /* Configure TIM1 using the parameters defined by TIM1CountInit structure */
  LL_TIM_InitTypeDef TIM1CountInit = {0};

  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;/* divider:tDTS=tCK_INT   */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;    /* count mode：up count   */
  TIM1CountInit.Prescaler           = 8000-1;                   /* clock prescaler：8000  */
  TIM1CountInit.Autoreload          = 1000-1;                   /* autoreload value：1000 */
  TIM1CountInit.RepetitionCounter   = 0;                        /* recount：0             */

  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);

  /* Enable TIM1 */
  LL_TIM_EnableCounter(TIM1);
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
