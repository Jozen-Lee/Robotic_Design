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
#include "App_Game.h"
#include "App_Drawing.h"
#include "App_Interface.h"
#include "Service_Devices.h"
#include "gluttonous_snake.h"
#include "tetris.h"
#include "football.h"
#include "ps2.h"
#include "touch.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

// 贪吃蛇
Gluttonous_Snake snake;
TaskHandle_t SnakeGame_Handle;
TaskHandle_t SnakeFood_Handle;
TaskHandle_t SnakeSport_Handle;
TaskHandle_t SnakeOver_Handle;
TaskHandle_t SnakeCtrl_Handle;

// 俄罗斯方块
Tetris tetris;
TaskHandle_t TetrisGame_Handle;
TaskHandle_t TetrisProgress_Handle;
TaskHandle_t TetrisOver_Handle;
TaskHandle_t TetrisCtrl_Handle;

// 双人足球
Football football;
TaskHandle_t FootballGame_Handle;
TaskHandle_t Role1Ctrl_Handle;
TaskHandle_t Role2Ctrl_Handle;
TaskHandle_t FootballProgress_Handle;
TaskHandle_t FootballOver_Handle;

/* Private function declarations ---------------------------------------------*/

// 贪吃蛇
void Game_Snake(void *arg);
void Snake_Food(void *arg);
void Snake_Sport(void *arg);
void Snake_Over(void *arg);
void Snake_Ctrl(void *arg);

// 俄罗斯方块
void Game_Tetris(void *arg);
void Tetris_Progress(void *arg);
void Tetris_Ctrl(void *arg);
void Tetris_Over(void *arg);

// 双人足球
void Game_Football(void *arg);
void Role1_Ctrl(void *arg);
void Role2_Ctrl(void *arg);
void Football_Progress(void *arg);
void Football_Over(void *arg);

/* Exported devices ----------------------------------------------------------*/
/* Motor & ESC & Other actuators*/
/* Remote control */
uint8_t CTRL_MODE = SINGLE_MODE;
/* IMU & NUC & Other sensors */

/* Other boards */

/* Function prototypes -------------------------------------------------------*/
/**
* @brief  Initialization of game
* @param  None.
* @return None.
*/
void App_Games_Init(void)
{
	// 贪吃蛇
	xTaskCreate(Game_Snake,							"Game.Snake", 				Large_Stack_Size,    	NULL, PriorityHigh, 			 &SnakeGame_Handle);
	xTaskCreate(Snake_Food,							"Snake.Food", 				Small_Stack_Size,     NULL, PriorityHigh, 			 &SnakeFood_Handle);
	xTaskCreate(Snake_Sport,						"Snake.Sport", 				Small_Stack_Size,     NULL, PriorityHigh, 			 &SnakeSport_Handle);
	xTaskCreate(Snake_Over,							"Snake.Over", 				Small_Stack_Size,     NULL, PriorityHigh, 			 &SnakeOver_Handle);	
	xTaskCreate(Snake_Ctrl,							"Snake.Ctrl", 				Small_Stack_Size,     NULL, PriorityHigh, 			 &SnakeCtrl_Handle);
	
	// 俄罗斯方块
	xTaskCreate(Game_Tetris,						"Game.Tetris", 			Small_Stack_Size,    NULL, PriorityHigh, 			 &TetrisGame_Handle);
	xTaskCreate(Tetris_Progress,				"Tetris.Progress", 	Small_Stack_Size,    NULL, PriorityHigh, 			 &TetrisProgress_Handle);
	xTaskCreate(Tetris_Over,						"Tetris.Over", 			Small_Stack_Size,    NULL, PriorityHigh, 			 &TetrisOver_Handle);
	xTaskCreate(Tetris_Ctrl,						"Tetris.Ctrl", 			Small_Stack_Size,    NULL, PriorityHigh, 			 &TetrisCtrl_Handle);
	
	// 双人足球
	xTaskCreate(Game_Football,					"Game.Football", 			Small_Stack_Size,    NULL, PriorityHigh, 			 &FootballGame_Handle);
	xTaskCreate(Role1_Ctrl,							"Football.Role1", 		Small_Stack_Size,    NULL, PriorityHigh, 			 &Role1Ctrl_Handle);
	xTaskCreate(Role2_Ctrl,							"Football.Role2", 		Small_Stack_Size,    NULL, PriorityHigh, 			 &Role2Ctrl_Handle);
	xTaskCreate(Football_Over,					"Football.Over", 			Small_Stack_Size,    NULL, PriorityHigh, 			 &FootballOver_Handle);
	xTaskCreate(Football_Progress,			"Football.Progress", 	Small_Stack_Size,    NULL, PriorityHigh, 			 &FootballProgress_Handle);
	
	// 任务全挂起
	vTaskSuspend(SnakeGame_Handle); 
	vTaskSuspend(SnakeFood_Handle); 
	vTaskSuspend(SnakeSport_Handle);
	vTaskSuspend(SnakeOver_Handle);
	vTaskSuspend(SnakeCtrl_Handle);
	
	vTaskSuspend(TetrisGame_Handle);
	vTaskSuspend(TetrisProgress_Handle);
	vTaskSuspend(TetrisOver_Handle);
	vTaskSuspend(TetrisCtrl_Handle);

	vTaskSuspend(FootballGame_Handle);
	vTaskSuspend(Role1Ctrl_Handle);
	vTaskSuspend(Role2Ctrl_Handle);
	vTaskSuspend(FootballOver_Handle);
	vTaskSuspend(FootballProgress_Handle);
}

