/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
	* @file    football.h
  * @author  LJY 2250017028@qq.com
  * @brief   Code for Football game.
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

#ifndef _FOOTBALL_H_
#define _FOOTBALL_H_

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
}
#endif	

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/  
#include "System_DataPool.h"
#include "text.h"
/* Private define ------------------------------------------------------------*/
#define NARMAL_SPEED 10
#define FAST_SPEED 5

// 挡板参数
#define BOARD_DWIDTH 	4
#define BOARD_DHEIGTH	12

// 足球参数
#define BALL_SIZE 7

// 游戏边界
#define LIMIT_UP 20
#define LIMIT_DOWN (240-5)
#define LIMIT_LEFT 5
#define LIMIT_RIGHT (320-5)
#define LIMIT_MID 160

// 碰壁类型
#define COLLISION_NULL 	0
#define COLLISION_UP 		1 
#define COLLISION_DOWN 	2 
#define COLLISION_LEFT 	3 
#define COLLISION_RIGHT 4 

// 球门参数
#define DOOR_UP 	100	// 上边界
#define DOOR_DOWN 140	// 下边界
/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/
typedef struct ball_t
{
	uint16_t loc[2];	// 球心位置x,y
	int	vel[2];				// 球运动速度
	uint16_t radius;	// 球半径
	uint8_t flag;			// 存活的标志位
}	ball;

typedef struct player_t
{
	uint16_t loc[2];	// 玩家挡板位置x,y
	float	vel;				// 挡板运动速度
	uint8_t index;		// 玩家编号
	uint8_t score;		// 得分
}	player;
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class Football
{
public:
	Football(){}
	~Football(){}
	void Game_Init(void);														// 游戏初始化 
	void Game_Update(void);													// 游戏界面更新	
	void GameOver_Interface(void);									// 游戏结束界面
	void GameStart_Interface(void);									// 游戏开始界面
	void Handle_Quit(void){over_flag = 3;}					// 手动退出
	void Set_Role_Location(int x, int y)
	{
		if(y > LIMIT_UP + BOARD_DHEIGTH && y < LIMIT_DOWN - BOARD_DHEIGTH)
		{
			if(x > LIMIT_LEFT + BOARD_DWIDTH && x < LIMIT_MID - BOARD_DWIDTH)
			{
				Player_XMove(1,x-role1.loc[0]);
				Player_YMove(1,y-role1.loc[1]);
			}
			else if(x > LIMIT_MID + BOARD_DWIDTH && x < LIMIT_RIGHT - BOARD_DWIDTH)
			{
				Player_XMove(2,x-role2.loc[0]);
				Player_YMove(2,y-role2.loc[1]);				
			}
		}
		
	}
		
	// 判断游戏是否结束 0 继续 1 结束
	uint8_t If_Over(void){return over_flag;}
		
	// 控制玩家运动 1 role1  2 role2
	void Player_XMove(uint8_t role, int dx)
	{
		if(role == 1) move1[0] = dx;
		else if(role == 2) move2[0] = dx;
	}
	void Player_YMove(uint8_t role, int dy)
	{
		if(role == 1) move1[1] = dy;
		else if(role == 2) move2[1] = dy;
	}	
private:
	
	/*====================================界面=======================================*/
	void Draw_Map(void);						// 绘制游戏画面
	void Draw_BackGround(void);			// 绘制游戏背景
	void Update_Score(void);				// 更新游戏分数
	void Draw_Player(player& role);	// 绘制玩家
	void Draw_Ball(ball& b);				// 绘制足球

	/*====================================逻辑=======================================*/
	void Ball_Sport(ball& b);				// 足球正常运动
	uint8_t Check_Scored(ball& b);	// 检测足球是否入洞,即一方得分
	uint8_t Collision_Detect(ball& b, int dx, int dy);						// 足球碰壁检测
	uint8_t Collision_Detect(player& role, int dis, uint8_t x_y);	// 玩家碰壁检测

	// 足球初始化
	void Ball_Init(ball& b)
	{
		// 存活标志
		b.flag = 1;
		// 半径
		b.radius = BALL_SIZE;
		
		// 位置
		b.loc[0] = 160; b.loc[1] = 120;
		
		// 速度
		b.vel[0] = (rand() % 2) ? 1 : (-1);
		b.vel[1] = (rand() % 2) ? 1 : (-1);
		b.vel[0] *= 6; b.vel[1] *= 6;
	}
	
	// 判断是否获胜 0 继续 1 玩家一获胜 2 玩家二获胜
	uint8_t Check_Vitory(void)
	{
		if(role1.score == 3)
		{
			over_flag = 1;
			return 1;
		}
		else if(role2.score == 3)
		{
			over_flag = 1;
			return 2;			
		}
		else return 0;
	}
	/*====================================交互=======================================*/
	void Player_Move(player& role);	// 控制某方玩家移动

	/*====================================变量=======================================*/
	ball b; // 足球
	player role1,role2;	// 玩家
	
	// 玩家的运动距离
	int move1[2] = {0, 0};
	int move2[2] = {0, 0};
	
	// 游戏结束标志
	uint8_t over_flag;
};

/* Exported variables --------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/

#endif	/* __cplusplus */

#endif	/* define */
	/************************ COPYRIGHT(C) TuTu Studio **************************/
