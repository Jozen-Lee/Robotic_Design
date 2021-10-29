/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
  * @file    tetris_map.cpp
  * @author  LJY 2250017028@qq.com
  * @brief   Code for tetris map.
  * @date    2021-09-04
  * @version 1.0
  * @par Change Log:
  * <table>
  * <tr><th>Date        <th>Version  <th>Author     <th>Description
  * <tr><td>2021-10-08  <td> 1.0     <td>TuTu  			<td>Creator
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
#include "tetris_map.h"
#include "text.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private type --------------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
 *@brief 绘制游戏的交互界面
 */ 
void Tetris_Map::Draw_Interface(void)
{
	//贪吃蛇主页面
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;	
	LCD_Fill(176,0,180,200,BLACK);
	
	//下一个图案的打印框
	LCD_DrawRectangle(180, 1, 240, 100);
	LCD_DrawRectangle(181, 2, 239,  99);
	Show_Str_Mid(180,15,(uint8_t*)"下一个",16,60);
	LCD_DrawLine(180,40,240,40);
	
	//得分打印框
	LCD_DrawRectangle(181, 99, 240,  200);
	LCD_DrawRectangle(180, 100, 239,  199);
	LCD_DrawRectangle(180, 199, 240,  320);
	Show_Str_Mid(180,115,(uint8_t*)"得分",16,60);
	LCD_DrawLine(180,140,240,140);
	
	LCD_DrawRectangle(180, 280, 240,  320);
	Show_Str_Mid(180,290,(uint8_t*)"退出",16,60);
	
	
	//操作框
	LCD_DrawRectangle(0, 200, 179,  319);
	
	//操作按键
	POINT_COLOR = BLACK;
	LCD_Draw_Circle(35,260,25);		//左键
	LCD_Draw_Circle(145,260,25);	//右键
	LCD_DrawRectangle(70,250,110,280);
	Show_Font(30,250,(uint8_t*)"左",16,0);
	Show_Font(140,250,(uint8_t*)"右",16,0);
	Show_Font(85,260,(uint8_t*)"转",12,0);
}

/**
 *@brief 根据地图数组绘制游戏界面
 */ 
void Tetris_Map::Draw_GameMap(void)
{
	for(int i=0;i<MAP_WIDTH;i++)
	{
		for(int j=0;j<MAP_HEIGTH;j++)
		{
			if(Map[i][j]) 
			{
				POINT_COLOR = BLACK;
				LCD_DrawPoint(i,j);
			}
			else 
			{
				POINT_COLOR = WHITE;
				LCD_DrawPoint(i,j);
			}
		}
	}
}

/**
 *@brief 说明内容的显示
 */ 
void Tetris_Map::Inf_Show(void)
{
	LCD_Clear(WHITE);
	POINT_COLOR = BLUE;
	Show_Str_Mid(0,140,(uint8_t*)"欢迎进入", 24,240);
	Show_Str_Mid(0,180,(uint8_t*)"俄罗斯方块", 24,240);
	POINT_COLOR = RED;
	Show_Str_Mid(0,240,(uint8_t*)"GoGoGo!!", 16, 240);
}

/**
 *@brief 结束界面的绘制
 */ 
void Tetris_Map::Quit_Show(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,80,(uint8_t*)"重新开始",24,240);	
	Show_Str_Mid(0,200,(uint8_t*)"返回",24,240);	
}

/**
 *@brief 初始化地图数组
 */ 
void Tetris_Map::Init(void)
{
	int i, j;
	for(i=0;i<MAP_WIDTH;i++)
	{
		for(j=0;j<MAP_HEIGTH;j++)
		{
			Map[i][j] = 0;
		}
	}
	
	// 绘制交互界面
	Draw_Interface();
}

/**
 *@brief 方块消除
 *@param p 存储要消除的行的数组 
 */ 
void Tetris_Map::Tetris_Eliminate(int p[])
{
	int i,j,k;
	for(i=0;i<8;i++)
	{
		if(p[i]!=-1)
		{
			for(j=p[i]*8+7;j>=0;j--)
			{
				if(j>=8)
				{
					for(k=0;k<MAP_WIDTH;k++)
					{
						Map[k][j] = Map[k][j-8];
					}
				}
				else 
				{
					for(k=0;k<MAP_WIDTH;k++)
					{
						Map[k][j] = 0;
					}					
				}
			}
		}
	}
}

/**
 *@brief 检测界面是否需要消除某些行
 *@return 消除的行数
 */ 

uint8_t Tetris_Map::Check_Map(void)
{
	uint8_t check=0;
	int records[8] = {-1, -1, -1, -1, -1, -1, -1, -1};//记录需要清空的行
	uint8_t t=0;	
	uint8_t i, j;
	for(i=0;i<MAP_HEIGTH/8;i++)
	{
		for(j=0;j<MAP_WIDTH;j++)
		{
			if(Map[j][i*8]) check++;
			else break;
			if(check == MAP_WIDTH-1) 	records[t++] = i;
		}
		check = 0;
	}
	Tetris_Eliminate(records);
	return t;
}



	/************************ COPYRIGHT(C) TuTu Studio **************************/
