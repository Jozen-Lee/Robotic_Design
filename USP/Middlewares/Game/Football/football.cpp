/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
  * @file    football.cpp
  * @author  LJY 2250017028@qq.com
  * @brief   Code for Football game.
  * @date    2021-10-20
  * @version 1.0
  * @par Change Log:
  * <table>
  * <tr><th>Date        <th>Version  <th>Author     <th>Description
  * <tr><td>2021-09-04  <td> 1.0     <td>TuTu  			<td>Creator
  * </table>
  *
  ==============================================================================
  ******************************************************************************
  * @attention
  * 
  * if you had modified this file, please make sure your code does not have many 
  * bugs, update the version Number, write dowm your name and the date, the most
  * important is make sure the users will have clear and definite understanding 
  * through your new brief.
  *
  * <h2><center>&copy; Copyright (c) 2021 - ~,TuTu Studio.
  * All rights reserved.</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "football.h"
#include "main.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private type --------------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *@brief ��Ϸ��ʼ����
 */ 
void Football::GameStart_Interface(void)
{
	LCD_Clear(WHITE);
	POINT_COLOR = BLUE;
	Show_Str_Mid(40,60,(uint8_t*)"��ӭ����", 24,240);
	Show_Str_Mid(40,120,(uint8_t*)"˫������", 32,240);
	POINT_COLOR = RED;
	Show_Str_Mid(40,180,(uint8_t*)"GoGoGo!!", 16, 240);	
}

/**
 *@brief ��Ϸ��������
 */ 
void Football::GameOver_Interface(void)
{
	LCD_Clear(BLACK);
	if(over_flag == 1) 
	{
		POINT_COLOR=YELLOW;
		Show_Str_Mid(40,80,(uint8_t*)"���һʤ��!",24,240);	
		HAL_Delay(2000);
	}
	else if(over_flag == 2) 
	{
		POINT_COLOR=YELLOW;
		Show_Str_Mid(40,80,(uint8_t*)"��Ҷ�ʤ��!",24,240);	
		HAL_Delay(2000);
	}
	POINT_COLOR=WHITE;
	LCD_Clear(BLACK);
	Show_Str_Mid(40,100,(uint8_t*)"���¿�ʼ",24,240);	
	Show_Str_Mid(40,180,(uint8_t*)"����",24,240);			
}

/**
 *@brief ������Ϸ���廭��
 */ 
void Football::Game_Init(void)
{
	// ��Ϸ��ʼ
	over_flag = 0;
	
	// ������ʼ��
	role1.index = 1; role1.score = 0;
	role2.index = 2; role2.score = 0;

	// ���λ�ó�ʼ��
	role1.loc[0] = 80; role1.loc[1] = 120; 
	role2.loc[0] = 240; role2.loc[1] = 120; 
	
	// ����
	Ball_Init(b);
	
	// �����������
	Draw_Map();
	
	// ���Ʊ���
	Draw_BackGround();
	
	// ���·���
	Update_Score();
	
	// �������
	Draw_Player(role1);
	Draw_Player(role2);
	
	// ������
	Draw_Ball(b);
}

/**
 *@brief ��Ϸ����
 */ 
void Football::Game_Update(void)
{
	if(!over_flag)
	{
		// �����
		if(!b.flag)
		{
			// ���·���
			Update_Score();
			Ball_Init(b);
		}
		
		// ���±���
		Draw_BackGround();
		
		// ����ƶ�
		Player_Move(role1);
		Player_Move(role2);
		
		// �����ƶ�
		Ball_Sport(b);
		
		// �������
		Draw_Player(role1);
		Draw_Player(role2);
		
		// ��������
		Draw_Ball(b);
		
		// �����Ϸʤ��
		over_flag = Check_Vitory();
	}
}

/**
 *@brief ������Ϸ���廭��
 */ 
