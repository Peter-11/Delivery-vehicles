#ifndef __BALANCE_H
#define __BALANCE_H

#include "main.h"
#include "tim.h"
#include "pid.h"
#include "packet.h"
#include "imu_data_decode.h"
#include "adc.h"
#include "IMU.h"
/*User Define*/
#define MOTO_CHANNOL_A 0
#define MOTO_CHANNOL_B 1
// #define MAX_SPEED  18    //18
#define MAX_TURN   15    //15
#define OpenMV_Len 4
#define K210_LEN   6
#define LEFT       0
#define RIGHT      1
#define FORCE_NUMBER 2      
#if 0
#define FORWARD_SPEED RC_Data.RC_y
#elif 1
#define FORWARD_SPEED 1
#else 
uint16_t FORWARD_SPEED 1;
#endif
/*Function Extern*/
void User_Balance_Init(void);
void User_Balance_Task(void);
float User_Moto_GetSpeed(TIM_HandleTypeDef *htim,uint16_t Time);
void OpenMV_Protocol(uint8_t *ptr,uint16_t len);
extern void K210_Protocol(uint8_t* ptr,uint8_t len);
/*Value Extern*/
typedef struct _Moto_t
{
  float Target;
  float Masure;
  float Output;
  int16_t counter;
}Moto_t;

typedef struct _OpenMV_t
{
  uint8_t Degre;
  uint8_t force;
	uint16_t flag;
  uint16_t T_flag;
  float data;
}OpenMV_t;

typedef struct _K210_t
{
  uint8_t Left_Flag;
  uint8_t Left_Num;
  uint8_t Right_Flag;
  uint8_t Right_Num;
  int8_t Target;
  uint16_t Num_pro_L[10];
  uint16_t Num_pro_R[10];
}K210_t;


#endif
