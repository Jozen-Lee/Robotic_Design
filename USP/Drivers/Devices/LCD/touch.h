#ifndef __TOUCH_H__
#define __TOUCH_H__
#include "stm32f4xx_hal.h"
//#include "ott2001a.h"	    
//#include "gt9147.h"	     
//#include "gt9271.h"	    
//#include "ft5206.h"	    
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//������������֧��ADS7843/7846/UH7843/7846/XPT2046/TSC2046/OTT2001A�ȣ� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/7/19
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									   
//********************************************************************************
//�޸�˵�� 
//V1.1 	20170606
//1��������GT9271����IC��֧��
//2��������10�㴥����֧��
////////////////////////////////////////////////////////////////////////////////// 


#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 
#define CT_MAX_TOUCH 10    //������֧�ֵĵ���,�̶�Ϊ5��

//������оƬ��������	   

//T_PEN
#define PEN_GPIO   GPIOH    
#define PEN_PIN		GPIO_PIN_7

//T_MISO
#define DOUT_GPIO   GPIOG  
#define DOUT_PIN		GPIO_PIN_3

//T_MOSI
#define TDIN_GPIO   GPIOI  
#define TDIN_PIN		GPIO_PIN_3

//T_SCK
#define TCLK_GPIO   GPIOH  
#define TCLK_PIN		GPIO_PIN_6

//T_CS 
#define TCS_GPIO   GPIOI  
#define TCS_PIN		GPIO_PIN_8 

//������������
typedef struct
{
	uint8_t (*init)(void);			//��ʼ��������������
	uint8_t (*scan)(uint8_t);		//ɨ�败����.0,��Ļɨ��;1,��������;	 
	void (*adjust)(void);				//������У׼ 
	uint16_t x[CT_MAX_TOUCH]; 	//��ǰ����
	uint16_t y[CT_MAX_TOUCH];		//�����������10������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								//x[9],y[9]�洢��һ�ΰ���ʱ������. 
	uint16_t sta;	//�ʵ�״̬ 
								//b15:����1/�ɿ�0; 
	              //b14:0,û�а�������;1,�а�������. 
								//b13~b10:����
								//b9~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)							
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
	uint8_t touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��  
   
#ifdef  __cplusplus
extern "C"{
#endif
	
//����������
void TP_Write_Byte(uint8_t num);						//�����оƬд��һ������
uint16_t TP_Read_AD(uint8_t CMD);							//��ȡADת��ֵ
uint16_t TP_Read_XOY(uint8_t xy);							//���˲��������ȡ(X/Y)
uint8_t TP_Read_XY(uint16_t *x,uint16_t *y);					//˫�����ȡ(X+Y)
uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y);					//����ǿ�˲���˫���������ȡ
void TP_Drow_Touch_Point(uint16_t x,uint16_t y,uint16_t color);//��һ������У׼��
void TP_Draw_Big_Point(uint16_t x,uint16_t y,uint16_t color);	//��һ�����
void TP_Save_Adjdata(void);						//����У׼����
uint8_t TP_Get_Adjdata(void);						//��ȡУ׼����
void TP_Adjust(void);							//������У׼
void TP_Adj_Info_Show(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t fac);//��ʾУ׼��Ϣ
//������/������ ���ú���
uint8_t TP_Scan(uint8_t tp);								//ɨ��
uint8_t TP_Init(void);								//��ʼ��
	
#ifdef __cplusplus
}
#endif	

#endif

















