#include "HC_SR04.h"
#include "main.h"
float Front_Dis;      //��������
uint32_t Front_Buf[3] = {0};   //��Ŷ�ʱ������ֵ������
uint8_t  Front_Cnt = 0;    //״̬��־λ
uint32_t Front_Time;   //������ģ�鷵�صĸߵ�ƽʱ��
float Rear_Dis;      //��������
uint32_t Rear_Buf[3] = {0};   //��Ŷ�ʱ������ֵ������
uint8_t  Rear_Cnt = 0;    //״̬��־λ
uint32_t Rear_Time;   //������ģ�鷵�صĸߵ�ƽʱ��
uint8_t Front_Show_STR[4];
//===============================================��ȡ����
void Get_Front_Dis(void)
{
switch (Front_Cnt){
	case 0:
         FRONT_TRIG_H;
         delay_us(30);
         FRONT_TRIG_L;
    
		Front_Cnt++;
		__HAL_TIM_SET_CAPTUREPOLARITY(&htim3, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
		HAL_TIM_IC_Start_IT(&htim3, TIM_CHANNEL_1);	//�������벶��       ����: __HAL_TIM_ENABLE(&htim5);                                                                                    		
        break;
	case 3:
		Front_Time = Front_Buf[1]- Front_Buf[0];    //�ߵ�ƽʱ��				
		Front_Dis=(Front_Time*0.034)/2;  //��λcm       
		Front_Cnt = 0;  //��ձ�־λ
    TIM3->CNT=0;     //��ռ�ʱ������
		break;
				
	}
}

//===============================================��ȡ����

 
 
//===============================================us��ʱ����
void delay_us(uint32_t us)//��Ƶ72M
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
  
	if(TIM3 == htim->Instance){// �жϴ������жϵĶ�ʱ��ΪTIM3
		switch(Front_Cnt){
			case 1:
				Front_Buf[0] = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
				__HAL_TIM_SET_CAPTUREPOLARITY(&htim3,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //����Ϊ�½��ز���
				Front_Cnt++;                                            
				break;              
			case 2:
				Front_Buf[1] = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
				HAL_TIM_IC_Stop_IT(&htim3,TIM_CHANNEL_1); //ֹͣ����   ����: __HAL_TIM_DISABLE(&htim3);
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

 