/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
  * @file    gs_object.cpp
  * @author  LJY 2250017028@qq.com
  * @brief   Code for .
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
#include "gs_object.h"

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private type --------------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

	/************************ COPYRIGHT(C) TuTu Studio **************************/

/**
 *@brief ��ʾʳ��ĺ��� 
 */ 
void GS_Object::Food_Appear(void)
{
	//ʳ�ﲻ���ڵ�ʱ������ʾ
	if(food.food_flag==0)
	{
		//����ѡ��ʳ������
		uint8_t food_choose;
		static uint8_t food_cnt=0;
		
		//��Ϸ����ʱ,����Ҫ��0
		if(current_score == 0) food_cnt=0;
			
		//�����������ʽnum=rand()%(n-m+1)+m,��Χ��[m,n]
		if(snake.size==2)
		{
			food.food_x=(unsigned)snake.size*(rand()%(88-2+1)+2);//[4,176]
			food.food_y=(unsigned)snake.size*(rand()%(99-2+1)+2);//[4,198]
		}
		else if(snake.size==3)
		{
			food.food_x=(unsigned)snake.size*(rand()%(58-2+1)+2);//[6,174]
			food.food_y=(unsigned)snake.size*(rand()%(66-2+1)+2);//[6,198]
		}	
		else if(snake.size==6)
		{
			food.food_x=(unsigned)snake.size*(rand()%(28-2+1)+2);//[12,168]
			food.food_y=(unsigned)snake.size*(rand()%(32-2+1)+2);//[12,192]			
		}
		
		//����ʳ�����ɫ�͵÷�
		food.food_color=BLACK;
		food.food_grade=BLACK_GRADE;
		food_cnt++;
		
		//����ʳ��BUFF
		if(food_cnt==5)
		{
			food_choose=rand()%(4-1+1)+1;
			switch(food_choose)
				{
				case 1:food.food_color=BROWN;
							 food.food_grade=BROWN_GRADE;
							 food_cnt=0;
							 break;
				case 2:food.food_color=BLUE;
							 food.food_grade=BLUE_GRADE;
							 food_cnt=0;
							 break;
				case 3:food.food_color=GREEN;
							 food.food_grade=GREEN_GRADE;
							 food_cnt=0;
							 break;
				case 4:food.food_color=RED;
							 food.food_grade=RED_GRADE;
							 food_cnt=0;
							 break;				
					
				} 
		 }
		
		//��ʾʳ��
		LCD_Fill(food.food_x,food.food_y,food.food_x+snake.size-1,food.food_y+snake.size-1,food.food_color);
	 
		//��־ʳ���Ѵ���
		food.food_flag = 1;
  }
}


/**
 *@brief ���˶����� 
 */ 
void GS_Object::Snake_Sport(void)
{
	uint16_t i;
	static uint8_t last_direction=RIGHT;
	
	//���β������β��
	if(EatFood_Check())
	{
		//����Ե���ʳ��,����β��
		LCD_Fill(food.food_x,food.food_y,food.food_x+snake.size-1,food.food_y+snake.size-1,WHITE);
	}
	else  
	{
		//���β��
		LCD_Fill(snake.snake_x[snake.node-1],snake.snake_y[snake.node-1],
		snake.snake_x[snake.node-1]+snake.size-1,snake.snake_y[snake.node-1]+snake.size-1,WHITE);	
	}
 //ȷ���ƶ���������������
	for(i=1;i<snake.node;i++)
	{
		snake.snake_x[snake.node-i]=snake.snake_x[snake.node-1-i];
		snake.snake_y[snake.node-i]=snake.snake_y[snake.node-1-i];		
	}
	
//ȷ��ͷ���µ�����
	switch(snake.direction)
		{
			case UP :
				if(last_direction!=DOWN)
				{
					snake.snake_y[0]-=snake.size;
					last_direction=UP;
				}
				else snake.snake_y[0]+=snake.size;
				break;
	
			case DOWN :
				if(last_direction!=UP)
				{
					snake.snake_y[0]+=snake.size;
					last_direction=DOWN;
				}
				else snake.snake_y[0]-=snake.size;
				break;
	
			case LEFT :
				if(last_direction!=RIGHT)
				{
					snake.snake_x[0]-=snake.size;
					last_direction=LEFT;
				}
				else snake.snake_x[0]+=snake.size;
				break;
	
			case RIGHT :
				if(last_direction!=LEFT)
				{
					snake.snake_x[0]+=snake.size;
					last_direction=RIGHT;
				}
				else snake.snake_x[0]-=snake.size;
				break;
		}
		
	// �����ƶ������
	for(i=0;i<snake.node;i++)
	{
		LCD_Fill(snake.snake_x[i],snake.snake_y[i],snake.snake_x[i]+snake.size-1,snake.snake_y[i]+snake.size-1,BLACK);
	}
}



