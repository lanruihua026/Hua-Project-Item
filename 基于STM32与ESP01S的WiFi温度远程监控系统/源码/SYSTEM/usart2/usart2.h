#ifndef __USART2_H
#define __USART2_H

#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "usart.h"

/*****************���絥Ƭ�����******************
											STM32
 * ��Ŀ			:	������ƽ̨�ʵ��                     
 * �汾			: V1.0
 * ����			: 2024.10.7
 * MCU			:	STM32F103C8T6
 * �ӿ�			:	�δ���2						
 * BILIBILI	:	���絥Ƭ�����
 * CSDN			:	���絥Ƭ�����
 * ����			:	���� 

**********************BEGIN***********************/

extern uint8_t Usart2_RxPacket[6];				//����������ݰ�����
extern uint8_t Usart2_RxFlag;

void USART2_Config(void);
uint8_t Usart2_GetRxFlag(void);


#endif


