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

#ifndef  __ps2_H_
#define  __ps2_H_

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
}
#endif	

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/  
#include "main.h"

/* Private define ------------------------------------------------------------*/

/*
	PC4-->DI
	PH13-->DO
	PH15-->CS
	PI1-->CLK
*/
#define DI    HAL_GPIO_ReadPin(PS2_DAT_GPIO_Port,PS2_DAT_Pin) 
#define DO_H  HAL_GPIO_WritePin(PS2_CMD_GPIO_Port,PS2_CMD_Pin,GPIO_PIN_SET)     
#define DO_L  HAL_GPIO_WritePin(PS2_CMD_GPIO_Port,PS2_CMD_Pin,GPIO_PIN_RESET)     
#define CS_H  HAL_GPIO_WritePin(PS2_CS_GPIO_Port,PS2_CS_Pin,GPIO_PIN_SET)      
#define CS_L  HAL_GPIO_WritePin(PS2_CS_GPIO_Port,PS2_CS_Pin,GPIO_PIN_RESET)     
#define CLK_H  HAL_GPIO_WritePin(PS2_CLK_GPIO_Port,PS2_CLK_Pin,GPIO_PIN_SET)   
#define CLK_L  HAL_GPIO_WritePin(PS2_CLK_GPIO_Port,PS2_CLK_Pin,GPIO_PIN_RESET)     

/*全部状态*/
#define PSB_SELECT     	1
#define PSB_L3          2
#define PSB_R3          3
#define PSB_START       4
#define PSB_PAD_UP      5
#define PSB_PAD_RIGHT   6
#define PSB_PAD_DOWN    7
#define PSB_PAD_LEFT    8
#define PSB_L2          9
#define PSB_R2          10
#define PSB_L1          11
#define PSB_R1          12
#define PSB_GREEN       13
#define PSB_RED         14
#define PSB_BLUE        15
#define PSB_PINK        16
#define PSB_TRIANGLE    13
#define PSB_CIRCLE      14
#define PSB_CROSS       15
#define PSB_SQUARE      26

#define PSS_RX          5       //右摇杆X轴
#define PSS_RY          6       //右摇杆Y轴
#define PSS_LX          7       //左摇杆X轴
#define PSS_LY          8       //左摇杆Y轴

//按键
typedef enum
{
	KEY_SELECT = PSB_SELECT,
	KEY_START = PSB_START,
	KEY_L1 = PSB_L1,            
	KEY_R1 = PSB_R1,
	KEY_L2 = PSB_L2,           
	KEY_R2 = PSB_R2, 
	KEY_L3 = PSB_L3,    
	KEY_R3 = PSB_R3,   
	KEY_PAD_UP = PSB_PAD_UP,
	KEY_PAD_DOWN = PSB_PAD_DOWN,
	KEY_PAD_LEFT = PSB_PAD_LEFT,
	KEY_PAD_RIGHT = PSB_PAD_RIGHT,	
	KEY_GREEN = PSB_GREEN, 	//三角   
	KEY_RED = PSB_RED,   		//圆   
	KEY_BLUE = PSB_BLUE,  	//叉   
	KEY_PINK = PSB_PINK,   	//粉 
}PS2_KEY_t;	

//摇杆
typedef enum
{
	ROD_RX = PSS_RX,
	ROD_RY = PSS_RY,
	ROD_LX = PSS_LX,
	ROD_LY = PSS_LY,
}PS2_ROD_t;


/*状态*/
typedef enum
{
	PS2_LOOSE,
	PS2_PRESS,
} PS2_States_t;
/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/
	
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class PS2
{
public:
	void Init(void);													// 手柄配置初始化
	void UpdateData(void); 										// 更新数据
	PS2_States_t GetKeyData(PS2_KEY_t key);		// 获取按键数据
	uint8_t GetRodData(PS2_ROD_t rod); 				// 获取摇杆数据
private:
	
	void Cmd(uint8_t CMD);				//发数据		  
	void ClearData(void);	  			//清除
	void ShortPoll(void);					//配置初始化
	void EnterConfing(void); 			//进入配置
	void TurnOnAnalogMode(void);	//发送模式设置
	void VibrationMode(void);			//振动设置
	void ExitConfing(void);				//完成并保存配置
	uint8_t RedLight(void);				//读ID

	uint16_t Handkey;

	// 数据存储数组
	uint8_t Data[9]; 

	//开始命令。请求数据（主机发送到手柄）
	uint8_t Comd[2]={0x01,0x42};	
};

/* Exported variables --------------------------------------------------------*/
extern PS2 ps2;

/* Exported function declarations --------------------------------------------*/

#endif	/* __cplusplus */

#endif	/* define */
	/************************ COPYRIGHT(C) TuTu Studio **************************/
