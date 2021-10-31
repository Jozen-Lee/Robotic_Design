#ifndef __ROS_CONNECT_H_
#define __ROS_CONNECT_H_

#include <stm32f4xx.h>
uint8_t UnpackJointsStates(uint8_t* src, float* dst, uint8_t joints_num);
void PackJointsStates(float* src, uint8_t* dst, uint8_t joints_num);

#endif
