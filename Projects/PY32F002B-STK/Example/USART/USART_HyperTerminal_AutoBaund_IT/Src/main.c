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

/* Private define ------------------------------------------------------------*/
#define AUTO_BAUD_MODE0    /*Automatic Baud detection mode selection, measuring
                             from the start bit; If shielding is selected,
                             measure from falling edge to falling edge */
#define RXBUFFERSIZE  1

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef UartHandle;
uint8_t aTxBuffer[] = "Auto BaudRate Test";
uint8_t aRxBuffer[RXBUFFERSIZE];
uint8_t submitsum = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_UsartConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();
  
  /* USART initialization */
  APP_UsartConfig();
  
  /* Receiving data through interruption */
  if (HAL_UART_Receive_IT(&UartHandle, (uint8_t *)aRxBuffer, 1) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  while (1)
  {
    if ((__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_ABRE) == RESET) && \
      (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_ABRF) == SET))
    {
      /* Clear the automatic Baud detection completion flag bit  */
      __HAL_UART_SEND_AUTOBAUD_REQ(&UartHandle);
      
      /* send data */
      HAL_UART_Transmit_IT(&UartHandle, (uint8_t *)aTxBuffer, 18);
    }
    else if((__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_ABRE) == SET) && \
        (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_ABRF) == SET))
    {
      /* Baud Rate Adaptive Detection Error */
    }
    else
    {
    }
  }
}

/**
  * @brief  USART configuration
  * @param  None
  * @retval None
  */
void APP_UsartConfig(void)
{
  /* USART initialization */
  UartHandle.Instance          = USART1;
  UartHandle.Init.BaudRate     = 115200;
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = UART_STOPBITS_1;
  UartHandle.Init.Parity       = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_AUTOBAUDRATE_INIT;
  UartHandle.AdvancedInit.AutoBaudRateEnable = UART_ADVFEATURE_AUTOBAUDRATE_ENABLE; /* Automatic Baud enable */
#ifdef AUTO_BAUD_MODE0
  UartHandle.AdvancedInit.AutoBaudRateMode = UART_ADVFEATURE_AUTOBAUDRATE_ONSTARTBIT; /* Automatic Baud detection mode measures
                                                                                         the Baud from the start bit, and the
                                                                                         upper computer sends 0x7f */
#else
  UartHandle.AdvancedInit.AutoBaudRateMode = UART_ADVFEATURE_AUTOBAUDRATE_ONFALLINGEDGE; /* Automatic Baud detection mode measures
                                                                                            from falling edge to falling edge, and
                                                                                            the upper computer sends 0x55 */
#endif
  if (HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  Error executing function.
  * @param  None
  * @retval None
  */
void APP_ErrorHandler(void)
{
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* Users can add their own printing information as needed,
     for example: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
