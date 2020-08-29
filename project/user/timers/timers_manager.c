/**
*	@file
*	@author
*	@date
*	@brief
*
*
*/
//------------------------------------------------------------------------------
//------------------------------INCLUDES----------------------------------------
//------------------------------------------------------------------------------
#include "timers_manager.h"
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES INTERNAS-------------------------
//------------------------------------------------------------------------------
static __IO uint32_t TimingDelay;

static __IO uint32_t timing_value[MAX_TIMERS_QUANTITY];
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES EXTERNAS-------------------------
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//-----------------PROTOTIPOS DE FUNCIONES INTERNAS-----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES INTERNAS-----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES PUBLICAS----------------------------
//------------------------------------------------------------------------------
/**
  * @brief  Inserts a blocking delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}
//------------------------------------------------------------------------------
/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
//------------------------------------------------------------------------------
/**
  * @brief  Initialize non-blocking timer
  * @param  timer_index: number of the timer to reset.
  * @retval None
  */
void reset_timer(uint8_t timer_index)
{
  timing_value[timer_index] = 0;
}
//------------------------------------------------------------------------------
/**
  * @brief  Set time value to non-blocking timer
  * @param  timer_index: number of the timer to reset.
  * @param  time_value: specifies the time value in milliseconds.
  * @retval None
  */
void set_timer(uint8_t timer_index, uint32_t time_value)
{
  timing_value[timer_index] = time_value;
}
//------------------------------------------------------------------------------
/**
  * @brief  Decrements time_value from all non-blocking the timers configurated.
  * @param  None
  * @retval None
  */
void decrement_time_value(void)
{
  uint8_t timer_index;
  
  for(timer_index = 0; timer_index < MAX_TIMERS_QUANTITY; timer_index++)
  {
    if(timing_value[timer_index] > 0)
    {
      timing_value[timer_index]--;
    }
  }
}
//------------------------------------------------------------------------------
/**
  * @brief  Inform if a timeout event happened.
  * @param  timer_index: number of the timer to reset.
  * @retval None
  */
uint8_t timeout_event(uint8_t timer_index)
{
    if(timing_value[timer_index] == 0)
    {
      return(true);
    }
    else
    {
      return(false);
    }
}
//------------------------------------------------------------------------------
//----------------------------END OF FILE---------------------------------------
//------------------------------------------------------------------------------