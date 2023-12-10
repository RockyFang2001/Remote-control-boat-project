#ifndef __DHT11_H__
#define __DHT11_H__
 
/* Private includes ----------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx.h"
 
/* Private define ------------------------------------------------------------*/
#define DHT11_PIN_SET   HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,GPIO_PIN_SET)                                            //  ??GPIO??
#define DHT11_PIN_RESET HAL_GPIO_WritePin(DHT11_GPIO_Port,DHT11_Pin,GPIO_PIN_RESET)                                          //  ??GPIO??
#define DHT11_READ_IO   HAL_GPIO_ReadPin(DHT11_GPIO_Port,DHT11_Pin)                                                          //  DHT11 GPIO??
 
#define DLY_TIM_Handle (&htim3)                                                                                     //  ?????
 
 
/* Private variables ---------------------------------------------------------*/
 
/* Private typedef -----------------------------------------------------------*/
 
/* Private function prototypes -----------------------------------------------*/
void DHT11(void);
void DHT11_START(void);
unsigned char DHT11_READ_BIT(void);
unsigned char DHT11_READ_BYTE(void);
unsigned char DHT11_READ_DATA(void);
unsigned char DHT11_Check(void);
static void DHT11_GPIO_MODE_SET(uint8_t mode);
void Tims_delay_us(uint16_t nus);
//void delay_us(uint16_t nus);
extern uint8_t dht11_send_data[5];
#endif