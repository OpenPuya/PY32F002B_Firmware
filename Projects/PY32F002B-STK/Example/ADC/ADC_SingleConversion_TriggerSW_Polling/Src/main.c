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

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_ADCConfig(void);

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
    
  while (1)
  {   
    /* ADC Start */
    HAL_ADC_Start(&hadc);  
    
    /* Polling for ADC Conversion */
    HAL_ADC_PollForConversion(&hadc, 1000000);        
    
    /* Get ADC Value */
    aADCxConvertedData = HAL_ADC_GetValue(&hadc);     
    
    /* print channel4 value */
    printf("Channel 4:%u",(unsigned int)aADCxConvertedData);
    
    HAL_Delay(1000);
  }
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
  
  hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV64;               /* Set ADC clock*/
  hadc.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 12-bit resolution for converted data */
  hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* Right-alignment for converted data */
  hadc.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* Scan sequence direction: forward */
  hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* Single Conversion */
  hadc.Init.LowPowerAutoWait      = DISABLE;                                 /* Auto-delayed conversion feature disabled */
  hadc.Init.ContinuousConvMode    = DISABLE;                                 /* Continuous mode disabled to have only 1 conversion at each conversion trig */
  hadc.Init.DiscontinuousConvMode = DISABLE;                                 /* Disable discontinuous mode */
  hadc.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* Software start to trig the 1st conversion manually, without external event */
  hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* Parameter discarded because software trigger chosen */
  hadc.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* DR register is overwritten with the last conversion result in case of overrun */
  hadc.Init.SamplingTimeCommon    = ADC_SAMPLETIME_239CYCLES_5;              /* The channel sampling time is 239.5 ADC clock cycles */
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
