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
uint8_t  aRxBuffer[RX_MAX_LEN] = {0};
uint32_t cRxIndex = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigUsart(USART_TypeDef *USARTx);

/**
  * @brief  Main program
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig(); 

  /* Configure LED_GREEN */
  BSP_LED_Init(LED_GREEN);
  
  /* Configure USART1 */
  APP_ConfigUsart(USART1);

  /* Enable RX Not Empty Interrupt */
  LL_USART_EnableIT_RXNE(USART1);

  while (1)
  {

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

  /* Set AHB divider:HCLK = SYSCLK*/
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* HSISYS used as SYSCLK source */
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
  * @brief  USART1 configuration function
  * @param  USARTx：USART1 Instance
  * @retval None
  */
static void APP_ConfigUsart(USART_TypeDef *USARTx)
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  LL_USART_InitTypeDef USART_InitStruct = {0};
  /*Enable GPIOB clock*/
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  /* Enable USART1 clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);

  /* Select pin 4 */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
  /* Select alternate mode */
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  /* Set output speed */
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  /* Set output type to push pull */
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  /* Enable pull up */
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  /* Set alternate function to USART1 function  */
  GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
  /* Initialize GPIOB */
  LL_GPIO_Init(GPIOB,&GPIO_InitStruct);

  /* Select pin 5 */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  /* Set alternate function to USART1 function */
  GPIO_InitStruct.Alternate = LL_GPIO_AF1_USART1;
  /* Initialize GPIOB */
  LL_GPIO_Init(GPIOB,&GPIO_InitStruct);

  /* Set USART1 interrupt priority  */
  NVIC_SetPriority(USART1_IRQn,0);
  /* Enable USART1 interrupt request */
  NVIC_EnableIRQ(USART1_IRQn);
  
  /* Set USART feature */
  /* Set baud rate */
  USART_InitStruct.BaudRate = 115200;
  /* set word length to 8 bits: Start bit, 8 data bits, n stop bits */
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  /* 1 stop bit */
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
 /* Parity control disabled  */
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  /* Initialize USART */
  LL_USART_Init(USARTx, &USART_InitStruct);
  
  /* Set mode as full-duplex asynchronous mode */
  LL_USART_ConfigAsyncMode(USARTx);
  
  /*Enable USART */
  LL_USART_Enable(USARTx);
}

/**
  * @brief  USART Error interrupt handler function
  * @param  None
  * @retval None
  */
void APP_UsartErrorCallback(void)
{
  /* Turn on the LED */
  BSP_LED_On(LED_GREEN);
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
