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
/* Semaphores */
/* Mutexes */
/* Notifications */

/* Other Resources -----------------------------------------------------------*/
uint8_t Uart1_Rx_Buff[USART1_RX_BUFFER_SIZE];     /*!< Receive buffer for Uart1 */
uint8_t Uart2_Rx_Buff[USART2_RX_BUFFER_SIZE];     /*!< Receive buffer for Uart2 */

// �ؽ���Ϣ�洢
float js_upper[JOINTS_NUM]; // ���͸���λ���İ�
float js_mp[JOINTS_NUM];		// ���͸���е�۵İ�

// ���߶��
BusSteering bs(&huart2);

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/