/* =============================================== 贪吃蛇 =============================================== */
/**
 *@brief 贪吃蛇控制任务
 */ 
void Snake_Ctrl(void *arg)
{
  /* Cache for Task */
  /* Pre-Load for task */
	uint8_t cmd;
  /* Infinite loop */
  for(;;)
  {
		if(xQueueReceive(Ctrl_Port,&cmd,portMAX_DELAY) == pdPASS)
		{
			if(cmd == DIR_UP || cmd == DIR_DOWN || cmd == DIR_LEFT || cmd == DIR_RIGHT)		
			{
				snake.object.Get_Snake().direction = cmd;
			}
			OLED_DrawingArrow(cmd);
		}
	}	
}

/**
 *@brief 贪吃蛇说明界面的触屏函数
 */ 
uint8_t Snake_ID_Touch(void)
{
	// 扫描触屏按键
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)
	{
		 if(tp_dev.x[0]>(120-60)&&tp_dev.x[0]<(120+60)&&tp_dev.y[0]>(280-15)&&tp_dev.y[0]<(280+15))
		 {
				return 1;
		 }
		 else return 0;
	}
	else return 0;
}

/**
 *@brief 贪吃蛇游戏运行界面的触屏函数
 */ 
uint8_t Snake_Processing_Touch(void)
{ 
	tp_dev.scan(0); 
	uint8_t cmd;
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{	
		if(tp_dev.x[0]>(90-25)&&tp_dev.x[0]<(90+25)&&tp_dev.y[0]>(230-25)&&tp_dev.y[0]<(230+25))
		{	
			cmd = DIR_UP;
			xQueueSend(Ctrl_Port, &cmd, 0);
		} 
		if(tp_dev.x[0]>(90-25)&&tp_dev.x[0]<(90+25)&&tp_dev.y[0]>(290-25)&&tp_dev.y[0]<(290+25))
		{	
			cmd = DIR_DOWN;
			xQueueSend(Ctrl_Port, &cmd, 0);	
		}
		if(tp_dev.x[0]>(40-25)&&tp_dev.x[0]<(40+25)&&tp_dev.y[0]>(260-25)&&tp_dev.y[0]<(260+25))
		{	
			cmd = DIR_LEFT;
			xQueueSend(Ctrl_Port, &cmd, 0);			
		} 
		if(tp_dev.x[0]>(140-25)&&tp_dev.x[0]<(140+25)&&tp_dev.y[0]>(260-25)&&tp_dev.y[0]<(260+25))
		{	
			cmd = DIR_RIGHT;
			xQueueSend(Ctrl_Port, &cmd, 0);			
		}  			
	}
	return 0;
}

