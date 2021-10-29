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

//���淽���״̬
typedef struct _Condition
{
	uint8_t num; 			 		//��ǰ�����˶��ķ���
	uint16_t color;				//������ɫ
	uint8_t pos_choice; 	//����̬��Ӧ�ı��
	uint32_t pos[32]; 		//�˶������Ӧ����̬
	int x;				 				//����ĺ�����
	int y;				 				//�����������
	uint8_t alive;			 	//0:ʧ�� 1:���
	
} Condition;	

#ifdef __cplusplus

class Tetris
{
public:
	// ��ʼ��
	void Init(void);

	// ���̺���
	void Progress(void);

	// ң�غ���
	void Action(uint8_t action);

	// �ж���Ϸ�Ƿ����
	uint8_t Game_Over(void);

	// ��ȡ�ٶ�
	uint16_t Get_Speed(void){return speed;}

	// ��Ϸ��ͼ����
	Tetris_Map map;
private:
	
	// ���Ʒ���
	void Draw_Tetris(const Condition& con, char mode, char place);

	// ���÷���
	void Reset_Tetris(void);
	
	// ���µ�ͼ
	void Update_Map(const Condition& con);

	// ��յ�ͼ
	void Clear_Map(int p[]);

	// ��������
	uint8_t Go_Down(void);
	
	// ������̬�任
	void Pos_Turn(void);

	// ���Ʒ��������ƶ�
	void Linear_Move(uint8_t dir);
	
	// �ж��Ƿ���������
	uint8_t Judge_Side(const Condition& con);
	
	// �ж��Ƿ������ײ�
	uint8_t Judge_Bottom(const Condition& con);
	
	// ���ֺ���
	uint8_t Game_Score(uint8_t num);
	
	// ������Ϸ��ʾ����
	void Update_GameShow(void);

	//���浱ǰ��״̬�ı���
	Condition con_old;
	Condition con_now;
	Condition con_next;
	uint16_t scores;
	uint8_t over;
	uint16_t speed;
	uint8_t speed_flag = 0;

	// ��Ϸ�ڲ���������
	Tetris_Object obj;
};

/* Exported variables --------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/

#endif	/* __cplusplus */

#endif	/* define */
	/************************ COPYRIGHT(C) TuTu Studio **************************/
