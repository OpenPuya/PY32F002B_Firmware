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
#define DATA_LENGTH      15                 /* Data length*/
#define I2C_ADDRESS      0xA0               /* Local address 0xA0 */
#define I2C_SPEEDCLOCK   100000             /* Communication speed 100K */
#define I2C_DUTYCYCLE    I2C_DUTYCYCLE_16_9 /* Duty cycle */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef I2cHandle;
uint8_t aTxBuffer[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t aRxBuffer[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_CheckEndOfTransfer(void);
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);
static void APP_LedBlinking(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */
  HAL_Init();
  
  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialization button */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);
  
  /* I2C initialization */
  I2cHandle.Instance             = I2C;                       /* I2C */
  I2cHandle.Init.ClockSpeed      = I2C_SPEEDCLOCK;            /* I2C communication speed */
  I2cHandle.Init.DutyCycle       = I2C_DUTYCYCLE;             /* I2C duty cycle */
  I2cHandle.Init.OwnAddress1     = I2C_ADDRESS;               /* I2C address */
  I2cHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;   /* Prohibit broadcast calls */
  I2cHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;     /* Allow clock extension */
  if (HAL_I2C_Init(&I2cHandle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Waiting for the user to press the button */
  while (BSP_PB_GetState(BUTTON_KEY) == 1)
  {
  }

  /*I2C master polling method sending*/
  if (HAL_I2C_Master_Transmit(&I2cHandle, I2C_ADDRESS, (uint8_t *)aTxBuffer, DATA_LENGTH, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  /*Determine the current I2C status*/
  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY);
  /*I2C host polling reception*/
  if (HAL_I2C_Master_Receive(&I2cHandle, I2C_ADDRESS, (uint8_t *)aRxBuffer, DATA_LENGTH, 5000) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  /*Determine the current I2C status*/
  while (HAL_I2C_GetState(&I2cHandle) != HAL_I2C_STATE_READY);
  
  /* Check the received data */
  APP_CheckEndOfTransfer();
  
  while (1)
  {
  }
}

/**
  * @brief  Verify Data Function
  * @param  None
  * @retval None
  */
static void APP_CheckEndOfTransfer(void)
{
  /* Compare sending and receiving data */
  if(APP_Buffercmp8((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, DATA_LENGTH))
  {
    /* error handling */
    APP_LedBlinking();
  }
  else
  {
    /* If data is received, turn on the LED */
    BSP_LED_On(LED_GREEN);
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
  * @brief  LED flashing
  * @param  None
  * @retval None
  */
static void APP_LedBlinking(void)
{
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(500);
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
