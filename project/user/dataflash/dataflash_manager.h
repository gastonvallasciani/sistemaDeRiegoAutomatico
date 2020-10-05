#ifndef DATAFLASH_MANAGER_H__
#define DATAFLASH_MANAGER_H__
/**
*	@file   dataflash_manager
* @addtogroup Application
* @{
* @defgroup dataflash_manager
* @addtogroup dataflash_manager
* @{
*	@author Gaston Vallasciani
*	@date   04-10-2020
*	@brief  dataflash_manager
*
*         Used to save non volatil information
*
*/
//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
#include "board.h"
//------------------------------------------------------------------------------
//--------------------MACROS Y DEFINES------------------------------------------
//------------------------------------------------------------------------------
#define FLASH_PAGE_SIZE                 ((uint16_t)0x400)

#define BANK1_WRITE_START_ADDR          ((uint32_t)0x08008000)
#define BANK1_WRITE_END_ADDR            ((uint32_t)0x0800C000)

#define FIRST_TIME_FLAG_SET              0x64

#define FIRST_TIME_FLAG_ADDRESS_START    BANK1_WRITE_START_ADDR
#define FIRST_TIME_FLAG_ADDRESS_LENGTH   4
#define DEFAULT_NEXT_ADDRESS_START       FIRST_TIME_FLAG_ADDRESS_START + FIRST_TIME_FLAG_ADDRESS_LENGTH  
#define DEFAULT_NEXT_ADDRESS_LENGTH      4
//------------------------------------------------------------------------------
//--------------------TYPEDEF---------------------------------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------------DECLARACION DE DATOS EXTERNOS-----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------------DECLARACION DE FUNCIONES PUBLICAS-------------------------
//------------------------------------------------------------------------------
/** @brief Initialize non volatil information
 **
 ** Save non volatil information in microcontrollers flash
 **
 ** @param[in] None
 ** @return None
 **/
void dataflash__first_time(void);
/** @brief Gets first time flag status
 **
 ** Save non volatil information in microcontrollers flash
 **
 ** @param[in] None
 ** @return 0x64 if dataflash init, else is not init
 **/
uint32_t dataflash__get_first_time_status(void);
//------------------------------------------------------------------------------
//--------------------FIN DEL ARCHIVO-------------------------------------------
//------------------------------------------------------------------------------
/** @}
  * @}
*/
#endif /* DATAFLASH_MANAGER_H__ */
