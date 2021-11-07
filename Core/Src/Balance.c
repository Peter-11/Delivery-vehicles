#include "Balance.h"

Moto_t Moto_Left,Moto_Right;
PID_TypeDef OutputL_Pid,OutputR_Pid,Input_Pid;
OpenMV_t OpenMV;
K210_t K210;
uint8_t Target_number=2;
uint8_t Static_Flag;//0:未开始/数字检测 1：巡线 2：转弯 3:卸货 4：掉头
uint16_t Touch_HighCounter=0;
uint16_t MAX_SPEED=15;
/**
 * @brief 平衡车初始化程序
 * 
 */
void User_Balance_Init(void)
{
  PID_Init(&OutputL_Pid,8399,0,6000,0,150,52,0,0,0,Integral_Limit);//左轮输出函数
  PID_Init(&OutputR_Pid,8399,0,6500,0,150,60,0,0,0,Integral_Limit);//右轮输出函数
  PID_Init(&Input_Pid,MAX_TURN,0,50,0,1,0,0,0,0,Integral_Limit);
  // PID_Init(&Gyr_Pid,50,0,10,0,0.01,0.08,0.01,0,0,Integral_Limit);
  // PID_Init(&Eul_Pid,500,0,50,0,2,0,0,0,0,Integral_Limit);
  // PID_Init(&Speed_Pid,200,0,50,0,1,0,0,0,0,Integral_Limit);
}

/**
 * @brief 通过控制pwm占空比控制电机转速
 * 
 * @param channal TB6612的A相或B相，0为A相，1为B相
 * @param Duty PWM占空比，（-8400 ~ 8400）
 */
static void Pwm_Genrate(uint8_t channal , int16_t Duty)
{ 
  if(Battery_Value <= 10.5f) Duty=0;
  switch(channal)
  {
    case MOTO_CHANNOL_A:
      if(Duty < 0 ) 
      {
        HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
      }
      else if(Duty == 0 )
      {
        HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
      }
      else if(Duty > 0 )
      {
        HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
      }
    __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,fabs(Duty));
    break;
    case MOTO_CHANNOL_B:
      if(Duty < 0 ) 
      {
        HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
      }
      else if(Duty == 0 )
      {
        HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
      }
      else if(Duty > 0 )
      {
        HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
      }
    __HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,fabs(Duty));
    break;
  }
}

void Moto_Speed_Calculate(Moto_t* data,float forward,float turn)
{
  if(data == &Moto_Left)
    data->Target=forward  + turn;
  else if(data == &Moto_Right)
    data->Target=forward  - turn;
}

void Walking(Moto_t* data)
{
  if(data == &Moto_Left)
    data->Target=FORWARD_SPEED * MAX_SPEED - OpenMV.data * MAX_TURN;
  else if(data == &Moto_Right)
    data->Target=FORWARD_SPEED * MAX_SPEED + OpenMV.data * MAX_TURN;
  if(OpenMV.flag > 3) Static_Flag = 2;
}

void Number_Counter(K210_t* k210)
{
  switch (k210->Left_Num)
  {
  case 1:
    K210.Num_pro_L[1]++;
    break;
  case 2:
    K210.Num_pro_L[2]++;
    break;
  case 3:
    K210.Num_pro_L[3]++;
    break;
  case 4:
    K210.Num_pro_L[4]++;
    break;
  case 5:
    K210.Num_pro_L[5]++;
    break;
  case 6:
    K210.Num_pro_L[6]++;
    break;
  case 7:
    K210.Num_pro_L[7]++;
    break;
  case 8:
    K210.Num_pro_L[8]++;
    break;
  default:
    break;
  }
  switch (k210->Right_Num)
  {
  case 1:
    K210.Num_pro_R[1]++;
    break;
  case 2:
    K210.Num_pro_R[2]++;
    break;
  case 3:
    K210.Num_pro_R[3]++;
    break;
  case 4:
    K210.Num_pro_R[4]++;
    break;
  case 5:
    K210.Num_pro_R[5]++;
    break;
  case 6:
    K210.Num_pro_R[6]++;
    break;
  case 7:
    K210.Num_pro_R[7]++;
    break;
  case 8:
    K210.Num_pro_R[8]++;
    break;
  case 9:
    K210.Num_pro_R[9]++;
    break;
  default:
    break;
  }
}

