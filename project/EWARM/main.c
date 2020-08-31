//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
#include "board.h"
#include "led_manager.h"
#include "analog_reading_manager.h"

int main()
{ 
  /* Systick configuration: the systick timer interrupts every 1ms */
   SysTick_Config(SystemCoreClock / 1000); 
 
   blink_led_init();
   analog_reading__init();
   
  while(1)
  {
    blink_led_handler();
    analog_reading__handler();
  }
}
//------------------------------------------------------------------------------
//--------------------END OF FILE-----------------------------------------------
//------------------------------------------------------------------------------