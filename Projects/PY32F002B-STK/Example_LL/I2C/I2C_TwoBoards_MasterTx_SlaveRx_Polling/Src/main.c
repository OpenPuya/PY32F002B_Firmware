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
/* I2C SPEEDCLOCK is defined as the maximum value：Fast mode(400kHz) */
#define I2C_SPEEDCLOCK           400000
#define I2C_DUTYCYCLE            LL_I2C_DUTYCYCLE_2

/* Private variables ---------------------------------------------------------*/
const uint8_t aLedOn[]           = "LED ON";
#ifdef SLAVE_BOARD
uint8_t      aReceiveBuffer[0xF] = {0};
uint8_t ubReceiveIndex      = 0;
#else /* MASTER_BOARD */
uint8_t  ubNbDataToTransmit = sizeof(aLedOn);
uint8_t*      pTransmitBuffer    = (uint8_t*)aLedOn;
#endif /* SLAVE_BOARD */

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
#ifdef SLAVE_BOARD
static void     APP_ConfigI2cSlave(void);
static void     APP_ActivateI2cSlave(void);
static void     APP_HandleI2cSlave(void);
static uint8_t  APP_Buffercmp8(uint8_t* pBuffer1, uint8_t* pBuffer2, uint8_t BufferLength);
#else /* MASTER_BOARD */
static void     APP_ConfigI2cMaster(void);
static void     APP_ActivateI2cMaster(void);
static void     APP_HandleI2cMaster(void);
#endif /* SLAVE_BOARD */

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

  #ifdef SLAVE_BOARD
  /* Configure I2C1（I2C configuration in slave mode and related GPIO initialization）*/
  APP_ConfigI2cSlave();

  /* Wait for the button to be pressed */
  while(BSP_PB_GetState(BUTTON_KEY))
  {}

  /* Enable I2C1 periphreal（as slave ） */
  APP_ActivateI2cSlave();

  /* Handling I2C1 events (as slave) */
  APP_HandleI2cSlave();
#else /* MASTER_BOARD */
  /* Configure I2C1（I2C configuration in master mode and related GPIO initialization）*/
  APP_ConfigI2cMaster();

  /* Wait for the button to be pressed */
  while(BSP_PB_GetState(BUTTON_KEY))
  {}

  /* Enable I2C1 periphreal（as master ） */
  APP_ActivateI2cMaster();

  /* Handling I2C1 events (as master ) */
  APP_HandleI2cMaster();
#endif /* SLAVE_BOARD */

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

#ifdef SLAVE_BOARD
/**
  * @brief  Configure I2C peripheral(as slave)
  * @param  None
  * @retval None
  */
static void APP_ConfigI2cSlave(void)
{
  /* (1) Enable GPIO clock ************************/

  /* Enabel GPIOB clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

  /* (2) Enable I2C1 peripheral clock *************************************/

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

  /* (3) configure I2C1 features***********************/

  /* Disable I2C1 before modify I2C1 control register */
  LL_I2C_Disable(I2C1);

  /* Set slave address：
    * - OwnAddress1 is SLAVE_OWN_ADDRESS
    */
  LL_I2C_SetOwnAddress1(I2C1, SLAVE_OWN_ADDRESS, 0);

  /* Enable clock stretching */
  /* Reset value is clock stretching enabled */
  /* LL_I2C_EnableClockStretching(I2C1); */

  /* Enable general call  */
  /* Reset value is general call disabled */
  /* LL_I2C_EnableGeneralCall(I2C1); */
}

/**
  * @brief  Enable I2C1(as slave)
  * @param
  * @retval None
  */
static void APP_ActivateI2cSlave(void)
{
  LL_I2C_Enable(I2C1);
}

#else /* MASTER_BOARD */

/**
  * @brief  Configure I2C1 as master
  * @param  None
  * @retval None
  */
static void APP_ConfigI2cMaster(void)
{
  LL_RCC_ClocksTypeDef rcc_clocks = {0};

  /* (1) Enable GPIO clock ************************/

  /* Enable GPIOB clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

  /* (2) Enable I2C1 clock *************************************/

  /* Enable I2C1 periphreal clock */
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

  /* Set PB4 to SCL pin , Select alternate function mode
     and fast output speed. output type is Selected open-drain,
     Enable I/O pull up*/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_6;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* (3) Set I2C1 feature********************************/

  /* Disable I2C1 before modify I2C1 control register */
  LL_I2C_Disable(I2C1);

  /* Record sysclk、pclk and hclk to rcc_clocks structure  */
  LL_RCC_GetSystemClocksFreq(&rcc_clocks);

  /* Set SCL clock frequency */
  LL_I2C_ConfigSpeed(I2C1, rcc_clocks.PCLK1_Frequency, I2C_SPEEDCLOCK, I2C_DUTYCYCLE);

  /* Enable clock stretching */
  /* Reset value is clock stretching enabled */
  /* LL_I2C_EnableClockStretching(I2C1); */

  /* Enable general call  */
  /* Reset value is general call disabled */
  /* LL_I2C_EnableGeneralCall(I2C1); */
}

