#include "lcd1602.h"
#include "public.h"
#include <intrins.h>
#include "Ultrasonic.h"
#include <stdio.h>
#include "standaloneKey.h"

/*��ر�������*/
u8 i;
float dis;	//���ڳ������洢����ֵ
u8 distan[8];
float low=0.50,high=3.00; //�趨ˮλ��ֵ
u8 lower[8],higher[8];
sbit motor=P2^4; //�������ܽţ��������ü̵�������
sbit mode=P1^7; //�ֶ��Զ�����λ

void main()
{
	motor=0;	//�����ʼ���ر�
	timer0_init();	//��ʱ��0��ʼ��
	lcd1602_init(); //lcd1602��ʼ��
	lcd1602_clear();	//lcd1602����
	
	sprintf(lower,"%.2f",low);	//�ߵ�ˮλת�ַ���
	sprintf(higher,"%.2f",high);
	
	lcd1602_show_string(0,0,"LEVEL:");	//lcd1602��ʾˮλ
	
	lcd1602_show_string(0,1,"L:");
	lcd1602_show_string(2,1,lower);
	lcd1602_show_string(6,1,"m");
	
	lcd1602_show_string(8,1,"H:");
	lcd1602_show_string(10,1,higher);
	lcd1602_show_string(14,1,"m");
	ultrasonic_init(); //������ģ���ʼ��
	
	/*��ˮ����*/
	while(1)
	{
	
		dis=GetDistance(); //�ϵ���Ȳ��һ��
		sprintf(distan,"%.2f",dis);	//��ʽ���ַ���
		lcd1602_show_string(9,0,distan);
		lcd1602_show_string(13,0,"m");
		
		if(mode==0) //�ֶ�
		{
			LCD1602_Clear_2LINE();
			lcd1602_show_string(1,1,"MANUAL CONTROL");
			while(mode==0)
			{
				if(key_scan(1)==3)
				{
					motor=1;
			
				}
				if(key_scan(1)==4)
				{
					motor=0;
				}
				dis=GetDistance(); //ѭ������ˮλ
				sprintf(distan,"%.2f",dis);	//��ʽ���ַ���
				lcd1602_show_string(9,0,distan);
				lcd1602_show_string(13,0,"m");
				TH0=0,TL0=0;	//��ն�ʱ��
				delay_ms(80);	//���һ��ʱ����ٴβ���
				
			}
			motor=0;
			LCD1602_Clear_2LINE();
		}
		else //�Զ�
		{
			
			lcd1602_show_string(0,1,"L:");
			lcd1602_show_string(2,1,lower);
			lcd1602_show_string(6,1,"m");
	
			lcd1602_show_string(8,1,"H:");
			lcd1602_show_string(10,1,higher);
			lcd1602_show_string(14,1,"m");
			if(dis<low) //ˮλ�жϣ��Ƿ�ȱˮ
			{
			
				motor=1; //ȱˮ�����
				while(1)
				{
					dis=GetDistance(); //��ˮ�����в���ˮλ
					if(mode==0) //�ֶ�����
					{
						motor=0;
						break;
					}
					if(dis>high)	//ˮλ�ﵽ�رյ��������ѭ��
					{
						motor=0;
						break;						
					}
					
					sprintf(distan,"%.2f",dis);	//��ʾˮλֵ
					lcd1602_show_string(9,0,distan);
					lcd1602_show_string(13,0,"m");
					TH0=0,TL0=0;
					delay_ms(80);				
				}
			}					
		}
		TH0=0,TL0=0;	//��ն�ʱ��
		delay_ms(80);	//���һ��ʱ����ٴβ���		
	}

}