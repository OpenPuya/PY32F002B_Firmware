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
  
  /* ADC manually calibration */
  APP_AdcCalibrate();

  /* Configure ADC parameters */
  APP_AdcConfig();

  /* Enable ADC */
  APP_AdcEnable();

  while (1)
  {
    /* Start ADC conversion */
    LL_ADC_REG_StartConversion(ADC1);
    while(LL_ADC_IsActiveFlag_EOC(ADC1)==0);
    LL_ADC_ClearFlag_EOC(ADC1);
    printf("CH4:%d",LL_ADC_REG_ReadConversionData12(ADC1));
    LL_mDelay(1000);
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

  /* Set ADC clock to pclk/8 */
  LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV8);

  /* Set ADC resolution to 12 bit */
  LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);

  /* ADC conversion data alignment: right aligned */
  LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

  /* No ADC low power mode activated */
  LL_ADC_SetLowPowerMode(ADC1, LL_ADC_LP_MODE_NONE);

  /* Sampling time 239.5 ADC clock cycles */
  LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_28CYCLES_5);

  /* ADC regular group conversion trigger from Software */
  LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

  /* Set ADC conversion mode to single mode: one conversion per trigger */
  LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);

  /* ADC regular group behavior in case of overrun: data overwritten */
  LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);

  /* Disable ADC regular group sequencer discontinuous mode  */
  LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);

  /* Set channel 4 as conversion channel */
  LL_ADC_REG_SetSequencerChannels(ADC1, LL_ADC_CHANNEL_4);
  
  LL_ADC_SetVrefBufferVoltage(ADC1,LL_ADC_VREFBUF_1P5V);
    
  LL_ADC_EnableVrefBufferVoltage(ADC1);
    
  /* Dose not enable internal conversion channel */
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_VREFINT );
}

/**
  * @brief  ADC calibration program.
  * @param  None
  * @retval None
  */
