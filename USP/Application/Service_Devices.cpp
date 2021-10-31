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
#include "ps2.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TaskHandle_t DevicePS2_Handle;
TaskHandle_t DeviceTouch_Handle;
TaskHandle_t Manipulator_Handle;

/* Private function declarations ---------------------------------------------*/
void Device_PS2(void *arg);
void Device_Manipulator(void *arg);

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
	xTaskCreate(Device_Manipulator,			"Dev.Manipulator", 		Normal_Stack_Size,     NULL, PriorityHigh, 			 &Manipulator_Handle);
}

/**
 *@brief PS2任务
 */ 
uint8_t rx,ry,lx,ly;
void Device_PS2(void *arg)
{
  /* Cache for Task */
//	QueueHandle_t port;
  /* Pre-Load for task */
//  uint8_t dir;
//	uint8_t trans[3] = {1, 2, 3};
  /* Infinite loop */
  for(;;)
  {
//		if(ps2.GetKeyData(KEY_PAD_LEFT) == PS2_PRESS )  	{ dir = DIR_LEFT; xQueueSend(port, &dir, 0);}
//		if(ps2.GetKeyData(KEY_PAD_RIGHT) == PS2_PRESS)  { dir = DIR_RIGHT; xQueueSend(port, &dir, 0);}
//		rx = ps2.GetRodData(ROD_RX);
//		ry = ps2.GetRodData(ROD_RY);
//		lx = ps2.GetRodData(ROD_LX);
//		ly = ps2.GetRodData(ROD_LY);
		vTaskDelay(100);
		
//		HAL_UART_Transmit_DMA(&huart2, trans, 3);
	}
}


void Device_Manipulator(void *arg)
{
  for(;;)
  {
		// 等待通知 
    ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
		
		// 发送数据给机械臂
		bs.Control_Manipulator(js_mp);	
	}	
}

/* User Code End Here ---------------------------------*/

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
