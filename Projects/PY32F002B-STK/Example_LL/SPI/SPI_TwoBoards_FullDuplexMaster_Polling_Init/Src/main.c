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
/* Send buffer define */
uint8_t aTxBuffer[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
uint8_t ubNbDataToTransmit = sizeof(aTxBuffer);
uint8_t ubTransmitIndex = 0;

/* Receive buffer define */
uint8_t aRxBuffer[sizeof(aTxBuffer)] = {0};
uint8_t ubNbDataToReceive = sizeof(aTxBuffer);
uint8_t ubReceiveIndex = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigSPI(void);
static void APP_SpiMasterTransmitReceive(void);
static void APP_WaitAndCheckEndOfTransfer(void);
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Initialize USART( for printf use) */
  BSP_USART_Config();

  /* Intialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* Initialize SPI peripheral */
  APP_ConfigSPI();

  /* wait for the button to be pressed */
  while(BSP_PB_GetState(BUTTON_KEY));

  /* Enable SPI1 */
  LL_SPI_Enable(SPI1);

  /* Master send and receive data */
  APP_SpiMasterTransmitReceive();

  /* Wait for transfer to be completed,and check received data */
  APP_WaitAndCheckEndOfTransfer();

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

  /* Set APB1 divider*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(24000000);

  /* Update the system clock global variable SystemCoreClock (can also be updated by calling the SystemCoreClockUpdate() function) */
  LL_SetSystemCoreClock(24000000);
}

/**
  * @brief  Set SPI1 fearures
  * @param  None
  * @retval None
  */
static void APP_ConfigSPI(void)
{
  LL_SPI_InitTypeDef SPI_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Enable SPI1 periphreal clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SPI1);

  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /**SPI1 I/O configuration
  PB2   ------> SPI1_SCK
  PA1   ------> SPI1_MISO
  PA7   ------> SPI1_MOSI
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Set SPI1 features */
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV128;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  LL_SPI_Init(SPI1, &SPI_InitStruct);
}

/**
  * @brief  SPI1 receive and send data program
  * @param  None
  * @retval None
  */
static void APP_SpiMasterTransmitReceive(void)
{
  uint32_t             txallowed = 1U;

  /* Data is sent and received in polling mode */
  while((ubReceiveIndex < ubNbDataToReceive) || (ubTransmitIndex < ubNbDataToTransmit))
  {
    /* wait to send data(The following conditions are required to start sending data：send data register is empty，
       there's still data to transfer ，Receive completely) */
    if ((LL_SPI_IsActiveFlag_TXE(SPI1) == 1) && (ubTransmitIndex < ubNbDataToTransmit) && txallowed == 1U)
    {
      LL_SPI_TransmitData8(SPI1, aTxBuffer[ubTransmitIndex++]);
      txallowed = 0U;
    }

    /* wait to receive data(The following conditions are required to start receiving data：receive data register is empty，
       there's still data to receive ，send completely) */
    if((LL_SPI_IsActiveFlag_RXNE(SPI1) == 1) && (ubReceiveIndex < ubNbDataToReceive))
    {
      aRxBuffer[ubReceiveIndex++] = LL_SPI_ReceiveData8(SPI1);
      txallowed = 1U;
    }
  }
}

/**
  * @brief Wait for transfer to be completed,and check received data
  * @param  None
  * @retval None
  */
static void APP_WaitAndCheckEndOfTransfer(void)
{
  /* 1 - Wait for transfer to be completed */
  while (ubTransmitIndex != ubNbDataToTransmit)
  {
  }
  /* Disable TXE interrupt request   */
  LL_SPI_DisableIT_TXE(SPI1);

  /* 2 - Wait for receive to be completed */
  while (ubNbDataToReceive > ubReceiveIndex)
  {
  }
  /*  Disable RxNE interrupt request */
  LL_SPI_DisableIT_RXNE(SPI1);

  /* 3 - Compare sent data with received data */
  if(APP_Buffercmp8((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, ubNbDataToTransmit))
  {
    /* printf error notice */
    printf("SPI Transfer Error");
  }
  else
  {
    /* printf transfer successfully notice */
    printf("SPI transfer succeeded");
  }
}

/**
  * @brief  Character Comparison function
  * @param  pBuffer1：pBuffer1 pointer to buffer1
  * @param  pBuffer2：pBuffer1 pointer to buffer2
  * @param  BufferLength：The number of characters to be compared
  * @retval 0：The contents of buffer1 are equal to buffer2. 1: The contents of buffer1 are not equal to buffer2
  */
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }
    pBuffer1++;
    pBuffer2++;
  }

  return 0;
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
