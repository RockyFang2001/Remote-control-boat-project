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
	
	char isGetData;		//���ݻ�ȡ��ɱ�־λ
	char isParseData;	//������ɱ�־λ
	
	char UTCTime[UTCTime_Length];		//UTCʱ��
	char latitude[latitude_Length];		//γ��
	char N_S[N_S_Length];		//N/S
	char longitude[longitude_Length];	//����
	char E_W[E_W_Length];		//E/W
	
	char isUsefull;		//��Ϣ��Ч��־λ
}GNRMC;
extern GNRMC GNRMC_Info;
extern float Lat;
extern float Lon;
extern char dest[23];
extern char USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
#endif