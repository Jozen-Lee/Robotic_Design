/**
  ******************************************************************************
  * @file   Service_Devices.h
  * @brief  Devices service running file.
  ******************************************************************************
  * @note
  *  - Before running your devices, just do what you want ~ !
  *  - More devices or using other classification is decided by yourself ~ !
 */
#ifndef  _APP_INTERFACE_H_
#define  _APP_INTERFACE_H_
/* Includes ------------------------------------------------------------------*/
#include "System_DataPool.h"

/* Private macros ------------------------------------------------------------*/
/* Private type --------------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern TaskHandle_t StartIF_Handle;
extern TaskHandle_t GamesIF_Handle;
#ifdef  __cplusplus

#endif

#ifdef  __cplusplus
extern "C"{
#endif

/* Exported function declarations --------------------------------------------*/
void App_Interface_Init(void);
  
#ifdef  __cplusplus
}
#endif

#endif  

/************************ COPYRIGHT(C) SCUT-ROBOTLAB **************************/