void Football::Draw_Map(void)
{
	// �߽�
	POINT_COLOR = BLACK;
	for(int i = 0; i <= 5; i++)
	LCD_DrawRectangle(i,i,320-i,240-i);
	LCD_Fill(0,0,320,20,POINT_COLOR);
	
	// �Ʒֱ�
	POINT_COLOR = BLACK;
	LCD_Fill(140,0,180,18,WHITE);
	LCD_DrawRectangle(140,0,180,18);
	LCD_ShowChar(160-4,2,':',16,0);	
	
	// ����
	POINT_COLOR = WHITE;
	LCD_Fill(0,100,5,140,POINT_COLOR);
	LCD_Fill(320-5,100,320,140,POINT_COLOR);
}

/**
 *@brief ���Ʊ���
 */ 
void Football::Draw_BackGround(void)
{
	POINT_COLOR = BLACK;
	LCD_DrawLine(160,20+1,160,240-5-1);
	LCD_Fill(5+1,20+1,160-1,240-5-1,RED);
	LCD_Fill(160+1,20+1,320-5-1,240-5-1,BLUE);
}

/**
 *@brief ���·���
 */ 
void Football::Update_Score(void)
{
	POINT_COLOR = BLACK;
	// ���һ
	LCD_ShowNum(144,2,role1.score,1,16);
	
	// ��Ҷ�
	LCD_ShowNum(168,2,role2.score,1,16);
}

/**
 *@brief �������
 */ 
void Football::Draw_Player(player& role)
{
	POINT_COLOR = YELLOW;
	// ����
	LCD_DrawLine(role.loc[0], 21, role.loc[0], 240-6);
	
	// ����
	LCD_Fill(role.loc[0]-BOARD_DWIDTH, role.loc[1]-BOARD_DHEIGTH,role.loc[0]+BOARD_DWIDTH,role.loc[1]+BOARD_DHEIGTH, POINT_COLOR);
}

/**
 *@brief ��������
 */ 
void Football::Draw_Ball(ball& b)
{
	POINT_COLOR = WHITE;
	for(int i = 1; i <= b.radius; i ++)
	{
		LCD_Draw_Circle(b.loc[0],b.loc[1],i);
	}
}

/**
 *@brief �������ڼ��,���صķ�λ�������������Ե�
 */ 
uint8_t Football::Collision_Detect(ball& b, int dx, int dy)
{
	player* p;
	float x_new = b.loc[0] + dx;
	float y_new = b.loc[1] + dy;
	
	// �߽���
	if(x_new - b.radius <= LIMIT_LEFT) 	return COLLISION_LEFT;
	if(x_new + b.radius >= LIMIT_RIGHT) 	return COLLISION_RIGHT;
	if(y_new - b.radius <= LIMIT_UP) 		return COLLISION_UP;
	if(y_new + b.radius >= LIMIT_DOWN) 	return COLLISION_DOWN;	
	
	// ��������
	for(int i = 0; i < 2; i ++)
	{
		p = i ? &role2 : & role1;
		if(y_new <= p->loc[1] + BOARD_DHEIGTH && y_new >= p->loc[1] - BOARD_DHEIGTH)
		{
			if(dx > 0 && x_new < p->loc[0] && x_new + b.radius >= p->loc[0] - BOARD_DWIDTH) return COLLISION_RIGHT;
			if(dx < 0 && x_new > p->loc[0] && x_new - b.radius <= p->loc[0] + BOARD_DWIDTH) return COLLISION_LEFT;
		}
		if(x_new <= p->loc[0] + BOARD_DWIDTH && x_new >= p->loc[0] - BOARD_DWIDTH)
		{
			if(dy > 0 && y_new < p->loc[1] && y_new + b.radius >= p->loc[1] - BOARD_DHEIGTH) return COLLISION_DOWN;
			if(dy < 0 && y_new > p->loc[1] && y_new - b.radius <= p->loc[1] + BOARD_DHEIGTH) return COLLISION_UP;			
		}
	}
	return COLLISION_NULL;
}

