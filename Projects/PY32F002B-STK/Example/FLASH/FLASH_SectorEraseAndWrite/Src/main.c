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

/* Private define ------------------------------------------------------------*/
#define FLASH_USER_START_ADDR     0x08002000
/* Private variables ---------------------------------------------------------*/
typedef struct
{
  uint32_t arrA[64];
} NewDataType;                                                      /* Struct define */
#define VarA (*(volatile NewDataType *)FLASH_USER_START_ADDR)       
uint32_t dat2[10];

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

  /* Initialize Button */
  BSP_PB_Init(BUTTON_KEY,BUTTON_MODE_GPIO);

  /* Initialize Usart */
  BSP_USART_Config();

  /* Wait For Button */
  while(BSP_PB_GetState(BUTTON_KEY) == 1);

  /* Unlock Flash */
  HAL_FLASH_Unlock();

  /* Erase Flash */
  APP_FlashErase();

  /* Check Flash */
  APP_FlashBlank();

  /* Program Flash */
  APP_FlashProgram();

  /* Lock Flash */
  HAL_FLASH_Lock();

  /* Verify Flash */
  APP_FlashVerify();

  BSP_LED_On(LED3);
  while (1)
  {
  }
}

/**
  * @brief  Flash Erase
  * @param  None
  * @retval None
  */
static void APP_FlashErase(void)
{
  uint32_t SECTORError = 0;
  FLASH_EraseInitTypeDef EraseInitStruct = {0};

  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_SECTORERASE;      /* Sector Erase */
  EraseInitStruct.SectorAddress = FLASH_USER_START_ADDR;          /* Erase Start Address */
  EraseInitStruct.NbSectors  = 1;                                 /* Erase Sector Number */
  if (HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError) != HAL_OK)/* Sector Erase */
  {
    APP_ErrorHandler();
  }
}

/**
  * @brief  Flash Program
  * @param  None
  * @retval None
  */
static void APP_FlashProgram(void)
{
  uint32_t flash_program_start = FLASH_USER_START_ADDR ;                                /* flash program start address */
  uint32_t flash_program_end = (FLASH_USER_START_ADDR + sizeof(DATA));                  /* flash program end address */
  uint32_t *src = (uint32_t *)DATA;                                                     /* Program data */

  while (flash_program_start < flash_program_end)
  {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_PAGE, flash_program_start, src) == HAL_OK)  /* Program */
    {
      flash_program_start += FLASH_PAGE_SIZE;                                           /* flash Start point first page */
      src += FLASH_PAGE_SIZE / 4;                                                       /* Update data point */
    }
  }
}

/**
  * @brief  Flash Check
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
  * @brief  Flash Verify
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

/************************ (C) COPYRIGHT Puya *****END OF FILE****/
