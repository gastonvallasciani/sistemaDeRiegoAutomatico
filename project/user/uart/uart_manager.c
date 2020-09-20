/**
*	@file    uart_manager.c
*	@author
*	@date    5/09/2020
*	@brief   Uart configurated as master. Sends and then receive messages from 
*          USART 3.
*
*
*/
//------------------------------------------------------------------------------
//------------------------------INCLUDES----------------------------------------
//------------------------------------------------------------------------------
#include "uart_manager.h"
#include "timers_manager.h"
#include "misc.h"
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES PRIVADAS-------------------------
//------------------------------------------------------------------------------
USART_InitTypeDef USART_InitStructure;
uart_t            uart;
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES EXTERNAS-------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//-----------------PROTOTIPOS DE FUNCIONES PRIVADAS-----------------------------
//------------------------------------------------------------------------------
void NVIC_Configuration(void);
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
static void uart_config(uint32_t baudrate, uint32_t end_of_sequence_time_ms, 
                 uint32_t rx_timeout_ms);
//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES PRIVADAS----------------------------
//------------------------------------------------------------------------------
/**
  * @brief  Configures the nested vectored interrupt controller.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
//------------------------------------------------------------------------------
static void RCC_Configuration(void)
{
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  /* Enable USART clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
}
//------------------------------------------------------------------------------
static void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure in floating */
  GPIO_InitStructure.GPIO_Pin   = DISPLAY_TX_PIN;
  GPIO_InitStructure.GPIO_Mode  = DISPLAY_TX_PIN_MODE;
  GPIO_InitStructure.GPIO_Speed = DISPLAY_TX_PIN_SPEED;
  GPIO_Init(DISPLAY_USART_PORT, &GPIO_InitStructure);

  /* Configure push-pull */
  GPIO_InitStructure.GPIO_Pin   = DISPLAY_RX_PIN;;
  GPIO_InitStructure.GPIO_Mode  = DISPLAY_RX_PIN_MODE;
  GPIO_Init(DISPLAY_USART_PORT, &GPIO_InitStructure);
}
//------------------------------------------------------------------------------
void uart_config(uint32_t baudrate, uint32_t end_of_sequence_time_ms, 
                 uint32_t rx_timeout_ms)
{
 
  uart.end_of_sequence_time = end_of_sequence_time_ms;
  uart.timeout_rx_time      = rx_timeout_ms;
  uart.data_sent            = false;
  uart.data_received        = false;
  uart.receiving_data       = false;
  uart.tx_length            = 0;
  uart.rx_length            = 0;
  uart.timeout_counter      = 0;
  uart.tx_counter           = 0;
  uart.rx_counter           = 0;
  uart.rx_status            = RX_ERROR;
  
  RCC_Configuration();
  
  GPIO_Configuration();
  /* NVIC configuration */
  NVIC_Configuration();
  
  /* USARTx configuration -----------------------------------------------------*/
  /* USARTx configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - Two Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  
  USART_InitStructure.USART_BaudRate            = baudrate;
  USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits            = USART_StopBits_1;
  USART_InitStructure.USART_Parity              = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(USART3, &USART_InitStructure);
  enable_timer(TIMER__END_OF_SEQUENCE);

  /* Enable USART3 */
  USART_Cmd(USART3, ENABLE);
  
  reset_timer(TIMER__TIMEOUT_RX_UART);
  reset_timer(TIMER__END_OF_SEQUENCE);
}
//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES PUBLICAS----------------------------
//------------------------------------------------------------------------------
void uart__init(void)
{
  uart_config(115200, END_OF_SEQUENCE_TIME, RX_TIMEOUT_TIME);
}
//------------------------------------------------------------------------------
void uart__handler(void)
{
  uint16_t i = 0;
  
  if(timeout_event(TIMER__END_OF_SEQUENCE) && 
    (is_timer_enabled(TIMER__END_OF_SEQUENCE)) && 
    (uart.receiving_data == true))
  {
    /* End of sequence has ocurred*/
    uart.receiving_data  = false;
    uart.data_received   = true;
    uart.data_sent       = false;
    uart.rx_length       = uart.rx_counter;
    uart.rx_counter      = 0;
    uart.timeout_counter = 0;
    uart.rx_status       = RX_OK;
    
    //disable_timer(TIMER__END_OF_SEQUENCE);
 
    /* Disable the USART3 Receive interrupt */
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
  }

  if(timeout_event(TIMER__TIMEOUT_RX_UART) && (uart.data_sent == true) && 
    (uart.data_received == false) && (uart.receiving_data == false) && 
    (is_timer_enabled(TIMER__TIMEOUT_RX_UART)))
  {
    /* Reception timeout has ocurred and there is any byte received */
    uart.timeout_counter++;
    /* if there weren't slave device, this variable would go out of range. That's
       why it's limited to 255. */
    if(uart.timeout_counter == 255)
    {
      uart.timeout_counter = 0;
    }
    
    for(i = 0; i < RX_BUFFER_LENGTH; i++)
    {
      uart.rx_buffer[i] = 0;
    }
    
    uart.receiving_data  = false;
    uart.data_received   = false;
    uart.data_sent       = false;
    uart.rx_length       = 0;
    uart.rx_counter      = 0;
    uart.rx_status       = RX_ERROR;
    
    //disable_timer(TIMER__END_OF_SEQUENCE);
    disable_timer(TIMER__TIMEOUT_RX_UART);
    
    USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
  }
}
//------------------------------------------------------------------------------
void uart__send_data(uint8_t *tx_data, uint8_t tx_length)
{
  uint8_t i = 0;
  
  uart.tx_length = tx_length;
  
  if((uart.data_sent == false) && (uart.receiving_data == false))
  {
    for(i = 0; i < tx_length; i++)
    {
      uart.tx_buffer[i] = tx_data[i];
    }
    
    /* Enable USART 3 transmit interrupt */  
    USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
  }
}
//------------------------------------------------------------------------------
uint8_t uart__data_available_for_reading(void)
{
  return(uart.data_received);
}
//------------------------------------------------------------------------------
uint8_t uart__data_received_length(void)
{
  if(uart.data_received == true)
  {
    return(uart.rx_length);
  }
  else
  {
    return(0);
  }
}
//------------------------------------------------------------------------------
uint8_t uart__get_received_data(uint8_t *rx_data)
{
  uint8_t i = 0;
  
  if((uart.rx_length > 0) && (uart.data_received == true))
  {
    for(i = 0; i < uart.rx_length; i++)
    {
      rx_data[i] = uart.rx_buffer[i];
      uart.rx_buffer[i] = 0;
    }
    
    uart.rx_counter    = 0;
    uart.rx_length     = 0;
    uart.data_received = false;
    
    return(1);
  }
   return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//----------------------------END OF FILE---------------------------------------
//------------------------------------------------------------------------------