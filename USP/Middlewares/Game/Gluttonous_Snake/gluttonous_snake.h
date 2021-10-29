/**
  ******************************************************************************
  * Copyright (c) 2021 - ~, TuTu Studio
	* @file    gluttonous_snake.h
  * @author  LJY 2250017028@qq.com
  * @brief   Code for Gluttonous_Snake Game.
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

#ifndef _GLUTTONOUS_SNAKE_H_
#define _GLUTTONOUS_SNAKE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#ifdef __cplusplus
}
#endif	

#ifdef __cplusplus

/* Includes ------------------------------------------------------------------*/  
#include "stm32f4xx_hal.h" 
#include "gs_object.h"

/* Private define ------------------------------------------------------------*/
/* Private include -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
	 
/* Private type --------------------------------------------------------------*/
	
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
class Gluttonous_Snake
{
public:
	void Game_Introduction(void);
	void GameOver_Inf(void);
	void Game_Init(void);
	uint16_t Get_SnakeSpeed(void){return object.GetLevel();}
	void Snake_Sport(void)
	{
		object.Snake_Sport();
	}
	void Food_Update(void)
	{
		object.EatFood_Check();
		object.Food_Appear();
		Grade_Print();		
	}
	uint8_t Game_Over(void){return object.GameOver_Check();}
	
	// ”Œœ∑∂‘œÛ
	GS_Object object;
private:
	void Game_Map(void);
	void Font_Print(void);
	void Grade_Print(void);
	void Map_Init(void);
	
	void Beginning_Vedio(void);

};

/* Exported variables --------------------------------------------------------*/
/* Exported function declarations --------------------------------------------*/

#endif	/* __cplusplus */

#endif	/* define */
	/************************ COPYRIGHT(C) TuTu Studio **************************/