/**
 *@brief 贪吃蛇结束界面的触屏函数
 */ 
uint8_t SnakeOver_Touch(void)
{
	// 扫描触屏按键
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)
	{
		 // 重新开始
		 if(tp_dev.x[0]>40&&tp_dev.x[0]<200&&tp_dev.y[0]>80&&tp_dev.y[0]<110)
		 {
				return 1;
		 }
		 // 返回
		 else if(tp_dev.x[0]>40&&tp_dev.x[0]<200&&tp_dev.y[0]>200&&tp_dev.y[0]<230)
		 {
			 return 2;
		 }
		 else return 0;
	}
	else return 0;
}

/**
 *@brief 贪吃蛇游戏任务
 */ 
void Game_Snake(void *arg)
{
  /* Cache for Task */
	
  /* Pre-Load for task */
	uint8_t res;
  /* Infinite loop */
  for(;;)
  {
		// 单人模式
		CTRL_MODE = SINGLE_MODE;
		
		// 说明界面
		snake.Game_Introduction();
		HAL_Delay(500);
		touch_func = Snake_ID_Touch;
		
		// 等待
		xQueueReceive(Action_Port,&res,portMAX_DELAY);
		
		// 游戏初始化
		touch_func = Snake_Processing_Touch;
		snake.Game_Init();
		vTaskResume(SnakeFood_Handle);
		vTaskResume(SnakeSport_Handle);
		vTaskResume(SnakeOver_Handle);
		vTaskResume(SnakeCtrl_Handle);
		
		if(xQueueReceive(Action_Port,&res,portMAX_DELAY) == pdPASS)
		{
			if(res == GAME_OVER) 
			{
				vTaskSuspend(SnakeFood_Handle);
				vTaskSuspend(SnakeSport_Handle);
				vTaskSuspend(SnakeCtrl_Handle);
				vTaskSuspend(NULL);
			}
		}
	}
}

/**
 *@brief 贪吃蛇游戏中的食物更新任务
 */ 
void Snake_Food(void *arg)
{
  /* Cache for Task */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(100);
  /* Pre-Load for task */
  /* Infinite loop */
  for(;;)
  {
		snake.Food_Update();
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);	
	}	
}

/**
 *@brief 贪吃蛇游戏中的小蛇移动任务
 */ 
void Snake_Sport(void *arg)
{
  /* Cache for Task */
  /* Pre-Load for task */
	TickType_t _xTicksToWait;
  /* Infinite loop */
  for(;;)
  {
		_xTicksToWait = snake.Get_SnakeSpeed();
		snake.Snake_Sport();
		vTaskDelay(_xTicksToWait);
	}	
}

/**
 *@brief 贪吃蛇游戏中的游戏结束任务
 */ 
void Snake_Over(void *arg)
{
  /* Cache for Task */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(50);
  /* Pre-Load for task */
		uint8_t over;
  /* Infinite loop */
  for(;;)
  {
		if(snake.Game_Over()) 
		{
			// 终止游戏
			over = GAME_OVER;
			xQueueSend(Action_Port, &over, 0);
			vTaskDelay(200);
			
			// 游戏结束界面
			snake.GameOver_Inf();
			HAL_Delay(500);
			touch_func = SnakeOver_Touch;
			if(xQueueReceive(Action_Port,&over,portMAX_DELAY) == pdPASS)
			{
				touch_func = NULL;
				if(over == 1) vTaskResume(SnakeGame_Handle);
				else if(over == 2) vTaskResume(GamesIF_Handle);
				vTaskSuspend(NULL);
			}
		}
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);	
	}	
}


/* =============================================== 俄罗斯方块 =============================================== */

/**
 *@brief 俄罗斯方块说明界面的触屏函数
 */ 
