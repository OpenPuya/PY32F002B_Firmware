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
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define TXSTARTMESSAGESIZE    (COUNTOF(aTxStartMessage) - 1)
#define TXENDMESSAGESIZE      (COUNTOF(aTxEndMessage) - 1)

/* Private variables ---------------------------------------------------------*/
uint8_t aRxBuffer[12] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
uint8_t aTxStartMessage[] = "\n\r USART Hyperterminal communication based on polling \n\r Enter 12 characters using keyboard :\n\r";
uint8_t aTxEndMessage[] = "\n\r Example Finished\n\r";

uint8_t *TxBuff = NULL;
__IO uint16_t TxCount = 0;

uint8_t *RxBuff = NULL;
__IO uint16_t RxCount = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigUsart(USART_TypeDef *USARTx);
static void APP_UsartTransmit(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);
static void APP_UsartReceive(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Configure LED */
  BSP_LED_Init(LED_GREEN);
  
  /* Configure USART */
  APP_ConfigUsart(USART1);

  /* Start the transmission process */
  APP_UsartTransmit(USART1, (uint8_t*)aTxStartMessage, TXSTARTMESSAGESIZE);

  /* receive data */
  APP_UsartReceive(USART1, (uint8_t *)aRxBuffer, 12);

  /* Transmit data */
  APP_UsartTransmit(USART1, (uint8_t*)aRxBuffer, 12);
  
  /* Send the End Message  */
  APP_UsartTransmit(USART1, (uint8_t*)aTxEndMessage, TXENDMESSAGESIZE);
  
  /* Turn on LED if test passes then enter infinite loop */
  BSP_LED_On(LED_GREEN);
  
  /* Infinite loop */
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
  * @brief  USART configuration functions
  * @param  USARTx：USART1 Instance
  * @retval None
  */
static void APP_ConfigUsart(USART_TypeDef *USARTx)
{
  /* Enable clock, initialize GPIO, enable NVIC interrupt */
  if (USARTx == USART1)
  {
    /* Enable GPIOB clock */
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
    /* Enable USART1 peripheral clock */
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);

    /* Initialize PB4 */
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
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
  }

  /* Set USART feature */
  LL_USART_InitTypeDef USART_InitStruct = {0};
  /* Set baud rate */
  USART_InitStruct.BaudRate = 9600;
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

  /* Configure as full duplex asynchronous mode */
  LL_USART_ConfigAsyncMode(USARTx);

  /* Enable USART */
  LL_USART_Enable(USARTx);
}

/**
  * @brief  USART transmission function
  * @param  USARTx：USART1 Instance
  * @param  pData：Pointer to transmission buffer
  * @param  Size：Size of transmission buffer
  * @retval None
  */
static void APP_UsartTransmit(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
  TxBuff = pData;
  TxCount = Size;

  /* transmit data */
  while (TxCount > 0)
  {
    /* Wait for TXE bit to be set */
    while(LL_USART_IsActiveFlag_TXE(USARTx) != 1);
    /* transmit data */
    LL_USART_TransmitData8(USARTx, *TxBuff);
    TxBuff++;
    TxCount--;
  }

  /* Wait for TC bit to be set */
  while(LL_USART_IsActiveFlag_TC(USARTx) != 1);
}

/**
  * @brief  USART receive function
  * @param  USARTx：USART1 Instance
  * @param  pData：Pointer to receive buffer
  * @param  Size：Size of receive buffer
  * @retval None
  */
static void APP_UsartReceive(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size)
{
  RxBuff = pData;
  RxCount = Size;

  /* Receive data */
  while (RxCount > 0)
  {
    /* Wait for RxNE bit to be set */
    while(LL_USART_IsActiveFlag_RXNE(USARTx) != 1);
    /* Receive data */
    *RxBuff = LL_USART_ReceiveData8(USARTx);
    RxBuff++;
    RxCount--;
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
