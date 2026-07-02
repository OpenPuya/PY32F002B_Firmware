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
#define FLASH_USER_START_ADDR     0x08001000
/* Private variables ---------------------------------------------------------*/
uint32_t DATA[64] = {0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
                     0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
                     0x01010101, 0x23456789, 0x3456789A, 0x456789AB, 0x56789ABC, 0x6789ABCD, 0x789ABCDE, 0x89ABCDEF,
                     0x9ABCDEF0, 0xABCDEF01, 0xBCDEF012, 0xCDEF0123, 0xDEF01234, 0xEF012345, 0xF0123456, 0x01234567,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                     0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa, 0x55555555, 0x23456789, 0xaaaaaaaa,
                    };

/* Private function prototypes -----------------------------------------------*/
/* Private user code ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void APP_FlashErase(void);
static void APP_FlashProgram(void);
static void APP_FlashBlank(void);
static void APP_FlashVerify(void);
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
  while(BSP_PB_GetState(BUTTON_KEY));

  LL_FLASH_Unlock(FLASH);

  LL_FLASH_TIMMING_SEQUENCE_CONFIG_24M();

  /* Erase Flash */
  APP_FlashErase();

  /* Check Flash if blank */
  APP_FlashBlank();

  /* Write user data to Flash */
  APP_FlashProgram();

  /* Lock the Flash to disable the flash control register access */
  LL_FLASH_Lock(FLASH);

  /* Verify that data is written */
  APP_FlashVerify();

  BSP_LED_On(LED3);

  while (1)
  {
  }
}

/**
  * @brief  Erase the user Flash area
  * @param  None
  * @retval None
  */
static void APP_FlashErase(void)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                                /* Start address of user erase page */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(DATA));                  /* End address of user erase page */
  
  while (flash_program_start < flash_program_end)
  {
    /* Wait Busy=0 */
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);

    /* Enable EOP */
    LL_FLASH_EnableIT_EOP(FLASH);

    /* Enable Page Erase */
    LL_FLASH_EnablePageErase(FLASH);

    /* Set Erase Address */
    LL_FLASH_SetEraseAddress(FLASH,flash_program_start);

    /* Wait Busy=0 */
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);

    /* Wait EOP=1 */
    while(LL_FLASH_IsActiveFlag_EOP(FLASH)==0);

    /* Clear EOP */
    LL_FLASH_ClearFlag_EOP(FLASH);

    /* Disable EOP */
    LL_FLASH_DisableIT_EOP(FLASH);

    /* Disable Page Erase */
    LL_FLASH_DisablePageErase(FLASH);
    flash_program_start += FLASH_PAGE_SIZE;                                           /* Point to the start address of the next page to be erase */
  }
}

/**
  * @brief  Write FLASH
  * @param  None
  * @retval None
  */
static void APP_FlashProgram(void)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                                /* Start address of user write flash */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(DATA));                  /* End address of user write flash */
  uint32_t *src = (uint32_t *)DATA;                                                     /* Pointer to array */

  while (flash_program_start < flash_program_end)
  {
    /* Wait Busy=0 */
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);
    
    /* Enable EOP */
    LL_FLASH_EnableIT_EOP(FLASH);

    /* Enable Program */
    LL_FLASH_EnablePageProgram(FLASH);

    /* Page Program */
    LL_FLASH_PageProgram(FLASH,flash_program_start,src);
    
    /* Wait Busy=0 */
    while(LL_FLASH_IsActiveFlag_BUSY(FLASH)==1);
    
    /* Wait EOP=1 */
    while(LL_FLASH_IsActiveFlag_EOP(FLASH)==0);
    
    /* Clear EOP */
    LL_FLASH_ClearFlag_EOP(FLASH);
   
    /* Disable EOP */
    LL_FLASH_DisableIT_EOP(FLASH);

    /* Disable Program */
    LL_FLASH_DisablePageProgram(FLASH);
    flash_program_start += FLASH_PAGE_SIZE;                                           /* Point to the start address of the next page to be written */
    src += FLASH_PAGE_SIZE / 4;                                                       /* Point to the next data to be written */
  }
}

/**
  * @brief  Check Flash if blank
  * @param  None
  * @retval None
  */
static void APP_FlashBlank(void)
{
  uint32_t addr = 0;

  while (addr < sizeof(DATA))
  {
    if (0xFFFFFFFF != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
      APP_ErrorHandler();
    }
    addr += 4;
  }
}
/**
  * @brief  Verify that data is written
  * @param  None
  * @retval None
  */
static void APP_FlashVerify(void)
{
  uint32_t addr = 0;

  while (addr < sizeof(DATA))
  {
    if (DATA[addr / 4] != HW32_REG(FLASH_USER_START_ADDR + addr))
    {
      APP_ErrorHandler();
    }
    addr += 4;
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