/**
  * @brief  Enable I2C1(as master)
  * @param  None
  * @retval None
  */
static void APP_ActivateI2cMaster(void)
{
  LL_I2C_Enable(I2C1);
}
#endif /* SLAVE_BOARD */

#ifdef SLAVE_BOARD
/**
  * @brief  I2C(as slave) handle program
  * @param  None
  * @retval None
  */
static void APP_HandleI2cSlave(void)
{
  /* (1) Prepare to return a successfully addressed ACK ************************/
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

  /* (2) Wait for ADDR bit to be set and check transmission direction ************/
  while(!LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
  }

  /* Check transmission direction if is read，Slave enter receiver mode */
  if(LL_I2C_GetTransferDirection(I2C1) == LL_I2C_DIRECTION_READ)
  {
    /* Clear ADDR flag */
    LL_I2C_ClearFlag_ADDR(I2C1);
  }
  else
  {
    /* Clear ADDR flag */
    LL_I2C_ClearFlag_ADDR(I2C1);

    /* Call error handling program */
    APP_ErrorHandler();
  }

  /* (3) Wait for STOP to be set ***************/

  /* Wait for STOP to be set */
  while(!LL_I2C_IsActiveFlag_STOP(I2C1))
  {
    /* (3.1) receive data（RXNE bit is set） **********************************/

    /* Check RxNE if is set */
    if(LL_I2C_IsActiveFlag_RXNE(I2C1))
    {
      /* Read data register to clear RxNE bit */
      aReceiveBuffer[ubReceiveIndex++] = LL_I2C_ReceiveData8(I2C1);
    }

    /* (3.2) receive dara（BTF is set） ***********************************/
    /* Check BTF if is set */
    if(LL_I2C_IsActiveFlag_BTF(I2C1))
    {
      /* Read data register to clear BTF bit */
      aReceiveBuffer[ubReceiveIndex++] = LL_I2C_ReceiveData8(I2C1);
    }
  }

  /* (4) Clear Stop detection flag ，check data consistency **************************/
  LL_I2C_ClearFlag_STOP(I2C1);

  /* Check whether the data is the same*/
  if(APP_Buffercmp8((uint8_t*)aReceiveBuffer, (uint8_t*)aLedOn, (ubReceiveIndex-1)) == 0)
  {
    /* turn on LED：
      * - The expected bytes have been received
      * - Rx sequence completed successfully
      */
      BSP_LED_On(LED_GREEN);
  }
  else
  {
    /* Call error handling program */
    APP_ErrorHandler();
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

#else /* MASTER_BOARD */

/**
  * @brief  I2C(as master) handling program
  * @param  None
  * @retval None
  */
static void APP_HandleI2cMaster(void)
{
  /* (1) Prepare to return a successfully received ACK ************************/
  LL_I2C_AcknowledgeNextData(I2C1, LL_I2C_ACK);

  /* (2) Generate START signal ***********************/
   /* Master Generate START condition */
  LL_I2C_GenerateStartCondition(I2C1);

  /* (3) Wait for SB bit be set ********************/
  while(!LL_I2C_IsActiveFlag_SB(I2C1))
  {
  }

  /* (4) Send 7 bit slave adderss + 1 bit R/W bit */
  LL_I2C_TransmitData8(I2C1, SLAVE_OWN_ADDRESS | I2C_REQUEST_WRITE);

  /* (5) Loop until a successfully addressed ACK is received (ADDR flag set)*******/
  /* wait for ADDR bit be set */
  while(!LL_I2C_IsActiveFlag_ADDR(I2C1))
  {
  }

  /* (6) Clear ADDR flag and loop until transmission completed (ubNbDataToTransmit == 0) */
  /* clear ADDR flag */
  LL_I2C_ClearFlag_ADDR(I2C1);

  /* wait for TXE bit be set */
  while(ubNbDataToTransmit > 0)
  {
    /* (6.1) send data（TXE bit is set） **********************************/

    /* Check TxE if is set */
    if(LL_I2C_IsActiveFlag_TXE(I2C1))
    {
      /* Read data register to clear TxE bit */
      LL_I2C_TransmitData8(I2C1, (*pTransmitBuffer++));

      ubNbDataToTransmit--;
    }
  }

  /* (7) Transmission completed，the slave is checking data consistency *****/
  /* Generate STOP signal */
  LL_I2C_GenerateStopCondition(I2C1);

  /*turn on LED：
    * - The expected bytes have been received
    * - Tx sequence completed successfully
    */
  BSP_LED_On(LED_GREEN);
}
#endif /* SLAVE_BOARD */

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
