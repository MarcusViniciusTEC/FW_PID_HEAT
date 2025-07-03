/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define BOARD_LED_Pin GPIO_PIN_13
#define BOARD_LED_GPIO_Port GPIOC
#define RELE_LAMP_Pin GPIO_PIN_10
#define RELE_LAMP_GPIO_Port GPIOB
#define LAMP_ENABLE_Pin GPIO_PIN_11
#define LAMP_ENABLE_GPIO_Port GPIOB
#define BT_RIGHT_Pin GPIO_PIN_12
#define BT_RIGHT_GPIO_Port GPIOB
#define BT_UP_Pin GPIO_PIN_13
#define BT_UP_GPIO_Port GPIOB
#define BT_DOWN_Pin GPIO_PIN_14
#define BT_DOWN_GPIO_Port GPIOB
#define BT_LEFT_Pin GPIO_PIN_15
#define BT_LEFT_GPIO_Port GPIOB
#define LCD_DB7_Pin GPIO_PIN_8
#define LCD_DB7_GPIO_Port GPIOA
#define LCD_DB6_Pin GPIO_PIN_9
#define LCD_DB6_GPIO_Port GPIOA
#define LCD_DB5_Pin GPIO_PIN_10
#define LCD_DB5_GPIO_Port GPIOA
#define LCD_DB4_Pin GPIO_PIN_11
#define LCD_DB4_GPIO_Port GPIOA
#define LCD_EN_Pin GPIO_PIN_12
#define LCD_EN_GPIO_Port GPIOA
#define LCD_RS_Pin GPIO_PIN_15
#define LCD_RS_GPIO_Port GPIOA
#define VCC_LCD_EN_Pin GPIO_PIN_5
#define VCC_LCD_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
