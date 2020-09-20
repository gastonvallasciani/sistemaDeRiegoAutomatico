/**
*	@file
*	@author
*	@date
*	@brief
*
*
*/
#ifndef UART_MANAGER_H__
#define UART_MANAGER_H__
//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
#include "board.h"
//------------------------------------------------------------------------------
//--------------------MACROS Y DEFINES------------------------------------------
//------------------------------------------------------------------------------
#define END_OF_SEQUENCE_TIME 25
#define RX_TIMEOUT_TIME      800

#define RX_BUFFER_LENGTH     256
#define TX_BUFFER_LENGTH     256

#define RX_OK                0
#define RX_ERROR             1
//------------------------------------------------------------------------------
//--------------------TYPEDEF---------------------------------------------------
//------------------------------------------------------------------------------
typedef struct{
  uint32_t timeout_rx_time;
  uint32_t end_of_sequence_time;
  uint8_t  rx_buffer[RX_BUFFER_LENGTH];
  uint8_t  tx_buffer[TX_BUFFER_LENGTH];
  uint8_t  tx_length;
  uint8_t  rx_length;
  uint8_t  data_sent;
  uint8_t  data_received;
  uint8_t  receiving_data;
  uint8_t  timeout_counter;
  uint16_t tx_counter;
  uint16_t rx_counter;
  uint8_t  rx_status;
}uart_t;
//------------------------------------------------------------------------------
//--------------------DECLARACION DE DATOS EXTERNOS-----------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//--------------------DECLARACION DE FUNCIONES PUBLICAS-------------------------
//------------------------------------------------------------------------------
void uart__init(void);
void uart__handler(void);
void uart__send_data(uint8_t *tx_data, uint8_t tx_length);
uint8_t uart__data_available_for_reading(void);
uint8_t uart__data_received_length(void);
uint8_t uart__get_received_data(uint8_t *rx_data);
//------------------------------------------------------------------------------
//--------------------FIN DEL ARCHIVO-------------------------------------------
//------------------------------------------------------------------------------
#endif /* UART_MANAGER_H__ */