#if 0
void Target_Calculate(Moto_t* data)
{
  #if 0

  #else
    static uint8_t Counter=0;
    static uint8_t flag = 0;
    #if 0
    if(RC_Data.s1!=0 && RC_Data.s1 != 1 )
    {
      if(data == &Moto_Left)
      data->Target=RC_Data.RC_y * MAX_SPEED - RC_Data.RC_w * MAX_TURN;
      else if(data == &Moto_Right)
      data->Target=RC_Data.RC_y * MAX_SPEED + RC_Data.RC_w * MAX_TURN;
    }
    else
    {
      data->Target=0;
    }
    
    #else
      #if 1
        if(OpenMV.force == 2) 
        {
          if(data->counter++ <= 20 )
          {
            data->Target=0;
            return;
          } 
          else if(data->counter <= 50)
          {
            flag =1;
          }
          else data->counter =0;
        }
        if(flag == 1 && Counter++ < 25)
        {
          if(Target_number == 1) Moto_Speed_Calculate(data,1.7,-1.5);
          else if(Target_number == 2) Moto_Speed_Calculate(data,1.7,1.5);
          else data->Target = FORWARD_SPEED * MAX_SPEED;
          return;
        }
        else
        {
          flag=0;
          Counter=0;
        }
        data->counter =0;
        Moto_Speed_Calculate(data,FORWARD_SPEED,OpenMV.data);
      #else
        if(RC_Data.s2 == 2)
        {static uint32_t counter;
          if(counter++ < 2000)
          {
            if(data == &Moto_Left)
            data->Target= MAX_SPEED + MAX_TURN;
            else if(data == &Moto_Right)
            data->Target= MAX_SPEED - MAX_TURN;
            if(OpenMV.flag) data->Target=0;
          }
          else data->Target=0;
        }
      #endif
    #endif
  #endif
}
#endif
/**
 * @brief 清空pid积分值并使小车停下
 * 
 */
void Stop(void)
{
  OutputL_Pid.ITerm=OutputL_Pid.Iout=OutputR_Pid.Iout=OutputR_Pid.ITerm=0;
  Moto_Left.Masure=User_Moto_GetSpeed(&htim3,5);
  Moto_Right.Masure=User_Moto_GetSpeed(&htim8,5);
  Moto_Left.Output=PID_Calculate(&OutputL_Pid,Moto_Left.Masure,0);
  Moto_Right.Output=PID_Calculate(&OutputR_Pid,Moto_Right.Masure,0);
  Pwm_Genrate(MOTO_CHANNOL_A,Moto_Left.Output);
  Pwm_Genrate(MOTO_CHANNOL_B,Moto_Right.Output);
}



uint8_t Target_Number_Get(void)
{
  uint8_t Target=FORCE_NUMBER ;
  for(uint8_t i=1;i<9;i++)
  {
    Target=K210.Num_pro_L[Target] < K210.Num_pro_L[i]? i:Target;
    Target=K210.Num_pro_R[Target] < K210.Num_pro_R[i]? i:Target;
  }
  return Target;
}

void Walking_Task(void)
{
  Number_Counter(&K210);
  Moto_Left.Masure=User_Moto_GetSpeed(&htim3,5);
  Moto_Right.Masure=User_Moto_GetSpeed(&htim8,5);
  Walking(&Moto_Left);
  Walking(&Moto_Right);
  Moto_Left.Output=PID_Calculate(&OutputL_Pid,Moto_Left.Masure,Moto_Left.Target);
  Moto_Right.Output=PID_Calculate(&OutputR_Pid,Moto_Right.Masure,Moto_Right.Target);
  Pwm_Genrate(MOTO_CHANNOL_A,Moto_Left.Output);
  Pwm_Genrate(MOTO_CHANNOL_B,Moto_Right.Output);
  Number_Counter(&K210);
}

