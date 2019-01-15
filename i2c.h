#ifndef _I2C_H
#define _I2C_H
#include "comm.h"
#define FSCL 1000000
//端口宏定义
void i2cInit();                //初始化I2c
void i2cStart();               //启动总线
void i2cStop();                //停止总线
void i2cAck();                 //发送ACK确认
void i2cNoAck();               //发送NOACK确认
void i2cWriteByte(uchar data); //I2C写一字节数据
void i2cRead(uchar deviceAddress,uchar address,uchar *Data,uchar Bytes); //写数据
void i2cWrite(uchar deviceAddress,uchar address,uchar *Data,uchar Bytes);//读数据
#endif
