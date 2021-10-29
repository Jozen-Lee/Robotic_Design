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
      -# ��ʼ��
		 	
      -# �÷�,
				1. ��ѯ����
					ps2.UpdateData();
				2. ��ȡң��������
				
					// ��������:����ΪPS2_KEY_t����ֵ
					ps2.GetKeyData(KEY_START);
					
					// ҡ������:����ΪPS2_ROD_t����ֵ
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
    PSB_GREEN, //����   
    PSB_RED,   //Բ   
    PSB_BLUE,  //��   
    PSB_PINK   //��  
	};

PS2 ps2;
/* Private type --------------------------------------------------------------*/
/* Private function declarations ---------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
	
/**
	*@brief ��ʼ��
*/
void PS2::Init(void)
{ 
	ShortPoll(); 
	ShortPoll(); 
	ShortPoll(); 
	
	// ��������ģʽ
	EnterConfing(); 		
	
	// �����̵ơ�����ģʽ����ѡ���Ƿ񱣴� 
	TurnOnAnalogMode(); 
	
	// ������ģʽ
	VibrationMode(); 	

	// ��ɲ���������	
	ExitConfing(); 			
} 

/**
	*@brief ��ȡĳ����������
 */ 
PS2_States_t PS2::GetKeyData(PS2_KEY_t key)
{
	//����
	uint8_t index = key - 1;  

	//����16������,����Ϊ0,δ����Ϊ1
	Handkey=(Data[4]<<8)|Data[3];     
	if((Handkey&(1 <<(MASK[index]-1)))==0)
	{
		return PS2_PRESS;
	}
	else return PS2_LOOSE;          
}

/**
	*@brief �õ�ĳ��ҡ������
	*@note ��Χ0~256
 */ 	 
uint8_t PS2::GetRodData(PS2_ROD_t rod)
{
	return Data[rod];                 
}

/**
	*@brief �����ֱ�����
 */ 
void PS2::UpdateData(void)
{
	volatile uint8_t byte=0;
	volatile uint16_t ref=0x01;
	
	//�������
	ClearData();
	
	//ѡ������
	CS_L;
	
	//��ʼ����
	Cmd(Comd[0]);
	
	//��������  
	Cmd(Comd[1]);  

	//��ʼ��������
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
	*@brief ����ָ��
 */ 
void PS2::Cmd(uint8_t CMD)		  
{
	//ref=00000001
	volatile uint16_t ref=0x01;  
	Data[1] = 0;   
	
	// 00000001����>10000000
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
	*@brief �ж��Ƿ�Ϊ���ģʽ
	*@return 0 ���ģʽ 1 ����ģʽ
 */ 
uint8_t PS2::RedLight(void)
{
	CS_L;   
	Cmd(Comd[0]);  //��ʼ����
	Cmd(Comd[1]);  //��������
	CS_H;   
	if( Data[1] == 0X73) return 0;
	else return 1;

}

/**
	*@brief ������ݻ�����
 */ 	 
void PS2::ClearData()
{
	uint8_t a;
	for(a=0;a<9;a++)
		Data[a]=0x00;
}

/**
	*@brief �ֱ����ó�ʼ��
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
	*@brief ��������
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
	*@brief ����ģʽ����
 */
void PS2::TurnOnAnalogMode(void)
{ 
	CS_L; 
	Cmd(0x01);
	Cmd(0x44);
	Cmd(0X00); 
	
	//0x01���  0x00�̵�ģʽ
	Cmd(0x01);
	
	//Ox03 �������ã�������ͨ��������MODE ������ģʽ��
	//0xEE ������������ã���ͨ��������MODE ������ģʽ��
	Cmd(0xEE); 
								
	Cmd(0X00); 
	Cmd(0X00);
	Cmd(0X00); 
	Cmd(0X00); 
	CS_H;
	delay_us_nos(16); 
} 

/**
	*@brief ������
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
	*@brief ��ɲ���������
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
