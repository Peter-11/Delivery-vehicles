#ifndef __REPORT_H
#define __REPORT_H

#include "main.h"
#include "usart.h"

void report_SendData(UART_HandleTypeDef *huart,float data1,float data2,float data3,float data4,float data5,float data6);

#endif
