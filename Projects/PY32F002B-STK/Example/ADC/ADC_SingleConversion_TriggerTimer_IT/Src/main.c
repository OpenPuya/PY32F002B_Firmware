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
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef             hadc;
ADC_ChannelConfTypeDef        sConfig;
volatile uint16_t             aADCxConvertedData;
TIM_HandleTypeDef             TimHandle;
TIM_MasterConfigTypeDef       sMasterConfig;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_ADCConfig(void);
static void APP_TimConfig(void);

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

  /* Initialize UART */
  BSP_USART_Config();

  /* Configure ADC */
  APP_ADCConfig();
  
  /* Configure Timer */
  APP_TimConfig();
  
  HAL_ADC_Start_IT(&hadc);  
  
  while (1)
  {
  
  }
}

/**
  * @brief  ADC Conversion Callback
  * @param  None
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  aADCxConvertedData = hadc->Instance->DR;
  printf("ADC Channel4: %u\r\n", (unsigned int)aADCxConvertedData);
}

/**
  * @brief  ADC configuration function
  * @param  None
  * @retval None
  */
static void APP_ADCConfig(void)
{
  __HAL_RCC_ADC_CLK_ENABLE();                                                /* Enable ADC clock */

  hadc.Instance = ADC1;
  
  hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV32;               /* Set ADC clock*/
  hadc.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 12-bit resolution for converted data */
  hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* Right-alignment for converted data */
  hadc.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* Scan sequence direction: forward */
  hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* Single Conversion */
  hadc.Init.LowPowerAutoWait      = DISABLE;                                 /* Auto-delayed conversion feature disabled */
  hadc.Init.ContinuousConvMode    = DISABLE;                                 /* Continuous mode disabled to have only 1 conversion at each conversion trig */
  hadc.Init.DiscontinuousConvMode = DISABLE;                                 /* Disable discontinuous mode */
  hadc.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_TRGO;            /* Trig of conversion start done by external event */
  hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_RISING;         /* Trigger on rising edges */
  hadc.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* DR register is overwritten with the last conversion result in case of overrun */
  hadc.Init.SamplingTimeCommon    = ADC_SAMPLETIME_41CYCLES_5;               /* The channel sampling time is 41.5 ADC clock cycles */
  if (HAL_ADC_Init(&hadc) != HAL_OK)                                         /* ADC initialization */
  {
    APP_ErrorHandler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                             
  sConfig.Channel      = ADC_CHANNEL_4;                                      
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)                       /* Configure ADC Channel */
  {
    APP_ErrorHandler();
  }
    
  if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK)                           /* ADC Calibration */
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  TIM configuration function
  * @param  None
  * @retval None
  */
static void APP_TimConfig(void)
{
  __HAL_RCC_TIM1_CLK_ENABLE();                                        /* Enable TIM1 clock */
  TimHandle.Instance = TIM1;                                          /* TIM1 */
  TimHandle.Init.Period            = 24000 - 1;                       /* Period = 24000 - 1 */
  TimHandle.Init.Prescaler         = 1000 - 1;                        /* Prescaler = 1000 - 1 */
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;          /* ClockDivision = 0 */
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;              /* Counter direction = Up */
  TimHandle.Init.RepetitionCounter = 0;                               /* Repetition = 0 */
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;  /* Auto-reload register not buffered */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                        /* Initialize TIM1 */
  {
    APP_ErrorHandler();
  }

  /* Timer TRGO selection */
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;                
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;        
  HAL_TIMEx_MasterConfigSynchronization(&TimHandle, &sMasterConfig);  /* Configure TIM1 */
  if (HAL_TIM_Base_Start(&TimHandle) != HAL_OK)                       /* Start TIM1 */
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
