#ifndef _Ultrasonic_H
#define _Ultrasonic_H

#include "public.h"
/*定义超声波模块引脚*/
sbit Trig=P2^1;
sbit Echo=P2^0;
/*函数声明*/
float GetDistance();
void Delay20us();
void timer0_init();
void ultrasonic_init();
#endif