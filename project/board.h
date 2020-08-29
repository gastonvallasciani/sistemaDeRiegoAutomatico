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
// Std libraries
#include "stm32f10x.h"
//------------------------------------------------------------------------------
//--------------------MACROS Y DEFINES------------------------------------------
//------------------------------------------------------------------------------
/**
  * @brief  Definitions for the LED present on the main board.
  * 
  */
#define LED_PIN   GPIO_Pin_13
#define LED_SPEED GPIO_Speed_10MHz
#define LED_MODE  GPIO_Mode_Out_PP
#define LED_PORT  GPIOC
//------------------------------------------------------------------------------
//--------------------END OF FILE-----------------------------------------------
//------------------------------------------------------------------------------
#endif /* BOARD_H__ */
