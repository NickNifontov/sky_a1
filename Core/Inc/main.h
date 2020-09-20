/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_ll_adc.h"
#include "stm32f3xx_ll_comp.h"
#include "stm32f3xx_ll_dac.h"
#include "stm32f3xx_ll_hrtim.h"
#include "stm32f3xx_ll_iwdg.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_pwr.h"
#include "stm32f3xx_ll_dma.h"
#include "stm32f3xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SkyConv.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define rccPF0_Pin LL_GPIO_PIN_0
#define rccPF0_GPIO_Port GPIOF
#define rccPF1_Pin LL_GPIO_PIN_1
#define rccPF1_GPIO_Port GPIOF
#define adc1_V_Pin LL_GPIO_PIN_0
#define adc1_V_GPIO_Port GPIOA
#define adc1_AB_Pin LL_GPIO_PIN_1
#define adc1_AB_GPIO_Port GPIOA
#define adc2_I_Pin LL_GPIO_PIN_4
#define adc2_I_GPIO_Port GPIOA
#define adc2_TEMP_Pin LL_GPIO_PIN_5
#define adc2_TEMP_GPIO_Port GPIOA
#define adc2_16V_Pin LL_GPIO_PIN_6
#define adc2_16V_GPIO_Port GPIOA
#define compV_Pin LL_GPIO_PIN_7
#define compV_GPIO_Port GPIOA
#define compI_Pin LL_GPIO_PIN_0
#define compI_GPIO_Port GPIOB
#define drvONOFF_Pin LL_GPIO_PIN_1
#define drvONOFF_GPIO_Port GPIOB
#define pwmA1_Pin LL_GPIO_PIN_8
#define pwmA1_GPIO_Port GPIOA
#define pwmA2_Pin LL_GPIO_PIN_9
#define pwmA2_GPIO_Port GPIOA
#define pwmB1_Pin LL_GPIO_PIN_10
#define pwmB1_GPIO_Port GPIOA
#define pwmB2_Pin LL_GPIO_PIN_11
#define pwmB2_GPIO_Port GPIOA
#define pwmFLT_Pin LL_GPIO_PIN_12
#define pwmFLT_GPIO_Port GPIOA
#define sysDIO_Pin LL_GPIO_PIN_13
#define sysDIO_GPIO_Port GPIOA
#define sysCLK_Pin LL_GPIO_PIN_14
#define sysCLK_GPIO_Port GPIOA
#define ledI_Pin LL_GPIO_PIN_15
#define ledI_GPIO_Port GPIOA
#define ledV_Pin LL_GPIO_PIN_3
#define ledV_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
