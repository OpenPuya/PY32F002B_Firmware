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
static void APP_ConfigPWMChannel(void);
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

  /* Enabel GPIOB clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  
  /* Initialize button */
  BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
  
  /* wait the button to be pressed */
  while(BSP_PB_GetState(BUTTON_USER))
  {}
  
  /* Set TIM1 PWM related GPIO */
  APP_ConfigPWMChannel();
  
  /* Set TIM1 in PWM mode */
  APP_ConfigTIM1();
  while (1)
  {
  }
}

/**
  * @brief  Set TIM1 PWM related GPIO
  * @param  None
  * @retval None
  */
static void APP_ConfigPWMChannel(void)
{
  LL_GPIO_InitTypeDef TIM1CH1MapInit= {0};
  LL_TIM_OC_InitTypeDef TIM_OC_Initstruct ={0};

  /* Set PA5/PB0/PA4 as TIM1_CH1/TIM1_CH2/TIM1_CH3 */
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_5|LL_GPIO_PIN_4;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOA,&TIM1CH1MapInit);
  
  TIM1CH1MapInit.Pin        = LL_GPIO_PIN_0;
  TIM1CH1MapInit.Mode       = LL_GPIO_MODE_ALTERNATE;
  TIM1CH1MapInit.Alternate  = LL_GPIO_AF_2; 
  TIM1CH1MapInit.Speed      = LL_GPIO_SPEED_FREQ_HIGH;
  TIM1CH1MapInit.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  TIM1CH1MapInit.Pull       = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOB,&TIM1CH1MapInit);
   
  /* Set PWM channel */
  TIM_OC_Initstruct.OCMode        = LL_TIM_OCMODE_PWM2;       /* channle mode：PWM2         */
  TIM_OC_Initstruct.OCState       = LL_TIM_OCSTATE_ENABLE;    /* Enable selected channle    */
  TIM_OC_Initstruct.OCPolarity    = LL_TIM_OCPOLARITY_HIGH;   /* channle active level：high */
  TIM_OC_Initstruct.OCIdleState   = LL_TIM_OCIDLESTATE_LOW;   /* channle idle polarity：low */
  /* CH1 compare value:250 */
  TIM_OC_Initstruct.CompareValue  = 250;
  /* Configure CH1 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH1,&TIM_OC_Initstruct);
  /* CH2 compare value:500*/
  TIM_OC_Initstruct.CompareValue  = 500;
  /* Configure CH2 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH2,&TIM_OC_Initstruct);
  /* CH3 compare value:750*/
  TIM_OC_Initstruct.CompareValue  = 750;
  /* Configure CH3 */
  LL_TIM_OC_Init(TIM1,LL_TIM_CHANNEL_CH3,&TIM_OC_Initstruct);
}

/**
  * @brief  Configure TIM1.
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1(void)
{
  /* Configure TIM1 */
  LL_TIM_InitTypeDef TIM1CountInit = {0};
  
  TIM1CountInit.ClockDivision       = LL_TIM_CLOCKDIVISION_DIV1;/* Set divider:tDTS=tCK_INT  */
  TIM1CountInit.CounterMode         = LL_TIM_COUNTERMODE_UP;    /* count mode：up count      */
  TIM1CountInit.Prescaler           = 2400-1;                   /* clock prescaler：2400     */
  TIM1CountInit.Autoreload          = 1000-1;                   /* auto-reload value：1000   */
  TIM1CountInit.RepetitionCounter   = 0;                        /* recount：0                */
  
  /* Initialize TIM1 */
  LL_TIM_Init(TIM1,&TIM1CountInit);
  
  /* Enable output */
  LL_TIM_EnableAllOutputs(TIM1);

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
