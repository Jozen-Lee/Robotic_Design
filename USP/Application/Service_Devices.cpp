/**
  ******************************************************************************
  * @file   Service_Devices.cpp
  * @brief  Devices service running file.
  ******************************************************************************
  * @note
  *  - Before running your devices, just do what you want ~ !
  *  - More devices or using other classification is decided by yourself ~ !
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
#include "Service_Devices.h"
#include "App_Game.h"
#include "ps2.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TaskHandle_t DevicePS2_Handle;
TaskHandle_t DeviceTouch_Handle;

/* Private function declarations ---------------------------------------------*/
void Device_PS2(void *arg);
void Device_Touch(void *arg);

// 触屏任务的函数指针 0 无数据 1-6 有效数字
uint8_t (*touch_func)(void) = NULL;

/* Exported devices ----------------------------------------------------------*/
/* Motor & ESC & Other actuators*/
/* Remote control */

/* IMU & NUC & Other sensors */

/* Other boards */

/* Function prototypes -------------------------------------------------------*/
/**
* @brief  Initialization of device management service
* @param  None.
* @return None.
*/
void Service_Devices_Init(void)
{
	xTaskCreate(Device_PS2,							"Dev.PS2", 						Normal_Stack_Size,     NULL, PriorityHigh, 			 &DevicePS2_Handle);
	xTaskCreate(Device_Touch,						"Dev.Touch", 					Small_Stack_Size,     NULL, PriorityHigh, 			 &DeviceTouch_Handle);
}


/**
 *@brief PS2任务
 */ 
uint8_t rx,ry,lx,ly;
void Device_PS2(void *arg)
{
  /* Cache for Task */
	QueueHandle_t port;
  /* Pre-Load for task */
  uint8_t dir;
	uint8_t trans[3] = {1, 2, 3};
  /* Infinite loop */
  for(;;)
  {
		// 单双人模式信号放入不同队列
		if(CTRL_MODE == SINGLE_MODE) port = Ctrl_Port;
		else port = Role2_Port;
		ps2.UpdateData();
		if(ps2.GetKeyData(KEY_PAD_UP) == PS2_PRESS)  	
		{ 
			dir = DIR_UP; 	
			xQueueSend(port, &dir, 0);
		}
		if(ps2.GetKeyData(KEY_PAD_DOWN) == PS2_PRESS)  	
		{ 
			dir = DIR_DOWN; 
			xQueueSend(port, &dir, 0);
		}
		if(ps2.GetKeyData(KEY_PAD_LEFT) == PS2_PRESS )  	{ dir = DIR_LEFT; xQueueSend(port, &dir, 0);}
		if(ps2.GetKeyData(KEY_PAD_RIGHT) == PS2_PRESS)  { dir = DIR_RIGHT; xQueueSend(port, &dir, 0);}
		rx = ps2.GetRodData(ROD_RX);
		ry = ps2.GetRodData(ROD_RY);
		lx = ps2.GetRodData(ROD_LX);
		ly = ps2.GetRodData(ROD_LY);
		vTaskDelay(100);
		
		HAL_UART_Transmit_DMA(&huart2, trans, 3);
	}
}

/**
 *@brief 触屏检测任务
 */ 
void Device_Touch(void *arg)
{
  /* Cache for Task */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(50);
  /* Pre-Load for task */
	uint8_t Res = 0;
  /* Infinite loop */
  for(;;)
  {
		/* 检测触摸屏状态  */
		if(touch_func != NULL) 
		{
			Res = touch_func();
			if(Res) 
			{
				vTaskDelay(500);
				xQueueSend(Action_Port, &Res, 0);
			}
		}
		
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);	
	}
}



/* User Code End Here ---------------------------------*/

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
