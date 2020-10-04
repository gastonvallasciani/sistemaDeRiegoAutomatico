#ifndef TIMERS_MANAGER_H__
#define TIMERS_MANAGER_H__
/**
*	@file   timers_manager
* @addtogroup Application
* @{
* @defgroup timers_manager
* @addtogroup timers_manager
* @{
*	@author Gaston Vallasciani
*	@date   28-09-2020
*	@brief  timers_manager
*
*         Used to manage timers with a time base made with the Systick
*         timer
*
*/
//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
#include "board.h"
//------------------------------------------------------------------------------
//--------------------MACROS Y DEFINES------------------------------------------
//------------------------------------------------------------------------------
#define MAX_TIMERS_QUANTITY     4     /**< Maximum timers quantity */

#define TIMER__LED              0     /**< Led timer number */
#define TIMER__TIMEOUT_RX_UART  1     /**< Uart rx timeout timer */
#define TIMER__END_OF_SEQUENCE  2     /**< Uart end of sequence timer */
#define DEFAULT_NAME_TIMER3     3     /**< Default timer */

#define CLOCK_SECOND            1000  /**< define for setting 1 second time */
#define CLOCK_MINUTE            60*CLOCK_SECOND  /**< define for setting 1 minute time */
#define CLOCK_HOUR              60*CLOCK_MINUTE  /**< define for setting 1 hour time */
//------------------------------------------------------------------------------
//--------------------TYPEDEF---------------------------------------------------
//------------------------------------------------------------------------------
/**
 * @brief timer_info_t
 *
 * struct for setting the configuration of every timer
 */
typedef struct{
  uint8_t  enable;        /**< Enable flag */
  uint32_t timing_value;  /**< Timer timing value */
}timer_info_t;
//------------------------------------------------------------------------------
//--------------------DECLARACION DE DATOS EXTERNOS-----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------------DECLARACION DE FUNCIONES PUBLICAS-------------------------
//------------------------------------------------------------------------------
/* Blocking delay functions */

/** @brief Blocking delay
 **
 ** This function makes a blocking delay. Always is better to use a non blocking
 ** delay
 **
 ** @param[in]    timing value in miliseconds
 ** @return None
 **/
void Delay(__IO uint32_t nTime);
/** @brief Timing upgrade function
 **
 ** This function upgrades the timing values of the delays in course
 **
 ** @param[in] None
 ** @return None
 **/
void TimingDelay_Decrement(void);

/* Non-blocking delay functions */

/** @brief Reset timer timing value
 **
 ** This function clear the timing value of the timer index selected. It 
 ** must be use before setting for the first time the timer point by 
 ** timer_index parameter.
 **
 ** @param[in] timer_index timer index to be reset
 ** @return None
 **/
void reset_timer(uint8_t timer_index);
/** @brief Set timing value of the non-blocking timer
 **
 ** This function must be use every time you want to set a new timing cycle.
 **
 ** @param[in] timer_index number of the timer to reset.
 ** @param[in] time_value specifies the time value in milliseconds.
 ** @return None
 **/
void set_timer(uint8_t timer_index, uint32_t time_value);
/** @brief Decrements time_value from all non-blocking the timers configurated.
 **
 ** This function is used on Systick timer interrupt to upgrade timers value
 **
 ** @param[in] None
 ** @return None
 **/
void decrement_time_value(void);
/** @brief Inform if a timeout event happened on timer index
 **
 ** This function must be use to watch if a timer cycle had finished
 **
 ** @param[in] timer_index number of the timer to reset.
 ** @return None
 **/
uint8_t timeout_event(uint8_t timer_index);
/** @brief Enable timer
 **
 ** @param[in] timer_index number of the timer to enable.
 ** @return None
 **/
void enable_timer(uint8_t timer_index);
/** @brief Disable timer
 **
 ** @param[in] timer_index number of the timer to disable.
 ** @return None
 **/
void disable_timer(uint8_t timer_index);
/** @brief Return the enable status of the indicated timer.
 **
 ** @param[in] timer_index: number of the timer who enable status y asked for.
 ** @return 0 Disable, 1 Enable.
 **/
uint8_t is_timer_enabled(uint8_t timer_index);
//------------------------------------------------------------------------------
//--------------------FIN DEL ARCHIVO-------------------------------------------
//------------------------------------------------------------------------------
/** @}
  * @}
*/
#endif /* TIMERS_MANAGER_H__ */
