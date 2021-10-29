/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
  * @file    gluttonous_snake.cpp
  * @author  LJY 2250017028@qq.com
  * @brief   Code for Gluttonous_Snake Game.
  * @date    2021-09-04
  * @version 1.0
  * @par Change Log:
  * <table>
  * <tr><th>Date        <th>Version  <th>Author     <th>Description
  * <tr><td>2021-09-04  <td> 1.0     <td>TuTu  			<td>Creator
  * </table>
  *
  ==============================================================================
                              How to use this driver  
  ==============================================================================
    @note
      -# 初始化
		 
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
#include "gluttonous_snake.h"
#include "lcd.h"
#include "text.h"
#include "touch.h"

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private type --------------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

//求m的n次方,n>=0
uint32_t To_decarate_Num(uint32_t m,uint8_t n)
{
	uint8_t i;
	uint32_t j=1;
	for(i=0;i<n;i++)
	{
		j*=m;
	}
	return j;
}

/**
 *@brief 贪吃蛇游戏页面
 */ 
void Gluttonous_Snake::Game_Map(void)
{
	//贪吃蛇主页面
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;
	LCD_DrawRectangle(1, 1, 180, 200);
//	LCD_DrawRectangle(2, 2, 179, 199);
	if(object.Get_Snake().size==2)
	{
		LCD_DrawLine(3,3,3,198);
		LCD_DrawLine(178,3,178,198);//为了检测方便,加多两列
	}
	if(object.Get_Snake().size==3)
	{
		LCD_DrawLine(3,3,179,3);
		LCD_Fill(3,3,5,199,BLACK);
		LCD_Fill(177,3,178,199,BLACK);	
	}
	if(object.Get_Snake().size==6)
	{
		LCD_Fill(3,3,180,5,BLACK);
		LCD_Fill(3,3,5,199,BLACK);
		LCD_Fill(3,198,180,199,BLACK);
	}
	
	//成绩打印框
	LCD_DrawRectangle(180, 1, 240, 100);
	LCD_DrawRectangle(181, 2, 239,  99);
	
	//速度打印框
	LCD_DrawRectangle(181, 99, 240,  200);
	LCD_DrawRectangle(180, 100, 239,  199);
	LCD_DrawRectangle(181, 199, 240,  320);
	
	//下一目标分数打印框
	LCD_DrawRectangle(180, 200, 239,  319);
	LCD_DrawRectangle(1, 199, 180,  320);
	
	//操作框
	LCD_DrawRectangle(2, 200, 179,  319);
	
	//操作按键
	LCD_Draw_Circle(90 ,230,25); 	//上键
	LCD_Draw_Circle(90,290,25); 	//下键
	LCD_Draw_Circle(40,260,25);		//左键
	LCD_Draw_Circle(140,260,25);	//右键
}

/**
 *@brief 文字打印
 */ 
void Gluttonous_Snake::Font_Print(void)
{
	//成绩框打印
	POINT_COLOR=BLUE;
 Show_Str(185,10,200,30,(uint8_t*)"成绩",24,0);
	POINT_COLOR=BLACK;
	LCD_DrawLine(181,50, 240, 50);
	POINT_COLOR=RED;
	LCD_ShowNum(190,67,object.Get_Current_Score(),3,16);
	
	//速度框打印
	POINT_COLOR=BLUE;
  Show_Str(185,110,200,30,(uint8_t*)"速度",24,0);
	POINT_COLOR=BLACK;
	LCD_DrawLine(181,150, 240, 150);
	POINT_COLOR=RED;
	LCD_ShowNum(195,167,object.Get_Snake().speed,2,16);
	
	//通关分数框打印
	POINT_COLOR=BLUE;
	Show_Str(195,210,200,16,(uint8_t*)"通关",16,0);
	Show_Str(195,230,200,16,(uint8_t*)"分数",16,0);
  POINT_COLOR=BLACK;
	LCD_DrawLine(181,250, 240, 250);
  LCD_DrawLine(181,275, 240, 275);
	POINT_COLOR=RED;
	LCD_ShowNum(190,255,object.Get_Target_Score(),3,16);
	
	//按键打印
  Show_Font(90-8,230-8,(uint8_t*)"上",16,0);
	Show_Font(90-8,290-8,(uint8_t*)"下",16,0);
	Show_Font(40-8,260-8,(uint8_t*)"左",16,0);
	Show_Font(140-8,260-8,(uint8_t*)"右",16,0);
}

