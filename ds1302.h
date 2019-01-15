/* 
 * File:   ds1302.h
 * Author: czwgo
 *
 * Created on 2018年11月15日, 下午4:58
 */

#ifndef DS1302_H
#define	DS1302_H

#include "comm.h"

#define DS1302_CS        (1<<PB6)
#define DS1302_CS_LOW    PORTB&=~DS1302_CS
#define DS1302_CS_HIGH   PORTB|=DS1302_CS
#define DS1302_IO        (1<<PB5)
#define DS1302_IO_LOW    PORTB&=~DS1302_IO
#define DS1302_IO_HIGH   PORTB|=DS1302_IO
#define DS1302_OUT       DDRB|=DS1302_IO
#define DS1302_IN        DDRB&=~DS1302_IO
#define DS1302_DATA      PINB&DS1302_IO
#define DS1302_SCLK      (1<<PB4)
#define DS1302_SCLK_LOW  PORTB&=~DS1302_SCLK
#define DS1302_SCLK_HIGH PORTB|=DS1302_SCLK

void ds1302WriteByte(uchar byte);
void ds1302Write(uchar addr,uchar data);
void ds1302Init();
uchar ds1302Read(uchar addr);
uchar BcdToDec(uchar bcd);
uchar DecToBcd(uchar dec);

#endif	/* DS1302_H */
