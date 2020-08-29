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
#include "led_manager.h"
#include "timers_manager.h"
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES INTERNAS-------------------------
//------------------------------------------------------------------------------
static GPIO_InitTypeDef GPIO_InitStructure;
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
  * @brief  Blinking led initialize function.
  * @param  None
  * @retval None
  */
void blink_led_init(void)
{
  /* GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  
  /* Configure PD0 and PD2 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin   = LED_PIN;
  GPIO_InitStructure.GPIO_Speed = LED_SPEED;
  GPIO_InitStructure.GPIO_Mode  = LED_MODE;
  GPIO_Init(LED_PORT, &GPIO_InitStructure);
  
  reset_timer(TIMER__LED);
  set_timer(TIMER__LED, LED_TIME);
  
  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
}
//------------------------------------------------------------------------------
void blink_led_handler(void)
{
  if(timeout_event(TIMER__LED))
  {
    set_timer(TIMER__LED, LED_TIME);
    
    if(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13) == true)
    {
      GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
    }
    else
    {
      GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
    }
  }
}
//------------------------------------------------------------------------------
//----------------------------END OF FILE---------------------------------------
//------------------------------------------------------------------------------