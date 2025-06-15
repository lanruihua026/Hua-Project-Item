#include "usart2.h"
#include "gizwits_protocol.h"

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	������ƽ̨�ʵ��
 * �汾			: V1.0
 * ����			: 2024.10.7
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	����2
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	����

**********************BEGIN***********************/

uint8_t Usart2_RxPacket[6]; // ����������ݰ�����
uint8_t Usart2_RxFlag;		// ����������ݰ���־λ

void USART2_Config(void)
{
	// GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); // ʹ��USART2��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	// USART2_TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // �����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);			// ��ʼ��GPIOA.2

	// USART2_RX	  ��ʼ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  // PA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; // ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);				  // ��ʼ��GPIOA.3

	// Usart2 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // ��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  // �����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);							  // ����ָ���Ĳ�����ʼ��VIC�Ĵ���

	// USART ��ʼ������

	USART_InitStructure.USART_BaudRate = 9600;										// ���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;								// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					// �շ�ģʽ

	USART_Init(USART2, &USART_InitStructure);	   // ��ʼ������2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // �������ڽ����ж�
	USART_Cmd(USART2, ENABLE);					   // ʹ�ܴ���2
}

void USART2_IRQHandler(void) // ����2�жϷ������
{
	u8 Res;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // �����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE); // ����жϱ�־λ
		Res = USART_ReceiveData(USART2);				// ��ȡ���յ�������
		gizPutData(&Res, 1);
	}
}
