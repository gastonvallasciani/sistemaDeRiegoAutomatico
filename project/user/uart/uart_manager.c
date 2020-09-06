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
//------------------------------------------------------------------------------
//--------------------DECLARACION DE VARIABLES EXTERNAS-------------------------
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//-----------------PROTOTIPOS DE FUNCIONES PRIVADAS-----------------------------
//------------------------------------------------------------------------------
void NVIC_Configuration(void);
static void RCC_Configuration(void);
static void GPIO_Configuration(void);
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
///* Enable GPIO clock */
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
void uart_config(void)
{
  RCC_Configuration();
  
  GPIO_Configuration();
  /* NVIC configuration */
  NVIC_Configuration();
  
  /* USARTx configuration ------------------------------------------------------*/
  /* USARTx configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - Two Stop Bit
        - Odd parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  
  USART_InitStructure.USART_BaudRate            = 9600;
  USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits            = USART_StopBits_1;
  USART_InitStructure.USART_Parity              = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
  
  USART_Init(USART3, &USART_InitStructure);
  
  /* Enable the USART3 Transmit interrupt: this interrupt is generated when the 
     USART 3 transmit data register is empty */  
  USART_ITConfig(USART3, USART_IT_TXE, ENABLE);

  /* Enable the USART3 Receive interrupt: this interrupt is generated when the 
     USART3 receive data register is not empty */
  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  
    /* Enable the USART3 */
  USART_Cmd(USART3, ENABLE);
}
//------------------------------------------------------------------------------
//------------------DEFINICION DE FUNCIONES PUBLICAS----------------------------
//------------------------------------------------------------------------------
void uart__init(void)
{
  uart_config();
}
//------------------------------------------------------------------------------
void uart__handler(void)
{
  
}
//------------------------------------------------------------------------------
//void uart__send_data(uint8_t *tx_data, uint8_t tx_length)
//{
//}
//------------------------------------------------------------------------------
//----------------------------END OF FILE---------------------------------------
//------------------------------------------------------------------------------