/**
 *@brief 分数打印
 */ 
void Gluttonous_Snake::Grade_Print(void)
{
	POINT_COLOR=RED;
	LCD_ShowNum(190,67,object.Get_Current_Score(),3,16);
	LCD_ShowNum(195,167,object.Get_Snake().speed + 1,2,16);
	LCD_ShowNum(190,255,object.Get_Target_Score(),3,16);
}

/**
 *@brief 游戏界面初始化
 */ 
void Gluttonous_Snake::Map_Init(void)
{
	// 蛇体和食物初始化
	object.Snake_Init();
	
	// 游戏界面框图初始化
	Game_Map();
	
	// 界面文字初始化
	Font_Print();
}

/**
 *@brief 游戏说明
 */ 
void Gluttonous_Snake::Game_Introduction(void)
{
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;
	Show_Str(20,20,200,24,(uint8_t*)"关于食物:",24,0);
	Show_Str(20,48,200,32,(uint8_t*)"小蛇每吃4次食物,会出现一次加强食物",16,0);
	
	//BUFF说明
	LCD_Fill(20,90-4,20+8,90+4,BROWN);
	Show_Str(20+9,85,200,16,(uint8_t*)":加2分",16,0);
	LCD_Fill(20,110-4,20+8,110+4,BLUE);
	Show_Str(20+9,105,200,16,(uint8_t*)":加3分",16,0);
	LCD_Fill(20,130-4,20+8,130+4,GREEN);
	Show_Str(20+9,125,200,16,(uint8_t*)":加4分",16,0);
	LCD_Fill(20,150-4,20+8,150+4,RED);
	Show_Str(20+9,145,200,16,(uint8_t*)":加5分",16,0);
	
	
	Show_Str(20,180,200,24,(uint8_t*)"关于速度:",24,0);
	Show_Str(10,210,220,48,(uint8_t*)"小蛇的成绩每次高于通关分数,速度会加1,速度最大值为5",16,0);

	POINT_COLOR=RED;
	Show_Str_Mid(0,280-24,(uint8_t*)"GoGoGo!",24,240);
}

/**
 *@brief 游戏结束界面
 */ 
void Gluttonous_Snake::GameOver_Inf(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,80,(uint8_t*)"重新开始",24,240);	
	Show_Str_Mid(0,200,(uint8_t*)"返回",24,240);	
}

/**
 *@brief 游戏开始动画
 */ 
void Gluttonous_Snake::Beginning_Vedio(void)
{
	uint16_t i=0;
	uint16_t j=0;
	uint16_t k=0;
	uint16_t num;
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;
	LCD_ShowString(120-52,120,112,16,16,(uint8_t*)"Loading...00%");
	LCD_DrawRectangle(120-50,140,120+50,140+20);
  for(i=1;i<=80;i++)
	{
		//得到两位整数,且保证num<100
		num=i*100/81; 
		
		//进度条显示
	  LCD_Fill(120-50,140,120-50+num+1,140+20,BLACK);
		
		//数字显示
		for(j=0;j<2;j++)
		{
		  k=num/To_decarate_Num(10,1-j);
		  LCD_ShowNum(120-52+80+j*8,120,k,1,16);//依次显示十位,个位
			num-=k*To_decarate_Num(10,1-j);
		}
		HAL_Delay(100);
	}
	
	//100%进度显示
	LCD_ShowString(120-52,120,112,16,16,(uint8_t*)"Loading...100%");
  HAL_Delay(1000);
}

/**
 *@brief 游戏初始化
 */ 
void Gluttonous_Snake::Game_Init(void)
{
	// 改变随机种子
	srand(rand());
	
	// 加载动画
//	Beginning_Vedio();
	
	// 界面初始化
	Map_Init();
}

	/************************ COPYRIGHT(C) TuTu Studio **************************/
