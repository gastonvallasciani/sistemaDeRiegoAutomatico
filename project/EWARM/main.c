//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
#include "board.h"
#include "led_manager.h"
#include "analog_reading_manager.h"
#include "uart_manager.h"
#include "global_irrigation_manager.h"
#include "wdt_manager.h"
#include "timers_manager.h"

int main()
{ 
  /* Systick configuration: the systick timer interrupts every 1ms */
   SysTick_Config(SystemCoreClock / 1000); 
 
   blink_led_init();
   analog_reading__init();
   uart__init();
   global_irrigation_init();
#ifndef DEBUG
   wdt__init();
#endif
   
  while(1)
  {
    blink_led_handler();
    uart__handler();
#ifndef DEBUG
    wdt__handler();
#endif
  }
}
//------------------------------------------------------------------------------
//--------------------END OF FILE-----------------------------------------------
//------------------------------------------------------------------------------