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
#include "dataflash_manager.h"
#include "timers_manager.h"
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES INTERNAS-------------------------
//------------------------------------------------------------------------------
volatile FLASH_Status dataflash_status = FLASH_COMPLETE;
uint32_t  address = 0x00;
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
uint32_t data_saved = 0; 
/**
  * @brief  Blinking led initialize function.
  * @param  None
  * @retval None
  */
void dataflash__first_time(void)
{
  uint8_t memory_program_status = 0;
  
  FLASH_UnlockBank1();
  
  
  /* Clear All pending flags */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  
  //FLASH_EraseAllPages();
  dataflash_status = FLASH_ErasePage(BANK1_WRITE_START_ADDR);
  
  /* Program Flash Bank1 */
  address = FIRST_TIME_FLAG_ADDRESS_START;
   
  dataflash_status = FLASH_ProgramWord(address, FIRST_TIME_FLAG_SET);
  
  /* Program Flash Bank1 */
  address = FIRST_TIME_FLAG_ADDRESS_START + 4;
   
  dataflash_status = FLASH_ProgramWord(address, 101);
  
  FLASH_LockBank1();
 
}

/*uint32_t dataflash__get_first_time_status(void)
{
  uint32_t first_time_status = 0;
  
  first_time_status = *(__IO uint32_t*)FIRST_TIME_FLAG_ADDRESS_START;
  
  return(first_time_status);
}*/
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//----------------------------END OF FILE---------------------------------------
//------------------------------------------------------------------------------