#ifndef __TEXT_H__
#define __TEXT_H__	  

#include "stm32f4xx_hal.h" 
#include "lcd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板 
//汉字显示 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
//字库存放起始地址
#define FONTINFOADDR 	1024*1024*25
#define GBK12_SIZE 574560
#define GBK16_SIZE 766080
#define GBK24_SIZE 1723680
#define GBK32_SIZE 3064320

//字库地址结构体
__packed typedef struct 
{	 
	uint32_t f12addr;			//gbk12地址	
	uint32_t f16addr;			//gbk16地址	 
	uint32_t f24addr;			//gbk24地址
	uint32_t f32addr;			//gbk32地址
}_font_info; 

#ifdef  __cplusplus
extern "C"{
#endif

void Text_Init(void); 					     
void Get_HzMat(unsigned char *code,unsigned char *mat,uint8_t size);																				//得到汉字的点阵码
void Show_Font(uint16_t x,uint16_t y,uint8_t *font,uint8_t size,uint8_t mode);															//在指定位置显示一个汉字
void Show_Str(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t*str,uint8_t size,uint8_t mode);	//在指定位置显示一个字符串 
void Show_Str_Mid(uint16_t x,uint16_t y,uint8_t*str,uint8_t size,uint8_t len);
	
#ifdef  __cplusplus
}
#endif

#endif
