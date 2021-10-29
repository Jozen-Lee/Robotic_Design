/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
	* @file    tetris_map.h
  * @author  LJY 2250017028@qq.com
  * @brief   Code for tetris map.
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

#ifndef __TETRIS__MAP_H_
#define __TETRIS__MAP_H_

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
}
#endif	

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/  
#include "stm32f4xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define MAP_WIDTH 176
#define MAP_HEIGTH 200

/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/
	
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class Tetris_Map
{
public:
	void Init(void);
	void Draw_GameMap(void);
	void Inf_Show(void);
	void Quit_Show(void);
	uint8_t Check_Map(void);

	//µØÍ¼Êý×é 
	uint16_t Map[MAP_WIDTH][MAP_HEIGTH];
private:
	void Tetris_Eliminate(int p[]);
	void Draw_Interface(void);


};

/* Exported variables --------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/

#endif	/* __cplusplus */

#endif	/* define */

	/************************ COPYRIGHT(C) TuTu Studio **************************/
