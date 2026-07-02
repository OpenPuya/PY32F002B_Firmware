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
#define DATA_LENGTH       15
#define FLASH_ADDR        0

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef Spi1Handle;

uint8_t TxBuff[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t RxBuff[15] = {0};
uint8_t Transition[3] = {0};
uint8_t FlashStatus = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_WaitAndCheckEndOfTransfer(void);
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);

static void APP_External_FLASH_SectorErase(uint32_t Address);
static void APP_External_FLASH_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count);
static void APP_External_FLASH_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count);
/**
  * @brief  Main program
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick */
  HAL_Init();
  
  /* Configure Systemclock */
  APP_SystemClockConfig(); 

  /* Initialize debugging serial port (used by printf) */
  BSP_USART_Config();
  
  /* De-Initialize the SPI peripheral */
  Spi1Handle.Instance               = SPI1;                       /* SPI1 */
  Spi1Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;  /* 256 frequency division */
  Spi1Handle.Init.Direction         = SPI_DIRECTION_2LINES;       /* full duplex */
  Spi1Handle.Init.CLKPolarity       = SPI_POLARITY_LOW;           /* Low clock polarity */
  Spi1Handle.Init.CLKPhase          = SPI_PHASE_1EDGE ;           /* Data sampling starts from the first clock edge */
  Spi1Handle.Init.DataSize          = SPI_DATASIZE_8BIT;          /* SPI data length is 8 bits */
  Spi1Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;           /* Send MSB first */
  Spi1Handle.Init.NSS               = SPI_NSS_SOFT;               /* NSS Software Mode */
  Spi1Handle.Init.Mode              = SPI_MODE_MASTER;            /* Configure as master */
  if (HAL_SPI_DeInit(&Spi1Handle) != HAL_OK)                      
  {
    APP_ErrorHandler();
  }
  
  /* Initialize SPI peripheral */
  if (HAL_SPI_Init(&Spi1Handle) != HAL_OK)
  {
    APP_ErrorHandler();
  }

  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  
  /* Wait for the button to be press */
  while (BSP_PB_GetState(BUTTON_KEY));
  
  /* SectorErase */
  APP_External_FLASH_SectorErase(FLASH_ADDR);

  /* PageProgram */
  APP_External_FLASH_PageProgram(FLASH_ADDR, (uint8_t *)TxBuff, DATA_LENGTH);

  /* ReadData */
  APP_External_FLASH_ReadData(FLASH_ADDR, (uint8_t *)RxBuff, DATA_LENGTH);
  
  /* Wait for the transfer be completed and check the received data */
  APP_WaitAndCheckEndOfTransfer();
  
  while (1)
  {
  }
}

/**
  * @brief  Write specified bytes of data to the specified page at the page address
  * @param  Address: page address
  * @param  DataArray: Data to be written
  * @param  Count: Number of bytes
  * @retval None
  */
static void APP_External_FLASH_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_RESET);
  
  /*Write enable*/
  Transition[0] = P25Q64_WRITE_ENABLE;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 1, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_SET);
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_RESET);
  
  /*Send write instruction*/
  Transition[0] = P25Q64_PAGE_PROGRAM;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 1, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*Send address*/
  Transition[0] = (uint8_t)(Address >> 16);
  Transition[1] = (uint8_t)(Address >> 8);
  Transition[2] = (uint8_t)Address;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 3, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*Send write data*/
  if (HAL_SPI_Transmit(&Spi1Handle, DataArray, Count, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_SET);
  
  /*Wait for the write operation to finish*/
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_RESET);
  
  /*Send read status register instruction*/
  Transition[0] = P25Q64_READ_Status_Register;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 1, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*receive status data*/
  do {  
    if (HAL_SPI_Receive(&Spi1Handle,&FlashStatus, 1, 5000) != HAL_OK)
    {
      APP_ErrorHandler();
    }
  } while (FlashStatus & 0x01);
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_SET);
}

/**
  * @brief  Erases data in the specified sector
  * @param  Address: sector address
  * @retval None
  */
static void APP_External_FLASH_SectorErase(uint32_t Address)
{
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_RESET);
  
  /*Write enable*/
  Transition[0] = P25Q64_WRITE_ENABLE;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 1, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_SET);
  
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_RESET);
  
  /*Send erase instruction*/
  Transition[0] = P25Q64_SECTOR_ERASE;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 1, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*Send address*/
  Transition[0] = (uint8_t)(Address >> 16);
  Transition[1] = (uint8_t)(Address >> 8);
  Transition[2] = (uint8_t)Address;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 3, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_SET);
  
  /*Wait for the erase operation to finish*/
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_RESET);
  
  /*Send read status register instruction*/
  Transition[0] = P25Q64_READ_Status_Register;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 1, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*receive status data*/
  do {  
    if (HAL_SPI_Receive(&Spi1Handle,&FlashStatus, 1, 5000) != HAL_OK)
    {
      APP_ErrorHandler();
    }
  } while (FlashStatus & 0x01);
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_SET);
  
}
  
/**
  * @brief  Read specified bytes of data from the specified page at the page address
  * @param  Address: page address
  * @param  DataArray: Data being read out
  * @param  Count: Number of bytes
  * @retval None
  */
static void APP_External_FLASH_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
  /*Pull down NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_RESET);
  
  /*Send read instruction*/
  Transition[0] = P25Q64_READ_DATA;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 1, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*Send address*/
  Transition[0] = (uint8_t)(Address >> 16);
  Transition[1] = (uint8_t)(Address >> 8);
  Transition[2] = (uint8_t)Address;
  if (HAL_SPI_Transmit(&Spi1Handle,(uint8_t *)Transition, 3, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*read data*/
  if (HAL_SPI_Receive(&Spi1Handle, DataArray, Count, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /*Pull up NSS*/
  HAL_GPIO_WritePin(GPIOA,SPI_NSS,GPIO_PIN_SET);
}

/**
  * @brief  Wait for the transfer be completed and check the received data
  * @param  None
  * @retval None
  */
static void APP_WaitAndCheckEndOfTransfer(void)
{
  /* Wait for the transfer be completed */
  while (Spi1Handle.State != HAL_SPI_STATE_READY)
  {}

  /* Compare sent and received data */
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
  * @param  pBuffer1: Pointer to buffer 1 that to be compared 
  * @param  pBuffer2: Pointer to buffer 2 that to be compared 
  * @param  BufferLength: The number of characters to be compared
  * @retval 0: The comparison value is the same; 1: The comparison value is different
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

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
