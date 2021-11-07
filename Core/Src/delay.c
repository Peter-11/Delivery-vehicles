#include "delay.h"

void delay_us(uint16_t us)
{
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000000);
	HAL_Delay(us-1);
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
}
