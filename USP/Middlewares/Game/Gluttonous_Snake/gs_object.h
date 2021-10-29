/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
	* @file    snake.h
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
#ifndef __GS_OBJECT_H_
#define __GS_OBJECT_H_

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
}
#endif	

/* Includes ------------------------------------------------------------------*/  
#include "stm32f4xx_hal.h" 
#include "stdlib.h"
#include "lcd.h"

/* Private define ------------------------------------------------------------*/
//不同食物的得分
#define BLACK_GRADE  1
#define BROWN_GRADE  2
#define BLUE_GRADE   3
#define GREEN_GRADE  4
#define RED_GRADE    5

//蛇前进方向的定义
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4
#define MAX_LEN  500	//最大蛇身长度

/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/

#ifdef __cplusplus

// 蛇的状态信息
typedef struct
{
	uint16_t snake_x[MAX_LEN];	//蛇身的x坐标
	uint16_t snake_y[MAX_LEN];	//蛇身的y坐标
	uint8_t speed;						//速度
	uint8_t size;							//蛇的大小
	uint16_t node;						//蛇身的节数
	uint8_t direction; 				//蛇前进的方向
}snake_dev;	

// 食物的状态信息
typedef struct
{
	uint16_t food_x;		//食物的x坐标
	uint16_t food_y;		//食物的y坐标
	uint8_t food_flag;	//食物存在的标志
	uint16_t food_color;//食物的颜色,对应不同的分数
	uint8_t food_grade;	//食物对应的分数
} food_dev;

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class GS_Object
{
public:
	void Food_Appear(void);  					//显示食物的函数
	void Snake_Sport(void);  					//蛇运动的函数
	void Snake_Init(void);   					//蛇身初始化函数
	uint8_t EatFood_Check(void);  		//吃到食物的检测函数
	uint8_t TouchWall_Check(void);		//撞墙检测函数
	uint8_t GameOver_Check(void);     //游戏结束函数
	uint8_t EatSelf_Check(void);			//吃自己检测函数
	uint16_t Get_Current_Score(void){return current_score;}
	uint16_t Get_Target_Score(void){return target_score;}
	food_dev& Get_Food(void){return food;}
	snake_dev& Get_Snake(void){return snake;}
	uint16_t GetLevel(void){return speed_val[snake.speed];}
private:
	// 定义食物结构变量
	food_dev food;		

	// 定义蛇身结构变量
	snake_dev snake;	

	// 当前得分
	uint16_t current_score;

	// 下一关所需分数
	uint16_t target_score;

	// 游戏难度等级
	uint16_t speed_val[5] = {200, 150, 100, 50, 30};
};

/* Exported variables --------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/


#endif	/* __cplusplus */

#endif	/* define */

	/************************ COPYRIGHT(C) TuTu Studio **************************/
