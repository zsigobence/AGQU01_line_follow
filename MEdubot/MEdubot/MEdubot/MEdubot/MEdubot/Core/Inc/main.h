/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define DIR_CLK_Pin GPIO_PIN_12
#define DIR_CLK_GPIO_Port GPIOB
#define DIR_LATCH_Pin GPIO_PIN_13
#define DIR_LATCH_GPIO_Port GPIOB
#define DIR_SER_Pin GPIO_PIN_14
#define DIR_SER_GPIO_Port GPIOB
#define DIR_EN_Pin GPIO_PIN_15
#define DIR_EN_GPIO_Port GPIOB
#define PWM_M_2_Pin GPIO_PIN_6
#define PWM_M_2_GPIO_Port GPIOC
#define PWM_M_1_Pin GPIO_PIN_7
#define PWM_M_1_GPIO_Port GPIOC
#define PWM_M_3_Pin GPIO_PIN_8
#define PWM_M_3_GPIO_Port GPIOC
#define PWM_M_4_Pin GPIO_PIN_9
#define PWM_M_4_GPIO_Port GPIOC
#define SERVO_1_Pin GPIO_PIN_8
#define SERVO_1_GPIO_Port GPIOA
#define SERVO_2_Pin GPIO_PIN_9
#define SERVO_2_GPIO_Port GPIOA
#define SERVO_3_Pin GPIO_PIN_10
#define SERVO_3_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
