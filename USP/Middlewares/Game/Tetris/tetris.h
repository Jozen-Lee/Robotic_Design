/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
	* @file    .h
  * @author  LJY 2250017028@qq.com
  * @brief   Code for .
  ******************************************************************************
  * @attention
  * 
  * if you had modified this file, please make sure your code does not have many 
  * bugs, update the version Number, write dowm your name and the date, the most
  * important is make sure the users will have clear and definite understanding 
  * through your new brief.
  *
  * <h2><center>&copy; Copyright (c) 2021 - ~, TuTu Studio.
  * All rights reserved.</center></h2>
  ******************************************************************************
  */ 

#ifndef __TETRIS_H_
#define __TETRIS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
}
#endif	



/* Includes ------------------------------------------------------------------*/  
#include "stm32f4xx_hal.h"
#include "tetris_object.h"
#include "tetris_map.h"

/* Private define ------------------------------------------------------------*/
#define TETRIS_LEFT  	10	
#define TETRIS_RIGHT 	11
#define TETRIS_TURN 	12
#define TETRIS_ACC		13
#define TETRIS_QUIT 	14	

#define SPEED_SLOW 100
#define SPEED_FAST 30

/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

//储存方块的状态
typedef struct _Condition
{
	uint8_t num; 			 		//当前正在运动的方块
	uint16_t color;				//方块颜色
	uint8_t pos_choice; 	//该姿态对应的编号
	uint32_t pos[32]; 		//运动方块对应的姿态
	int x;				 				//方块的横坐标
	int y;				 				//方块的纵坐标
	uint8_t alive;			 	//0:失活 1:存活
	
} Condition;	

#ifdef __cplusplus

class Tetris
{
public:
	// 初始化
	void Init(void);

	// 进程函数
	void Progress(void);

	// 遥控函数
	void Action(uint8_t action);

	// 判断游戏是否结束
	uint8_t Game_Over(void);

	// 获取速度
	uint16_t Get_Speed(void){return speed;}

	// 游戏地图对象
	Tetris_Map map;
private:
	
	// 绘制方块
	void Draw_Tetris(const Condition& con, char mode, char place);

	// 重置方块
	void Reset_Tetris(void);
	
	// 更新地图
	void Update_Map(const Condition& con);

	// 清空地图
	void Clear_Map(int p[]);

	// 方块下落
	uint8_t Go_Down(void);
	
	// 方块姿态变换
	void Pos_Turn(void);

	// 控制方块左右移动
	void Linear_Move(uint8_t dir);
	
	// 判断是否左右碰壁
	uint8_t Judge_Side(const Condition& con);
	
	// 判断是否碰到底部
	uint8_t Judge_Bottom(const Condition& con);
	
	// 赋分函数
	uint8_t Game_Score(uint8_t num);
	
	// 更新游戏显示界面
	void Update_GameShow(void);

	//储存当前的状态的变量
	Condition con_old;
	Condition con_now;
	Condition con_next;
	uint16_t scores;
	uint8_t over;
	uint16_t speed;
	uint8_t speed_flag = 0;

	// 游戏内部操作对象
	Tetris_Object obj;
};

/* Exported variables --------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/

#endif	/* __cplusplus */

#endif	/* define */
	/************************ COPYRIGHT(C) TuTu Studio **************************/
