#ifndef __ATGM336H_H__
#define __ATGM336H_H__
#define GPS_Buffer_Length 80
#define UTCTime_Length 11
#define latitude_Length 11
#define N_S_Length 2
#define longitude_Length 12
#define E_W_Length 2 
#define USART_REC_LEN 128
typedef struct SaveData 
{
	char GPS_Buffer[GPS_Buffer_Length];
	
	char isGetData;		//数据获取完成标志位
	char isParseData;	//解析完成标志位
	
	char UTCTime[UTCTime_Length];		//UTC时间
	char latitude[latitude_Length];		//纬度
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];	//经度
	char E_W[E_W_Length];		//E/W
	
	char isUsefull;		//信息有效标志位
}GNRMC;
extern GNRMC GNRMC_Info;
extern float Lat;
extern float Lon;
extern char dest[23];
extern char USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
#endif