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
#include "App_Interface.h"
#include "App_Game.h"
#include "Service_Devices.h"
#include "App_Drawing.h"
#include "touch.h"
#include "lcd.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TaskHandle_t StartIF_Handle;
TaskHandle_t GamesIF_Handle;

/* Private function declarations ---------------------------------------------*/
uint8_t StartIF_TouchTask(void);
void IF_Start(void *arg);
void IF_Games(void *arg);

/* Exported devices ----------------------------------------------------------*/
/* Motor & ESC & Other actuators*/
/* Remote control */

/* IMU & NUC & Other sensors */

/* Other boards */

/* Function prototypes -------------------------------------------------------*/
/**
* @brief  Initialization of interface
* @param  None.
* @return None.
*/
void App_Interface_Init(void)
{
	xTaskCreate(IF_Start,				"IF.Start", 				Normal_Stack_Size,    NULL, PriorityHigh, 			 &StartIF_Handle);
	xTaskCreate(IF_Games,				"IF.Games", 				Small_Stack_Size,     NULL, PriorityHigh, 			 &GamesIF_Handle);
//	vTaskSuspend(StartIF_Handle);
	vTaskSuspend(GamesIF_Handle);
}

/**
 *@brief 开始界面的触摸屏检测函数
 */ 
uint8_t StartIF_TouchTask(void)
{
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)
	{
		 if(tp_dev.x[0]>20&&tp_dev.x[0]<220&&tp_dev.y[0]>80&&tp_dev.y[0]<120)
		 {
			 return 1;
		 }
		 else return 0;
	}
	else return 0;
}

/**
 *@brief 开始界面任务
 */ 
void IF_Start(void *arg)
{
  /* Cache for Task */
	
  /* Pre-Load for task */
	uint8_t res;
  /* Infinite loop */
  for(;;)
  {
		Start_Interface();
		HAL_Delay(1000);
		touch_func = StartIF_TouchTask;
		if(xQueueReceive(Action_Port,&res,portMAX_DELAY) == pdPASS)
		{
			touch_func = NULL;
			if(res == 1) 
			{
//				vTaskResume(GamesIF_Handle);
				vTaskResume(FootballGame_Handle);
				vTaskSuspend(NULL);
			}
		}
	}
}

/**
 *@brief 游戏选择界面的触摸屏检测函数
 */ 
uint8_t GameChoose_TouchTask(void)
{
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)
	{
		 if(tp_dev.x[0]>30&&tp_dev.x[0]<200&&tp_dev.y[0]>60&&tp_dev.y[0]<100)
		 {
			 return 1;
		 }
		 else if(tp_dev.x[0]>30&&tp_dev.x[0]<200&&tp_dev.y[0]>220&&tp_dev.y[0]<260)
		 {
			 return 2;
		 }		
		 else return 0;		 
	}
	else return 0;
}

/**
 *@brief 游戏选择界面任务
 */ 
void IF_Games(void *arg)
{
  /* Cache for Task */
	
  /* Pre-Load for task */
	uint8_t res;
  /* Infinite loop */
  for(;;)
  {
		GamesChoose_Interface();
		HAL_Delay(1000);
		touch_func = GameChoose_TouchTask;
		if(xQueueReceive(Action_Port,&res,portMAX_DELAY) == pdPASS)
		{
			touch_func = NULL;
			if(res == 1) 
			{
				vTaskResume(SnakeGame_Handle);
				vTaskSuspend(NULL);
			}
			else if(res == 2) 
			{
				vTaskResume(TetrisGame_Handle);
				vTaskSuspend(NULL);
			}			
		}
	}
}



/* User Code End Here ---------------------------------*/

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
