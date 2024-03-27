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
#define Vcc_Power     3.30                                            /* VCC power supply voltage, modify according to actual situation  */
#define TScal1        (float)((HAL_ADC_TSCAL1) * 3.3 / Vcc_Power)     /* Voltage corresponding to calibration value at 30 ℃ */
#define TScal2        (float)((HAL_ADC_TSCAL2) * 3.3 / Vcc_Power)     /* Voltage corresponding to calibration value at 85 ℃ */
#define TStem1        30                                              /* 30 ℃ */
#define TStem2        85                                              /* 85 ℃ */
#define Temp_k        ((float)(TStem2-TStem1)/(float)(TScal2-TScal1)) /* Temperature calculation */
  
/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef             AdcHandle;
ADC_ChannelConfTypeDef        sConfig;
volatile int16_t              aADCxConvertedData;
int16_t                       aTEMPERATURE;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_AdcConfig(void);

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
  APP_AdcConfig();                                                       
  while (1)
  {
    HAL_Delay(1000); 
    /* Start ADC and enable ADC interrupts */
    if (HAL_ADC_Start_IT(&AdcHandle) != HAL_OK)                           
    {
      APP_ErrorHandler();
    }
  }
}

/**
  * @brief  ADC configuration function
  * @param  None
  * @retval None
  */
static void APP_AdcConfig(void)
{
  __HAL_RCC_ADC_CLK_ENABLE();                                                     /* Enable ADC clock */

  AdcHandle.Instance = ADC1;
                                              
  AdcHandle.Instance                   = ADC1;                                    /* ADC1 */
  AdcHandle.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV32;               /* Set ADC clock */
  AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;                      /* 12-bit resolution for converted data */
  AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;                     /* Right-alignment for converted data */
  AdcHandle.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;              /* Scan sequence direction: forward */
  AdcHandle.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;                     /* Conversion completion flag */
  AdcHandle.Init.LowPowerAutoWait      = DISABLE;                                 /* Auto-delayed conversion feature disabled */
  AdcHandle.Init.ContinuousConvMode    = DISABLE;                                 /* Continuous mode disabled to have only 1 conversion at each conversion trig */
  AdcHandle.Init.DiscontinuousConvMode = DISABLE;                                 /* Disable discontinuous mode */
  AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;                      /* Software start to trig the 1st conversion manually, without external event */
  AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;           /* Parameter discarded because software trigger chosen */
  AdcHandle.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;                /* DR register is overwritten with the last conversion result in case of overrun */
  AdcHandle.Init.SamplingTimeCommon    = ADC_SAMPLETIME_41CYCLES_5;               /* Channel sampling time is 41.5 ADC clock cycles */
  /* ADC initialization */
  if (HAL_ADC_Init(&AdcHandle) != HAL_OK)                                         
  {
    APP_ErrorHandler();
  }

  sConfig.Rank         = ADC_RANK_CHANNEL_NUMBER;                                 /* Set the rank for the ADC channel order */
  sConfig.Channel      = ADC_CHANNEL_TEMPSENSOR;                                  /* ADC channel selection */
  /* Configure ADC channels */
  if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)                      
  {
    APP_ErrorHandler();
  }
  
  /* ADC calibration */
  if (HAL_ADCEx_Calibration_Start(&AdcHandle) != HAL_OK)                          
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  ADC transfer complete callback function
  * @param  adchandle：ADC handle 
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *adchandle)
{
  aADCxConvertedData = adchandle->Instance->DR;

  aTEMPERATURE =(int16_t)((85-30)*(aADCxConvertedData-TScal1)/(TScal2-TScal1) + TStem1);
  printf("Temperature = %d \r\n", (int)aTEMPERATURE);
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
