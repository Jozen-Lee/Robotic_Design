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
#define JOINTS_NUM 7	// 实际舵机数为6,这里是为了配合仿真
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
	// 初始化
	void Init(void);
	
	// 控制机械臂
	void Control_Manipulator(float* angles);
	void Control_Manipulator(float angle, uint8_t index);
private:
	
	// 数据传输串口
	UART_HandleTypeDef *huart;
															
	// 总的数据包(6个舵机)
	char data[DATA_SIZE*6+2];	

  // 状态存储
  float js[JOINTS_NUM];	

	// 控制单个舵机
	void Control_Single_Steering(float angle, uint8_t index);
		
	// 控制前n个舵机
	void Control_Steerings(float* angles, uint8_t n);
	
	// 打包函数
	void Pack(char* addr, float angle, uint8_t index);

	// 状态更新
	void Status_Update(float* sta)
	{
		for(int i = 0; i < JOINTS_NUM; i ++)
		{
			js[i] = sta[i];
		}
	}
	
	// 角度转换
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
