#include "ros_connect.h"
#include <string.h>
/**
 *@brief �������
 *@param src Դ���ݰ�
 *@param dst Ŀ��洢����,��λ��ǰ,�����СӦ����joints_num
 *@param joints_num �ؽ���Ŀ,�������ݰ���У��
 *@return 0 ���ʧ�� 1����ɹ�
 */ 
uint8_t UnpackJointsStates(uint8_t* src, float* dst, uint8_t joints_num)
{
	int data;
	
	// ���ݵ����һλ��ΪУ��λ
	if(src[4*joints_num] != joints_num) 
	{
		return 0;
	}
	
	// ���
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
 *@brief �������
 *@param src �ؽ�λ�����ݰ�
 *@param dst ��Ϣ�������ݰ�
 *@param joints_num �ؽ���Ŀ
 */ 
void PackJointsStates(float* src, uint8_t* dst, uint8_t joints_num)
{
	int data;
	// ���ݴ��
	for(int i = 0; i < joints_num; i++)
	{
		data = src[i] * 1000;
		memcpy(&dst[4*i], &data, 4);
	}
	
	// д��У��λ
	dst[joints_num*4] = joints_num;
}
