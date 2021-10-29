#ifndef __TEXT_H__
#define __TEXT_H__	  

#include "stm32f4xx_hal.h" 
#include "lcd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������ 
//������ʾ ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
//�ֿ�����ʼ��ַ
#define FONTINFOADDR 	1024*1024*25
#define GBK12_SIZE 574560
#define GBK16_SIZE 766080
#define GBK24_SIZE 1723680
#define GBK32_SIZE 3064320

//�ֿ��ַ�ṹ��
__packed typedef struct 
{	 
	uint32_t f12addr;			//gbk12��ַ	
	uint32_t f16addr;			//gbk16��ַ	 
	uint32_t f24addr;			//gbk24��ַ
	uint32_t f32addr;			//gbk32��ַ
}_font_info; 

#ifdef  __cplusplus
extern "C"{
#endif

void Text_Init(void); 					     
void Get_HzMat(unsigned char *code,unsigned char *mat,uint8_t size);																				//�õ����ֵĵ�����
void Show_Font(uint16_t x,uint16_t y,uint8_t *font,uint8_t size,uint8_t mode);															//��ָ��λ����ʾһ������
void Show_Str(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t*str,uint8_t size,uint8_t mode);	//��ָ��λ����ʾһ���ַ��� 
void Show_Str_Mid(uint16_t x,uint16_t y,uint8_t*str,uint8_t size,uint8_t len);
	
#ifdef  __cplusplus
}
#endif

#endif
