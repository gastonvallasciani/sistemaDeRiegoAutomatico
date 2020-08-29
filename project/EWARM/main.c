//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
#include "board.h"
#include "led_manager.h"

int main()
{ 
  /* Systick configuration: the systick timer interrupts every 1ms */
   SysTick_Config(SystemCoreClock / 1000); 
 
   blink_led_init();
  
  while(1)
  {
    blink_led_handler();
  }
}
//------------------------------------------------------------------------------
//--------------------END OF FILE-----------------------------------------------
//------------------------------------------------------------------------------