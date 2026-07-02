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
static void APP_ConfigTIM1XOR(void);
void APP_CCCallback(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Enable TIM1 peripheral clock*/
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  /* Enabel GPIOA clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* Initialize LED */
  BSP_LED_Init(LED3);

  /* Configure TIM1 CH1, CH2 and CH3 channles are connected to the TI1 input (XOR combination) */
  APP_ConfigTIM1XOR();

  while (1)
  {
  }
}


/**
  * @brief  Configure TIM1 CH1, CH2 and CH3 channles are connected to the TI1 input (XOR combination)
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1XOR(void)
{
  LL_TIM_InitTypeDef TIM1CountInit = {0};
  LL_GPIO_InitTypeDef TIM1ChannelInit = {0};

  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;  /* divider:tDTS=tCK_INT   */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;      /* count mode :up count   */
  TIM1CountInit.Prescaler           = 8000-1;                     /* prescaler：8000        */
  TIM1CountInit.Autoreload          = 1000-1;                     /* auto-rload value：1000 */
  TIM1CountInit.RepetitionCounter   = 0;                          /* recount：0             */

  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);

  /* Enable CC interrupt */
  LL_TIM_EnableIT_CC1(TIM1);
  NVIC_EnableIRQ(TIM1_CC_IRQn);

  /* Select TIM1 CH1, CH2 and CH3 channles are connected to the TI1 input (XOR combination) */
  LL_TIM_IC_EnableXORCombination(TIM1);
  
  LL_TIM_IC_SetPolarity(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_IC_POLARITY_BOTHEDGE);
  
  /* Configure CH1、CH2、CH3 in input mode */
  LL_TIM_IC_SetActiveInput(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_ACTIVEINPUT_DIRECTTI);
  LL_TIM_IC_SetActiveInput(TIM1,LL_TIM_CHANNEL_CH2,LL_TIM_ACTIVEINPUT_DIRECTTI);
  LL_TIM_IC_SetActiveInput(TIM1,LL_TIM_CHANNEL_CH3,LL_TIM_ACTIVEINPUT_DIRECTTI);

  /* CH1, CH2, and CH3 map to PA0, PA3, and PA4 */
  TIM1ChannelInit.Pin       = LL_GPIO_PIN_0 | LL_GPIO_PIN_3 | LL_GPIO_PIN_4;
  TIM1ChannelInit.Pull      = LL_GPIO_PULL_UP;
  TIM1ChannelInit.Mode      = LL_GPIO_MODE_ALTERNATE;
  TIM1ChannelInit.Alternate = LL_GPIO_AF_2;
  TIM1ChannelInit.Speed     = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1ChannelInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOA,&TIM1ChannelInit);

  /* Enable CH1、CH2、CH3 channels */
  LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);
  LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2);
  LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3);

  /* Enable TIM1 */
  LL_TIM_EnableCounter(TIM1);

}

/**
  * @brief  TIM1 input capture interrupt callback
  * @param  None
  * @retval None
  */
void APP_CCCallback(void)
{
  /* Toggle LED */
  BSP_LED_Toggle(LED3);
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
