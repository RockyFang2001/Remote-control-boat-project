#ifndef __SR04_H
#define __SR04_H
#include "main.h"
#include "stdio.h"

#define FRONT_TRIG_H  HAL_GPIO_WritePin(FRONT_TRIG_GPIO_Port,FRONT_TRIG_Pin,GPIO_PIN_SET)
#define FRONT_TRIG_L  HAL_GPIO_WritePin(FRONT_TRIG_GPIO_Port,FRONT_TRIG_Pin,GPIO_PIN_RESET)
extern uint8_t  Front_Cnt;    //状态标志位
extern uint32_t Front_Buf[3];   //存放定时器计数值的数组
 
#define REAR_TRIG_H  HAL_GPIO_WritePin(REAR_TRIG_GPIO_Port,REAR_TRIG_Pin,GPIO_PIN_SET)
#define REAR_TRIG_L  HAL_GPIO_WritePin(REAR_TRIG_GPIO_Port,REAR_TRIG_Pin,GPIO_PIN_RESET)
extern uint8_t  Rear_Cnt;    //状态标志位
extern uint32_t Rear_Buf[3];   //存放定时器计数值的数组
extern float Rear_Dis;      //测量距离
extern float Front_Dis;      //测量距离
extern uint8_t Front_Show_STR[4];
void delay_us(uint32_t us);
void Get_Front_Dis(void);
void Get_Rear_Dis(void);
void get_dis_str();
#endif