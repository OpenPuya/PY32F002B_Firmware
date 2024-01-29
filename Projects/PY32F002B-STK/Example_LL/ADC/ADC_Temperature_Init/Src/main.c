/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
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
#include "py32f002bxx_ll_Start_Kit.h"

/* Private define ------------------------------------------------------------*/
#define ADC_CALIBRATION_TIMEOUT_MS       ((uint32_t) 1)
#define VAR_CONVERTED_DATA_INIT_VALUE    (__LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B) + 1)

/* Private variables ---------------------------------------------------------*/
__IO uint32_t ubUserButtonPressed = 0;
__IO uint16_t uhADCxConvertedData = VAR_CONVERTED_DATA_INIT_VALUE;
__IO uint16_t uhADCxConvertedData_Temp = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_AdcConfig(void);
static void APP_AdcEnable(void);
static void APP_AdcCalibrate(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Configure HSI as Systemclock source */
  APP_SystemClockConfig();

  /* Initialize USART(for printf() use) */
  BSP_USART_Config();

  /* Configure ADC parameters */
  APP_AdcConfig();

  /* ADC automatic self-calibration */
  APP_AdcCalibrate();

  /* Enable ADC */
  APP_AdcEnable();

  /* Start ADC conversion (if it is software triggered then start conversion directly) */
  LL_ADC_REG_StartConversion(ADC1);
  while (1)
  {
    if(LL_ADC_IsActiveFlag_EOS(ADC1))
    {
      LL_ADC_ClearFlag_EOS(ADC1);
      /* Get ADC conversion data */
      uhADCxConvertedData = LL_ADC_REG_ReadConversionData12(ADC1);

      uhADCxConvertedData_Temp= __LL_ADC_CALC_TEMPERATURE(3300,uhADCxConvertedData,LL_ADC_RESOLUTION_12B);

      /* Printf current temperature value */
      printf("Temperature:%d \r\n",uhADCxConvertedData_Temp);
      LL_mDelay(200);
    }
  }
}

/**
  * @brief  Configure ADC parameters
  * @param  None
  * @retval None
  */
static void APP_AdcConfig(void)
{
  __IO uint32_t wait_loop_index = 0;
  LL_ADC_InitTypeDef ADC_Init;
  LL_ADC_REG_InitTypeDef LL_ADC_REG_InitType;
  ADC_Common_TypeDef ADC_Common_Type;

  /* Enable ADC clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);

  /* Initialize partical features of ADC instance */
  ADC_Init.Clock=LL_ADC_CLOCK_SYNC_PCLK_DIV64;
  ADC_Init.DataAlignment=LL_ADC_DATA_ALIGN_RIGHT;
  ADC_Init.LowPowerMode=LL_ADC_LP_MODE_NONE;
  ADC_Init.Resolution=LL_ADC_RESOLUTION_12B;
  LL_ADC_Init(ADC1,&ADC_Init);
  /* Sampling time 239.5 ADC clock cycles */
  LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_239CYCLES_5);

  /* Initialize partical features of ADC instance */
  LL_ADC_REG_InitType.ContinuousMode=LL_ADC_REG_CONV_CONTINUOUS;
  LL_ADC_REG_InitType.Overrun=LL_ADC_REG_OVR_DATA_OVERWRITTEN;
  LL_ADC_REG_InitType.SequencerDiscont=LL_ADC_REG_SEQ_DISCONT_DISABLE;
  LL_ADC_REG_InitType.TriggerSource=LL_ADC_REG_TRIG_SOFTWARE;
  LL_ADC_REG_Init(ADC1,&LL_ADC_REG_InitType);

  /* Set internal channel that connected to Temperature sensor as conversion channel */
  LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_TEMPSENSOR);

  /* Enable internal conversion channel */
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1),LL_ADC_PATH_INTERNAL_TEMPSENSOR);

  /* Delay for temperature sensor stabilization time */
  wait_loop_index = ((LL_ADC_DELAY_TEMPSENSOR_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
}

/**
  * @brief  ADC calibration program.
  * @param  None
  * @retval None
  */
static void APP_AdcCalibrate(void)
{
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 0; /* Variable used for timeout management */
#endif /* USE_TIMEOUT */

  if (LL_ADC_IsEnabled(ADC1) == 0)
  {

    /* Enable ADC calibration */
    LL_ADC_StartCalibration(ADC1);

#if (USE_TIMEOUT == 1)
    Timeout = ADC_CALIBRATION_TIMEOUT_MS;
#endif /* USE_TIMEOUT */

    while (LL_ADC_IsCalibrationOnGoing(ADC1) != 0)
    {
#if (USE_TIMEOUT == 1)
      /* Detects if the calibration has timed out */
      if (LL_SYSTICK_IsActiveCounterFlag())
      {
        if(Timeout-- == 0)
        {

        }
      }
#endif /* USE_TIMEOUT */
    }

    /* The delay between the end of ADC calibration and ADC enablement is at least 4 ADC clocks */
    LL_mDelay(1);
  }
}

/**
  * @brief  Enable ADC.
  * @param  None
  * @retval None
  */
static void APP_AdcEnable(void)
{
  /* Enable ADC */
  LL_ADC_Enable(ADC1);

  /* The delay between ADC enablement and ADC stabilization is at least 8 ADC clocks */
  LL_mDelay(1);
}

/**
  * @brief  Configure HSI as Systemclock source
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
