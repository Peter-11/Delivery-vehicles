#include "RC.h"

RC_Ctl_t RC_CtrlData;
RC_Data_t RC_Data={0};

uint32_t RC_LAST_TIME=0;

void RemoteDataProcess(uint8_t *pData)
{
if(pData == NULL)
{
return;
}
uwTick = RC_LAST_TIME;
RC_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF; 
RC_CtrlData.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF;
RC_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) |((int16_t)pData[4] << 10)) & 0x07FF;
RC_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF;
RC_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
RC_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);
RC_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
RC_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8); 
RC_CtrlData.mouse.press_l = pData[12];
RC_CtrlData.mouse.press_r = pData[13];
RC_CtrlData.key.v = ((int16_t)pData[14]);// | ((int16_t)pData[15] << 8);
//control code.
	RC_Data.RC_x=(RC_CtrlData.rc.ch0-RC_CH_VALUE_OFFSET)/660.0;
	if(RC_Data.RC_x<RC_dead_num&&RC_Data.RC_x>-RC_dead_num) RC_Data.RC_x=0;
	RC_Data.RC_y=(RC_CtrlData.rc.ch1-RC_CH_VALUE_OFFSET)/660.0;
	if(RC_Data.RC_y<RC_dead_num&&RC_Data.RC_y>-RC_dead_num) RC_Data.RC_y=0;
	RC_Data.RC_w=(RC_CtrlData.rc.ch2-RC_CH_VALUE_OFFSET)/660.0;
	if(RC_Data.RC_w<RC_dead_num&&RC_Data.RC_w>-RC_dead_num) RC_Data.RC_w=0;
	RC_Data.RC_p=(RC_CtrlData.rc.ch3-RC_CH_VALUE_OFFSET)/660.0;
	if(RC_Data.RC_p<RC_dead_num&&RC_Data.RC_p>-RC_dead_num) RC_Data.RC_p=0;
	RC_Data.s1=RC_CtrlData.rc.s1;
	RC_Data.s2=RC_CtrlData.rc.s2;
}
