#include "stm32f10x.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
#include "oled.h"
#include "usart2.h"
#include "timer.h"
#include "dht11.h"
#include "gizwits_product.h"

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	������ƽ̨�ʵ��
 * �汾			: V1.0
 * ����			: 2024.10.7
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�ο�usart2.h
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/

u8 temp;
u8 humi;

int main(void)
{

	SystemInit(); // ����ϵͳʱ��Ϊ72M
	delay_init(72);
	LED_Init();
	LED_Off();
	USART1_Config();				 // ���ڳ�ʼ��
	USART2_Config();				 // ���ڳ�ʼ��
	TIM3_Int_Init(1000 - 1, 72 - 1); // ��ʱ1ms�ж�

	while (DHT11_Init())
	{
		printf("DHT11 Error \r\n");
	}

	OLED_Init();
	printf("Start \n");
	delay_ms(1000);
	// ��ʾ���¶�:��
	OLED_ShowChinese(0, 0, 0, 16, 1);
	OLED_ShowChinese(16, 0, 1, 16, 1);
	OLED_ShowChar(32, 0, ':', 16, 1);
	// ��ʾ��ʪ��:��
	OLED_ShowChinese(0, 16, 2, 16, 1);
	OLED_ShowChinese(16, 16, 1, 16, 1);
	OLED_ShowChar(32, 16, ':', 16, 1);

	delay_ms(500);
	userInit();
	gizwitsInit();
	delay_ms(500);
	gizwitsSetMode(WIFI_AIRLINK_MODE); // ��������ģʽΪAirlink
	while (1)
	{
		DHT11_Read_Data(&temp, &humi); // DHT11��ȡ�¶�ʪ�Ⱥ���

		// LED_Toggle();
		delay_ms(1000);
		// ��ʾ�¶�����
		OLED_ShowNum(48, 0, temp, 2, 16, 1);
		// ��ʾʪ������
		OLED_ShowNum(48, 16, humi, 2, 16, 1);
		userHandle();
		gizwitsHandle((dataPoint_t *)&currentDataPoint);
	}
}
