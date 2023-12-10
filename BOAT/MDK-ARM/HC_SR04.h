#ifndef __SR04_H
#define __SR04_H
#include "main.h"
#include "stdio.h"

#define FRONT_TRIG_H  HAL_GPIO_WritePin(FRONT_TRIG_GPIO_Port,FRONT_TRIG_Pin,GPIO_PIN_SET)
#define FRONT_TRIG_L  HAL_GPIO_WritePin(FRONT_TRIG_GPIO_Port,FRONT_TRIG_Pin,GPIO_PIN_RESET)
extern uint8_t  Front_Cnt;    //״̬��־λ
extern uint32_t Front_Buf[3];   //��Ŷ�ʱ������ֵ������
 
#define REAR_TRIG_H  HAL_GPIO_WritePin(REAR_TRIG_GPIO_Port,REAR_TRIG_Pin,GPIO_PIN_SET)
#define REAR_TRIG_L  HAL_GPIO_WritePin(REAR_TRIG_GPIO_Port,REAR_TRIG_Pin,GPIO_PIN_RESET)
extern uint8_t  Rear_Cnt;    //״̬��־λ
extern uint32_t Rear_Buf[3];   //��Ŷ�ʱ������ֵ������
extern float Rear_Dis;      //��������
extern float Front_Dis;      //��������
extern uint8_t Front_Show_STR[4];
void delay_us(uint32_t us);
void Get_Front_Dis(void);
void Get_Rear_Dis(void);
void get_dis_str();
#endif