static void APP_AdcCalibrate(void)
{
  __IO uint32_t TotalData=0;
  __IO uint32_t TrimValue=0x0;
  __IO uint32_t Flag = 0; 
  __IO uint32_t wait_loop_index = 0;
  
#if (USE_TIMEOUT == 1)
  uint32_t Timeout = 0;
#endif

  if (LL_ADC_IsEnabled(ADC1) == 0)
  {    
    LL_ADC_SetVrefBufferVoltage(ADC1,LL_ADC_VREFBUF_1P5V);
    
    LL_ADC_EnableVrefBufferVoltage(ADC1);
    
    /* Enable internal conversion channel */
    LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_VREFINT );
    
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
    wait_loop_index = 4*32;
    while(wait_loop_index != 0)
    {
      wait_loop_index--;
    }
    
    LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
    /* Set PA3 Output */
    LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_3,LL_GPIO_MODE_OUTPUT);   
    /* Set PA3 PushPull */
    LL_GPIO_SetPinOutputType(GPIOA,LL_GPIO_PIN_3,LL_GPIO_OUTPUT_PUSHPULL);  
    /* Set PA3 NoPull */
    LL_GPIO_SetPinPull(GPIOA,LL_GPIO_PIN_3,LL_GPIO_PULL_NO);      
    
    /* Set ADC clock to pclk/8 */
    LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV8);

    /* Set ADC resolution to 12 bit */
    LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);

    /* ADC conversion data alignment: right aligned */
    LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);

    /* No ADC low power mode activated */
    LL_ADC_SetLowPowerMode(ADC1, LL_ADC_LP_MODE_NONE);

    /* Sampling time 28.5 ADC clock cycles */
    LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_28CYCLES_5);
    
    /* Set ADC conversion mode to single mode: one conversion per trigger */
    LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_SINGLE);
  
    /* ADC regular group conversion trigger from external IP: TIM1 TRGO. */
    LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);

    /* ADC regular group behavior in case of overrun: data preserved */    
    LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_PRESERVED);
    
    /* Disable ADC regular group sequencer discontinuous mode  */
    LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);
    
    /* Set channel 1 as conversion channel */
    LL_ADC_REG_SetSequencerChannels(ADC1,LL_ADC_CHANNEL_1);
   
    LL_ADC_Enable(ADC1);
    
    wait_loop_index = 8*32;
    while(wait_loop_index != 0)
    {
      wait_loop_index--;
    }

    *(uint32_t *)0x40012454=*(uint32_t *)0x40012448;
    *(uint32_t *)0x40012458=*(uint32_t *)0x4001244C; 
    *(uint32_t *)0x4001245C=0x00;
    
    SET_BIT(ADC1->CCSR,ADC_CCSR_CALSET);
 
    TotalData=0;
    for(int looptime=0;looptime<5;looptime++)
    {
      LL_ADC_REG_StartConversion(ADC1);  
      while(LL_ADC_IsActiveFlag_EOC(ADC1)==0);
      LL_ADC_ClearFlag_EOC(ADC1);      
      TotalData=TotalData+ LL_ADC_REG_ReadConversionData12(ADC1);     
    }
  
    if(TotalData<5 && TotalData>0)
    {   
      LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_3,LL_GPIO_MODE_ANALOG); 
      /* Disable ADC */
      LL_ADC_Disable(ADC1);
      /* Set ADC clock to pclk/1 */
      LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV1);
      /* Sampling time 3.5 ADC clock cycles */
      LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_3CYCLES_5);
      LL_ADC_ClearFlag_EOS(ADC1);
      LL_ADC_ClearFlag_EOSMP(ADC1);
      LL_ADC_REG_SetSequencerChRem(ADC1,LL_ADC_CHANNEL_1);      
      return;
    }

    if(TotalData>=5)
    {
      Flag=1;
    }
    else
    {
      Flag=0;
    }
  
    if(Flag==1)
    {
      TrimValue=0x1FF;
    }
    else
    {
      TrimValue=0;
    }
    for(int i=0;i<30;i++)
    {
      if(Flag==1)
      {
        TrimValue=TrimValue-8;
      }
      else
      {
        TrimValue=TrimValue+8;
      }
      *(uint32_t *)0x4001245C=TrimValue;
      SET_BIT(ADC1->CCSR,ADC_CCSR_CALSET);

      TotalData=0;
      for(int looptime=0;looptime<5;looptime++)
      {
        LL_ADC_REG_StartConversion(ADC1);  
        while(LL_ADC_IsActiveFlag_EOC(ADC1)==0);
        LL_ADC_ClearFlag_EOC(ADC1);      
        TotalData=TotalData+ LL_ADC_REG_ReadConversionData12(ADC1);    
      } 
      if(Flag==1)
      {
        if(TotalData<5)
        {
          break;
        }
      }
      else
      {
        if(TotalData>0)
        {
          break;
       }
      }        
    }   
  
    if(Flag==1)
    {
      TrimValue=TrimValue+8;
    }
    else
    {
      TrimValue=TrimValue-8;
    }
    for(int i=0;i<8;i++)
    {
      if(Flag==1)
      {
        TrimValue=TrimValue-1;
      }
      else
      {
        TrimValue=TrimValue+1;
      }
      *(uint32_t *)0x4001245C=TrimValue;
      SET_BIT(ADC1->CCSR,ADC_CCSR_CALSET);
      TotalData=0;
      for(int looptime=0;looptime<5;looptime++)
      {
        LL_ADC_REG_StartConversion(ADC1);  
        while(LL_ADC_IsActiveFlag_EOC(ADC1)==0);
        LL_ADC_ClearFlag_EOC(ADC1);      
        TotalData=TotalData+ LL_ADC_REG_ReadConversionData12(ADC1);      
      }    
      if(Flag==1)
      {
        if(TotalData<5)
        {
          break;
        }
      }
      else
      {
        if(TotalData>0)
        {
          break;
        }
      }   
    }
  
    LL_GPIO_SetPinMode(GPIOA,LL_GPIO_PIN_3,LL_GPIO_MODE_ANALOG); 
    
    LL_ADC_Disable(ADC1);
    /* Set ADC clock to pclk/1 */
    LL_ADC_SetClock(ADC1, LL_ADC_CLOCK_SYNC_PCLK_DIV1);
    /* Sampling time 3.5 ADC clock cycles */
    LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_3CYCLES_5);
    LL_ADC_ClearFlag_EOS(ADC1);
    LL_ADC_ClearFlag_EOSMP(ADC1);
    LL_ADC_REG_SetSequencerChRem(ADC1,LL_ADC_CHANNEL_1);      
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
