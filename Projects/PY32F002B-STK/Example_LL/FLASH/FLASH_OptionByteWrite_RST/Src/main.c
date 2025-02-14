/**
  ******************************************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @brief   Main program body
  * @date
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
#define OB_GPIO_PIN_MODE LL_FLASH_SWD_PB6_GPIO_PC0
/* #define OB_GPIO_PIN_MODE LL_FLASH_SWD_PB6_NRST_PC0 */
 
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void APP_SystemClockConfig(void);

/**
  * @brief  Main program.
  * @retval int
  */
int main(void)
{
  /* Configure Systemclock */
  APP_SystemClockConfig();

  /* Enable SYSCFG and PWR clocks */
  LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* Initialize LED */
  BSP_LED_Init(LED_GREEN);

  /* Initialize BUTTON */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* Wait for the BUTTON to be pressed */
  while(BSP_PB_GetState(BUTTON_KEY) == 1);

  if(LL_FLASH_GetSwdNrstMode(FLASH) != OB_GPIO_PIN_MODE)
  {
    /* Unlock Flash */
    LL_FLASH_Unlock(FLASH);
  
    /* Unlock Option */
    LL_FLASH_OBUnlock(FLASH);

    LL_FLASH_TIMMING_SEQUENCE_CONFIG_24M();

    /* Wait Busy=0 */
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);
    
    /* Enable EOP */
    LL_FLASH_EnableIT_EOP(FLASH);

    /* Set PC0 GPIO Mode */
    LL_FLASH_SetOPTR(FLASH,LL_FLASH_BOR_DISABLE,LL_FLASH_BOR_LEV0,LL_FLASH_IWDG_MODE_SW,OB_GPIO_PIN_MODE);
    
    LL_FLASH_EnableOptionProgramStart(FLASH);
    LL_FLASH_TriggerOptionProgramStart(FLASH);

    /* Wait Busy=0 */
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);

    /* Wait EOP=1 */
    while(LL_FLASH_IsActiveFlag_EOP(FLASH)==0);

    /* Clear EOP Flag */
    LL_FLASH_ClearFlag_EOP(FLASH);

    /* Disable EOP */
    LL_FLASH_DisableIT_EOP(FLASH);
    
    /* Lock Option */
    LL_FLASH_OBLock(FLASH);
    
    /* Lock Flash */
    LL_FLASH_Lock(FLASH);

    /* Launch */
    LL_FLASH_Launch(FLASH);
  }
  else
  {
    BSP_LED_On(LED_GREEN);
  }

  while (1)
  {
  }
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

/**
  * @brief  Configure Systemclock
  * @param  None
  * @retval None
  */
void APP_SystemClockConfig(void)
{
  /*  Set FLASH Latency Before modifying the HSI */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);

  /* Enable HSI */
  LL_RCC_HSI_Enable();
  while(LL_RCC_HSI_IsReady() != 1)
  {
  }

  /* Set AHB divider:HCLK = SYSCLK */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

  /* HSISYS used as SYSCLK clock source */
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
