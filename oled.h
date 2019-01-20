 /*
 * oled.h
 *
 * Created: 2018/11/8 15:27:41
 *  Author: 陈志伟
 */ 


#ifndef _OLED_H
#define _OLED_H

#include <avr/pgmspace.h>
#include "comm.h"

#define OLED_DC (1<<PF0)
#define OLED_DC_LOW  PORTF&=~OLED_DC
#define OLED_DC_HIGH PORTF|=OLED_DC
#define OLED_RST (1<<PF1)
#define OLED_RST_LOW  PORTF&=~OLED_RST
#define OLED_RST_HIGH PORTF|=OLED_RST

#define OLED_SCK (1<<PF3)
#define OLED_SCK_LOW  PORTF&=~OLED_SCK
#define OLED_SCK_HIGH PORTF|=OLED_SCK
#define OLED_SDO (1<<PF2)
#define OLED_SDO_LOW  PORTF&=~OLED_SDO
#define OLED_SDO_HIGH PORTF|=OLED_SDO

void oledWriteByte(uchar data);
void oledData(uchar data);
void oledCmd(uchar cmd);
void oledInit();
void oledClr();
void oledPos(uchar x, uchar y);
void oledChar(uchar x,uchar y,uchar start,uchar num,const uchar *data);
void oledCharInverse(uchar x,uchar y,uchar start,uchar num,const uchar *data);
void oledZh(uchar x,uchar y,uchar start,uchar num,const uchar *data);
void oledZhInverse(uchar x,uchar y,uchar start,uchar num,const uchar *data);

#endif /* OLED_H_ */
