/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DO_Pin GPIO_PIN_13
#define DO_GPIO_Port GPIOC
#define Touch2_Pin GPIO_PIN_2
#define Touch2_GPIO_Port GPIOC
#define Touch1_Pin GPIO_PIN_3
#define Touch1_GPIO_Port GPIOC
#define RED_Pin GPIO_PIN_12
#define RED_GPIO_Port GPIOB
#define YELLOW_Pin GPIO_PIN_13
#define YELLOW_GPIO_Port GPIOB
#define GREEN_Pin GPIO_PIN_14
#define GREEN_GPIO_Port GPIOB
#define DI_Pin GPIO_PIN_12
#define DI_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_4
#define BIN2_GPIO_Port GPIOB
#define BIN1_Pin GPIO_PIN_5
#define BIN1_GPIO_Port GPIOB
#define AIN1_Pin GPIO_PIN_6
#define AIN1_GPIO_Port GPIOB
#define AIN2_Pin GPIO_PIN_7
#define AIN2_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_9
#define LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t 
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
