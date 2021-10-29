/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
  * @file    tetris.cpp
  * @author  LJY 2250017028@qq.com
  * @brief   Code for tetris game core code.
  * @date    2021-09-04
  * @version 1.0
  * @par Change Log:
  * <table>
  * <tr><th>Date        <th>Version  <th>Author     <th>Description
  * <tr><td>2021-10-08  <td> 1.0     <td>TuTu  			<td>Creator
  * </table>
  *
  ==============================================================================
                              How to use this driver  
  ==============================================================================
    @note
      -# ��ʼ��
		 
    @warning	
      -# 
	  
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
#include "tetris.h"
#include "tetris_map.h"
#include "tetris_object.h"
#include "stdlib.h"
#include "time.h"
#include "lcd.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private type --------------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *@brief ��ȡ��Χ[min, max]�����
 */ 
int Random(int min, int max)
{
	return (rand()%((max-min)+1) + min);
}

/**
 *@brief ��ȡ��Χ[min, max]�����
 */ 
uint16_t Get_Random_Color(void)
{
	uint8_t seed = rand() % 10;
	switch(seed)
	{
		case 0: return RED;
		case 1: return GREEN;
		case 2: return BLUE;
		case 3: return LIGHTGREEN;
		case 4: return GRAYBLUE;
		case 5: return GRED;
		case 6: return MAGENTA;
		case 7: return CYAN;
		case 8: return BROWN;
		case 9: return LIGHTBLUE;		
		default: return 0;
	}
}

/**
 *@brief ���ƶ���˹����
 *@param mode 0 ��� 1 ��ʾ
 *@param place 0 ��ʾ����Ϸ���� 1 ��ʾ����Ϣ����
 */ 
void Tetris::Draw_Tetris(const Condition& con, char mode, char place)
{
	uint8_t i, j;
	if(mode) POINT_COLOR = con.color;
	else POINT_COLOR = WHITE;
	uint32_t index;
	for(i=0;i<32;i++)
	{
		index = 0x80000000;
		for(j=0;j<32;j++)
		{
			if(con.pos[i] & index)
			{
				if(place) 
				{
					switch(con.num)
					{
						case 1:	 LCD_DrawPoint(100+102+j,50+18+i); break;					
						case 2:  LCD_DrawPoint(100+102+j,50+14+i); break;
						case 3:  LCD_DrawPoint(100+104+j,50+16+i); break;
						case 4:  LCD_DrawPoint(100+100+j,50+18+i); break;
						case 5:  LCD_DrawPoint(100+100+j,50+18+i); break;
						case 6:  LCD_DrawPoint(100+104+j,50+18+i); break;
						case 7:  LCD_DrawPoint(100+104+j,50+18+i); break;
					}	
				}
				else 
				{
					if(con.y+i >= 0) LCD_DrawPoint(con.x+j,con.y+i);
				}
			}
			index >>= 1;
		}
	}
}

/**
 *@brief ��Ϸ���̵������ƺ���
 */ 
void Tetris::Progress(void)
{
	// �������
	if(Go_Down()) 
	{
		// ���µ�ͼ
		Update_Map(con_now);		
	}	
	
	// ������Ϸ��ʾ����
	Update_GameShow();	
	
	// ���������
	if(con_now.alive == 0) scores += Game_Score(map.Check_Map());	
	
	// ���÷���״̬
	if(con_now.alive == 0) Reset_Tetris();
	

	
	// ���ټ��
	if(speed_flag) speed_flag --;
	else speed = SPEED_SLOW;
}

void Tetris::Action(uint8_t action)
{
	// ˮƽ�ƶ�
	if(action == TETRIS_RIGHT || action == TETRIS_LEFT) Linear_Move(action);
	
	// ��̬�任
	if(action == TETRIS_TURN) Pos_Turn();		
	
	// ����
	if(action == TETRIS_ACC) 
	{
		speed = SPEED_FAST; 
		speed_flag = 3;
	}
	
	// �˳�
	if(action == TETRIS_QUIT) over = 1;			
}

