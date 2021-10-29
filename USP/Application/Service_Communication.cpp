/**
  ***********************************************************************************
  * @file   : Service_Communication.cpp
  * @brief  : Communication support file.This file provides access ports to interface
  *           with connected devices.
  ***********************************************************************************
                                 ##### Port List #####
  =================================================================================
  |Port Name     Physical-Layer     Data-Link-Layer    Application-Layer    Number
  |————————————————————————————————————————
  |EXAMPLE_Port       CAN1               CAN                CUSTOM            0
  |CAN2_Port          CAN2               CAN                Custom            1
  |EBUG_Port         USART1             Custom              Custom            2
  |USART2_Port       USART2              DBUS               DJI-DR16          3
  *
**/
/* Includes ------------------------------------------------------------------*/
#include "Service_Communication.h"
#include "App_Game.h"

/* Private define ------------------------------------------------------------*/
void Task_UsartRecieve(void *arg);
void Task_UsartTransmit(void *arg);

/**
* @brief  Initialization of communication service
* @param  None.
* @return None.
*/
void Service_Communication_Init(void)
{
  xTaskCreate(Task_UsartRecieve,	"Com.Usart RxPort" , 	Small_Stack_Size,    		NULL, PriorityHigh,   			&UsartRxPort_Handle);
//  xTaskCreate(Task_UsartTransmit,	"Com.Usart TxPort" , 	Small_Stack_Size,    		NULL, PriorityHigh,   			&UsartTxPort_Handle);
}

/*---------------------------------------------- USART Manager --------------------------------------------*/
/*Task Define ---------------------------*/
TaskHandle_t UsartRxPort_Handle;
TaskHandle_t UsartTxPort_Handle;

/*Function Prototypes--------------------*/
/**
* @brief  Tasks for USART Management.
          Attention:In this version we passing the pointer of data not copying
          data itself and we only have one buff zone, so user need to process 
          the data as soon as possible in case of over-write.
* @param  None.
* @return None.
*/

void Task_UsartRecieve(void *arg)
{
	USART_COB Usart_RxCOB;
	for(;;)
  {
    /* Usart Recevice Port */ 
		if(xQueueReceive(USART_RxPort,&Usart_RxCOB,portMAX_DELAY) == pdPASS)
    {
			switch(Usart_RxCOB.port_num)
			{
				case 1: 
					if(CTRL_MODE == SINGLE_MODE) xQueueSend(Ctrl_Port, Usart_RxCOB.address, 0);
					else if(CTRL_MODE == DOUBLE_MODE) xQueueSend(Role1_Port, Usart_RxCOB.address, 0);
					break;
				default: break;
			}
    }
  }
}

void Task_UsartTransmit(void *arg)
{
  /* Cache for Task */
	
  /* Pre-Load for task */
	
  /* Infinite loop */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(50);
  for(;;)
  {
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);
  }	
}

uint32_t User_UART1_RxCpltCallback(uint8_t* Recv_Data, uint16_t ReceiveLen)
{
  static USART_COB Usart_RxCOB;
  //Send To UART Receive Queue
  if(USART_RxPort != NULL)
  {
    Usart_RxCOB.port_num = 1;
    Usart_RxCOB.len      = ReceiveLen;
    Usart_RxCOB.address  = Recv_Data;
    xQueueSendFromISR(USART_RxPort,&Usart_RxCOB,0);
  }
  return 0;
}

/**
* @brief  Callback function in USART Interrupt
* @param  None.
* @return None.
*/
uint32_t User_UART2_RxCpltCallback(uint8_t* Recv_Data, uint16_t ReceiveLen)
{
  static USART_COB Usart_RxCOB;
  //Send To UART Receive Queue
  if(USART_RxPort != NULL)
  {
    Usart_RxCOB.port_num = 2;
    Usart_RxCOB.len      = ReceiveLen;
    Usart_RxCOB.address  = Recv_Data;
    xQueueSendFromISR(USART_RxPort,&Usart_RxCOB,0);
  }
  return 0;
}



/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
