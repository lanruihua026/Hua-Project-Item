#include "Ultrasonic.h"
#include <intrins.h>

void timer0_init()	//定时器0初始化
{
	TMOD=0x01; //定时器0工作方式1
	TH0=0;
	TL0=0;
	EA=0;	//关闭总中断
	ET0=0;
	TR0=0;	//关闭定时器
	TF0=0;
}
void Delay20us(void)	//@12.000MHz，20us延迟函数
{
	unsigned char data i;

	_nop_();
	i = 7;
	while (--i);
}

void ultrasonic_init() //超声波初始化
{
	
	Trig=0;
	Echo=1;
	timer0_init();
	
}

float GetDistance()
{
	float ss;					// 用于记录测得的距离
	float correctionFactor = 1.02/1.005;  // 校准系数，根据实验调整。1.02表示测量值整体稍微增加2%
	Trig=1;				// 给超声波模块一个开始脉冲
	Delay20us(); //延迟20us
	Trig=0;	//拉低
	while(Echo==0);	// 等待超声波模块的返回脉冲，接收到返回脉冲为高电平
	TH0=0x00;	//定时器0清零
	TL0=0x00;
	TR0=1;						// 启动定时器，开始计时
	while(Echo==1);		// 等待超声波模块的返回脉冲结束，返回脉冲结束为低电平
	TR0=0;						// 停止定时器，停止计时
	//返回测量值，单位为米
	ss=(((TH0*256+TL0)*0.00034)/2);		// 1.距离cm=（时间us * 速度cm/us）/2，2.真空中声速340m/s.3.	
	return ss*correctionFactor;	//测量值乘上校准系数	
}


