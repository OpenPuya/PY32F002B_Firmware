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
COMP_HandleTypeDef  hcomp2;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_RccInit(void);
static void APP_CompInit(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Systick. */ 
  HAL_Init();
  
  /* Initialize button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);
  
  /* Initialize clock settings */
  APP_RccInit();

  /* Initialize COMP */
  APP_CompInit();
   
  /* COMP Start */
  HAL_COMP_Start(&hcomp2); 
  
  BSP_LED_On(LED_GREEN);

  /* Wait for button press */
  while(BSP_PB_GetState(BUTTON_USER))
  {
  }
  
  BSP_LED_Off(LED_GREEN); 
  
  /* Suspend SysTick interrupt */
  HAL_SuspendTick();
  
  /* Enter Sleep mode */
  HAL_PWR_EnterSLEEPMode(PWR_SLEEPENTRY_WFI);  

  /* Restore SysTick interrupt */
  HAL_ResumeTick();

  while (1)
  {
    BSP_LED_Toggle(LED_GREEN);
    HAL_Delay(200); 
  }
}

/**
  * @brief  Comparator clock configuration function
  * @param  None
  * @retval None
  */
static void APP_RccInit(void)
{                    
  RCC_OscInitTypeDef RCCCONF = {0};
  RCC_PeriphCLKInitTypeDef COMPRCC = {0};
  
  RCCCONF.OscillatorType = RCC_OSCILLATORTYPE_LSI;        /* RCC uses internal LSI */
  RCCCONF.LSIState = RCC_LSI_ON;                          /* Enable LSI */
  RCCCONF.LSICalibrationValue = RCC_LSICALIBRATION_32768Hz ; /* Set LSI 32768 hz */
  HAL_RCC_OscConfig(&RCCCONF);                            /* Initialize clock settings */
  
  HAL_RCCEx_EnableLSCO(RCC_LSCOSOURCE_LSI);               /* Set LSC Source LSI and Enable LSC */
  
  COMPRCC.PeriphClockSelection = RCC_PERIPHCLK_COMP1;     /* Peripheral selection: COMP1 */
  COMPRCC.Comp1ClockSelection = RCC_COMP1CLKSOURCE_LSC;   /* Independent clock source for COMP1: LSC */

  HAL_RCCEx_PeriphCLKConfig(&COMPRCC);                    /* Initialize RCC peripheral clock settings */
  
  COMPRCC.PeriphClockSelection = RCC_PERIPHCLK_COMP2;     /* Peripheral selection: COMP2 */
  COMPRCC.Comp2ClockSelection = RCC_COMP2CLKSOURCE_LSC;   /* Independent clock source for COMP2: LSC */

  HAL_RCCEx_PeriphCLKConfig(&COMPRCC);                    /* Initialize RCC peripheral clock settings */
}

/**
  * @brief  Comparator initialization function
  * @param  None
  * @retval None
  */
static void APP_CompInit(void)
{
  hcomp2.Instance = COMP2;                                            /* COMP2 */
  hcomp2.Init.InputMinus      = COMP_INPUT_MINUS_IO1;                 /* Minus Input PA4 */
  hcomp2.Init.InputPlus       = COMP_INPUT_PLUS_IO2;                  /* Plus Input VrefCmp */
  hcomp2.Init.OutputPol       = COMP_OUTPUTPOL_NONINVERTED;           /* Output None Inverted */
  hcomp2.Init.WindowMode      = COMP_WINDOWMODE_DISABLE;              /* Window mode Disable */
  hcomp2.Init.VrefSrc         = COMP_VREFCMP_SOURCE_VCC;              /* VrefCmp Select VCC */
  hcomp2.Init.VrefDiv         = COMP_VREFCMP_DIV_8_16VREFCMP;         /* VrefCmp 8/16  */
  hcomp2.Init.DigitalFilter   = 0x0;                                  /* Filter Disable */
  hcomp2.Init.TriggerMode     = COMP_TRIGGERMODE_IT_RISING;           /* Trigger on Rising */
  /* Initialize COMP */
  if (HAL_COMP_Init(&hcomp2) != HAL_OK)                                 
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
