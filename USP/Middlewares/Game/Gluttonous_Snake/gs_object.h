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
//��ͬʳ��ĵ÷�
#define BLACK_GRADE  1
#define BROWN_GRADE  2
#define BLUE_GRADE   3
#define GREEN_GRADE  4
#define RED_GRADE    5

//��ǰ������Ķ���
#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4
#define MAX_LEN  500	//���������

/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/

#ifdef __cplusplus

// �ߵ�״̬��Ϣ
typedef struct
{
	uint16_t snake_x[MAX_LEN];	//�����x����
	uint16_t snake_y[MAX_LEN];	//�����y����
	uint8_t speed;						//�ٶ�
	uint8_t size;							//�ߵĴ�С
	uint16_t node;						//����Ľ���
	uint8_t direction; 				//��ǰ���ķ���
}snake_dev;	

// ʳ���״̬��Ϣ
typedef struct
{
	uint16_t food_x;		//ʳ���x����
	uint16_t food_y;		//ʳ���y����
	uint8_t food_flag;	//ʳ����ڵı�־
	uint16_t food_color;//ʳ�����ɫ,��Ӧ��ͬ�ķ���
	uint8_t food_grade;	//ʳ���Ӧ�ķ���
} food_dev;

/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class GS_Object
{
public:
	void Food_Appear(void);  					//��ʾʳ��ĺ���
	void Snake_Sport(void);  					//���˶��ĺ���
	void Snake_Init(void);   					//�����ʼ������
	uint8_t EatFood_Check(void);  		//�Ե�ʳ��ļ�⺯��
	uint8_t TouchWall_Check(void);		//ײǽ��⺯��
	uint8_t GameOver_Check(void);     //��Ϸ��������
	uint8_t EatSelf_Check(void);			//���Լ���⺯��
	uint16_t Get_Current_Score(void){return current_score;}
	uint16_t Get_Target_Score(void){return target_score;}
	food_dev& Get_Food(void){return food;}
	snake_dev& Get_Snake(void){return snake;}
	uint16_t GetLevel(void){return speed_val[snake.speed];}
private:
	// ����ʳ��ṹ����
	food_dev food;		

	// ��������ṹ����
	snake_dev snake;	

	// ��ǰ�÷�
	uint16_t current_score;

	// ��һ���������
	uint16_t target_score;

	// ��Ϸ�Ѷȵȼ�
	uint16_t speed_val[5] = {200, 150, 100, 50, 30};
};

/* Exported variables --------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/


#endif	/* __cplusplus */

#endif	/* define */

	/************************ COPYRIGHT(C) TuTu Studio **************************/