uint8_t Tetris_ID_Touch(void)
{
	// 扫描触屏按键
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)
	{
		 if(tp_dev.x[0]>(120-60)&&tp_dev.x[0]<(120+60)&&tp_dev.y[0]>(240)&&tp_dev.y[0]<(280))
		 {
				return 1;
		 }
		 else return 0;
	}
	else return 0;
}

/**
 *@brief 贪吃蛇游戏运行界面的触屏函数
 */ 
uint8_t Tetris_Processing_Touch(void)
{ 
	tp_dev.scan(0); 
	uint8_t cmd;
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{	
		if(tp_dev.x[0]>(35-25)&&tp_dev.x[0]<(35+25)&&tp_dev.y[0]>(260-25)&&tp_dev.y[0]<(260+25))
		{	
			cmd = DIR_LEFT;
			xQueueSend(Ctrl_Port, &cmd, 0);			
		} 
		if(tp_dev.x[0]>(140-25)&&tp_dev.x[0]<(140+25)&&tp_dev.y[0]>(260-25)&&tp_dev.y[0]<(260+25))
		{	
			cmd = DIR_RIGHT;
			xQueueSend(Ctrl_Port, &cmd, 0);			
		}  	
		if(tp_dev.x[0]>70&&tp_dev.x[0]<110&&tp_dev.y[0]>250&&tp_dev.y[0]<280)
		{	
			cmd = DIR_UP;
			xQueueSend(Ctrl_Port, &cmd, 0);			
		} 		
		if(tp_dev.x[0]>200&&tp_dev.x[0]<240&&tp_dev.y[0]>290&&tp_dev.y[0]<320)
		{	
			tetris.Action(TETRIS_QUIT);
		} 		
	}
	return 0;
}

/**
 *@brief 俄罗斯方块结束界面的触屏函数
 */ 
uint8_t TetrisOver_Touch(void)
{
	// 扫描触屏按键
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)
	{
		 // 重新开始
		 if(tp_dev.x[0]>40&&tp_dev.x[0]<200&&tp_dev.y[0]>80&&tp_dev.y[0]<110)
		 {
				return 1;
		 }
		 // 返回
		 else if(tp_dev.x[0]>40&&tp_dev.x[0]<200&&tp_dev.y[0]>200&&tp_dev.y[0]<230)
		 {
			 return 2;
		 }
		 else return 0;
	}
	else return 0;
}

/**
 *@brief 俄罗斯方块主任务
 */ 
void Game_Tetris(void *arg)
{
  /* Cache for Task */
  /* Pre-Load for task */
	uint8_t res;
  /* Infinite loop */
  for(;;)
  {
		// 单人模式
		CTRL_MODE = SINGLE_MODE;
		
		// 说明界面
		tetris.map.Inf_Show();
		HAL_Delay(500);
		touch_func = Tetris_ID_Touch;
		
		// 等待
		xQueueReceive(Action_Port,&res,portMAX_DELAY);
		
		// 游戏初始化
		touch_func = Tetris_Processing_Touch;
		tetris.Init();
		vTaskResume(TetrisCtrl_Handle);
		vTaskResume(TetrisProgress_Handle);
		vTaskResume(TetrisOver_Handle);

		// 等待游戏结束
		if(xQueueReceive(Action_Port,&res,portMAX_DELAY) == pdPASS)
		{
			if(res == GAME_OVER) 
			{
				vTaskSuspend(TetrisCtrl_Handle);
				vTaskSuspend(TetrisProgress_Handle);
				vTaskSuspend(NULL);
			}
		}
		tetris.Progress();
		vTaskDelay(100);	
	}
}

/**
 *@brief 俄罗斯方块控制任务
 */ 
