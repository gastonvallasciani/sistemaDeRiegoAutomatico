/**
*	@file
*	@author
*	@date
*	@brief
*
*
*/
#ifndef TIMERS_MANAGER_H__
#define TIMERS_MANAGER_H__
//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
#include "board.h"
//------------------------------------------------------------------------------
//--------------------MACROS Y DEFINES------------------------------------------
//------------------------------------------------------------------------------
#define MAX_TIMERS_QUANTITY     4

#define TIMER__LED              0
#define TIMER__TIMEOUT_RX_UART  1
#define TIMER__END_OF_SEQUENCE  2
#define DEFAULT_NAME_TIMER3     3

#define CLOCK_SECOND         1000
//------------------------------------------------------------------------------
//--------------------TYPEDEF---------------------------------------------------
//------------------------------------------------------------------------------
typedef struct{
  uint8_t  enable;
  uint32_t timing_value;
}timer_info_t;
//------------------------------------------------------------------------------
//--------------------DECLARACION DE DATOS EXTERNOS-----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------------DECLARACION DE FUNCIONES PUBLICAS-------------------------
//------------------------------------------------------------------------------
// Blocking delay functions
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
// Non-blocking delay functions
void reset_timer(uint8_t timer_index);
void set_timer(uint8_t timer_index, uint32_t time_value);
void decrement_time_value(void);
uint8_t timeout_event(uint8_t timer_index);
void enable_timer(uint8_t timer_index);
void disable_timer(uint8_t timer_index);
uint8_t is_timer_enabled(uint8_t timer_index);
//------------------------------------------------------------------------------
//--------------------FIN DEL ARCHIVO-------------------------------------------
//------------------------------------------------------------------------------
#endif /* TIMERS_MANAGER_H__ */