/**
 *@brief ��ʼ������
 */ 
void GS_Object::Snake_Init(void)
{
	// ����Ϣ��ʼ��
	snake.node=3;
	snake.size=6;
	snake.speed=0;
	snake.snake_x[0]=48;snake.snake_x[1]=snake.snake_x[0]-snake.size;snake.snake_x[2]=snake.snake_x[0]-2*snake.size;
	snake.snake_y[0]=48;snake.snake_y[1]=snake.snake_y[0];snake.snake_y[2]=snake.snake_x[0]-2*snake.size;
	snake.direction=RIGHT;
	
	// ʳ����Ϣ��ʼ��
	food.food_flag=0;
	
	// ������Ϣ��ʼ��
	current_score=0;
	target_score=3;
}


/**
 *@brief С�߳�ʳ��ļ��
 */ 
uint8_t GS_Object::EatFood_Check(void)
{
	uint8_t i;
	uint16_t check_x;
	uint16_t check_y;
		for(i=0;i<snake.node;i++)
		{
			check_x=snake.snake_x[i]-food.food_x;
			check_y=snake.snake_y[i]-food.food_y;
			
			//���Ե�ʳ��
			if(check_x == 0 && check_y == 0)  
			{
				//��־ʳ�ﲻ������
				food.food_flag = 0;
				
				//����Ľ�����һ
				snake.node++;	

				//��������
				current_score += food.food_grade;
				
				//�ﵽ��һ�ؿ�������
				if(snake.speed < 5 && current_score >= target_score)  
				{
					target_score += 5;
					if(snake.speed < 4) snake.speed ++;
				}
				return 1;
			}
			
		}
 
	 return 0;
}

/**
 *@brief ײǽ��⺯��
 */ 
uint8_t GS_Object::TouchWall_Check(void)
{
	if(snake.size==2)
	{
	if(snake.snake_x[0]<4||snake.snake_x[0]>176||snake.snake_y[0]<4||snake.snake_y[0]>198)
		return 1;
  }
	else if(snake.size==3)
	{
	if(snake.snake_x[0]<6||snake.snake_x[0]>174||snake.snake_y[0]<6||snake.snake_y[0]>198)
		return 1;
  }
	else if(snake.size==6)
	{
	if(snake.snake_x[0]<6||snake.snake_x[0]>174||snake.snake_y[0]<6||snake.snake_y[0]>192)
		return 1;
  }
	return 0;
}

/**
 *@brief ���Լ���⺯��
 */ 
uint8_t GS_Object::EatSelf_Check(void)
{
	uint16_t i;
	uint8_t check_x;
	uint8_t check_y;
	if(snake.node>3)
		{
	    for(i=0;i<snake.node-1;i++)
	     {
		     check_x=snake.snake_x[0]-snake.snake_x[i+1];
		     check_y=snake.snake_y[0]-snake.snake_y[i+1];
			   if(check_x==0&&check_y==0) return 1;
			 }
	  }
	return 0;
}


/**
 *@brief ��Ϸ��������
 */ 
uint8_t GS_Object::GameOver_Check(void)
{
	//������Ϸ����
	if(EatSelf_Check()||TouchWall_Check())
	{
	  return 1;
	}
	else return 0;
}










