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

#ifndef __BUS_STEERING_H_
#define __BUS_STEERING_H_

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
}
#endif	

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/  
#include "stm32f4xx.h"

/* Private define ------------------------------------------------------------*/
#define DATA_SIZE 15		
#define JOINTS_NUM 7	// ʵ�ʶ����Ϊ6,������Ϊ����Ϸ���
#define FLOAT2PWM 5.55f
/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/
	
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class BusSteering
{
public:
	BusSteering(UART_HandleTypeDef* _huart) : huart(_huart){}
	~BusSteering(){}
	// ��ʼ��
	void Init(void);
	
	// ���ƻ�е��
	void Control_Manipulator(float* angles);
	void Control_Manipulator(float angle, uint8_t index);
private:
	
	// ���ݴ��䴮��
	UART_HandleTypeDef *huart;
															
	// �ܵ����ݰ�(6�����)
	char data[DATA_SIZE*6+2];	

  // ״̬�洢
  float js[JOINTS_NUM];	

	// ���Ƶ������
	void Control_Single_Steering(float angle, uint8_t index);
		
	// ����ǰn�����
	void Control_Steerings(float* angles, uint8_t n);
	
	// �������
	void Pack(char* addr, float angle, uint8_t index);

	// ״̬����
	void Status_Update(float* sta)
	{
		for(int i = 0; i < JOINTS_NUM; i ++)
		{
			js[i] = sta[i];
		}
	}
	
	// �Ƕ�ת��
	int Angle_Transform(float angle)
	{
		float pwm = angle * FLOAT2PWM;
		return (int)pwm;
	}
};

/* Exported variables --------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/

#endif	/* __cplusplus */

#endif	/* define */
	/************************ COPYRIGHT(C) TuTu Studio **************************/
