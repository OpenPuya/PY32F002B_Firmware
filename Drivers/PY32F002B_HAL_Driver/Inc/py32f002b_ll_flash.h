/**
  ******************************************************************************
  * @file    py32f002b_ll_flash.h
  * @author  MCU Application Team
  * @brief   Header file of FLASH LL module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PY32F002B_LL_FLASH_H
#define PY32F002B_LL_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "py32f0xx.h"



/** @addtogroup PY32F002B_LL_Driver
  * @{
  */

#if defined (FLASH)

/** @defgroup FLASH_LL FLASH
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup FLASH_LL_Exported_Constants FLASH Exported Constants
  * @{
  */

/** @defgroup FLASH_LL_EC_BOR_ENABLE BOR Enable
  * @{
  */
#define LL_FLASH_BOR_DISABLE   (0x00000000U)                                                        /*!< BOR Reset Disable    */
#define LL_FLASH_BOR_ENABLE    (FLASH_OPTR_BOR_EN)                                                  /*!< BOR Reset Enable     */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_BOR_LEVEL BOR Level
  * @{
  */
#define LL_FLASH_BOR_LEV0      (0x00000000)                                                         /*!< BOR Reset threshold levels for 1.7V - 1.8V VDD power supply    */
#define LL_FLASH_BOR_LEV1      (                                              FLASH_OPTR_BOR_LEV_0) /*!< BOR Reset threshold levels for 1.9V - 2.0V VDD power supply    */
#define LL_FLASH_BOR_LEV2      (                       FLASH_OPTR_BOR_LEV_1                       ) /*!< BOR Reset threshold levels for 2.1V - 2.2V VDD power supply    */
#define LL_FLASH_BOR_LEV3      (                       FLASH_OPTR_BOR_LEV_1 | FLASH_OPTR_BOR_LEV_0) /*!< BOR Reset threshold levels for 2.3V - 2.4V VDD power supply    */
#define LL_FLASH_BOR_LEV4      (FLASH_OPTR_BOR_LEV_2                                              ) /*!< BOR Reset threshold levels for 2.5V - 2.6V VDD power supply    */
#define LL_FLASH_BOR_LEV5      (FLASH_OPTR_BOR_LEV_2                        | FLASH_OPTR_BOR_LEV_0) /*!< BOR Reset threshold levels for 2.7V - 2.8V VDD power supply    */
#define LL_FLASH_BOR_LEV6      (FLASH_OPTR_BOR_LEV_2 | FLASH_OPTR_BOR_LEV_1                       ) /*!< BOR Reset threshold levels for 2.9V - 3.0V VDD power supply    */
#define LL_FLASH_BOR_LEV7      (FLASH_OPTR_BOR_LEV_2 | FLASH_OPTR_BOR_LEV_1 | FLASH_OPTR_BOR_LEV_0) /*!< BOR Reset threshold levels for 3.1V - 3.2V VDD power supply   */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_SWDNRST Swd Nrst Mode
  * @{
  */
#define LL_FLASH_SWD_PB6_NRST_PC0      (0x00000000U)                                         /*!< PB6:SWD,PC0:NRST */
#define LL_FLASH_SWD_PB6_GPIO_PC0      (FLASH_OPTR_NRST_MODE)                                /*!< PB6:SWD,PC0:GPIO */
#define LL_FLASH_SWD_PC0_GPIO_PB6      (FLASH_OPTR_NRST_MODE | FLASH_OPTR_SWD_MODE )         /*!< PC0:SWD,PB6:GPIO */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_IWDGMODE IWDG Mode
  * @{
  */
#define LL_FLASH_IWDG_MODE_HW          (0x00000000U)                                         /*!< Hardware IWDG selected */
#define LL_FLASH_IWDG_MODE_SW          (FLASH_OPTR_IWDG_SW)                                  /*!< Software IWDG selected */

/**
  * @}
  */
#if defined(FLASH_OPTR_IWDG_STOP)
/** @defgroup FLASH_LL_EC_IWDG_INSTOP IWDG In Stop
  * @{
  */
#define LL_FLASH_IWDG_INSTOP_FREEZE    (0x00000000U)                                         /*!< Freeze IWDG counter in STOP mode */  
#define LL_FLASH_IWDG_INSTOP_ACTIVE    (FLASH_OPTR_IWDG_STOP)                                /*!< IWDG counter active in STOP mode */

/**
  * @}
  */
#endif

/** @defgroup FLASH_LL_EC_BOOTMODE Boot Mode
  * @{
  */
#define LL_FLASH_BOOTMODE_MAINFLASH    (0x00000000U)                                         /*!< Main Flash start   */
#define LL_FLASH_BOOTMODE_LOADFLASH    (FLASH_BTCR_NBOOT1 | FLASH_BTCR_BOOT0)                /*!< Load Flash start   */
#define LL_FLASH_BOOTMODE_SRAM         (FLASH_BTCR_BOOT0)                                    /*!< Sram start   */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_LOADFLASH LoadLFlash Size
  * @{
  */
#define LL_FLASH_LOADFLASH_NONE        (0x00000000U)                                     /*!< LoadFlash size None */
#define LL_FLASH_LOADFLASH_1K          (FLASH_BTCR_BOOT_SIZE_0)                          /*!< LoadFlash size 1k   */
#define LL_FLASH_LOADFLASH_2K          (FLASH_BTCR_BOOT_SIZE_1)                          /*!< LoadFlash size 2k   */
#define LL_FLASH_LOADFLASH_3K          (FLASH_BTCR_BOOT_SIZE_1 | FLASH_BTCR_BOOT_SIZE_0) /*!< LoadFlash size 3k   */
#define LL_FLASH_LOADFLASH_4K          (FLASH_BTCR_BOOT_SIZE_2)                          /*!< LoadFlash size 4k   */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_WRP Write Protection
  * @{
  */
#define LL_FLASH_WRP_DISABLE           ((uint32_t)0x00000000)       /* Write protection disable */
#define LL_FLASH_WRP_SECTOR_0          ((uint32_t)FLASH_WRPR_WRP_0) /* Write protection of Sector0 */
#define LL_FLASH_WRP_SECTOR_1          ((uint32_t)FLASH_WRPR_WRP_1) /* Write protection of Sector1 */
#define LL_FLASH_WRP_SECTOR_2          ((uint32_t)FLASH_WRPR_WRP_2) /* Write protection of Sector2 */
#define LL_FLASH_WRP_SECTOR_3          ((uint32_t)FLASH_WRPR_WRP_3) /* Write protection of Sector3 */
#define LL_FLASH_WRP_SECTOR_4          ((uint32_t)FLASH_WRPR_WRP_4) /* Write protection of Sector4 */
#define LL_FLASH_WRP_SECTOR_5          ((uint32_t)FLASH_WRPR_WRP_5) /* Write protection of Sector5 */

#define LL_FLASH_WRP_Pages0to31        ((uint32_t)FLASH_WRPR_WRP_0) /* Write protection from page0   to page31 */
#define LL_FLASH_WRP_Pages32to63       ((uint32_t)FLASH_WRPR_WRP_1) /* Write protection from page32  to page63 */
#define LL_FLASH_WRP_Pages64to95       ((uint32_t)FLASH_WRPR_WRP_2) /* Write protection from page64  to page95 */
#define LL_FLASH_WRP_Pages96to127      ((uint32_t)FLASH_WRPR_WRP_3) /* Write protection from page96  to page127 */
#define LL_FLASH_WRP_Pages128to159     ((uint32_t)FLASH_WRPR_WRP_4) /* Write protection from page128 to page159 */
#define LL_FLASH_WRP_Pages160to191     ((uint32_t)FLASH_WRPR_WRP_5) /* Write protection from page160 to page191 */

#define LL_FLASH_WRP_AllPages          ((uint32_t)0x0000003FU)      /*!< Write protection of all Sectors */
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_SDK SDK Address
  * @{
  */
#define LL_FLASH_SDKSTARTADDRESS_0X08000000    (0x00000000)                                                                                        
#define LL_FLASH_SDKSTARTADDRESS_0X08000800    (                                                                        FLASH_SDKR_SDK_STRT_0)
#define LL_FLASH_SDKSTARTADDRESS_0X08001000    (                                                FLASH_SDKR_SDK_STRT_1                        )    
#define LL_FLASH_SDKSTARTADDRESS_0X08001800    (                                                FLASH_SDKR_SDK_STRT_1 | FLASH_SDKR_SDK_STRT_0)
#define LL_FLASH_SDKSTARTADDRESS_0X08002000    (                        FLASH_SDKR_SDK_STRT_2                                                )
#define LL_FLASH_SDKSTARTADDRESS_0X08002800    (                        FLASH_SDKR_SDK_STRT_2                         | FLASH_SDKR_SDK_STRT_0) 
#define LL_FLASH_SDKSTARTADDRESS_0X08003000    (                        FLASH_SDKR_SDK_STRT_2 | FLASH_SDKR_SDK_STRT_1                        )
#define LL_FLASH_SDKSTARTADDRESS_0X08003800    (                        FLASH_SDKR_SDK_STRT_2 | FLASH_SDKR_SDK_STRT_1 | FLASH_SDKR_SDK_STRT_0)
#define LL_FLASH_SDKSTARTADDRESS_0X08004000    (FLASH_SDKR_SDK_STRT_3                                                                        )
#define LL_FLASH_SDKSTARTADDRESS_0X08004800    (FLASH_SDKR_SDK_STRT_3                                                 | FLASH_SDKR_SDK_STRT_0)
#define LL_FLASH_SDKSTARTADDRESS_0X08005000    (FLASH_SDKR_SDK_STRT_3                         | FLASH_SDKR_SDK_STRT_1                        )
#define LL_FLASH_SDKSTARTADDRESS_0X08005800    (FLASH_SDKR_SDK_STRT_3                         | FLASH_SDKR_SDK_STRT_1 | FLASH_SDKR_SDK_STRT_0)

#define LL_FLASH_SDKENDADDRESS_0X080007FF      (0x00000000)
#define LL_FLASH_SDKENDADDRESS_0X08000FFF      (                                                                      FLASH_SDKR_SDK_END_0)
#define LL_FLASH_SDKENDADDRESS_0X080017FF      (                                               FLASH_SDKR_SDK_END_1                       )    
#define LL_FLASH_SDKENDADDRESS_0X08001FFF      (                                               FLASH_SDKR_SDK_END_1 | FLASH_SDKR_SDK_END_0)
#define LL_FLASH_SDKENDADDRESS_0X080027FF      (                        FLASH_SDKR_SDK_END_2                                              )
#define LL_FLASH_SDKENDADDRESS_0X08002FFF      (                        FLASH_SDKR_SDK_END_2                        | FLASH_SDKR_SDK_END_0) 
#define LL_FLASH_SDKENDADDRESS_0X080037FF      (                        FLASH_SDKR_SDK_END_2 | FLASH_SDKR_SDK_END_1                       )
#define LL_FLASH_SDKENDADDRESS_0X08003FFF      (                        FLASH_SDKR_SDK_END_2 | FLASH_SDKR_SDK_END_1 | FLASH_SDKR_SDK_END_0)
#define LL_FLASH_SDKENDADDRESS_0X080047FF      (FLASH_SDKR_SDK_END_3                                                                      )
#define LL_FLASH_SDKENDADDRESS_0X08004FFF      (FLASH_SDKR_SDK_END_3                                                | FLASH_SDKR_SDK_END_0)
#define LL_FLASH_SDKENDADDRESS_0X080057FF      (FLASH_SDKR_SDK_END_3                         | FLASH_SDKR_SDK_END_1                       )
#define LL_FLASH_SDKENDADDRESS_0X08005FFF      (FLASH_SDKR_SDK_END_3                         | FLASH_SDKR_SDK_END_1 | FLASH_SDKR_SDK_END_0)
/**
  * @}
  */


/** @defgroup FLASH_LL_EC_KEY Key Value
  * @{
  */
#define LL_FLASH_KEY1                  (FLASH_KEY1)
#define LL_FLASH_KEY2                  (FLASH_KEY2)
/**
  * @}
  */

/** @defgroup FLASH_LL_EC_OPTKEY Optkey Value
  * @{
  */
#define LL_FLASH_OPTKEY1               (FLASH_OPTKEY1)
#define LL_FLASH_OPTKEY2               (FLASH_OPTKEY2)
/**
  * @}
  */



/**
  * @}
  */


#define LL_FLASH_TIMMING_SEQUENCE_CONFIG_4M()            \
                                                        do {                                            \
                                                            FLASH->TS0  = (*(uint32_t *)(0x1FFF0158))&0xFF;           \
                                                            FLASH->TS1  = ((*(uint32_t *)(0x1FFF0158))>>16)&0x1FF;    \
                                                            FLASH->TS3  = ((*(uint32_t *)(0x1FFF0158))>>8)&0xFF;      \
                                                            FLASH->TS2P = (*(uint32_t *)(0x1FFF015C))&0xFF;           \
                                                            FLASH->TPS3 = ((*(uint32_t *)(0x1FFF015C))>>16)&0x7FF;    \
                                                            FLASH->PERTPE = (*(uint32_t *)(0x1FFF0160))&0x1FFFF;      \
                                                            FLASH->SMERTPE = (*(uint32_t *)(0x1FFF0164))&0x1FFFF;     \
                                                            FLASH->PRGTPE = (*(uint32_t *)(0x1FFF0168))&0xFFFF;       \
                                                            FLASH->PRETPE = ((*(uint32_t *)(0x1FFF0168))>>16)&0xFFF; \
                                                         } while(0U)

#define LL_FLASH_TIMMING_SEQUENCE_CONFIG_8M()            \
                                                        do {                                            \
                                                            FLASH->TS0  = (*(uint32_t *)(0x1FFF016C))&0xFF;           \
                                                            FLASH->TS1  = ((*(uint32_t *)(0x1FFF016C))>>16)&0x1FF;    \
                                                            FLASH->TS3  = ((*(uint32_t *)(0x1FFF016C))>>8)&0xFF;      \
                                                            FLASH->TS2P = (*(uint32_t *)(0x1FFF0170))&0xFF;           \
                                                            FLASH->TPS3 = ((*(uint32_t *)(0x1FFF0170))>>16)&0x7FF;    \
                                                            FLASH->PERTPE = (*(uint32_t *)(0x1FFF0174))&0x1FFFF;      \
                                                            FLASH->SMERTPE = (*(uint32_t *)(0x1FFF0178))&0x1FFFF;     \
                                                            FLASH->PRGTPE = (*(uint32_t *)(0x1FFF017C))&0xFFFF;       \
                                                            FLASH->PRETPE = ((*(uint32_t *)(0x1FFF017C))>>16)&0xFFF; \
                                                         } while(0U)

#define LL_FLASH_TIMMING_SEQUENCE_CONFIG_24M()           \
                                                        do {                                            \
                                                            FLASH->TS0  = (*(uint32_t *)(0x1FFF011C))&0x1FF;           \
                                                            FLASH->TS1  = ((*(uint32_t *)(0x1FFF011C))>>18)&0x3FF;    \
                                                            FLASH->TS3  = ((*(uint32_t *)(0x1FFF011C))>>9)&0x1FF;      \
                                                            FLASH->TS2P = (*(uint32_t *)(0x1FFF0120))&0x1FF;           \
                                                            FLASH->TPS3 = ((*(uint32_t *)(0x1FFF0120))>>16)&0xFFF;    \
                                                            FLASH->PERTPE = (*(uint32_t *)(0x1FFF0124))&0x3FFFF;      \
                                                            FLASH->SMERTPE = (*(uint32_t *)(0x1FFF0128))&0x3FFFF;     \
                                                            FLASH->PRGTPE = (*(uint32_t *)(0x1FFF012C))&0xFFFF;       \
                                                            FLASH->PRETPE = ((*(uint32_t *)(0x1FFF012C))>>16)&0x3FFF; \
                                                         } while(0U)

#if defined(RCC_HSI48M_SUPPORT)
#define LL_FLASH_TIMMING_SEQUENCE_CONFIG_48M()           \
                                                        do {                                            \
                                                            FLASH->TS0  = (*(uint32_t *)(0x1FFF0130))&0x1FF;           \
                                                            FLASH->TS1  = ((*(uint32_t *)(0x1FFF0130))>>18)&0x3FF;    \
                                                            FLASH->TS3  = ((*(uint32_t *)(0x1FFF0130))>>9)&0x1FF;      \
                                                            FLASH->TS2P = (*(uint32_t *)(0x1FFF0134))&0x1FF;           \
                                                            FLASH->TPS3 = ((*(uint32_t *)(0x1FFF0134))>>16)&0xFFF;    \
                                                            FLASH->PERTPE = (*(uint32_t *)(0x1FFF0138))&0x3FFFF;      \
                                                            FLASH->SMERTPE = (*(uint32_t *)(0x1FFF013C))&0x3FFFF;     \
                                                            FLASH->PRGTPE = (*(uint32_t *)(0x1FFF0140))&0xFFFF;       \
                                                            FLASH->PRETPE = ((*(uint32_t *)(0x1FFF0140))>>16)&0x3FFF; \
                                                         } while(0U)
#endif


/* Exported macro ------------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Macros FLASH Exported Macros
  * @{
  */

/** @defgroup FLASH_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in FLASH register
  * @param  __INSTANCE__ FLASH Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_FLASH_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in FLASH register
  * @param  __INSTANCE__ FLASH Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_FLASH_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup FLASH_LL_Exported_Functions FLASH Exported Functions
  * @{
  */

/** @defgroup FLASH_LL_EF_FLAG_Management Flag Management
  * @{
  */

/**
  * @brief  Indicate the status of End of operation flag.
  * @rmtoll SR          EOP              LL_FLASH_IsActiveFlag_EOP
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_EOP(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_EOP) == (FLASH_SR_EOP));
}

/**
  * @brief  Indicate the status of WRPERR flag.
  * @rmtoll SR          WPRERR           LL_FLASH_IsActiveFlag_WRPERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_WRPERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_WRPERR) == (FLASH_SR_WRPERR));
}

/**
  * @brief  Indicate the status of OPTVERR flag.
  * @rmtoll SR          OPTVERR          LL_FLASH_IsActiveFlag_OPTVERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OPTVERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_OPTVERR) == (FLASH_SR_OPTVERR));
}

/**
  * @brief  Indicate the status of BUSY flag.
  * @rmtoll SR          BSY              LL_FLASH_IsActiveFlag_BUSY
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_BUSY(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SR, FLASH_SR_BSY) == (FLASH_SR_BSY));
}

/**
  * @brief  Clear End of operation flag.
  * @rmtoll SR          EOP              LL_FLASH_ClearFlag_EOP
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_EOP(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_EOP);
}

/**
  * @brief  Clear WRPERR flag.
  * @rmtoll SR          WRPERR           LL_FLASH_ClearFlag_WRPERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_WRPERR(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_WRPERR);
}

/**
  * @brief  Clear OPTVERR flag.
  * @rmtoll SR          OPTVERR          LL_FLASH_ClearFlag_OPTVERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearFlag_OPTVERR(FLASH_TypeDef *FLASHx)
{
  WRITE_REG(FLASHx->SR, FLASH_SR_OPTVERR);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_ERASE_Management Erase Management
  * @{
  */

/**
  * @brief  Enable Page Program
  * @rmtoll CR          PG               LL_FLASH_EnablePageProgram
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnablePageProgram(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_PG);
}

/**
  * @brief  Enable Mass Erase
  * @rmtoll CR          MER              LL_FLASH_EnableMassErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableMassErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_MER);
}

/**
  * @brief  Enable Page Erase
  * @rmtoll CR          PER              LL_FLASH_EnablePageErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnablePageErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_PER);
}

/**
  * @brief  Enable Sector Erase
  * @rmtoll CR          SER              LL_FLASH_EnableSectorErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableSectorErase(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_SER);
}

/**
  * @brief  Disable Page Program
  * @rmtoll CR          PG               LL_FLASH_DisablePageProgram
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisablePageProgram(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_PG);
}

/**
  * @brief  Disable Mass Erase
  * @rmtoll CR          MER              LL_FLASH_DisableMassErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableMassErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_MER);
}

/**
  * @brief  Disable Page Erase
  * @rmtoll CR          PER              LL_FLASH_DisablePageErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisablePageErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_PER);
}

/**
  * @brief  Disable Sector Erase
  * @rmtoll CR          SER              LL_FLASH_DisableSectorErase
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableSectorErase(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_SER);
}

/**
  * @brief  Check if Page Program is enabled
  * @rmtoll CR          PG               LL_FLASH_IsEnabledPageProgram
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageProgram(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_PG) == (FLASH_CR_PG)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Mass erase is enabled
  * @rmtoll CR          MER              LL_FLASH_IsEnabledMassErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledMassErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_MER) == (FLASH_CR_MER)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Page erase is enabled
  * @rmtoll CR          PER              LL_FLASH_IsEnabledPageErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_PER) == (FLASH_CR_PER)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Sector Erase is enabled
  * @rmtoll CR          SER              LL_FLASH_IsEnabledSectorErase
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledSectorErase(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_SER) == (FLASH_CR_SER)) ? 1UL : 0UL);
}

/**
  * @brief  Set the Erase Address
  * @rmtoll LL_FLASH_SetEraseAddress
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetEraseAddress(FLASH_TypeDef *FLASHx,uint32_t address)
{
  *(__IO uint32_t *)(address) = 0xFFFFFFFF;
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_Lock_Management Lock Management
  * @{
  */

/**
  * @brief Unlock the Flash
  * @rmtoll KEYR        KEYR             LL_FLASH_Unlock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Unlock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->KEYR, LL_FLASH_KEY1);
  SET_BIT(FLASHx->KEYR, LL_FLASH_KEY2);
}

/**
  * @brief  Unlock the Option
  * @rmtoll OPTKEYR     OPTKEYR          LL_FLASH_OBUnlock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OBUnlock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->OPTKEYR, LL_FLASH_OPTKEY1);
  SET_BIT(FLASHx->OPTKEYR, LL_FLASH_OPTKEY2);
}



/**
  * @brief  Lock the Flash
  * @rmtoll CR          LOCK             LL_FLASH_Lock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Lock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_LOCK);
}

/**
  * @brief  Lock the Option
  * @rmtoll CR          OPTLOCK          LL_FLASH_OBLock
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_OBLock(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_OPTLOCK);
}

/**
  * @brief  Check if Flash is locked
  * @rmtoll CR          LOCK             LL_FLASH_IsLocked
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsLocked(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_LOCK) == (FLASH_CR_LOCK)) ? 1UL : 0UL);
}

/**
  * @brief  Check if Option is locked
  * @rmtoll CR          OPTLOCK          LL_FLASH_IsOBLocked
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsOBLocked(FLASH_TypeDef *FLASHx)
{
  return ((READ_BIT(FLASHx->CR, FLASH_CR_OPTLOCK) == (FLASH_CR_OPTLOCK)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_LAUNCH_Management Launch Management
  * @{
  */

/**
  * @brief  Force the Option byte loading
  * @rmtoll CR          OBL_LAUNCH       LL_FLASH_Launch
  * @param  FLASHx FLASH Instance
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_Launch(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_OBL_LAUNCH);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_IT_Management Interrupt Management
  * @{
  */

/**
  * @brief  Enable Error interrupts.
  * @rmtoll CR          ERRIR            LL_FLASH_EnableIT_ERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableIT_ERR(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_ERRIE);
}

/**
  * @brief  Enable End of operation interrupts.
  * @rmtoll CR          EOPIE            LL_FLASH_EnableIT_EOP
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableIT_EOP(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_EOPIE);
}

/**
  * @brief  Disable Error interrupts.
  * @rmtoll CR          ERRIE            LL_FLASH_DisableIT_ERR
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableIT_ERR(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_ERRIE);
}

/**
  * @brief  Disable End of operation interrupts.
  * @rmtoll CR          EOPIE            LL_FLASH_DisableIT_EOP
  * @param  FLASHx FLASH Instance.
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableIT_EOP(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_EOPIE);
}

/**
  * @brief  Check if Error interrupts are enabled or disabled.
  * @rmtoll CR          ERRIE            LL_FLASH_IsEnabledIT_ERR
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_ERR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASH->CR, FLASH_CR_ERRIE) == (FLASH_CR_ERRIE));
}

/**
  * @brief  Check if End of operation interrupts are enabled or disabled.
  * @rmtoll CR          EOPIE            LL_FLASH_IsEnabledIT_EOP
  * @param  FLASHx FLASH Instance.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledIT_EOP(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASH->CR, FLASH_CR_EOPIE) == (FLASH_CR_EOPIE));
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_PROGRAM_Management Program Management
  * @{
  */

/**
  * @brief  Enable Page Program Start
  * @rmtoll CR          PGSTRT           LL_FLASH_EnablePageProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_EnablePageProgramStart(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_PGSTRT);
}

/**
  * @brief  Enable Option Program Start
  * @rmtoll CR          OPTSTRT          LL_FLASH_EnableOptionProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_EnableOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  SET_BIT(FLASHx->CR, FLASH_CR_OPTSTRT);
}

/**
  * @brief  Disable Page Program start
  * @rmtoll CR          PGSTRT           LL_FLASH_DisablePageProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_DisablePageProgramStart(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_PGSTRT);
}

/**
  * @brief  Disable Option Program start
  * @rmtoll CR          OPTSTRT          LL_FLASH_DisableOptionProgramStart
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_DisableOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  CLEAR_BIT(FLASHx->CR, FLASH_CR_OPTSTRT);
}

/**
  * @brief  Check if Page Program Start is enabled
  * @rmtoll CR          PGSTRT           LL_FLASH_IsEnabledPageProgramStart
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledPageProgramStart(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->CR, FLASH_CR_PGSTRT) == (FLASH_CR_PGSTRT));
}

/**
  * @brief  Check if Option program is enabled
  * @rmtoll CR          OPTSTRT         LL_FLASH_IsEnabledOptionProgramStart
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->CR, FLASH_CR_OPTSTRT) == (FLASH_CR_OPTSTRT));
}

/**
  * @brief  Trigger the Option Program
  * @param  FLASHx FLASH Instance
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_TriggerOptionProgramStart(FLASH_TypeDef *FLASHx)
{
  *((__IO uint32_t *)(0x40022080))=0xff;
}

/**
  * @brief  Program the page
  * @rmtoll CR          PGSTRT          LL_FLASH_PageProgram
  * @param  FLASHx FLASH Instance
  * @param  Address   Program Address
  * @param  DataAddress Data Address
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_PageProgram(FLASH_TypeDef *FLASHx,uint32_t Address, uint32_t * DataAddress)
{
  uint8_t index=0;
  uint32_t dest = Address;
  uint32_t * src = DataAddress;
  uint32_t primask_bit;
  /* Enter critical section */
  primask_bit = __get_PRIMASK();
  __disable_irq();
  /* 32 words*/
  while(index<32U)
  {
    *(uint32_t *)dest = *src;
    src += 1U;
    dest += 4U;
    index++;
    if(index==31)
    {
      LL_FLASH_EnablePageProgramStart(FLASHx);
    }
  }

  /* Exit critical section: restore previous priority mask */
  __set_PRIMASK(primask_bit);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_BOR_Management Bor Management
  * @{
  */


/**
  * @brief  Check if BOR is enabled
  * @rmtoll OPTR        BOR_EN          LL_FLASH_IsEnabledBOR
  * @param  FLASHx FLASH Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEnabledBOR(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->OPTR, FLASH_OPTR_BOR_EN) == (FLASH_OPTR_BOR_EN));
}


/**
  * @brief  Get the BOR Level
  * @rmtoll OPTR        BOR_LEV         LL_FLASH_GetBORLevel
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_BOR_LEV0
  *         @arg @ref LL_FLASH_BOR_LEV1
  *         @arg @ref LL_FLASH_BOR_LEV2
  *         @arg @ref LL_FLASH_BOR_LEV3
  *         @arg @ref LL_FLASH_BOR_LEV4
  *         @arg @ref LL_FLASH_BOR_LEV5
  *         @arg @ref LL_FLASH_BOR_LEV6
  *         @arg @ref LL_FLASH_BOR_LEV7
  */
__STATIC_INLINE uint32_t LL_FLASH_GetBORLevel(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_BOR_LEV);
}

/**
  * @brief  Get SWD NRST Mode
  * @rmtoll OPTR        NRST_MODE       LL_FLASH_GetSwdNrstMode
  * @rmtoll OPTR        SWD_MODE        LL_FLASH_GetSwdNrstMode
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_SWD_PB6_NRST_PC0
  *         @arg @ref LL_FLASH_SWD_PB6_GPIO_PC0
  *         @arg @ref LL_FLASH_SWD_PC0_GPIO_PB6
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSwdNrstMode(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_NRST_MODE | FLASH_OPTR_SWD_MODE);
}

/**
  * @brief Get IWDG Mode
  * @rmtoll OPTR        IWDG_SW          LL_FLASH_GetIWDGMode
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_IWDG_MODE_HW
  *         @arg @ref LL_FLASH_IWDG_MODE_SW
  */
__STATIC_INLINE uint32_t LL_FLASH_GetIWDGMode(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_IWDG_SW);
}

#if defined(FLASH_OPTR_IWDG_STOP)
/**
  * @}
  */

/** @defgroup FLASH_LL_EF_IWDGINSTOP_Management Iwdg in Stop Management
  * @{
  */

/**
  * @brief  Get IWDG In Stop Mode
  * @rmtoll OPTR        IWDG_STOP       LL_FLASH_GetIWDGInStop
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_IWDG_INSTOP_FREEZE
  *         @arg @ref LL_FLASH_IWDG_INSTOP_ACTIVE
  */
__STATIC_INLINE uint32_t LL_FLASH_GetIWDGInStop(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->OPTR, FLASH_OPTR_IWDG_STOP);
}
#endif

/**
  * @brief  Get Boot Mode
  * @rmtoll BTCR        nBOOT1          LL_FLASH_GetBootMode
  * @rmtoll BTCR        BOOT0           LL_FLASH_GetBootMode
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_BOOTMODE_MAINFLASH
  *         @arg @ref LL_FLASH_BOOTMODE_LOADFLASH
  *         @arg @ref LL_FLASH_BOOTMODE_SRAM
  */
__STATIC_INLINE uint32_t LL_FLASH_GetBootMode(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->BTCR, FLASH_BTCR_NBOOT1 | FLASH_BTCR_BOOT0);
}

/**
  * @brief  Get LoadFlash size
  * @rmtoll BTCR        BOOT_SIZE       LL_FLASH_GetLoadFlashSize
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LOADFLASH_NONE
  *         @arg @ref LL_FLASH_LOADFLASH_1K
  *         @arg @ref LL_FLASH_LOADFLASH_2K
  *         @arg @ref LL_FLASH_LOADFLASH_3K
  *         @arg @ref LL_FLASH_LOADFLASH_4K
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLoadFlashSize(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->BTCR, FLASH_BTCR_BOOT_SIZE);
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_SDK_Management SDK Management
  * @{
  */
/**
  * @brief  Set SDK Address
  * @rmtoll SDKR        SDK_STRT        LL_FLASH_SetSDKAddress
  * @rmtoll SDKR        SDK_END         LL_FLASH_SetSDKAddress
  * @param  FLASHx FLASH Instance
  * @param  SDKStartAddress This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08000000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08000800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08001000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08001800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08002000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08002800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08003000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08003800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08004000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08004800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08005000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08005800
  * @param  SDKEndAddress This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080007FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08000FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080017FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08001FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080027FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08002FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080037FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08003FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080047FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08004FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080057FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08005FFF
  * @retval None.
  */
__STATIC_INLINE void LL_FLASH_SetSDKAddress(FLASH_TypeDef *FLASHx,uint32_t SDKStartAddress,uint32_t SDKEndAddress)
{
  MODIFY_REG(FLASHx->SDKR, FLASH_SDKR_SDK_STRT | FLASH_SDKR_SDK_END , SDKStartAddress | SDKEndAddress);
}

/**
  * @brief  Get SDK Start Address
  * @rmtoll SDKR        SDK_STRT        LL_FLASH_GetSDKStartAddress
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08000000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08000800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08001000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08001800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08002000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08002800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08003000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08003800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08004000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08004800
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08005000
  *         @arg @ref LL_FLASH_SDKSTARTADDRESS_0X08005800
  * @retval None
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSDKStartAddress(FLASH_TypeDef *FLASHx)
{
  return READ_BIT(FLASHx->SDKR, FLASH_SDKR_SDK_STRT);
}

/**
  * @brief  Get SDK End Address
  * @rmtoll SDKR        SDK_END         LL_FLASH_GetSDKEndAddress
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080007FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08000FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080017FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08001FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080027FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08002FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080037FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08003FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080047FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08004FFF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X080057FF
  *         @arg @ref LL_FLASH_SDKENDADDRESS_0X08005FFF
  * @retval None
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSDKEndAddress(FLASH_TypeDef *FLASHx)
{
  return (READ_BIT(FLASHx->SDKR, FLASH_SDKR_SDK_END));
}

/**
  * @}
  */

/** @defgroup FLASH_LL_EF_WRP_Management WRP Management
  * @{
  */
/**
  * @brief  Set WRP Address
  * @rmtoll WRPR        WRP             LL_FLASH_SetWRPRAddress
  * @param  FLASHx FLASH Instance
  * @param  Address This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_WRP_DISABLE
  *         @arg @ref LL_FLASH_WRP_SECTOR_0
  *         @arg @ref LL_FLASH_WRP_SECTOR_1
  *         @arg @ref LL_FLASH_WRP_SECTOR_2
  *         @arg @ref LL_FLASH_WRP_SECTOR_3
  *         @arg @ref LL_FLASH_WRP_SECTOR_4
  *         @arg @ref LL_FLASH_WRP_SECTOR_5
  *         @arg @ref LL_FLASH_WRP_Pages0to31
  *         @arg @ref LL_FLASH_WRP_Pages32to63
  *         @arg @ref LL_FLASH_WRP_Pages64to95
  *         @arg @ref LL_FLASH_WRP_Pages96to127
  *         @arg @ref LL_FLASH_WRP_Pages128to159
  *         @arg @ref LL_FLASH_WRP_Pages160to191
  *         @arg @ref LL_FLASH_WRP_AllPages
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetWRPAddress(FLASH_TypeDef *FLASHx,uint32_t Address)
{
  MODIFY_REG(FLASHx->WRPR, FLASH_WRPR_WRP , ((~(Address)) & FLASH_WRPR_WRP));
}

/**
  * @brief  Get WRP Address
  * @rmtoll WRPR        WRP             LL_FLASH_GetWRPAddress
  * @param  FLASHx FLASH Instance
  * @retval Returned value can be a combination of the following values:
  *         @arg @ref LL_FLASH_WRP_DISABLE
  *         @arg @ref LL_FLASH_WRP_SECTOR_0
  *         @arg @ref LL_FLASH_WRP_SECTOR_1
  *         @arg @ref LL_FLASH_WRP_SECTOR_2
  *         @arg @ref LL_FLASH_WRP_SECTOR_3
  *         @arg @ref LL_FLASH_WRP_SECTOR_4
  *         @arg @ref LL_FLASH_WRP_SECTOR_5
  *         @arg @ref LL_FLASH_WRP_Pages0to31
  *         @arg @ref LL_FLASH_WRP_Pages32to63
  *         @arg @ref LL_FLASH_WRP_Pages64to95
  *         @arg @ref LL_FLASH_WRP_Pages96to127
  *         @arg @ref LL_FLASH_WRP_Pages128to159
  *         @arg @ref LL_FLASH_WRP_Pages160to191
  *         @arg @ref LL_FLASH_WRP_AllPages
  */
__STATIC_INLINE uint32_t LL_FLASH_GetWRPAddress(FLASH_TypeDef *FLASHx)
{
  return ((~(READ_BIT(FLASHx->WRPR, FLASH_WRPR_WRP))) & FLASH_WRPR_WRP);
}
/**
  * @}
  */


/** @defgroup FLASH_LL_EF_BTCR_Management BTCR Management
  * @{
  */
/**
  * @brief  Set BTCR
  * @rmtoll BTCR        NBOOT1             LL_FLASH_SetBTCR
  * @rmtoll BTCR        BOOT0              LL_FLASH_SetBTCR
  * @rmtoll BTCR        BOOT_SIZE          LL_FLASH_SetBTCR
  * @param  FLASHx FLASH Instance
  * @param  BootMode This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_BOOTMODE_MAINFLASH
  *         @arg @ref LL_FLASH_BOOTMODE_LOADFLASH
  *         @arg @ref LL_FLASH_BOOTMODE_SRAM
  * @param  LoadFlashSize This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_LOADFLASH_NONE
  *         @arg @ref LL_FLASH_LOADFLASH_1K
  *         @arg @ref LL_FLASH_LOADFLASH_2K
  *         @arg @ref LL_FLASH_LOADFLASH_3K
  *         @arg @ref LL_FLASH_LOADFLASH_4K
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetBTCR(FLASH_TypeDef *FLASHx,uint32_t BootMode,uint32_t LoadFlashSize)
{
  MODIFY_REG(FLASHx->BTCR, (FLASH_BTCR_NBOOT1 | FLASH_BTCR_BOOT0 | FLASH_BTCR_BOOT_SIZE), (BootMode | LoadFlashSize));
}
/**
  * @}
  */

/** @defgroup FLASH_LL_EF_OPTR_Management OPTR Management
  * @{
  */

#if defined(FLASH_OPTR_IWDG_STOP)
/**
  * @brief  Set Optr
  * @rmtoll OPTR            BOR_EN           LL_FLASH_SetOPTR
  * @rmtoll OPTR            BOR_LEV          LL_FLASH_SetOPTR
  * @rmtoll OPTR            IWDG_SW          LL_FLASH_SetOPTR
  * @rmtoll OPTR            SWD_MODE         LL_FLASH_SetOPTR
  * @rmtoll OPTR            NRST_MODE        LL_FLASH_SetOPTR
  * @rmtoll OPTR            IWDG_STOP        LL_FLASH_SetOPTR
  * @param  FLASHx FLASH Instance
  * @param  BOREnable This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BOR_ENABLE
  *         @arg @ref LL_FLASH_BOR_DISABLE
  * @param  BORLevel This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_BOR_LEV0
  *         @arg @ref LL_FLASH_BOR_LEV1
  *         @arg @ref LL_FLASH_BOR_LEV2
  *         @arg @ref LL_FLASH_BOR_LEV3
  *         @arg @ref LL_FLASH_BOR_LEV4
  *         @arg @ref LL_FLASH_BOR_LEV5
  *         @arg @ref LL_FLASH_BOR_LEV6
  *         @arg @ref LL_FLASH_BOR_LEV7
  * @param  IWDGMode This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_IWDG_MODE_HW
  *         @arg @ref LL_FLASH_IWDG_MODE_SW
  * @param  SwdNrstMode This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_SWD_PB6_NRST_PC0
  *         @arg @ref LL_FLASH_SWD_PB6_GPIO_PC0
  *         @arg @ref LL_FLASH_SWD_PC0_GPIO_PB6
  * @param  IWDGInStop This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_IWDG_INSTOP_FREEZE
  *         @arg @ref LL_FLASH_IWDG_INSTOP_ACTIVE
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetOPTR(FLASH_TypeDef *FLASHx,uint32_t BOREnable,uint32_t BORLevel,uint32_t IWDGMode,uint32_t SwdNrstMode, uint32_t IWDGInStop)
{
  MODIFY_REG(FLASHx->OPTR, (FLASH_OPTR_BOR_EN | FLASH_OPTR_BOR_LEV | FLASH_OPTR_IWDG_SW | FLASH_OPTR_SWD_MODE | FLASH_OPTR_NRST_MODE | FLASH_OPTR_IWDG_STOP), (BOREnable | BORLevel | IWDGMode | SwdNrstMode | IWDGInStop));
}
#else
/**
  * @brief  Set Optr
  * @rmtoll OPTR            BOR_EN           LL_FLASH_SetOPTR
  * @rmtoll OPTR            BOR_LEV          LL_FLASH_SetOPTR
  * @rmtoll OPTR            IWDG_SW          LL_FLASH_SetOPTR
  * @rmtoll OPTR            SWD_MODE         LL_FLASH_SetOPTR
  * @rmtoll OPTR            NRST_MODE        LL_FLASH_SetOPTR
  * @param  FLASHx FLASH Instance
  * @param  BOREnable This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_BOR_ENABLE
  *         @arg @ref LL_FLASH_BOR_DISABLE
  * @param  BORLevel This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_BOR_LEV0
  *         @arg @ref LL_FLASH_BOR_LEV1
  *         @arg @ref LL_FLASH_BOR_LEV2
  *         @arg @ref LL_FLASH_BOR_LEV3
  *         @arg @ref LL_FLASH_BOR_LEV4
  *         @arg @ref LL_FLASH_BOR_LEV5
  *         @arg @ref LL_FLASH_BOR_LEV6
  *         @arg @ref LL_FLASH_BOR_LEV7
  * @param  IWDGMode This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_IWDG_MODE_HW
  *         @arg @ref LL_FLASH_IWDG_MODE_SW
  * @param  SwdNrstMode This parameter can be a combination of the following values:
  *         @arg @ref LL_FLASH_SWD_PB6_NRST_PC0
  *         @arg @ref LL_FLASH_SWD_PB6_GPIO_PC0
  *         @arg @ref LL_FLASH_SWD_PC0_GPIO_PB6
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetOPTR(FLASH_TypeDef *FLASHx,uint32_t BOREnable,uint32_t BORLevel,uint32_t IWDGMode,uint32_t SwdNrstMode)
{
  MODIFY_REG(FLASHx->OPTR, (FLASH_OPTR_BOR_EN | FLASH_OPTR_BOR_LEV | FLASH_OPTR_IWDG_SW | FLASH_OPTR_SWD_MODE | FLASH_OPTR_NRST_MODE), (BOREnable | BORLevel | IWDGMode | SwdNrstMode));
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
#endif /* defined (FLASH) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* PY32F002B_LL_FLASH_H */

/************************ (C) COPYRIGHT Puya *****END OF FILE******************/
