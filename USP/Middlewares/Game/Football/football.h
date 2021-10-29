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

// �������
#define BOARD_DWIDTH 	4
#define BOARD_DHEIGTH	12

// �������
#define BALL_SIZE 7

// ��Ϸ�߽�
#define LIMIT_UP 20
#define LIMIT_DOWN (240-5)
#define LIMIT_LEFT 5
#define LIMIT_RIGHT (320-5)
#define LIMIT_MID 160

// ��������
#define COLLISION_NULL 	0
#define COLLISION_UP 		1 
#define COLLISION_DOWN 	2 
#define COLLISION_LEFT 	3 
#define COLLISION_RIGHT 4 

// ���Ų���
#define DOOR_UP 	100	// �ϱ߽�
#define DOOR_DOWN 140	// �±߽�
/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/
typedef struct ball_t
{
	uint16_t loc[2];	// ����λ��x,y
	int	vel[2];				// ���˶��ٶ�
	uint16_t radius;	// ��뾶
	uint8_t flag;			// ���ı�־λ
}	ball;

typedef struct player_t
{
	uint16_t loc[2];	// ��ҵ���λ��x,y
	float	vel;				// �����˶��ٶ�
	uint8_t index;		// ��ұ��
	uint8_t score;		// �÷�
}	player;
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class Football
{
public:
	Football(){}
	~Football(){}
	void Game_Init(void);														// ��Ϸ��ʼ�� 
	void Game_Update(void);													// ��Ϸ�������	
	void GameOver_Interface(void);									// ��Ϸ��������
	void GameStart_Interface(void);									// ��Ϸ��ʼ����
	void Handle_Quit(void){over_flag = 3;}					// �ֶ��˳�
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
		
	// �ж���Ϸ�Ƿ���� 0 ���� 1 ����
	uint8_t If_Over(void){return over_flag;}
		
	// ��������˶� 1 role1  2 role2
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
	
	/*====================================����=======================================*/
	void Draw_Map(void);						// ������Ϸ����
	void Draw_BackGround(void);			// ������Ϸ����
	void Update_Score(void);				// ������Ϸ����
	void Draw_Player(player& role);	// �������
	void Draw_Ball(ball& b);				// ��������

	/*====================================�߼�=======================================*/
	void Ball_Sport(ball& b);				// ���������˶�
	uint8_t Check_Scored(ball& b);	// ��������Ƿ��붴,��һ���÷�
	uint8_t Collision_Detect(ball& b, int dx, int dy);						// �������ڼ��
	uint8_t Collision_Detect(player& role, int dis, uint8_t x_y);	// ������ڼ��

	// �����ʼ��
	void Ball_Init(ball& b)
	{
		// ����־
		b.flag = 1;
		// �뾶
		b.radius = BALL_SIZE;
		
		// λ��
		b.loc[0] = 160; b.loc[1] = 120;
		
		// �ٶ�
		b.vel[0] = (rand() % 2) ? 1 : (-1);
		b.vel[1] = (rand() % 2) ? 1 : (-1);
		b.vel[0] *= 6; b.vel[1] *= 6;
	}
	
	// �ж��Ƿ��ʤ 0 ���� 1 ���һ��ʤ 2 ��Ҷ���ʤ
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
	/*====================================����=======================================*/
	void Player_Move(player& role);	// ����ĳ������ƶ�

	/*====================================����=======================================*/
	ball b; // ����
	player role1,role2;	// ���
	
	// ��ҵ��˶�����
	int move1[2] = {0, 0};
	int move2[2] = {0, 0};
	
	// ��Ϸ������־
	uint8_t over_flag;
};

/* Exported variables --------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/

#endif	/* __cplusplus */

#endif	/* define */
	/************************ COPYRIGHT(C) TuTu Studio **************************/
