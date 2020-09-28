#ifndef ANALOG_READING_MANAGER_H__
#define ANALOG_READING_MANAGER_H__
/**
*	@file   analog_reading_manager
* @addtogroup Application
* @{
* @defgroup analog_reading_manager
* @addtogroup analog_reading_manager
* @{
*	@author Gaston Vallasciani
*	@date   28-09-2020
*	@brief  Analog reading module.
*
*         Used for reading ldr sensors and battery voltage.
*
*/
//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
#include "board.h"
//------------------------------------------------------------------------------
//--------------------MACROS Y DEFINES------------------------------------------
//------------------------------------------------------------------------------
 
//------------------------------------------------------------------------------
//--------------------TYPEDEF---------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------------DECLARACION DE DATOS EXTERNOS-----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------------DECLARACION DE FUNCIONES PUBLICAS-------------------------
//------------------------------------------------------------------------------
/**
  * @brief  Analog reading initialize function.
  * @param  None
  * @retval None
  */
void analog_reading__init(void);
/**
  * @brief  Return the battery voltage reading value in the param given as a 
  *         pointer.
  * @param  battery_voltage pointer to the return value.
  * @retval 1 always
  */
uint8_t analog_reading__get_battery_voltage(uint16_t *battery_voltage);
/**
  * @brief  Return the wired ldr 1 reading value in the param given as a 
  *         pointer.
  * @param  wired_ldr1_reading_value pointer to the return value.
  * @retval 1 always
  */
uint8_t analog_reading__get_ldr1_reading(uint16_t *wired_ldr1_reading_value);
/**
  * @brief  Return the wired ldr 2 reading value in the param given as a 
  *         pointer.
  * @param  wired_ldr2_reading_value pointer to the return value.
  * @retval 1 always
  */
uint8_t analog_reading__get_ldr2_reading(uint16_t *wired_ldr2_reading_value);
//------------------------------------------------------------------------------
//--------------------FIN DEL ARCHIVO-------------------------------------------
//------------------------------------------------------------------------------
/** @}
  * @}
*/
#endif /* LED_MANAGER_H__ */
