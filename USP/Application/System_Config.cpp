/**
  ******************************************************************************
  * @file   System_config.cpp
  * @brief  Deploy resources,tasks and services in this file.
  ******************************************************************************
  * @note
  *  - Before running your Task you should first include your headers and init- 
  *    ialize used resources in "System_Resource_Init()". This function will be 
  *    called before tasks Start.
  *    
  *  - All tasks should be created in "System_Tasks_Init()", this function will
  *    be called in 'defaultTask()'.
  *
  ===============================================================================
                                    Task List
  ===============================================================================
  * <table>
  * <tr><th>Task Name     <th>Priority          <th>Frequency/Hz    <th>Stack/Byte
  * <tr><td>              <td>                  <td>                <td>    
  * </table>
  *
 */
/* Includes ------------------------------------------------------------------*/
#include "System_Config.h"
#include "System_DataPool.h"

/* Service */
#include "Service_Devices.h"
#include "Service_Debug.h"
#include "Service_Communication.h"

/* Application */
#include "App_Interface.h"
#include "App_Game.h"
#include "App_Drawing.h"

/* User support package & SRML */
#include <SRML.h>
#include "text.h"
#include "lcd.h"
#include "oled.h"
#include "touch.h"
#include "flash.h"
#include "ps2.h"

/* Private variables ---------------------------------------------------------*/
uint8_t trans[5] = {1, 2, 3, 4, 5};
uint8_t rev[80];
/*Founctions------------------------------------------------------------------*/
/**
* @brief Load drivers ,modules, and data resources for tasks.
* @note  Edit this function to add Init-functions and configurations.
*/
void System_Resource_Init(void)
{
  /* Drivers Init ---------------------*/
  Timer_Init(&htim5, USE_HAL_DELAY);
	
	Uart_Init(&huart1, Uart1_Rx_Buff, USART1_RX_BUFFER_SIZE, User_UART1_RxCpltCallback);
  
  /* RTOS resources Init --------------*/
  USART_RxPort    = xQueueCreate(4,sizeof(USART_COB));
	Action_Port 		= xQueueCreate(1,1);
	Ctrl_Port 			= xQueueCreate(1,1);
	Role1_Port 			= xQueueCreate(2,1);
	Role2_Port 			= xQueueCreate(2,1);
	
  /* Other resources Init -------------*/
	// 字库初始化
	Text_Init();
	
	// 外部FLASH
	flash.Init(W25Q256, FLASH_CS_GPIO_Port, FLASH_CS_Pin);

	// PS2
	ps2.Init();
	
	// OLED
	OLED_Init();
	
	// LCD
	LCD_Init();
	TP_Init();
	
	// 
  /* Service configurations -----------*/
	System_Tasks_Init();
}  

/**
* @brief Load and start User Tasks. 
* @note  Edit this function to add tasks into the activated tasks list.
*/
void System_Tasks_Init(void)
{ 
  /* Syetem Service init --------------*/
//  Service_Debug_Init();
  Service_Devices_Init();
  Service_Communication_Init();
//	
//  /* Applications Init ----------------*/
	App_Interface_Init();
	App_Games_Init();

}



/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

