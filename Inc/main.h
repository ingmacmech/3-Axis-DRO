/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define TEST_OUTPUT_Pin GPIO_PIN_2
#define TEST_OUTPUT_GPIO_Port GPIOE
#define BUTTON_SEL_AXIS_Pin GPIO_PIN_4
#define BUTTON_SEL_AXIS_GPIO_Port GPIOE
#define BUTTON_SEL_AXIS_EXTI_IRQn EXTI4_IRQn
#define BUTTON_TOOL_UP_Pin GPIO_PIN_5
#define BUTTON_TOOL_UP_GPIO_Port GPIOE
#define BUTTON_TOOL_UP_EXTI_IRQn EXTI9_5_IRQn
#define BUTTON_TOOL_DOWN_Pin GPIO_PIN_6
#define BUTTON_TOOL_DOWN_GPIO_Port GPIOE
#define BUTTON_TOOL_DOWN_EXTI_IRQn EXTI9_5_IRQn
#define BUTTON_CHANGE_COORIDINATE_Pin GPIO_PIN_13
#define BUTTON_CHANGE_COORIDINATE_GPIO_Port GPIOC
#define BUTTON_CHANGE_COORIDINATE_EXTI_IRQn EXTI15_10_IRQn
#define PC14_OSC32_IN_Pin GPIO_PIN_14
#define PC14_OSC32_IN_GPIO_Port GPIOC
#define PC15_OSC32_OUT_Pin GPIO_PIN_15
#define PC15_OSC32_OUT_GPIO_Port GPIOC
#define PH0_OSC_IN_Pin GPIO_PIN_0
#define PH0_OSC_IN_GPIO_Port GPIOH
#define PH1_OSC_OUT_Pin GPIO_PIN_1
#define PH1_OSC_OUT_GPIO_Port GPIOH
#define OTG_FS_PowerSwitchOn_Pin GPIO_PIN_0
#define OTG_FS_PowerSwitchOn_GPIO_Port GPIOC
#define CSn_Pin GPIO_PIN_1
#define CSn_GPIO_Port GPIOC
#define PDM_OUT_Pin GPIO_PIN_3
#define PDM_OUT_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define I2S3_WS_Pin GPIO_PIN_4
#define I2S3_WS_GPIO_Port GPIOA
#define SPI1_SCK_Pin GPIO_PIN_5
#define SPI1_SCK_GPIO_Port GPIOA
#define SPI1_MISO_Pin GPIO_PIN_6
#define SPI1_MISO_GPIO_Port GPIOA
#define SPI1_MOSI_Pin GPIO_PIN_7
#define SPI1_MOSI_GPIO_Port GPIOA
#define BUTTON_Y_ZERRO_Pin GPIO_PIN_1
#define BUTTON_Y_ZERRO_GPIO_Port GPIOB
#define BUTTON_Y_ZERRO_EXTI_IRQn EXTI1_IRQn
#define BOOT1_Pin GPIO_PIN_2
#define BOOT1_GPIO_Port GPIOB
#define CLK_IN_Pin GPIO_PIN_10
#define CLK_IN_GPIO_Port GPIOB
#define KEYPAD_ROW_0_Pin GPIO_PIN_11
#define KEYPAD_ROW_0_GPIO_Port GPIOB
#define KEYPAD_ROW_1_Pin GPIO_PIN_12
#define KEYPAD_ROW_1_GPIO_Port GPIOB
#define KEYPAD_ROW_2_Pin GPIO_PIN_13
#define KEYPAD_ROW_2_GPIO_Port GPIOB
#define KEYPAD_ROW_3_Pin GPIO_PIN_14
#define KEYPAD_ROW_3_GPIO_Port GPIOB
#define BUTTON_Z_ZERRO_Pin GPIO_PIN_11
#define BUTTON_Z_ZERRO_GPIO_Port GPIOD
#define BUTTON_Z_ZERRO_EXTI_IRQn EXTI15_10_IRQn
#define BUTTON_X_ZERRO_Pin GPIO_PIN_12
#define BUTTON_X_ZERRO_GPIO_Port GPIOD
#define BUTTON_X_ZERRO_EXTI_IRQn EXTI15_10_IRQn
#define KEYPAD_COLUMN_0_Pin GPIO_PIN_6
#define KEYPAD_COLUMN_0_GPIO_Port GPIOC
#define KEYPAD_COLUMN_1_Pin GPIO_PIN_7
#define KEYPAD_COLUMN_1_GPIO_Port GPIOC
#define KEYPAD_COLUMN_2_Pin GPIO_PIN_8
#define KEYPAD_COLUMN_2_GPIO_Port GPIOC
#define KEYPAD_COLUMN_3_Pin GPIO_PIN_9
#define KEYPAD_COLUMN_3_GPIO_Port GPIOC
#define BUTTON_W_ZERRO_Pin GPIO_PIN_10
#define BUTTON_W_ZERRO_GPIO_Port GPIOA
#define BUTTON_W_ZERRO_EXTI_IRQn EXTI15_10_IRQn
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define I2S3_SCK_Pin GPIO_PIN_10
#define I2S3_SCK_GPIO_Port GPIOC
#define I2S3_SD_Pin GPIO_PIN_12
#define I2S3_SD_GPIO_Port GPIOC
#define LCD_RST_PIN_Pin GPIO_PIN_3
#define LCD_RST_PIN_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define SCL_EEPROM_Pin GPIO_PIN_8
#define SCL_EEPROM_GPIO_Port GPIOB
#define SDA_EEPROM_Pin GPIO_PIN_9
#define SDA_EEPROM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define TRUE 1
#define FALSE 0
/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
