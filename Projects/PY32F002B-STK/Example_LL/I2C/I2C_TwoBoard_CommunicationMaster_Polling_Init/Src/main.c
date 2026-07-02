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
#define I2C_ADDRESS        0xA0     /* Master\Slave Address */
#define I2C_SPEEDCLOCK     100000   /* Communication frequency:100K */
#define I2C_STATE_READY    0        /* Ready state */
#define I2C_STATE_BUSY_TX  1        /* Send state */
#define I2C_STATE_BUSY_RX  2        /* Receive state */

/* Private variables ---------------------------------------------------------*/
uint8_t aTxBuffer[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
uint8_t aRxBuffer[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint8_t         *pBuffPtr   = NULL;
__IO uint16_t   XferCount   = 0;
__IO uint32_t   Devaddress  = 0;
__IO uint32_t   State       = I2C_STATE_READY;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_ConfigI2cMaster(void);
static void APP_MasterTransmit(uint16_t DevAddress, uint8_t *pData, uint16_t Size);
static void APP_MasterReceive(uint16_t DevAddress, uint8_t *pData, uint16_t Size);
static void APP_CheckEndOfTransfer(void);
static uint8_t APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);
static void APP_LedBlinking(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* Configure I2C */
  APP_ConfigI2cMaster();

  /* Wait for the button to be pressed */
  while(BSP_PB_GetState(BUTTON_KEY));

  /* Master send data */
  APP_MasterTransmit(I2C_ADDRESS, (uint8_t *)aTxBuffer, sizeof(aTxBuffer));

  /* Wait for the master to finish sending data */
  while (State != I2C_STATE_READY);

  /* Delay to wait for the slave to prepare data */
  LL_mDelay(5);

  /* Master receive data */
  APP_MasterReceive(I2C_ADDRESS, (uint8_t *)aRxBuffer, sizeof(aRxBuffer));

  /* Wait for the master to finish receiving data */
  while (State != I2C_STATE_READY);

  /* Check received data */
  APP_CheckEndOfTransfer();

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
  * @brief  Configure I2C peripheral
  * @param  None
  * @retval None
  */
static void APP_ConfigI2cMaster(void)
{
  /* Enabel GPIOB clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

  /* Enabke I2C1 peripheral clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

  /* Set PB3 to SCL pin , Select alternate function mode
     and fast output speed. output type is Selected open-drain,
     Enable I/O pull up*/
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Set PB4 to SDA pin , Select alternate function mode
     and fast output speed. output type is Selected open-drain,
     Enable I/O pull up*/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* Reset I2C peripheral */
  LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_I2C1);
  LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_I2C1);

  /* Initialize I2C1 peripheral */
  LL_I2C_InitTypeDef I2C_InitStruct = {0};
  I2C_InitStruct.ClockSpeed      = I2C_SPEEDCLOCK;
  I2C_InitStruct.DutyCycle       = LL_I2C_DUTYCYCLE_16_9;
  I2C_InitStruct.OwnAddress1     = I2C_ADDRESS;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_NACK;
  LL_I2C_Init(I2C1, &I2C_InitStruct);

  /* Enable clock stretching */
  /* Reset value is clock stretching enabled */
  /* LL_I2C_EnableClockStretching(I2C1); */

  /* Enable general call  */
  /* Reset value is general call disabled */
  /* LL_I2C_EnableGeneralCall(I2C1); */
}

/**
  * @brief  I2C Send data
  * @param  DevAddress：Slave address
  * @param  pData：pData pointer to Send buffer
  * @param  Size：Size Amount of data to be sent
  * @retval None
  */
