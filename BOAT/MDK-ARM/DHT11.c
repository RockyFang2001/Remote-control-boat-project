#include "dht11.h"

 
/**
  * @brief  ��ʪ�ȴ�����������
  * @param  void
  * @retval None
  */
void DHT11(void)
{
    DHT11_READ_DATA();
    HAL_Delay(50);  		             // Ԥ��һ������
}
 
/**
  * @brief  ��ʪ�ȴ����������źŷ���
  * @param  void
  * @retval None
  */
void DHT11_START(void)
{
    DHT11_GPIO_MODE_SET(0);                         //  ��������Ϊ���ģʽ
    
    DHT11_PIN_RESET;                                //  �������͵�ƽ
    
    HAL_Delay(20);                                  //  �����ȴ� 18 < ms > 30
    
    DHT11_GPIO_MODE_SET(1);                         //  ��������Ϊ����ģʽ���ȴ�DHT11��Ӧ
}                                                   //  ��Ϊ�������������룬GPIO -> 1
 
/**
  * @brief  ��ȡһλ���� 1bit
  * @param  void
  * @retval 0/1
  */
unsigned char DHT11_READ_BIT(void)
{
    while(!DHT11_READ_IO);                          //  �������ݵĵ͵�ƽ 
    
    Tims_delay_us(40);                              //  �������ݵĸߵ�ƽ
    
    if(DHT11_READ_IO)                               //  ��ʱ�����Ϊ�ߵ�ƽ������Ϊ 1
    {
        while(DHT11_READ_IO);                       //  �������ݵĸߵ�ƽ
        return 1;
    }   
    else                                            //  ����ʱΪ����Ϊ 0
    {
        return 0;
    }
}
 
/**
  * @brief  ��ȡһ���ֽ����� 1byte / 8bit
  * @param  void
  * @retval temp
  */
unsigned char DHT11_READ_BYTE(void)
{
    uint8_t i,temp = 0;                             //  ��ʱ�洢����
    
    for(i=0; i<8 ;i++)
    {
        temp <<= 1;                                 
        if(DHT11_READ_BIT())                        //  1byte -> 8bit
        {
            temp |= 1;                              //  0000 0001
        }
    }
    return temp;
}
 
/**
  * @brief  ��ȡ��ʪ�ȴ��������� 5byte / 40bit
  * @param  void
  * @retval 0/1/2
  */
uint8_t dht11_data[5] = {0};
uint8_t dht11_send_data[5] = {0};
unsigned char DHT11_READ_DATA(void)
{
    uint8_t i;
    
    
    DHT11_START();                                  //  �������������ź�
    
    if(DHT11_Check())                               //  ���DHT11Ӧ��     
    {  
        while(!DHT11_READ_IO);                      //  ����DHT11���źŵĵ͵�ƽ
        while(DHT11_READ_IO);                       //  ����DHT11���źŵĸߵ�ƽ
        
        for(i=0; i<5; i++)
        {                        
            dht11_data[i] = DHT11_READ_BYTE();            //  ��ȡ 5byte
        }
        
        if(dht11_data[0] + dht11_data[1] + dht11_data[2] + dht11_data[3] == dht11_data[4])
        {
					dht11_send_data[1] = (dht11_data[0] / 10 );
					dht11_send_data[2] = (dht11_data[0] - dht11_send_data[1] * 10 );
					dht11_send_data[3] = (dht11_data[2] / 10 );
					dht11_send_data[4] = (dht11_data[2] - dht11_send_data[3] * 10 );
					dht11_send_data[0] = '\n' ;
					dht11_send_data[1] += '0';
					dht11_send_data[2] += '0';
					dht11_send_data[3] += '0';
					dht11_send_data[4] += '0';
					
					
            //��ʾ�¶�
//			OLED_ShowCN_STR(0,4,0,2);
//			OLED_ShowStr(32,4,":",2);
//            OLED_ShowNum(40,4,data[2],2,16);
//			OLED_ShowCN_STR(59,4,4,1);
//					
//			//��ʾʪ��
//			OLED_ShowCN_STR(0,6,2,2);
//			OLED_ShowStr(32,6,":",2);
//			OLED_ShowNum(40,6,data[0],2,16);
//			OLED_ShowStr(59,6,"HR",2);
            return 1;                               //  ����У��ͨ��
        }
        else
        {
            return 0;                               //  ����У��ʧ��
        }
    }
    else                                            //  ���DHT11��Ӧ��
    {
        return 2;
    }
}
 
/**
  * @brief  �����ʪ�ȴ������Ƿ����(���DHT11��Ӧ���ź�)
  * @param  void
  * @retval 0/1
  */
unsigned char DHT11_Check(void)
{
    Tims_delay_us(40);
    if(DHT11_READ_IO == 0)                          //  ��⵽DHT11Ӧ��
    {
        return 1;
    }
    else                                            //  ��⵽DHT11��Ӧ��
    {
        return 0;
    }
}
 
/**
  * @brief  ��������ģʽ
  * @param  mode: 0->out, 1->in
  * @retval None
  */
static void DHT11_GPIO_MODE_SET(uint8_t mode)
{
    if(mode)
    {
        /*  ����  */
        GPIO_InitTypeDef GPIO_InitStruct;
        GPIO_InitStruct.Pin = DHT11_Pin;                   //  9������
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;             //  ����ģʽ
        GPIO_InitStruct.Pull = GPIO_PULLUP;                 //  ��������
        HAL_GPIO_Init(DHT11_GPIO_Port, &GPIO_InitStruct);
    }
    else 
    {
        /*  ���  */
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.Pin = DHT11_Pin;                //  9������
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;      //  Push Pull �������ģʽ
        GPIO_InitStructure.Pull = GPIO_PULLUP;              //  �������
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;    //  ����
        HAL_GPIO_Init(DHT11_GPIO_Port,&GPIO_InitStructure);
    }
}
 
/**
  * @brief  ��ʱ����ʱus��Prescaler -> 32-1
  * @param  us: <= 65535
  * @retval None
  */
void Tims_delay_us(uint16_t nus)
{
    uint32_t delay = (HAL_RCC_GetHCLKFreq() / 4000000 * nus);
    while (delay--)
	{
		;
	}
}