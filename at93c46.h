/* 
 * File:   at93c46.h
 * Author: godart
 *
 * Created on 2018年12月30日, 下午11:01
 */

#ifndef AT93C46_H
#define	AT93C46_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "comm.h"

#define AT93C46_CS       (1<<PD7)
#define AT93C46_CS_LOW   PORTD&=~AT93C46_CS
#define AT93C46_CS_HIGH  PORTD|=AT93C46_CS
#define AT93C46_SCK      (1<<PD6)
#define AT93C46_SCK_LOW  PORTD&=~AT93C46_SCK
#define AT93C46_SCK_HIGH PORTD|=AT93C46_SCK
#define AT93C46_SDI      (1<<PD5)
#define AT93C46_SDI_LOW  PORTD&=~AT93C46_SDI
#define AT93C46_SDI_HIGH PORTD|=AT93C46_SDI
#define AT93C46_SDO      (1<<PD4)
#define AT93C46_DATA     PIND&AT93C46_SDO

void at93c46WriteByte(uchar data,uchar bytes);
uchar at93c46ReadByte();
void at93c46EWEN();
void at93c46EWDS();
uchar at93c46Read(uchar addr);
void at93c46Write(uchar addr,uchar data);

#ifdef	__cplusplus
}
#endif

#endif	/* AT93C46_H */

