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

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
COMP_HandleTypeDef  hcomp2;
COMP_HandleTypeDef  hcomp1;

/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

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
  
  hcomp1.Instance = COMP1;                                               /* COMP1 */
  hcomp1.Init.InputMinus      = COMP_INPUT_MINUS_IO1;                    /* Minus PB0 */
  hcomp1.Init.InputPlus       = COMP_INPUT_PLUS_IO1;                     /* Plus None*/
  hcomp1.Init.OutputPol       = COMP_OUTPUTPOL_NONINVERTED;              /* Output None Inverted */
  hcomp1.Init.WindowMode      = COMP_WINDOWMODE_COMP2_INPUT_PLUS_COMMON; /* Window mode COMP2 Plus as Common plus  */
  hcomp1.Init.VrefSrc         = COMP_VREFCMP_SOURCE_VCC;                 /* VrefCmp Select VCC */
  hcomp1.Init.VrefDiv         = COMP_VREFCMP_DIV_8_16VREFCMP;            /* Vrefbuf 8/16  */
  hcomp1.Init.DigitalFilter   = 0x0;                                     /* Filter Disable */
  hcomp1.Init.TriggerMode     = COMP_TRIGGERMODE_NONE;                   /* Trigger None */
  
  /* Initialize COMP */
  if (HAL_COMP_Init(&hcomp1) != HAL_OK)                                 
  {
    APP_ErrorHandler();
  }
  
  hcomp2.Instance = COMP2;                                               /* COMP2 */
  hcomp2.Init.InputMinus      = COMP_INPUT_MINUS_IO2;                    /* Minus PA3 */
  hcomp2.Init.InputPlus       = COMP_INPUT_PLUS_IO2;                     /* Plus VrefBuf */
  hcomp2.Init.OutputPol       = COMP_OUTPUTPOL_NONINVERTED;              /* Output None Inverted */
  hcomp2.Init.WindowMode      = COMP_WINDOWMODE_COMP2_INPUT_PLUS_COMMON; /* Window mode COMP2 Plus as Common plus */
  hcomp2.Init.VrefSrc         = COMP_VREFCMP_SOURCE_VCC;                 /* VrefCmp Select VCC */
  hcomp2.Init.VrefDiv         = COMP_VREFCMP_DIV_8_16VREFCMP;            /* Vrefbuf 8/16  */
  hcomp2.Init.DigitalFilter   = 0x0;                                     /* Filter Disable */
  hcomp2.Init.TriggerMode     = COMP_TRIGGERMODE_NONE;                   /* Trigger None */
  
  /* Initialize COMP */
  if (HAL_COMP_Init(&hcomp2) != HAL_OK)                                 
  {
    APP_ErrorHandler();
  }
  
  /* COMP Start */
  HAL_COMP_Start(&hcomp1); 

  while (1)
  {
    if(HAL_COMP_GetOutputLevel(&hcomp1) == 1)
    {
      BSP_LED_On(LED_GREEN);
    }
    else
    {
      BSP_LED_Off(LED_GREEN);
    }      
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
