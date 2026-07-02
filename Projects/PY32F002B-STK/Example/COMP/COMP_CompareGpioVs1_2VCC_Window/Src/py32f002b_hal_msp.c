/**
  ******************************************************************************
  * @file    py32f002b_hal_msp.c
  * @author  MCU Application Team
  * @brief   This file provides code for the MSP Initialization
  *          and de-Initialization codes.
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
  * @brief Initialize COMP MSP
  */
void HAL_COMP_MspInit(COMP_HandleTypeDef *hcomp)
{
  __HAL_RCC_GPIOB_CLK_ENABLE();                 /* Enable GPIOB Clock */
  __HAL_RCC_COMP1_CLK_ENABLE();                 /* Enable COMP1 Clock */    
  __HAL_RCC_COMP2_CLK_ENABLE();                 /* Enable COMP2 Clock */  

  /* Configure PB0 Analog */
  GPIO_InitTypeDef COMPINPUT = {0};
  COMPINPUT.Pin = GPIO_PIN_0;
  COMPINPUT.Mode = GPIO_MODE_ANALOG;            /* Analog Mode */
  COMPINPUT.Speed = GPIO_SPEED_FREQ_HIGH;
  COMPINPUT.Pull = GPIO_NOPULL;                 /* NO PULL */
  HAL_GPIO_Init(GPIOB,  &COMPINPUT);            /* GPIO Init */
}

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
