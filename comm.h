#ifndef _COMM_H
#define _COMM_H
//全局宏定义
#define uint unsigned int
#define uchar unsigned char
#define ulong unsigned long
#define F_CPU 14745600UL       //晶振频率
#include <util/delay.h>
#include <avr/io.h>

#define RUN (1<<PE3)//运行指示灯
#define RUN_ON  PORTE^=RUN
#define RUN_OFF PORTE|=RUN

#define ALARM_LED (1<<PE2)//报警指示灯
#define ALARM_ON  PORTE&=~ALARM_LED
#define ALARM_OFF PORTE|=ALARM_LED

#define AIR (1<<PG0)//空调开关
#define AIR_ON  PORTG&=~AIR
#define AIR_OFF PORTG|=AIR

#define WIND (1<<PG1)//风机开关
#define WIND_ON  PORTG&=~WIND
#define WIND_OFF PORTG|=WIND
#define WIND_DIR (1<<PC0)//风机方向
#define WIND_CCW  PORTC&=~WIND_DIR
#define WIND_CW   PORTC|=WIND_DIR
#define BRUSH (1<<PC2)//风机刷子
#define BRUSH_ON  PORTC&=~BRUSH
#define BRUSH_OFF PORTC|=BRUSH

#define WIND2 (1<<PC1)//风机2开关
#define WIND2_ON  PORTC&=~WIND2
#define WIND2_OFF PORTC|=WIND2

#endif