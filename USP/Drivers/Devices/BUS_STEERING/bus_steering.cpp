/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
  * @file    .cpp
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
#include "bus_steering.h"
#include "usart.h"
#include <stdio.h>
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private type --------------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/**
*@brief 位置初始化,即让机械臂运动到竖直状态
 */ 
void BusSteering::Init(void)
{
	// 状态初始化
	for(int i = 0; i < JOINTS_NUM; i ++) js[i] = 0;
	
	// 控制机械臂
	Control_Manipulator(js);
}

/**
*@brief 控制机械臂到指定位置
 */ 
void BusSteering::Control_Manipulator(float* angles)
{
	Control_Steerings(angles,6);
}

/**
*@brief 控制机械臂到指定位置
 */ 
void BusSteering::Control_Manipulator(float angle, uint8_t index)
{
	Control_Single_Steering(angle,index);
}

/**
*@brief 控制多个舵机
 */ 
void BusSteering::Control_Steerings(float* angles, uint8_t n)
{
	data[0] = '{';
	for(int i = 0; i < n; i ++)
	{
		Pack(data+1+i*DATA_SIZE,angles[i],i);
	}
	data[n*DATA_SIZE+1] = '}';
	HAL_UART_Transmit_DMA(huart, (uint8_t*)data, DATA_SIZE*n+2);
}

/**
*@brief 控制单个舵机
 */ 
void BusSteering::Control_Single_Steering(float angle, uint8_t index)
{
	Pack(data,angle,index);
	HAL_UART_Transmit_DMA(huart, (uint8_t*)data, DATA_SIZE);
}

/**
*@brief 打包函数
*@note 通信协议
				#000P1500T1000! 000表示舵机号,1500表示占空比(500-2500),1000表示速度,不用改
 */ 
void BusSteering::Pack(char* addr, float angle, uint8_t index)
{
	// 角度转换
	int _angle = Angle_Transform(angle);

	// 数据打包
	addr[0] = '#';
	sprintf(addr+1,"%03dP%04dT1000!",index,_angle);
}

	/************************ COPYRIGHT(C) TuTu Studio **************************/
