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
/* Private function prototypes -----------------------------------------------*/
void APP_SystemClockConfig(void);
static void APP_ConfigGPIO(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_USER,BUTTON_MODE_GPIO);

  /* Wait for the BUTTON to be pressed */
  while(BSP_PB_GetState(BUTTON_USER))
  {
  }

  /* Configure LSE as Systemclock source */
  APP_SystemClockConfig();

  /* Configure PA07 as an MCO alternate function */
  APP_ConfigGPIO();

  /*Set SYSCLK as MCO source: MCO = SYSCLK*/
  LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_SYSCLK,LL_RCC_MCO1_DIV_1);

  while (1)
  {

  }
}

/**
  * @brief  Configure PA07 as an MCO alternate function
  * @param  None
  * @retval None
  */
static void APP_ConfigGPIO(void)
{
  /* Enable GPIOA clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* Configure PA07 as an MCO alternate function*/
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* Select pin 7*/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
  /* Select alternate function mode */
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  /* Select alternate function 4*/
  GPIO_InitStruct.Alternate = LL_GPIO_AF4_MCO;
  /* Select I/O high output speed */
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  /* Select pushpull as output type*/
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  /* Select I/O no pull*/
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;

  /* Initialize GPIOA*/
  LL_GPIO_Init(GPIOA,&GPIO_InitStruct);

}

/**
  * @brief  Configure LSE as Systemclock source
  * @param  None
  * @retval None
  */
void APP_SystemClockConfig(void)
{
  /* Disable Low Speed External (LSE) crystal */
  LL_RCC_LSE_Disable();
  while(LL_RCC_LSE_IsReady() != 0)
  {
  }
  /* Set LSE oscillator drive capability */
  LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_MEDIUM);
  /* Enable Low Speed External (LSE) crystal */
  LL_RCC_LSE_Enable();
  while(LL_RCC_LSE_IsReady() != 1)
  {
  }

  /* Set AHB divider:HCLK = SYSCLK */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* Set FLASH Latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  /* LSE used as SYSCLK clock source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_LSE);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_LSE)
  {
  }

  /* Set APB1 divider */
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(LSE_VALUE);
}

/**
  * @brief  Error handling function
  * @param  None
  * @retval None
  */
void Error_Handler(void)
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
