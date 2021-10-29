/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
	* @file    App_Drawing.h
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

#ifndef __APP_DRAWING_H_
#define __APP_DRAWING_H_
#include "stm32f4xx.h"

#ifdef __cplusplus
 extern "C" {
#endif
void Start_Interface(void);
void GamesChoose_Interface(void); 
void OLED_DrawingArrow(uint8_t cmd);
#ifdef __cplusplus
}
#endif	


#endif	/* define */
	/************************ COPYRIGHT(C) TuTu Studio **************************/