void Cross_Target_Clean(void)
{
  for(uint8_t i=0;i<9;i++)
  {
    K210.Num_pro_L[i]=K210.Num_pro_R[i]=0;
  }
}
uint8_t Cross_Number=0;
uint16_t Cross_Counter =0;
uint8_t Measure_L[8]={1};
uint8_t Measure_R[8]={2};
uint8_t Counter;
void Cross_Speed_Get(Moto_t* moto)
{
  static uint8_t flag;
  #if 0
    if(Cross_Counter++ < 40 ) moto->Target=0;
    else if(Cross_Counter < 60 )
    {
      if(K210.Target == 1) Moto_Speed_Calculate(moto,40,47);
      else if(K210.Target == 2) Moto_Speed_Calculate(moto,40,-47);
      else if(K210.Target == -1) Moto_Speed_Calculate(moto,40,-47);
      else if(K210.Target == -2) Moto_Speed_Calculate(moto,40,47);
      else moto->Target = MAX_SPEED;
      return;
    }
    else
    {
      if(K210.Target == 1 || K210.Target == -2) Moto_Speed_Calculate(moto,0,15);
      else if(K210.Target == -1 || K210.Target == 2) Moto_Speed_Calculate(moto,0,-15);
      if(OpenMV.data!=0)  
      {
        Counter++;
        if(Counter > 5 )
        {
          Cross_Counter =0;
          Static_Flag=1;
          Cross_Number++;
          Cross_Target_Clean();
        }
      }
    }
  #else
    if(Cross_Number!=0 && K210.Target > 0 && flag == 0)
    {
      for(uint8_t i=1;i<9;i++) 
      {
				if( K210.Num_pro_L[Measure_L[Cross_Number]] < K210.Num_pro_L[i] ) 
        {
          Measure_L[Cross_Number] = i;
        }
				if( K210.Num_pro_R[Measure_R[Cross_Number]] < K210.Num_pro_R[i] ) 
        {
          Measure_R[Cross_Number] = i;
        }
      }
			flag=1;
    }
    if(Cross_Counter++ < 10 ) 
    {
      moto->Target=0;
    }
    else if(Cross_Counter < 40)
    {
//			if(K210.Target == Measure_R[Cross_Number] || K210.Target == -Measure_L[Cross_Number]) Moto_Speed_Calculate(moto,18,-15);
      if((K210.Target == Measure_L[Cross_Number] )|| (K210.Target == -Measure_R[Cross_Number])) Moto_Speed_Calculate(moto,18,15);
      else if((K210.Target == Measure_R[Cross_Number]) || (K210.Target == -Measure_L[Cross_Number])) Moto_Speed_Calculate(moto,18,-15);
      else Moto_Speed_Calculate(moto,MAX_SPEED,0);
    }
    else
    {
      if((K210.Target == Measure_L[Cross_Number] )|| (K210.Target == -Measure_R[Cross_Number])) Moto_Speed_Calculate(moto,0,10);
      else if((K210.Target == Measure_R[Cross_Number]) || (K210.Target == -Measure_L[Cross_Number])) Moto_Speed_Calculate(moto,0,-10);
      if(OpenMV.data!=0)
      {
          // Static_Flag=5;
          if(moto==&Moto_Right)
          {
            if(K210.Target > 0 ) Cross_Number++;
            else Cross_Number--;
            Static_Flag=1;
						flag=0;
            Cross_Counter =0;
          }
          Cross_Target_Clean();
      }
    }
  #endif
}

void Cross_Task(void)
{
  OpenMV.flag=0;
  Moto_Left.Masure=User_Moto_GetSpeed(&htim3,5);
  Moto_Right.Masure=User_Moto_GetSpeed(&htim8,5);
  Cross_Speed_Get(&Moto_Left);
  Cross_Speed_Get(&Moto_Right);
  if(Static_Flag != 1)
  {
    Moto_Left.Output=PID_Calculate(&OutputL_Pid,Moto_Left.Masure,Moto_Left.Target);
    Moto_Right.Output=PID_Calculate(&OutputR_Pid,Moto_Right.Masure,Moto_Right.Target);
    Pwm_Genrate(MOTO_CHANNOL_A,Moto_Left.Output);
    Pwm_Genrate(MOTO_CHANNOL_B,Moto_Right.Output);
  }
}

void turn_Target_Get(Moto_t* data,uint8_t* flag)
{
  static uint8_t counter=0;
  if(counter++ <= 50)//掉头
  {
    Moto_Speed_Calculate(data,0,20);
  }
  else 
	{
    *flag=1;
    K210.Target = -K210.Target;
    data->Target=0;
    if(data == &Moto_Right)
    {
      Static_Flag = 1;
      Cross_Number--;
    }
	}
}

void Turn_Task(void)
{
  static uint8_t Flag=0;
  if(Flag == 0)
  {
    Moto_Left.Masure=User_Moto_GetSpeed(&htim3,5);
    Moto_Right.Masure=User_Moto_GetSpeed(&htim8,5);
    turn_Target_Get(&Moto_Left,&Flag);
    turn_Target_Get(&Moto_Right,&Flag);
    Moto_Left.Output=PID_Calculate(&OutputL_Pid,Moto_Left.Masure,Moto_Left.Target);
    Moto_Right.Output=PID_Calculate(&OutputR_Pid,Moto_Right.Masure,Moto_Right.Target);
    Pwm_Genrate(MOTO_CHANNOL_A,Moto_Left.Output);
    Pwm_Genrate(MOTO_CHANNOL_B,Moto_Right.Output);
  }
  else 
  {
    Static_Flag = 1;
    HAL_GPIO_WritePin(GREEN_GPIO_Port,GREEN_Pin,GPIO_PIN_SET);
  }
}

/**
 * @brief 平衡车主任务,控制周期25ms
 * 
 */
