/**
  ******************************************************************************
  * @file   System_DataPool.cpp
  * @brief  All used resources are contained in this file.
  ******************************************************************************
  * @note
  *  - User can define datas including variables ,structs ,and arrays in
  *    this file, which are used in deffrient tasks or services.
**/
#include "System_DataPool.h"

/* RTOS Resources ------------------------------------------------------------*/
/* Queues */
QueueHandle_t USART_RxPort;
QueueHandle_t USART_TxPort;
QueueHandle_t	Action_Port;
QueueHandle_t	Ctrl_Port;
QueueHandle_t Role1_Port;
QueueHandle_t Role2_Port;

/* Semaphores */
/* Mutexes */
/* Notifications */

/* Other Resources -----------------------------------------------------------*/
uint8_t Uart1_Rx_Buff[USART1_RX_BUFFER_SIZE];     /*!< Receive buffer for Uart1 */
uint8_t Uart2_Rx_Buff[USART2_RX_BUFFER_SIZE];     /*!< Receive buffer for Uart2 */



/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/



