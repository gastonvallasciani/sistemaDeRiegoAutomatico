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
#include "global_irrigation_manager.h"
#include "timers_manager.h"
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES INTERNAS-------------------------
//------------------------------------------------------------------------------
static global_irrigation_zone_t gi_zone[MAX_IRRIGATION_ZONES_QUANTITY];
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES EXTERNAS-------------------------
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//-----------------PROTOTIPOS DE FUNCIONES INTERNAS-----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES INTERNAS----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES PUBLICAS----------------------------
//------------------------------------------------------------------------------
void global_irrigation_init(void)
{
  uint8_t i = 0;
  
  for(i = 0; i < MAX_IRRIGATION_ZONES_QUANTITY; i++)
  {
    strcpy((char *)gi_zone[i].alias, "zone");
  }
  
}
//------------------------------------------------------------------------------
void global_irrigation_handler(void)
{
  
}
//------------------------------------------------------------------------------
//----------------------------END OF FILE---------------------------------------
//------------------------------------------------------------------------------