void Tetris_Ctrl(void *arg)
{
  /* Cache for Task */
  /* Pre-Load for task */
	uint8_t cmd;
  /* Infinite loop */
  for(;;)
  {
		if(xQueueReceive(Ctrl_Port,&cmd,portMAX_DELAY) == pdPASS)
		{
			switch(cmd)
			{
				case DIR_RIGHT: tetris.Action(TETRIS_RIGHT); 	break;
				case DIR_LEFT: tetris.Action(TETRIS_LEFT); 		break;
				case DIR_UP: tetris.Action(TETRIS_TURN); 			break;
				case DIR_DOWN: tetris.Action(TETRIS_ACC); 		break;
			}
		}
		OLED_DrawingArrow(cmd);
	}	
}

/**
 *@brief 俄罗斯方块中的进程任务
 */ 
void Tetris_Progress(void *arg)
{
  /* Cache for Task */
  /* Pre-Load for task */
	
  /* Infinite loop */
  for(;;)
  {
		tetris.Progress();
		vTaskDelay(tetris.Get_Speed());	
	}	
}

/**
 *@brief 俄罗斯方块中的游戏结束任务
 */ 
void Tetris_Over(void *arg)
{
  /* Cache for Task */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(50);
  /* Pre-Load for task */
		uint8_t over;
  /* Infinite loop */
  for(;;)
  {
		if(tetris.Game_Over()) 
		{
			// 终止游戏
			over = GAME_OVER;
			xQueueSend(Action_Port, &over, 0);
			vTaskDelay(200);
			
			// 游戏结束界面
			tetris.map.Quit_Show();
			HAL_Delay(500);
			touch_func = SnakeOver_Touch;
			if(xQueueReceive(Action_Port,&over,portMAX_DELAY) == pdPASS)
			{
				touch_func = NULL;
				if(over == 1) vTaskResume(TetrisGame_Handle);
				else if(over == 2) vTaskResume(GamesIF_Handle);
				vTaskSuspend(NULL);
			}
		}
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);	
	}	
}

/* =============================================== 双人足球 =============================================== */

/**
 *@brief 双人足球说明界面的触屏函数
 */ 
uint8_t Football_ID_Touch(void)
{
	// 扫描触屏按键
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)
	{
		uint16_t y = tp_dev.x[0]; 
		uint16_t x = 320 - tp_dev.y[0];
		
	  if(x > 40 && x < 240 && y > 160 && y < 220)
		{
			return 1;
		}
		else return 0;
	}
	else return 0;
}

/**
 *@brief 双人足球结束界面的触屏函数
 */ 
uint8_t FootballOver_Touch(void)
{
	// 扫描触屏按键
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)
	{
		uint16_t y = tp_dev.x[0]; 
		uint16_t x = 320 - tp_dev.y[0];

		// 重新开始
		if(x > 40 && x < 200 && y > 80 && y < 110)
		{
			return 1;
		}

		// 返回
		else if(x > 40 && x < 200 && y > 200 && y < 230)
		{
			return 2;
		}
		else return 0;
	}
	else return 0;
}

/**
 *@brief 双人足球游戏运行界面的触屏函数
 */ 
uint8_t Football_Processing_Touch(void)
{ 
	tp_dev.scan(0); 
	if(tp_dev.sta&TP_PRES_DOWN)	// 触摸屏被按下
	{			
		uint16_t y = tp_dev.x[0]; 
		uint16_t x = 320 - tp_dev.y[0];
		
		// 控制玩家移动
		football.Set_Role_Location(x, y);
		
		if(x > 140 && x < 180 && y > 0 && y < 20)
		{	
			football.Handle_Quit();
		} 		
	}
	return 0;
}

/**
 *@brief 双人足球游戏的主任务
 */ 
