#ifndef _Ultrasonic_H
#define _Ultrasonic_H

#include "public.h"
/*���峬����ģ������*/
sbit Trig=P2^1;
sbit Echo=P2^0;
/*��������*/
float GetDistance();
void Delay20us();
void timer0_init();
void ultrasonic_init();
#endif