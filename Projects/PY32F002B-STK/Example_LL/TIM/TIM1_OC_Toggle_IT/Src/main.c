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
static void APP_ConfigTIM1OutputComparison(void);

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

  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);

  /* Initialize LED */
  BSP_LED_Init(LED3);

  /* Configure TIM1 in output compare mode */
  APP_ConfigTIM1OutputComparison();

  while (1)
  {
  }
}

/**
  * @brief  Configure TIM1 in output compare mode
  * @param  None
  * @retval None
  */
static void APP_ConfigTIM1OutputComparison(void)
{
  /* Set divider:tDTS=tCK_INT */
  LL_TIM_SetClockDivision(TIM1,LL_TIM_CLOCKDIVISION_DIV1);

  /* Up count mode */
  LL_TIM_SetCounterMode(TIM1,LL_TIM_COUNTERMODE_UP);

  /* Set auto reload valve:3000 */
  LL_TIM_SetAutoReload(TIM1,3000-1);

  /* Prescaler：CK_CNT = fCK_PSC / 8000 */
  LL_TIM_SetPrescaler(TIM1,8000-1);

  /* Set channle 1 */
  /* Configure output polarity to high active */
  LL_TIM_OC_SetPolarity(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCPOLARITY_HIGH);

  /* Configure idle polarity to low */
  LL_TIM_OC_SetIdleState(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCIDLESTATE_LOW);

  /* Set compare value：1000 */
  LL_TIM_OC_SetCompareCH1(TIM1,1000);

  /* SET TIM1 OC1REF to toggles on compare match */
  LL_TIM_OC_SetMode(TIM1,LL_TIM_CHANNEL_CH1,LL_TIM_OCMODE_TOGGLE);

  /* CH1 map to PA5 */
  LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_5,LL_GPIO_MODE_ALTERNATE);
  LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_5,LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetAFPin_0_7(GPIOA,LL_GPIO_PIN_5,LL_GPIO_AF_2);

  /* Enable channel 1 */
  LL_TIM_CC_EnableChannel(TIM1,LL_TIM_CHANNEL_CH1);

  /* Enable capture/compare 1 interrupt */
  LL_TIM_EnableIT_CC1(TIM1);

  /* Enable update interrupt */
  LL_TIM_EnableIT_UPDATE(TIM1);

  /* Set capture/compare 1 interrupt priority */
  NVIC_SetPriority(TIM1_CC_IRQn, 1);
  /* Enable TIM1 capture/compare interrupt in the NVIC interrupt controller */
  NVIC_EnableIRQ(TIM1_CC_IRQn);

  /* Set TIM1 update interrupt priority */
  NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 1);
  /* Enable TIM1 update interrupt in NVIC */
  NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);

  /* Disable automatic output */
  LL_TIM_DisableAutomaticOutput(TIM1);

  /* Enable output */
  LL_TIM_EnableAllOutputs(TIM1);

  /* Enable TIM1 */
  LL_TIM_EnableCounter(TIM1);
}

/**
  * @brief  TIM capture/compare interrupt callback
  * @param  None
  * @retval None
  */
void APP_CCCallback(void)
{
  /* toggle LED */
  BSP_LED_Toggle(LED3);
}

/**
  * @brief  TIM update interrupt callback
  * @param  None
  * @retval None
  */
void APP_UPDATECallback(void)
{
  LL_GPIO_TogglePin(GPIOA,LL_GPIO_PIN_4);
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
