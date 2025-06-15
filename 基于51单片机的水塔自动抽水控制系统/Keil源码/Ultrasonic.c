#include "Ultrasonic.h"
#include <intrins.h>

void timer0_init()	//��ʱ��0��ʼ��
{
	TMOD=0x01; //��ʱ��0������ʽ1
	TH0=0;
	TL0=0;
	EA=0;	//�ر����ж�
	ET0=0;
	TR0=0;	//�رն�ʱ��
	TF0=0;
}
void Delay20us(void)	//@12.000MHz��20us�ӳٺ���
{
	unsigned char data i;

	_nop_();
	i = 7;
	while (--i);
}

void ultrasonic_init() //��������ʼ��
{
	
	Trig=0;
	Echo=1;
	timer0_init();
	
}

float GetDistance()
{
	float ss;					// ���ڼ�¼��õľ���
	float correctionFactor = 1.02/1.005;  // У׼ϵ��������ʵ�������1.02��ʾ����ֵ������΢����2%
	Trig=1;				// ��������ģ��һ����ʼ����
	Delay20us(); //�ӳ�20us
	Trig=0;	//����
	while(Echo==0);	// �ȴ�������ģ��ķ������壬���յ���������Ϊ�ߵ�ƽ
	TH0=0x00;	//��ʱ��0����
	TL0=0x00;
	TR0=1;						// ������ʱ������ʼ��ʱ
	while(Echo==1);		// �ȴ�������ģ��ķ�����������������������Ϊ�͵�ƽ
	TR0=0;						// ֹͣ��ʱ����ֹͣ��ʱ
	//���ز���ֵ����λΪ��
	ss=(((TH0*256+TL0)*0.00034)/2);		// 1.����cm=��ʱ��us * �ٶ�cm/us��/2��2.���������340m/s.3.	
	return ss*correctionFactor;	//����ֵ����У׼ϵ��	
}


