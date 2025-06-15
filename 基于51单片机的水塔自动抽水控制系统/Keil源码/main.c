#include "lcd1602.h"
#include "public.h"
#include <intrins.h>
#include "Ultrasonic.h"
#include <stdio.h>
#include "standaloneKey.h"

/*相关变量声明*/
u8 i;
float dis;	//用于超声波存储测量值
u8 distan[8];
float low=0.50,high=3.00; //设定水位阈值
u8 lower[8],higher[8];
sbit motor=P2^4; //定义电机管脚，仿真中用继电器代替
sbit mode=P1^7; //手动自动控制位

void main()
{
	motor=0;	//电机初始化关闭
	timer0_init();	//定时器0初始化
	lcd1602_init(); //lcd1602初始化
	lcd1602_clear();	//lcd1602清屏
	
	sprintf(lower,"%.2f",low);	//高低水位转字符串
	sprintf(higher,"%.2f",high);
	
	lcd1602_show_string(0,0,"LEVEL:");	//lcd1602显示水位
	
	lcd1602_show_string(0,1,"L:");
	lcd1602_show_string(2,1,lower);
	lcd1602_show_string(6,1,"m");
	
	lcd1602_show_string(8,1,"H:");
	lcd1602_show_string(10,1,higher);
	lcd1602_show_string(14,1,"m");
	ultrasonic_init(); //超声波模块初始化
	
	/*抽水控制*/
	while(1)
	{
	
		dis=GetDistance(); //上电后先测第一次
		sprintf(distan,"%.2f",dis);	//格式化字符串
		lcd1602_show_string(9,0,distan);
		lcd1602_show_string(13,0,"m");
		
		if(mode==0) //手动
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
				dis=GetDistance(); //循环测量水位
				sprintf(distan,"%.2f",dis);	//格式化字符串
				lcd1602_show_string(9,0,distan);
				lcd1602_show_string(13,0,"m");
				TH0=0,TL0=0;	//清空定时器
				delay_ms(80);	//间隔一段时间后再次测量
				
			}
			motor=0;
			LCD1602_Clear_2LINE();
		}
		else //自动
		{
			
			lcd1602_show_string(0,1,"L:");
			lcd1602_show_string(2,1,lower);
			lcd1602_show_string(6,1,"m");
	
			lcd1602_show_string(8,1,"H:");
			lcd1602_show_string(10,1,higher);
			lcd1602_show_string(14,1,"m");
			if(dis<low) //水位判断，是否缺水
			{
			
				motor=1; //缺水开电机
				while(1)
				{
					dis=GetDistance(); //抽水过程中测量水位
					if(mode==0) //手动结束
					{
						motor=0;
						break;
					}
					if(dis>high)	//水位达到关闭电机，跳出循环
					{
						motor=0;
						break;						
					}
					
					sprintf(distan,"%.2f",dis);	//显示水位值
					lcd1602_show_string(9,0,distan);
					lcd1602_show_string(13,0,"m");
					TH0=0,TL0=0;
					delay_ms(80);				
				}
			}					
		}
		TH0=0,TL0=0;	//清空定时器
		delay_ms(80);	//间隔一段时间后再次测量		
	}

}