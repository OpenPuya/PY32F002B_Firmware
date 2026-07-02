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
uint32_t uwStep = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigTIM1Base(void);
static void APP_Config6StepPWMChannel(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Enable SysTick interrupt */
  LL_SYSTICK_EnableIT();

  /* Enable TIM1、GPIOA、GPIOB clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA|LL_IOP_GRP1_PERIPH_GPIOB);

  /* Configure TIM1 in TIM1 6StepPWM mode */
  APP_ConfigTIM1Base();

  /* infinite loop  */
  while (1)
  {
  }
}

/**
  * @brief  Configure TIM1 6StepPWM mode related GPIO
  * @param  None
  * @retval None
  */
static void APP_Config6StepPWMChannel(void)
{
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};

  /* Set PA5 as TIM1_CH1 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_5;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2;
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);

  /* Set PB2 as TIM1_CH1N */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_2;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2;
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB,&TIM1CH1MapInit);

  /* Set PA3 as TIM1_CH2 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_3;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2;
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);

  /* Set PB1 as TIM1_CH2N */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_1;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2;
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB,&TIM1CH1MapInit);

  /* Set PA4 as TIM1_CH3 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_4;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2;
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);

  /* Set PB0 as TIM1_CH3N */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_0;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_3;
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB,&TIM1CH1MapInit);

  /* Configure PWM channel */
  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM1;     /* channle mode：PWM1                      */
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;  /* Enable selected channle                 */
  TIM_OC_Initstruct.OCNState      = LL_TIM_OCSTATE_ENABLE;  /* Enable complementary ouptput            */
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH; /* Active level：high                      */
  TIM_OC_Initstruct.OCNPolarity   = LL_TIM_OCPOLARITY_HIGH; /* complementary output polarity：high     */
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW; /* idle polarity：low                      */
  TIM_OC_Initstruct.OCNIdleState  = LL_TIM_OCIDLESTATE_LOW; /* complementary output idle polarity: low */
  TIM_OC_Initstruct.CompareValue  = 50;                     /* compare value：50                       */
  /* Configure CH1 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1,&TIM_OC_Initstruct);
  /* Configure CH2 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH2,&TIM_OC_Initstruct);
  /* Configure CH3 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH3,&TIM_OC_Initstruct);
  /* Disable all channle output */
  LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1|LL_TIM_CHANNEL_CH1N|
                                LL_TIM_CHANNEL_CH2|LL_TIM_CHANNEL_CH2N|
                                LL_TIM_CHANNEL_CH3|LL_TIM_CHANNEL_CH3N);
}

/**
  * @brief  TIM1 6StepPWM Configuration function
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1Base(void)
{
  /* Configure TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};

  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;  /* Set divider:tDTS=tCK_INT */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;      /* count mode：up count     */
  TIM1CountInit.Prescaler           = 24-1;                       /* clock prescaler：24      */
  TIM1CountInit.Autoreload          = 100-1;                      /* auto-reload value：100   */
  TIM1CountInit.RepetitionCounter   = 0;                          /* recount：0               */

  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);

  /* Configure TIM1 6stepPWM related channle */
  APP_Config6StepPWMChannel();

  /* Enable COM interrupt */
  LL_TIM_EnableIT_COM(TIM1);

  /* Set COM interrupt priority */
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,1);
  /* Enable COM interrupt in NVIC */
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

  /* Enable  the capture/compare control bits (CCxE, CCxNE and OCxM) preload */
  LL_TIM_CC_EnablePreload(TIM1);

  /* Enable output */
  LL_TIM_EnableAllOutputs(TIM1);

  /* Enable TIM1 */
  LL_TIM_EnableCounter(TIM1);
}

/**
  * @brief  TIM1 COM interrupr callback
  * @param  None
  * @retval None
  */
void APP_COMCallback(void)
{
  switch(uwStep)
  {
    /* first（start state） */
    case 0:
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);   /* CH1 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3N);  /* CH3N: 1 */
      uwStep++;
      break;
    /* configuration of step 2 */
    case 1:
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);   /* CH1 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2N);  /* CH2N: 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* configuration of step 3 */
    case 2:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2N);  /* CH2N: 1 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3);   /* CH3 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* configuration of step 4 */
    case 3:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1N);  /* CH1N: 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3);   /* CH3 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* configuration of step 5 */
    case 4:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1N);  /* CH1N: 1 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2);   /* CH2 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3N); /* CH3N: 0 */
      uwStep++;
      break;
    /* configuration of step 6 */
    case 5:
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1);  /* CH1 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH2);   /* CH2 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3N);  /* CH3N: 1 */
      uwStep++;
      break;
    /* configuration of step 1 */
    case 6:
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);   /* CH1 : 1 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH1N); /* CH1N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2);  /* CH2 : 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH2N); /* CH2N: 0 */
      LL_TIM_CC_DisableChannel(TIM1,LL_TIM_CHANNEL_CH3);  /* CH3 : 0 */
      LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH3N);  /* CH3N: 1 */
      uwStep = 1;
      break;
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