void User_Balance_Task(void)
{
  static uint32_t Touch_LowCounter =0;
  if(Static_Flag == 0)//识别数字
  {
    Stop();
    Number_Counter(&K210);
    if(HAL_GPIO_ReadPin(Touch1_GPIO_Port,Touch1_Pin) == 0 && HAL_GPIO_ReadPin(Touch2_GPIO_Port,Touch2_Pin) == 0 ) 
    {
      if(Touch_LowCounter++ >= 20)
      {
        K210.Target=Target_Number_Get();
        memset(K210.Num_pro_L,0,10);
        memset(K210.Num_pro_R,0,10);
        Static_Flag=1;
      } 
    }
  else Touch_LowCounter =0;
    // if(Touch_Detack_Task() == 1)
    // {
    //   K210.Target=Target_Number_Get();
    //   Static_Flag=1;
    // }
  }
  else if(Static_Flag == 1)//巡线 
  {
    Walking_Task();
  }
  else if(Static_Flag == 2)//转弯
  {
    Cross_Task();
  }
  else if(Static_Flag == 3)//等待卸货
  {
    static uint8_t flag;
    if(flag==0){
      HAL_GPIO_WritePin(RED_GPIO_Port,RED_Pin,GPIO_PIN_SET);
      flag=1;
    }
    Stop();
    if(HAL_GPIO_ReadPin(Touch1_GPIO_Port,Touch1_Pin) == 1 && HAL_GPIO_ReadPin(Touch2_GPIO_Port,Touch2_Pin) == 1 ) 
    {
      if(Touch_HighCounter++ >= 20)
      {
        HAL_GPIO_WritePin(RED_GPIO_Port,RED_Pin,GPIO_PIN_RESET);
        Static_Flag=4;
      } 
    }
    else Touch_HighCounter=0;
  }
  else if(Static_Flag == 4)//掉头
  {
    Turn_Task();
  }
  else if(Static_Flag == 5)
  {
    Stop();
  }
  else 
  {
    OutputL_Pid.ITerm=OutputL_Pid.Iout=OutputR_Pid.Iout=OutputR_Pid.ITerm=0;
    Pwm_Genrate(MOTO_CHANNOL_A,0);
    Pwm_Genrate(MOTO_CHANNOL_B,0);
  }
  report_SendData(&huart1,K210.Target,K210.Num_pro_L[Measure_L[Cross_Number]] ,K210.Num_pro_R[Measure_R[Cross_Number]],K210.Num_pro_R[K210.Target],Measure_L[Cross_Number],Measure_R[Cross_Number]);
};

/**
 * @brief 调用定时器编码器模式获取电机转速
 * 
 * @param htim 编码器所连接的定时器
 * @param Time 调用间隔时间（ms）
 * @return float 电机转速
 */
float User_Moto_GetSpeed(TIM_HandleTypeDef *htim,uint16_t Time)
{
  uint16_t counter;
  counter=__HAL_TIM_GET_COUNTER(htim);
  // force=__HAL_TIM_IS_TIM_COUNTING_DOWN(htim);
  __HAL_TIM_SetCounter(htim,32768);
  return ((float)(counter-32768)/720.0f)*(1000.0f/Time);
}

void OpenMV_Protocol(uint8_t *ptr,uint16_t len)
{
  if(ptr[0] == 0x7e && ptr[3] == 0x7f)
  {
    OpenMV.force=ptr[1];
    OpenMV.Degre=ptr[2];
		if(OpenMV.Degre > 52) 
		{
			OpenMV.Degre=0;
      if(Static_Flag == 1)
      {
        Touch_HighCounter=0;
        Static_Flag = 3;
      } 
		}	
		switch (OpenMV.force)
    {
    case 0:
      OpenMV.data = (float)OpenMV.Degre/90.0f;
      break;
    case 1:
      OpenMV.data = -(float)OpenMV.Degre/90.0f;
      break;
    case 2:
      OpenMV.data = 0;
      OpenMV.flag++;
      break;
    case 3:
      OpenMV.T_flag++;
      if(OpenMV.T_flag >= 2) Static_Flag=2; 
    break;
    default:
      OpenMV.data =0;
      break;
    }
  }
}

void K210_Protocol(uint8_t* ptr,uint8_t len)
{
  if(ptr[0]==0x7f && ptr[5]==0x7e)
  {
    K210.Left_Flag=ptr[1];
    if(K210.Left_Flag) K210.Left_Num =ptr[2];
    else K210.Left_Num=0;
    K210.Right_Flag=ptr[3];
    if(K210.Right_Flag) K210.Right_Num =ptr[4];
    else K210.Right_Num=0;
  }
  memset(ptr,0,K210_LEN);
}


