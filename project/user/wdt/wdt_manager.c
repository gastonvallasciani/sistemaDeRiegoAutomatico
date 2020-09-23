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
#include "wdt_manager.h"
#include "timers_manager.h"
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES INTERNAS-------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES EXTERNAS-------------------------
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//-----------------PROTOTIPOS DE FUNCIONES INTERNAS-----------------------------
//------------------------------------------------------------------------------
__IO uint32_t LsiFreq = LSI_TYPICAL_FREQUENCY_VALUE;
//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES INTERNAS----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES PUBLICAS----------------------------
//------------------------------------------------------------------------------
/**
  * @brief  Configures and init a 2 second individual watchdog timer. 
  * @param  None
  * @retval None
  */
void wdt__init(void)
{
  /* Check if the system has resumed from IWDG reset */
  if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
  {
    /* IWDGRST flag set */
    /* Clear reset flags */
    RCC_ClearFlag();
  }
  else
  {
    /* IWDGRST flag is not set */
  }
  
  /* IWDG timeout equal to 2s (the timeout may varies due to LSI frequency
     dispersion) */
  /* Enable write access to IWDG_PR and IWDG_RLR registers */
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

  /* IWDG counter clock: LSI/32 */
  IWDG_SetPrescaler(IWDG_Prescaler_32);

  /* Set counter reload value to obtain 250ms IWDG TimeOut.
     Counter Reload Value = 2s/IWDG counter clock period
                          = 2s / (LSI/32)
                          = 2s / (LsiFreq/32)
                          = LsiFreq/(32/2) 
                          = LsiFreq/16
   */
  IWDG_SetReload(((LsiFreq))/16);

  /* Reload IWDG counter */
  IWDG_ReloadCounter();

  /* Enable IWDG */
  IWDG_Enable();
   
}
//------------------------------------------------------------------------------
/**
  * @brief  This function reloads watchdog timer. 
  * @param  None
  * @retval None
  */
void wdt__handler(void)
{
  /* Reload IWDG counter */
    IWDG_ReloadCounter();  
}
//------------------------------------------------------------------------------
//----------------------------END OF FILE---------------------------------------
//------------------------------------------------------------------------------