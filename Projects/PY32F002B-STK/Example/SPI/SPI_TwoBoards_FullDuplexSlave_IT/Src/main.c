/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
#define DATA_LENGTH       15

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef Spi1Handle;
uint8_t TxBuff[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t RxBuff[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_WaitAndCheckEndOfTransfer(void);
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();
  
  /* System clock configuration */
  APP_SystemClockConfig();
  
  /* Initialize debugging serial port (used by printf) */
  BSP_USART_Config();

  /* Initialization button */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  
  /* De-initialize SPI configuration */
  Spi1Handle.Instance               = SPI1;                       /* SPI1 */
  Spi1Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;  /* 256 frequency division */
  Spi1Handle.Init.Direction         = SPI_DIRECTION_2LINES;       /* full duplex */
  Spi1Handle.Init.CLKPolarity       = SPI_POLARITY_LOW;           /* Low clock polarity */
  Spi1Handle.Init.CLKPhase          = SPI_PHASE_1EDGE ;           /* Data sampling starts from the first clock edge */
  Spi1Handle.Init.DataSize          = SPI_DATASIZE_8BIT;          /* SPI data length is 8 bits */
  Spi1Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;           /* Send MSB first */
  Spi1Handle.Init.NSS               = SPI_NSS_HARD_INPUT;         /* NSS software mode (hardware mode) */
  Spi1Handle.Init.Mode = SPI_MODE_SLAVE;                          /* Configure as a slave */
  if (HAL_SPI_DeInit(&Spi1Handle) != HAL_OK)                      /* SPI deinitialization */
  {
  }
  
  /* SPI initialization */
  if (HAL_SPI_Init(&Spi1Handle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* SPI interrupt mode transmission */
  if (HAL_SPI_TransmitReceive_IT(&Spi1Handle, (uint8_t *)TxBuff, (uint8_t *)RxBuff, DATA_LENGTH) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Wait for the transmission to end and check the received data */
  APP_WaitAndCheckEndOfTransfer();
  
  while (1)
  {
  }
}

/**
  * @brief  SPI1 waits for the transmission to complete and verifies the data.
  * @param  None
  * @retval None
  */
static void APP_WaitAndCheckEndOfTransfer(void)
{
  /* Waiting for transmission to end */
  while (Spi1Handle.State != HAL_SPI_STATE_READY)
  {}

  /* Compare sending and receiving data */
  if(APP_Buffercmp8((uint8_t*)TxBuff, (uint8_t*)RxBuff, DATA_LENGTH))
  {
    /* Communication error prompt */
    printf("SPI Transfer Error");
  }
  else
  {
    /* Communication success prompt */
    printf("SPI transfer succeeded");
  }
}

/**
  * @brief  Character comparison function
  * @param  pBuffer1：Buffer 1 to be compared
  * @param  pBuffer2：Buffer 2 to be compared
  * @param  BufferLength：Number of characters to be compared
  * @retval 0：Same comparison value；1：Different comparison values
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
  * @brief  System clock configuration function
  * @param  None
  * @retval None
  */
static void APP_SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /* Oscillator configuration */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE; /* Select oscillator HSE, HSI, LSI, LSE */
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;                           /* Enable HSI */
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;                           /* HSI 1 frequency division */
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_24MHz;  /* Configure HSI clock 24MHz */
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS_DISABLE;               /* Close HSE bypass */
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;                          /* Close LSI */
  /*RCC_OscInitStruct.LSICalibrationValue = RCC_LSICALIBRATION_32768Hz;*/
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;                          /* Close LSE */
  /*RCC_OscInitStruct.LSEDriver = RCC_LSEDRIVE_MEDIUM;*/
  /* Configure oscillator */
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Clock source configuration */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1; /* Choose to configure clock HCLK, SYSCLK, PCLK1 */
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSISYS; /* Select HSISYS as the system clock */
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;        /* AHB clock 1 division */
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;         /* APB clock 1 division */
  /* Configure clock source */
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