/**
 *@brief ������ڼ�� 0 δ���� 1 ����
 *@param dis �˶�����
 *@param x_y 0 ���x����, 1 ���y����
 */ 
uint8_t Football::Collision_Detect(player& role, int dis, uint8_t x_y)
{
	int loc_new;
	if(!x_y) 
	{
		loc_new = role.loc[0] + dis;
		if(role.index == 1 && (loc_new - BOARD_DWIDTH <= LIMIT_LEFT || loc_new + BOARD_DWIDTH >= LIMIT_MID)) return 1;
		else if(role.index == 2 && (loc_new - BOARD_DWIDTH <= LIMIT_MID || loc_new + BOARD_DWIDTH >= LIMIT_RIGHT)) return 1;
		else return 0;
	}
	else 
	{
		loc_new = role.loc[1] + dis;
		if(loc_new - BOARD_DHEIGTH <= LIMIT_UP || loc_new + BOARD_DHEIGTH >= LIMIT_DOWN) 
		{
			return 1;
		}
		else return 0;
	}
}

/**
 *@brief �����˶�
 */ 
void Football::Ball_Sport(ball& b)
{
	uint8_t check;
	int dx,dy;
	for(int i = 0; i < abs(b.vel[0]); i ++)
	{
		// λ��΢��
		dx = b.vel[0] > 0 ? 1 : (-1);
		dy = b.vel[1] > 0 ? 1 : (-1);
		check = Collision_Detect(b,dx,dy);
		if(check == COLLISION_NULL) 
		{
			b.loc[0] += dx; 
			b.loc[1] += dy;
			
			// �жϵ÷�
			if(Check_Scored(b)) return;
		}
		else
		{
			switch(check)
			{
				case COLLISION_LEFT: 	b.vel[0] = abs(b.vel[0]); return;
				case COLLISION_RIGHT: b.vel[0] = -abs(b.vel[0]); return;
				case COLLISION_UP: 		b.vel[1] = abs(b.vel[1]); return;
				case COLLISION_DOWN: 	b.vel[1] = -abs(b.vel[1]); return;
			}
		}
	}
}

/**
 *@brief ����˶�
 */ 
void Football::Player_Move(player& role)
{
	int dx, dy;
	int _dx, _dy;
	if(role.index == 1)
	{
		dx = move1[0]; dy = move1[1];
		move1[0] = 0; move1[1] = 0;
	}
	else if(role.index == 2)
	{
		dx = move2[0]; dy = move2[1];
		move2[0] = 0; move2[1] = 0;		
	}
	else return;
	
	
	// λ��΢��
	_dx = dx > 0 ? 1 : (-1);
	for(int i = 0; i < abs(dx); i ++)
	{
		if(!Collision_Detect(role,_dx,0)) 
		{
			role.loc[0] += _dx;
		}
	}	
	_dy = dy > 0 ? 1 : (-1);
	for(int i = 0; i < abs(dy); i ++)
	{
		if(!Collision_Detect(role,_dy,1)) 
		{
			role.loc[1] += _dy;
		}
	}	
}

/**
 *@brief �����Ϸʤ��
 *@note 0 ��Ϸ���� 1 ���һ�÷� 2 ��Ҷ��÷�
 */ 
uint8_t Football::Check_Scored(ball& b)
{
	if(b.loc[1] > DOOR_UP && b.loc[1] < DOOR_DOWN)
	{
		if(b.loc[0] - b.radius == LIMIT_LEFT+1) 
		{
			b.flag = 0;
			role2.score += 1;
			return 1;
		}			
		else if(b.loc[0] + b.radius == LIMIT_RIGHT-1)
		{
			b.flag = 0;
			role1.score += 1;
			return 2;
		}
		else return 0;
	}
	else return 0;
}



	/************************ COPYRIGHT(C) TuTu Studio **************************/
