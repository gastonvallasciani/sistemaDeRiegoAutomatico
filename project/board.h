/**
*	@file   board.h
*	@author Gaston Vallasciani 
*	@date   28/08/2020
*	@brief  Board module, this module have the definitions for all the pins use on
*         the main board.
*         Microcontroller: stm32f103c8t6.
*         Library        : STM32F10x_StdPeriph_Lib_V3.5.0.
*/
#ifndef BOARD_H__
#define BOARD_H__
//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
// C standard libraries
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
// Std libraries
#include "stm32f10x.h"
//------------------------------------------------------------------------------
//--------------------MACROS Y DEFINES------------------------------------------
//------------------------------------------------------------------------------
/**
  * @brief  Definitions for the LED present on the main board.
  * 
  */
#define LED_PIN                   GPIO_Pin_13
#define LED_SPEED                 GPIO_Speed_10MHz
#define LED_MODE                  GPIO_Mode_Out_PP
#define LED_PORT                  GPIOC

/**
  * @brief  Definitions for the ANALOG READING pins: Battery reading pin and ldr 
  *         reading pin.
  * 
  */
#define BATTERY_READING_PIN        GPIO_Pin_0
#define BATTERY_ADC_CHANNEL        ADC_Channel_0  
#define WIRED_LDR1_PIN             GPIO_Pin_1
#define WIRED_LDR1_ADC_CHANNEL     ADC_Channel_1
#define WIRED_LDR2_PIN             GPIO_Pin_5
#define WIRED_LDR2_ADC_CHANNEL     ADC_Channel_4
#define ANALOG_READING_MODE        GPIO_Mode_AIN
#define ANALOG_READING_PORT        GPIOA

/**
  * @brief  Definitions for the DISPLAY USART pins.
  * 
  */
#define DISPLAY_TX_PIN             GPIO_Pin_10
#define DISPLAY_TX_PIN_MODE        GPIO_Mode_AF_PP
#define DISPLAY_TX_PIN_SPEED       GPIO_Speed_50MHz

#define DISPLAY_RX_PIN             GPIO_Pin_11
#define DISPLAY_RX_PIN_MODE        GPIO_Mode_IN_FLOATING

#define DISPLAY_USART_PORT         GPIOB

//------------------------------------------------------------------------------
//--------------------END OF FILE-----------------------------------------------
//------------------------------------------------------------------------------
#endif /* BOARD_H__ */