void Game_Football(void *arg)
{
  /* Cache for Task */
	
  /* Pre-Load for task */
	uint8_t res;
	
  /* Infinite loop */
  for(;;)
  {
		// 双人模式
		CTRL_MODE = DOUBLE_MODE;
		
		// 切换横屏
		LCD_Display_Dir(1);	
		
		// 说明界面
		football.GameStart_Interface();
		HAL_Delay(500);
		touch_func = Football_ID_Touch;
		
		// 等待
		xQueueReceive(Action_Port,&res,portMAX_DELAY);
		
		// 游戏初始化
		
		touch_func = Football_Processing_Touch;
		football.Game_Init();
		vTaskResume(Role1Ctrl_Handle);
		vTaskResume(Role2Ctrl_Handle);
		vTaskResume(FootballOver_Handle);
		vTaskResume(FootballProgress_Handle);
		
		// 等待游戏结束
		if(xQueueReceive(Action_Port,&res,portMAX_DELAY) == pdPASS)
		{
			if(res == GAME_OVER) 
			{
				vTaskSuspend(Role1Ctrl_Handle);
				vTaskSuspend(Role2Ctrl_Handle);
				vTaskSuspend(FootballProgress_Handle);
				vTaskSuspend(NULL);
			}
		}
		vTaskDelay(100);	
	}
}

/**
 *@brief 双人足球游戏的控制任务
 */ 
void Role1_Ctrl(void *arg)
{
  /* Cache for Task */
	
  /* Pre-Load for task */
	uint8_t cmd;
	const uint8_t role = 1;
	int vel = 3;
  /* Infinite loop */
  for(;;)
  {
		if(xQueueReceive(Role1_Port,&cmd,portMAX_DELAY) == pdPASS)
		{
			switch(cmd)
			{
				case DIR_UP: 		football.Player_YMove(role, -vel); 		break;
				case DIR_DOWN: 	football.Player_YMove(role, vel); 		break; 
				case DIR_LEFT: 	football.Player_XMove(role, -vel); 		break;
				case DIR_RIGHT: football.Player_XMove(role, vel); 		break;
				default: break;
			}
		}
	}	
}

/**
 *@brief 双人足球游戏的控制任务
 */ 
void Role2_Ctrl(void *arg)
{
  /* Cache for Task */
	
  /* Pre-Load for task */
	uint8_t cmd;
	const uint8_t role = 2;
	int vel = 12;
  /* Infinite loop */
  for(;;)
  {
		if(xQueueReceive(Role2_Port,&cmd,portMAX_DELAY) == pdPASS)
		{
			switch(cmd)
			{
				case DIR_UP: 		football.Player_YMove(role, -vel); 		break;
				case DIR_DOWN: 	football.Player_YMove(role, vel); 		break; 
				case DIR_LEFT: 	football.Player_XMove(role, -vel); 		break;
				case DIR_RIGHT: football.Player_XMove(role, vel); 		break;
				default: break;
			}
		}
	}	
}

/**
 *@brief 双人足球界面刷新任务
 */ 
void Football_Progress(void *arg)
{
  /* Cache for Task */
	TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(30);
	
  /* Pre-Load for task */

  /* Infinite loop */
  for(;;)
  {
		vTaskDelay(_xTicksToWait);
		football.Game_Update();
	}	
}

/**
 *@brief 双人足球的游戏结束任务
 */ 
void Football_Over(void *arg)
{
  /* Cache for Task */
  TickType_t xLastWakeTime_t = xTaskGetTickCount();
	TickType_t _xTicksToWait = pdMS_TO_TICKS(50);
  /* Pre-Load for task */
	uint8_t over;
  /* Infinite loop */
  for(;;)
  {
		if(football.If_Over()) 
		{
			// 终止游戏
			over = GAME_OVER;
			xQueueSend(Action_Port, &over, 0);
			vTaskDelay(200);
			
			// 游戏结束界面
			football.GameOver_Interface();
			HAL_Delay(500);
			touch_func = FootballOver_Touch;
			if(xQueueReceive(Action_Port,&over,portMAX_DELAY) == pdPASS)
			{
				touch_func = NULL;
				if(over == 1) vTaskResume(FootballGame_Handle);
				else if(over == 2) vTaskResume(GamesIF_Handle);
				LCD_Display_Dir(0);	// 恢复竖屏
				vTaskSuspend(NULL);
			}
		}
		vTaskDelayUntil(&xLastWakeTime_t, _xTicksToWait);	
	}	
}

/* User Code End Here ---------------------------------*/

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/