static void APP_MasterTransmit(uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  /* Clear pos bit */
  LL_I2C_DisableBitPOS(I2C1);

  /* Update the slave address, data to be sent, data size, and status to global variables */
  pBuffPtr    = pData;
  XferCount   = Size;
  Devaddress  = DevAddress;
  State       = I2C_STATE_BUSY_TX;

  /* Generate Start signal */
  LL_I2C_GenerateStartCondition(I2C1);
  while(LL_I2C_IsActiveFlag_SB(I2C1) != 1);

  /* Send slave address */
  LL_I2C_TransmitData8(I2C1, (Devaddress & (uint8_t)(~0x01)));
  while(LL_I2C_IsActiveFlag_ADDR(I2C1) != 1);
  LL_I2C_ClearFlag_ADDR(I2C1);

  /* Send data */
  while(XferCount > 0)
  {
    while(LL_I2C_IsActiveFlag_TXE(I2C1) != 1);
    LL_I2C_TransmitData8(I2C1, *pBuffPtr);
    pBuffPtr++;
    XferCount--;

    if ((LL_I2C_IsActiveFlag_BTF(I2C1) == 1) && (XferCount != 0U))
    {
      LL_I2C_TransmitData8(I2C1, *pBuffPtr);
      pBuffPtr++;
      XferCount--;
    }

    while(LL_I2C_IsActiveFlag_BTF(I2C1) != 1);
  }

  /* Generate STOP signal */
  LL_I2C_GenerateStopCondition(I2C1);

  State = I2C_STATE_READY;
}

/**
  * @brief  I2C receive data
  * @param  DevAddress：Slave address
  * @param  pData：pData pointer to receive buffer
  * @param  Size：Size Amount of data to be received
  * @retval None
  */
static void APP_MasterReceive(uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  /* clear pos bit */
  LL_I2C_DisableBitPOS(I2C1);

  /* Update the slave address, data to be received, data size, and status to global variables */
  pBuffPtr    = pData;
  XferCount   = Size;
  Devaddress  = DevAddress;
  State       = I2C_STATE_BUSY_RX;

  /* Prepare the generation of a ACKnowledge condition */
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

  /* Generate Start signal */
  LL_I2C_GenerateStartCondition(I2C1);
  while(LL_I2C_IsActiveFlag_SB(I2C1) != 1);

  /* Send slave address */
  LL_I2C_TransmitData8(I2C1, (Devaddress | 0x1));
  while(LL_I2C_IsActiveFlag_ADDR(I2C1) != 1);

  /* Receive data */
  if (XferCount == 0U)
  {
    LL_I2C_ClearFlag_ADDR(I2C1);
    LL_I2C_GenerateStopCondition(I2C1);
  }
  else if(XferCount == 1U)
  {
    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);

    __disable_irq();
    LL_I2C_ClearFlag_ADDR(I2C1);
    LL_I2C_GenerateStopCondition(I2C1);
    __enable_irq();
  }
  else if(XferCount == 2U)
  {
    LL_I2C_EnableBitPOS(I2C1);

    __disable_irq();
    LL_I2C_ClearFlag_ADDR(I2C1);
    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);
    __enable_irq();
  }
  else
  {
    LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);
    LL_I2C_ClearFlag_ADDR(I2C1);
  }

  while (XferCount > 0U)
  {
    if (XferCount <= 3U)
    {
      if (XferCount == 1U)
      {
        while(LL_I2C_IsActiveFlag_RXNE(I2C1) != 1);
        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
      }
      else if (XferCount == 2U)
      {
        while(LL_I2C_IsActiveFlag_BTF(I2C1) != 1);

        __disable_irq();
        LL_I2C_GenerateStopCondition(I2C1);
        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
        __enable_irq();

        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
      }
      else
      {
        while(LL_I2C_IsActiveFlag_BTF(I2C1) != 1);

        LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_NACK);

        __disable_irq();
        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
        while(LL_I2C_IsActiveFlag_BTF(I2C1) != 1);
        LL_I2C_GenerateStopCondition(I2C1);
        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
        __enable_irq();

        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
      }
    }
    else
    {
      while(LL_I2C_IsActiveFlag_RXNE(I2C1) != 1);

      *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
       pBuffPtr++;
       XferCount--;

      if (LL_I2C_IsActiveFlag_BTF(I2C1) == 1)
      {
        *pBuffPtr = LL_I2C_ReceiveData8(I2C1);
        pBuffPtr++;
        XferCount--;
      }
    }
  }

  State = I2C_STATE_READY;
}

/**
  * @brief  Compare sent and received data
  * @param  None
  * @retval None
  */
static void APP_CheckEndOfTransfer(void)
{
  /* Compare sent data and received data */
  if(APP_Buffercmp8((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, sizeof(aRxBuffer)))
  {
    /* Error handle */
    APP_LedBlinking();
  }
  else
  {
    /* if data received successfully, turn on the LED */
    BSP_LED_On(LED_GREEN);
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
  * @brief  LED blinking
  * @param  None
  * @retval None
  */
static void APP_LedBlinking(void)
{
  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);
    LL_mDelay(500);
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
