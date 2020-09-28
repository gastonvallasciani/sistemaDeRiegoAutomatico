
#ifndef UART_MANAGER_H__
#define UART_MANAGER_H__
/**
*	@file   uart_manager
* @addtogroup Application
* @{
* @defgroup uart_manager
* @addtogroup uart_manager
* @{
*	@author Gaston Vallasciani
*	@date   28-09-2020
*	@brief  Uart module.
*
*         Uart configurated as master. Sends and then receive messages from 
*         USART 3.
*
*/
//------------------------------------------------------------------------------
//--------------------INCLUDES--------------------------------------------------
//------------------------------------------------------------------------------
#include "board.h"
//------------------------------------------------------------------------------
//--------------------MACROS Y DEFINES------------------------------------------
//------------------------------------------------------------------------------
#define END_OF_SEQUENCE_TIME 20   /**< End of sequence time */
#define RX_TIMEOUT_TIME      500  /**< Rx tiemout time */

#define RX_BUFFER_LENGTH     256  /**< Receive buffer length */
#define TX_BUFFER_LENGTH     256  /**< Transmit buffer length */

#define RX_OK                0    /**< Receive status OK */
#define RX_ERROR             1    /**< Receive status ERROR */
//------------------------------------------------------------------------------
//--------------------TYPEDEF---------------------------------------------------
//------------------------------------------------------------------------------
/**
 * @brief uart_t
 *
 * Main struct for setting all the variables involved on the uart usage.
 */
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
/**
  * @brief  uart init function. To be called on main.
  * @param  None
  * @retval None
  */
void uart__init(void);
/**
  * @brief  uart handler function. To be called on main loop.
  * @param  None
  * @retval None
  */
void uart__handler(void);
/**
  * @brief  function for sending data over USART3
  * @param  *tx_data: pointer to tx buffer data.
  *         tx_length: length of buffer to be send over USART3.
  * @retval None
  */
void uart__send_data(uint8_t *tx_data, uint8_t tx_length);
/**
  * @brief  function for checking if there is new data to be read
  * @param  None
  * @retval 1: new data available for reading.
  *         0: no data available for reading.
  */
uint8_t uart__data_available_for_reading(void);
/**
  * @brief  function for getting the length of received data
  * @param  None
  * @retval uart.rx_length: length of received data.
  *         0: no data to be read.
  */
uint8_t uart__data_received_length(void);
/**
  * @brief  function for getting received data
  * @param  *rx_data: pointer for reading rx buffer.
  * @retval 1: data read correctly.
  *         0: no data available on read buffer.
  */
uint8_t uart__get_received_data(uint8_t *rx_data);
//------------------------------------------------------------------------------
//--------------------FIN DEL ARCHIVO-------------------------------------------
//------------------------------------------------------------------------------
/** @}
  * @}
*/
#endif /* UART_MANAGER_H__ */
