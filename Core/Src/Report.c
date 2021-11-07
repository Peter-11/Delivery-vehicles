#include "report.h"

void report_SendData(UART_HandleTypeDef *huart,float data1,float data2,float data3,float data4,float data5,float data6)
{	
	uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f};	//֡β
	HAL_UART_Transmit(huart,(uint8_t *)&data1,sizeof(data1),0x10);
	HAL_UART_Transmit(huart,(uint8_t *)&data2,sizeof(data2),0x10);
	HAL_UART_Transmit(huart,(uint8_t *)&data3,sizeof(data3),0x10);
	HAL_UART_Transmit(huart,(uint8_t *)&data4,sizeof(data4),0x10);
	HAL_UART_Transmit(huart,(uint8_t *)&data5,sizeof(data5),0x10);
	HAL_UART_Transmit(huart,(uint8_t *)&data6,sizeof(data6),0x10);
	HAL_UART_Transmit(huart,(uint8_t *)tail,4,0x10);
		
};
