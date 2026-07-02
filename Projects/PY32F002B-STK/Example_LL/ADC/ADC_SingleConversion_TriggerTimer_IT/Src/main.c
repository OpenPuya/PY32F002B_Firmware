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
#define ADC_CALIBRATION_TIMEOUT_MS       ((uint32_t) 1)
#define VDDA_APPLI                       ((uint32_t)3300)
#define VAR_CONVERTED_DATA_INIT_VALUE    (__LL_ADC_DIGITAL_SCALE(LL_ADC_RESOLUTION_12B) + 1)

/* Private variables ---------------------------------------------------------*/
__IO uint16_t uhADCxConvertedData = VAR_CONVERTED_DATA_INIT_VALUE;
__IO uint16_t uhADCxConvertedData_Voltage_mVolt = 0;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_SystemClockConfig(void);
static void APP_AdcEnable(void);
static void APP_AdcCalibrate(void);
static void APP_AdcConfig(void);
static void APP_TimerInit(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval int
  */
int main(void)
{
  /* Enable SYSCFG clock and PWR clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* Initialize USART(for printf use) */
  BSP_USART_Config();

  /* Enable ADC1 clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_ADC1);

  /* Configure ADC parameters */
  APP_AdcConfig();

  /*  ADC automatic self-calibration */
  APP_AdcCalibrate();

  /* Enable ADC */
  APP_AdcEnable();

  /* Start ADC conversion (if it is software triggered then start conversion directly) */
  LL_ADC_REG_StartConversion(ADC1);

  /* Initialize TIM1 */
  APP_TimerInit();
  while (1)
  {
    /* LED toggle */
    BSP_LED_Toggle(LED_GREEN);
    LL_mDelay(500);
  }
}

/**
  * @brief  Configure ADC parameters
  * @param  None
  * @retval None
  */
static void APP_AdcConfig(void)
{
  /* Enable GPIOA clock */
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);

  /* Configure PA7 pin in analog input mode */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_ANALOG);

  /* Set ADC clock to pclk/4 */
  LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV4);

  /* Set ADC resolution to 12 bit */
  LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);

  /* ADC conversion data alignment: right aligned */
  LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

  /* No ADC low power mode activated */
  LL_ADC_SetLowPowerMode(ADC1, LL_ADC_LP_MODE_NONE);

  /* Sampling time 239.5 ADC clock cycles */
  LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_239CYCLES_5);

  /* ADC regular group conversion trigger from external IP: TIM1 TRGO. */
  LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_EXT_TIM1_TRGO);

  /* Set Trigger edge to rising edge */
  LL_ADC_REG_SetTriggerEdge(ADC1, LL_ADC_REG_TRIG_EXT_RISING);

  /* Set ADC conversion mode to single mode: one conversion per trigger */
  LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

  /* ADC regular group behavior in case of overrun: data overwritten */
  LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

  /* Disable ADC regular group sequencer discontinuous mode  */
  LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

  /* Set channel 4 as conversion channel */
  LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_4);

  /* Dose not enable internal conversion channel */
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_NONE );

  /* Enable EOC IT */
  LL_ADC_EnableIT_EOC(ADC1);

  NVIC_SetPriority(ADC_COMP_IRQn, 0);
  NVIC_EnableIRQ(ADC_COMP_IRQn);
}

/**
  * @brief  ADC calibration program.
  * @param  None
  * @retval None
  */
static void APP_AdcCalibrate(void)
{
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 0;
#endif

  if (LL_ADC_IsEnabled(ADC1) == 0)
  {

    /* Enable ADC calibration */
    LL_ADC_StartCalibration(ADC1);

#if (USE_TIMEOUT == 1)
    Timeout = ADC_CALIBRATION_TIMEOUT_MS;
#endif

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
#endif
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
  * @brief  TIM1 configuration program.
  * @param  None
  * @retval None
  */
static void APP_TimerInit()
{
  /* Enable TIM1 clock */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM1);

  /* Set TIM1 prescale */
  LL_TIM_SetPrescaler(TIM1,6000);

  /* Set TIM1 auto-reload value */
  LL_TIM_SetAutoReload(TIM1, 4000);

  /* TIM1 Update event is used as trigger output */
  LL_TIM_SetTriggerOutput(TIM1,LL_TIM_TRGO_UPDATE);

  /* Enable TIM1 */
  LL_TIM_EnableCounter(TIM1);
}

/**
  * @brief  ADC interruption handler callback program.
  * @param  None
  * @retval None
  */
void APP_AdcGrpRegularUnitaryConvCompleteCallback()
{
  /* Get ADC conversion data */
  uhADCxConvertedData = LL_ADC_REG_ReadConversionData12(ADC1);

  printf("ch4 DR:%u\r\n",(unsigned int)uhADCxConvertedData);

  /* Convert ADC raw data to voltage value */
  uhADCxConvertedData_Voltage_mVolt = __LL_ADC_CALC_DATA_TO_VOLTAGE(VDDA_APPLI,   \
     uhADCxConvertedData, LL_ADC_RESOLUTION_12B);

  /* Printf voltage sampled value by ADC  */
  printf("ch4:%umV\r\n",(unsigned int)uhADCxConvertedData_Voltage_mVolt);
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
