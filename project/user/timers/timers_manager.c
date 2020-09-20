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

static __IO timer_info_t timer_info[MAX_TIMERS_QUANTITY];
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
  timer_info[timer_index].timing_value = 0;
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
  timer_info[timer_index].timing_value = time_value;
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
    if((timer_info[timer_index].timing_value > 0) && 
       (timer_info[timer_index].enable == true))
    {
      timer_info[timer_index].timing_value--;
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
    if(timer_info[timer_index].timing_value == 0)
    {
      return(true);
    }
    else
    {
      return(false);
    }
}
//------------------------------------------------------------------------------
/**
  * @brief  Enable timer
  * @param  timer_index: number of the timer to enable.
  * @retval None
  */
void enable_timer(uint8_t timer_index)
{
  timer_info[timer_index].enable = true;
}
//------------------------------------------------------------------------------
/**
  * @brief  Disable timer
  * @param  timer_index: number of the timer to disable.
  * @retval None
  */
void disable_timer(uint8_t timer_index)
{
  timer_info[timer_index].enable = false;
}
//------------------------------------------------------------------------------
/**
  * @brief  Return the enable status of the indicated timer.
  * @param  timer_index: number of the timer who enable status y asked for.
  * @retval 0 Disable, 1 Enable.
  */
uint8_t is_timer_enabled(uint8_t timer_index)
{
  return(timer_info[timer_index].enable);
}
//------------------------------------------------------------------------------
//----------------------------END OF FILE---------------------------------------
//------------------------------------------------------------------------------