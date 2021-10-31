#include "ros_connect.h"
#include <string.h>
/**
 *@brief 解包函数
 *@param src 源数据包
 *@param dst 目标存储数组,低位在前,数组大小应大于joints_num
 *@param joints_num 关节数目,用于数据包的校验
 *@return 0 解包失败 1解包成功
 */ 
uint8_t UnpackJointsStates(uint8_t* src, float* dst, uint8_t joints_num)
{
	int data;
	
	// 数据的最后一位作为校验位
	if(src[4*joints_num] != joints_num) 
	{
		return 0;
	}
	
	// 解包
	else
	{
		for(int i = 0; i < joints_num; i++)
		{
			memcpy(&data, &src[i*4], 4);
			dst[i] = data / 1000.f;
		}
		return 1;
	}
}

/**
 *@brief 打包函数
 *@param src 关节位置数据包
 *@param dst 信息传输数据包
 *@param joints_num 关节数目
 */ 
void PackJointsStates(float* src, uint8_t* dst, uint8_t joints_num)
{
	int data;
	// 数据打包
	for(int i = 0; i < joints_num; i++)
	{
		data = src[i] * 1000;
		memcpy(&dst[4*i], &data, 4);
	}
	
	// 写入校验位
	dst[joints_num*4] = joints_num;
}
