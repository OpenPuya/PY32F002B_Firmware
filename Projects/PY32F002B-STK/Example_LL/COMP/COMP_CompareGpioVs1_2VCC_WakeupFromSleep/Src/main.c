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
static void APP_CompInit(void);
static void APP_EnterSleep(void);
static void APP_CompRccInit(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Enable SYSCFG clock and PWR clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize Button */
  BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);
 
  /* LED ON */
  BSP_LED_On(LED_GREEN);
  
  /* Wait Button */
  while(BSP_PB_GetState(BUTTON_KEY))
  {
  }
  
  /* COMP Rcc Init */
  APP_CompRccInit();
  
  /* COMP Init */
  APP_CompInit();
  
  /* LED OFF */
  BSP_LED_Off(LED_GREEN);

  /* Enter Sleep Mode */
  APP_EnterSleep();

  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);
    
    LL_mDelay(200); 
  }
}

/**
  * @brief  Comp Init
  * @param  None
  * @retval None
  */
static void APP_CompInit(void)
{
  /* Enable GPIOA Clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  
  /* PA4 Mode Analog */
  LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_4,LL_GPIO_MODE_ANALOG);

  /* Enable COMP2 Clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_COMP2);
  
  /* Enable COMP1 Clock*/
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_COMP1);
  
  /* VREFCMP Select VCC */
  LL_COMP_SetVrefCmpSource(COMP1,LL_COMP_VREFCMP_SOURCE_VCC);
  
  /* Set 1/2Vrefcmp */
  LL_COMP_SetVrefCmpDivider(COMP1,LL_COMP_VREFCMP_DIV_8_16VREFCMP);
  
  /* Enable VrefCmp */
  LL_COMP_EnableVrefCmpDivider(COMP1);

  /* Plus Select VrefCmp */
  LL_COMP_SetInputPlus(COMP2,LL_COMP_INPUT_PLUS_IO2);
  
  /* Minus Select PA4 */
  LL_COMP_SetInputMinus(COMP2,LL_COMP_INPUT_MINUS_IO1);
  
  /* Disable Window Mode */
  LL_COMP_SetCommonWindowMode(__LL_COMP_COMMON_INSTANCE(COMP1), LL_COMP_WINDOWMODE_DISABLE);
  
  /* Enable Rising Trigger */
  LL_EXTI_EnableRisingTrig(LL_EXTI_LINE_18);

  /* Enable Interrupt */
  LL_EXTI_EnableIT(LL_EXTI_LINE_18);

  NVIC_SetPriority(ADC_COMP_IRQn, 0);
  NVIC_EnableIRQ(ADC_COMP_IRQn);

  /* Enable COMP2 */
  LL_COMP_Enable(COMP2);
  __IO uint32_t wait_loop_index = 0;
  wait_loop_index = ((LL_COMP_DELAY_STARTUP_US / 10UL) * (SystemCoreClock / (100000UL * 2UL)));
  while(wait_loop_index != 0UL)
  {
    wait_loop_index--;
  }
}

/**
  * @brief  Comp Clock Init
  * @param  None
  * @retval None
  */
static void APP_CompRccInit()
{
  /* Enable LSI */
  LL_RCC_LSI_Enable();
 
  /* Wait LSI Ready */
  while(LL_RCC_LSI_IsReady() != 1)
  {
  }
 
  /* Set LSC Source LSI */
  LL_RCC_LSCO_SetSource(LL_RCC_LSCO_CLKSOURCE_LSI);

  /* Enable LSC */
  LL_RCC_LSCO_Enable();

  /* Set Comp2 Clock Source LSC */
  LL_RCC_SetCOMPClockSource(LL_RCC_COMP2_CLKSOURCE_LSC);
  
  /* Set Comp1 Clock Source LSC */
  LL_RCC_SetCOMPClockSource(LL_RCC_COMP1_CLKSOURCE_LSC);
}

/**
  * @brief  Enter Sleep
  * @param  None
  * @retval None
  */
void APP_EnterSleep(void)
{
  /* Enable PWR Clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* Enter Sleep Mode */
  LL_LPM_EnableSleep();

  /* WFI */
  __WFI();

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

  /* HSISYS used as SYSCLK clock source */
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
