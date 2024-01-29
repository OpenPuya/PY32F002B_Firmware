/**
  ******************************************************************************
  * @file    py32f002b_hal_msp.c
  * @author  MCU Application Team
  * @brief   This file provides code for the MSP Initialization
  *          and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) Puya Semiconductor Co.
  * All rights reserved.</center></h2>
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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* External functions --------------------------------------------------------*/

/**
  * @brief Initialize global MSP
  */
void HAL_MspInit(void)
{
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
}

/**
  * @brief Initialize TIM MSP
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  /* Enable TIM1 Clock */
  __HAL_RCC_TIM1_CLK_ENABLE();
  /* Enable GPIOA Clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  /* Enable GPIOB Clock */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* GPIO Configure */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  
  /* TIM1_CH1 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* TIM1_CH1N */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  /* TIM1_CH2 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* TIM1_CH2N */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  /* TIM1_CH3 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
  /* TIM1_CH3N */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Alternate = GPIO_AF3_TIM1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* TIM Interrupt Configure */
  HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