void Tetris::Init(void)
{
	scores = 0;
	over = 0;
	
	// �����ʼ��
	map.Init();
	
	// �����ʼ��
	Reset_Tetris(); 
	con_now = con_next;
	con_old = con_now;
	Reset_Tetris();
}

//���÷�����Ϣ
void Tetris::Reset_Tetris(void)
{
	int i;
	if(con_now.alive == 0) 
	{
		con_now = con_next;
		con_old = con_now;
	}
	con_next.alive = 1;
	con_next.num = Random(1,7); //�����÷�����ʽ
	con_next.x = 8 * Random(0, 16); // ��������ʼλ��
	con_next.y = -16;
	con_next.color = Get_Random_Color();
	switch(con_next.num)
	{
		case 1: con_next.pos_choice = 0;
						for(i=0;i<32;i++) con_next.pos[i] = obj.pos_1.shape[con_next.pos_choice][i];
						break;
		case 2: con_next.pos_choice = Random(0,1);
						for(i=0;i<32;i++) con_next.pos[i] = obj.pos_2.shape[con_next.pos_choice][i];
						break;
		case 3: con_next.pos_choice = Random(0,3);
						for(i=0;i<32;i++) con_next.pos[i] = obj.pos_3.shape[con_next.pos_choice][i];
						break;
		case 4: con_next.pos_choice = Random(0,3);
						for(i=0;i<32;i++) con_next.pos[i] = obj.pos_4.shape[con_next.pos_choice][i];
						break;
		case 5: con_next.pos_choice = Random(0,3);
						for(i=0;i<32;i++) con_next.pos[i] = obj.pos_5.shape[con_next.pos_choice][i];
						break;
		case 6: con_next.pos_choice = Random(0,1);
						for(i=0;i<32;i++) con_next.pos[i] = obj.pos_6.shape[con_next.pos_choice][i];
						break;
		case 7: con_next.pos_choice = Random(0,1);
						for(i=0;i<32;i++) con_next.pos[i] = obj.pos_7.shape[con_next.pos_choice][i];
						break;
	}
}

/**
 *@brief ���µ�ͼ����
 */ 
void Tetris::Update_Map(const Condition& con)
{
	int i, j;
	uint32_t index = 0x80000000;
	for(i=0;i<32;i++)
	{
		index = 0x80000000;
		for(j=0;j<32;j++)
		{
				if(con.pos[i] & index) 
				{
					if(con.y+i >=0)	map.Map[con.x+j][con.y+i] = 1;
				}
				index >>= 1;			
		}
	}
	
	// ���µ�ͼ��,�÷����Ī����
	con_now.alive = 0;	
}

//�������亯��
//0:����ɹ�
//1:����ʧ��
uint8_t Tetris::Go_Down(void)
{
//	uint32_t count = 0;
//	count = (count + 1) % speed;
//	if(!count) 
//	{
		con_now.y += 8;
		if(Judge_Bottom(con_now)) 
		{
			con_now.y -= 8;
			return 1;
		}
		else 
		{
			return 0;
		}
//	}
//	return 0;
}

/**
 *@brief ���Ʒ��������ƶ�
 *@param dir TETRIS_LEFT ���� TETRIS_RIGHT ����
 */ 
void Tetris::Linear_Move(uint8_t dir)
{
	// �����ƶ�
	if(dir == TETRIS_RIGHT) con_now.x += 8;
	else con_now.x -= 8;
	
	// ���ڴ���
	if(Judge_Side(con_now))
	{
		if(dir == TETRIS_RIGHT) con_now.x -= 8;
		else con_now.x += 8;
	}
}

/**
 *@brief ��̬ת������
 *@note �ú������б���,��ȷ����̬�任���е�ǰ������ִ�б任

 */ 
