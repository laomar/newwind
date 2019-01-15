#include "ds1302.h"

void ds1302WriteByte(uchar byte){
    uchar i;
    for(i=0;i<8;i++){
        DS1302_SCLK_LOW;
        if(byte&0x01){
            DS1302_IO_HIGH;
        }else{
            DS1302_IO_LOW;
        }
        DS1302_SCLK_HIGH;
        _delay_us(10);
        byte>>=1;
    }
}

void ds1302Write(uchar addr,uchar data){
    DS1302_OUT;
    DS1302_CS_LOW;
    DS1302_SCLK_LOW;
    DS1302_CS_HIGH;
    ds1302WriteByte(addr);
    ds1302WriteByte(data);
    DS1302_CS_LOW;
}

uchar ds1302Read(uchar addr){
    uchar i,data=0;
    DS1302_OUT;
    DS1302_CS_LOW;
    DS1302_SCLK_LOW;
    DS1302_CS_HIGH;
    ds1302WriteByte(addr+1);
    DS1302_IN;
    DS1302_IO_HIGH;
    for(i=0;i<8;i++){
        DS1302_SCLK_LOW;
        _delay_us(10);
        data>>=1;
        if(DS1302_DATA) data|=0x80;
        DS1302_SCLK_HIGH;
    }
    DS1302_CS_LOW;
    return data;
}

uchar BcdToDec(uchar bcd){  
    return (bcd >> 4) *10+(bcd &0x0f); 
}

uchar DecToBcd(uchar dec){
    return ((dec / 10) *16+dec % 10);
}

void ds1302Init(){
    ds1302Write(0x80,ds1302Read(0x80)&0x7F);
}