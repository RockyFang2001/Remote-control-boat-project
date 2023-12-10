#include "HC_SR04.h"
#include "main.h"
float Front_Dis;      //测量距离
uint32_t Front_Buf[3] = {0};   //存放定时器计数值的数组
uint8_t  Front_Cnt = 0;    //状态标志位
uint32_t Front_Time;   //超声波模块返回的高电平时间
float Rear_Dis;      //测量距离
uint32_t Rear_Buf[3] = {0};   //存放定时器计数值的数组
uint8_t  Rear_Cnt = 0;    //状态标志位
uint32_t Rear_Time;   //超声波模块返回的高电平时间
uint8_t Front_Show_STR[4];
//===============================================读取距离
void Get_Front_Dis(void)
{
switch (Front_Cnt){
	case 0:
         FRONT_TRIG_H;
         delay_us(30);
         FRONT_TRIG_L;
    
		Front_Cnt++;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
		HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);	//启动输入捕获       或者: __HAL_TIM_ENABLE(&htim5);                                                                                    		
        break;
	case 3:
		Front_Time = Front_Buf[1]- Front_Buf[0];    //高电平时间				
		Front_Dis=(Front_Time*0.034)/2;  //单位cm       
		Front_Cnt = 0;  //清空标志位
    TIM3->CNT=0;     //清空计时器计数
		break;
				
	}
}

//===============================================读取距离

 
 
//===============================================us延时函数
void delay_us(uint32_t us)//主频72M
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * us);
    while (delay--)
	{
		;
	}
}
 
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  
	if(TIM3 == htim->Instance){// 判断触发的中断的定时器为TIM3
		switch(Front_Cnt){
			case 1:
				Front_Buf[0] = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//获取当前的捕获值.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
				Front_Cnt++;                                            
				break;              
			case 2:
				Front_Buf[1] = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//获取当前的捕获值.
				HAL_TIM_IC_Stop_IT(&htim3,TIM_CHANNEL_1); //停止捕获   或者: __HAL_TIM_DISABLE(&htim3);
				Front_Cnt++;  
                         
		}
	}

}

void get_dis_str(){
		Front_Show_STR[0] = Front_Dis / 1000;
		Front_Show_STR[1] = (Front_Dis - Front_Show_STR[0] * 1000) / 100;
		Front_Show_STR[2] = (Front_Dis - Front_Show_STR[0] * 1000 - Front_Show_STR[1] * 100) / 10;
		Front_Show_STR[3] = Front_Dis - Front_Show_STR[0] * 1000 - Front_Show_STR[1] * 100 - Front_Show_STR[2] * 10;
		Front_Show_STR[3] += '0';
		Front_Show_STR[2] += '0';
		Front_Show_STR[1] += '0';
		Front_Show_STR[0] += '0';
}

 