void Tetris::Pos_Turn(void)
{
	uint8_t i;
	Condition con;
	con = con_now;
	switch(con.num)
	{
		case 1: con.pos_choice = (con.pos_choice + 1)%1;
						for(i=0;i<32;i++) con.pos[i] = obj.pos_1.shape[con.pos_choice][i];
						break;
		case 2: con.pos_choice = (con.pos_choice + 1)%2;
						for(i=0;i<32;i++) con.pos[i] = obj.pos_2.shape[con.pos_choice][i];
						break;
		case 3: con.pos_choice = (con.pos_choice + 1)%4;
						for(i=0;i<32;i++) con.pos[i] = obj.pos_3.shape[con.pos_choice][i];
						break;
		case 4: con.pos_choice = (con.pos_choice + 1)%4;
						for(i=0;i<32;i++) con.pos[i] = obj.pos_4.shape[con.pos_choice][i];
						break;
		case 5: con.pos_choice = (con.pos_choice + 1)%4;
						for(i=0;i<32;i++) con.pos[i] = obj.pos_5.shape[con.pos_choice][i];
						break;
		case 6: con.pos_choice = (con.pos_choice + 1)%2;
						for(i=0;i<32;i++) con.pos[i] = obj.pos_6.shape[con.pos_choice][i];
						break;
		case 7: con.pos_choice = (con.pos_choice + 1)%2;
						for(i=0;i<32;i++) con.pos[i] = obj.pos_7.shape[con.pos_choice][i];
						break;
	}
	if((!Judge_Side(con)) && (!Judge_Bottom(con))) 
	{
		con_now = con;
		con_now.color = Get_Random_Color();
	}
}

/**
 *@brief ��������Ƿ�Խ��
 *@return 0 ��һ���˶�δ����
					1 ��һ���˶�����,�޷�����
 */ 
uint8_t Tetris::Judge_Side(const Condition& con)
{
	int i,j;
	uint32_t index = 0x80000000;
	for(i=0;i<32;i++)
	{
		index = 0x80000000;
		for(j=0;j<32;j++)
		{
			if(con.pos[i]&index)
			{
				if((map.Map[con.x + j][con.y + i]) || con.x + j > MAP_WIDTH || con.x + j < 0)
				{
					return 1;
				}
			}
			index >>= 1;
		}
	}
	return 0;
}

/**
 *@brief ����Ƿ������·�
 *@return 0 ��һ���˶�δ����
					1 ��һ���˶�����,�޷�����
 */ 
uint8_t Tetris::Judge_Bottom(const Condition& con)
{
	int i,j;
	uint32_t index = 0x80000000;
	for(i=0;i<32;i++)
	{
		index = 0x80000000;
		for(j=0;j<32;j++)
		{
			if((con.pos[i] & index) && (con.y+i>=0) && (map.Map[con.x+j][con.y+i] || (con.y + i >= MAP_HEIGTH)))
			{
				return 1;		
			}
			index >>= 1;
		}
	}
	return 0;
}
/**
 *@brief ���ֺ���
 */ 
uint8_t Tetris::Game_Score(uint8_t num)
{
	switch(num)
	{
		case 0: return 0;
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		default: return 0;
	}
}

/**
 *@brief ��Ϸ��������
 *@param 0 ��Ϸ����
				 1 ��Ϸ����
 */ 
uint8_t Tetris::Game_Over(void)
{
	int i;
	if(over) return 1;
	else if(Judge_Bottom(con_now) && con_now.y<0)
	{
		for(i=0;i<-con_now.y;i++)
		{
			if(con_now.pos[i]!=0) 
			{
				return 1;
			}
		}
		return 0;
	}
	return 0;
}

void Tetris::Update_GameShow(void)
{
//	// �����һ�εķ���
//	Draw_Tetris(con_old,0,0); 
	
	// ������Ϸ��ͼ
	map.Draw_GameMap();	
	
	// ���µ�ǰ�ķ���
	Draw_Tetris(con_now,1,0); 
		
	// ��ʾ����
	POINT_COLOR = BLACK;
	LCD_ShowNum(203,155,scores,2,24);
	
	// ��ʾ��һ��ͼ��
	if(con_now.alive == 0) Draw_Tetris(con_next, 0, 1); 
	else Draw_Tetris(con_next, 1, 1);
	
	// ��ʾ���, ����con_old
	con_old = con_now; 
}


									/************************ COPYRIGHT(C) TuTu Studio **************************/
