/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
  * @file    ps2.cpp
  * @author  LJY 2250017028@qq.com
  * @brief   Code for .
  * @date    2021-10-05
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
		 	
      -# 用法,
				1. 轮询调用
					ps2.UpdateData();
				2. 读取遥控器数据
				
					// 按键数据:参数为PS2_KEY_t类型值
					ps2.GetKeyData(KEY_START);
					
					// 摇杆数据:参数为PS2_ROD_t类型值
					ps2.GetRodData(ROD_RX);
	  
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
#include "ps2.h"
#include "Drivers/Components/drv_timer.h"
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint16_t MASK[]={
    PSB_SELECT, 
    PSB_L3,      
    PSB_R3 ,     
    PSB_START,   
    PSB_PAD_UP,  
    PSB_PAD_RIGHT,
    PSB_PAD_DOWN,
    PSB_PAD_LEFT,
    PSB_L2,           
    PSB_R2,                   
    PSB_L1,            
    PSB_R1 ,           
    PSB_GREEN, //三角   
    PSB_RED,   //圆   
    PSB_BLUE,  //叉   
    PSB_PINK   //粉  
	};

PS2 ps2;
/* Private type --------------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
	
/**
	*@brief 初始化
*/
void PS2::Init(void)
{ 
	ShortPoll(); 
	ShortPoll(); 
	ShortPoll(); 
	
	// 进入配置模式
	EnterConfing(); 		
	
	// “红绿灯”配置模式，并选择是否保存 
	TurnOnAnalogMode(); 
	
	// 开启震动模式
	VibrationMode(); 	

	// 完成并保存配置	
	ExitConfing(); 			
} 

/**
	*@brief 获取某个按键数据
 */ 
PS2_States_t PS2::GetKeyData(PS2_KEY_t key)
{
	//按键
	uint8_t index = key - 1;  

	//这是16个按键,按下为0,未按下为1
	Handkey=(Data[4]<<8)|Data[3];     
	if((Handkey&(1 <<(MASK[index]-1)))==0)
	{
		return PS2_PRESS;
	}
	else return PS2_LOOSE;          
}

/**
	*@brief 得到某个摇杆数据
	*@note 范围0~256
 */ 	 
uint8_t PS2::GetRodData(PS2_ROD_t rod)
{
	return Data[rod];                 
}

/**
	*@brief 更新手柄数据
 */ 
void PS2::UpdateData(void)
{
	volatile uint8_t byte=0;
	volatile uint16_t ref=0x01;
	
	//清除数据
	ClearData();
	
	//选中器件
	CS_L;
	
	//开始命令
	Cmd(Comd[0]);
	
	//请求数据  
	Cmd(Comd[1]);  

	//开始接受数据
	for(byte=2;byte<9;byte++)          
	{
		for(ref=0x01;ref<0x100;ref<<=1)
		{
			CLK_H;
			CLK_L;
			delay_us_nos(10);
			CLK_H;
		  if(DI) Data[byte] = ref|Data[byte];
		}
    delay_us_nos(10);
	}
	CS_H;	
}

/**
	*@brief 发送指令
 */ 
void PS2::Cmd(uint8_t CMD)		  
{
	//ref=00000001
	volatile uint16_t ref=0x01;  
	Data[1] = 0;   
	
	// 00000001——>10000000
	for(ref=0x01;ref<0x0100;ref<<=1) 
	{
		if(ref&CMD)    
		{              
			DO_H;             
		}             
		else DO_L;    

		CLK_H;                 
		delay_us_nos(10);          
		CLK_L;                
		delay_us_nos(10);           
		CLK_H;         
		if(DI)
		{Data[1] = ref|Data[1];} 
	}
}
	
/**
	*@brief 判断是否为红灯模式
	*@return 0 红灯模式 1 正常模式
 */ 
uint8_t PS2::RedLight(void)
{
	CS_L;   
	Cmd(Comd[0]);  //开始命令
	Cmd(Comd[1]);  //请求数据
	CS_H;   
	if( Data[1] == 0X73) return 0;
	else return 1;

}

/**
	*@brief 清除数据缓冲区
 */ 	 
void PS2::ClearData()
{
	uint8_t a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}

/**
	*@brief 手柄配置初始化
 */ 	
void PS2::ShortPoll(void) 
{
	CS_L; delay_us_nos(16); 
  Cmd(0x01);
	Cmd(0x42);
  Cmd(0X00);
	Cmd(0x00);   
  Cmd(0x00); 
	CS_H;
  delay_us_nos(16); 
}

/**
	*@brief 进入配置
 */ 	
void PS2::EnterConfing(void) 
{ 
	CS_L;
	delay_us_nos(16);
	Cmd(0x01);
	Cmd(0x43);
	Cmd(0X00);
	Cmd(0x01); 
	Cmd(0x00); 
	Cmd(0X00);
	Cmd(0X00); 
	Cmd(0X00);
	Cmd(0X00);
	CS_H;
	delay_us_nos(16);
} 

/**
	*@brief 发送模式设置
 */
void PS2::TurnOnAnalogMode(void)
{ 
	CS_L; 
	Cmd(0x01);
	Cmd(0x44);
	Cmd(0X00); 
	
	//0x01红灯  0x00绿灯模式
	Cmd(0x01);
	
	//Ox03 锁存设置，即不可通过按键“MODE ”设置模式。
	//0xEE 不锁存软件设置，可通过按键“MODE ”设置模式。
	Cmd(0xEE); 
								
	Cmd(0X00); 
	Cmd(0X00);
	Cmd(0X00); 
	Cmd(0X00); 
	CS_H;
	delay_us_nos(16); 
} 

/**
	*@brief 振动设置
 */
void PS2::VibrationMode(void)
{ 
	CS_L; 
	delay_us_nos(16); 
	Cmd(0x01);
	Cmd(0x4D);
	Cmd(0X00);
	Cmd(0x00);
	Cmd(0X01);
	CS_H;
	delay_us_nos(16);
} 
	
/**
	*@brief 完成并保存配置
 */
void PS2::ExitConfing(void)
{
  CS_L; 
	delay_us_nos(16);
	Cmd(0x01); 
	Cmd(0x43); 
	Cmd(0X00);
	Cmd(0x00);
	Cmd(0x5A);
	Cmd(0x5A);
	Cmd(0x5A);
	Cmd(0x5A); 
	Cmd(0x5A);
	CS_H; 
	delay_us_nos(16);
}
	


							/************************ COPYRIGHT(C) TuTu Studio **************************/
