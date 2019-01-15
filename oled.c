 /*
 * oled.c
 *
 * Created: 2018/11/8 18:41:47
 *  Author: 陈志伟
 */
#include "oled.h"
//写字节
void oledWriteByte(uchar data){
    for(uchar i=0;i<8;i++){			  
		OLED_SCK_LOW;
		if(data&0x80){
            OLED_SDO_HIGH;
        }else {
            OLED_SDO_LOW;
        }
		OLED_SCK_HIGH;
		data<<=1;
	}
}
//写数据
void oledData(uchar data){
    OLED_DC_HIGH;
    oledWriteByte(data);
    OLED_DC_HIGH;
}
//写命令
void oledCmd(uchar cmd){
    OLED_DC_LOW;
    oledWriteByte(cmd);
    OLED_DC_HIGH;
}
//OLED唤醒
void oledON(void){
	oledCmd(0X8D);  //设置电荷泵
	oledCmd(0X14);  //开启电荷泵
	oledCmd(0XAF);  //OLED唤醒
}

//OLED休眠
void oledOFF(void){
	oledCmd(0X8D);  //设置电荷泵
	oledCmd(0X10);  //关闭电荷泵
	oledCmd(0XAE);  //OLED休眠
}
//清屏
void oledClr(){
	uchar y,x;
	for(y=0;y<8;y++){
		oledCmd(0xb0+y);
		oledCmd(0x01);
		oledCmd(0x10);
		for(x=0;x<129;x++)
		oledData(0);
	}
}
//设置坐标
void oledPos(uchar x, uchar y) {
	oledCmd(0xb0+y);
	oledCmd(((x&0xf0)>>4)|0x10);
	oledCmd((x&0x0f)|0x01);
}
//初始化
void oledInit(){
    //OLED_RST_HIGH;
	//_delay_ms(100);
    OLED_RST_LOW;
    _delay_ms(100);
    OLED_RST_HIGH;
	oledCmd(0xae);//--turn off oled panel
	oledCmd(0x00);//---set low column address
	oledCmd(0x10);//---set high column address
	oledCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	oledCmd(0x81);//--set contrast control register
	oledCmd(0xFF); // Set SEG Output Current Brightness
	oledCmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	oledCmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	oledCmd(0xa6);//--set normal display
	oledCmd(0xa8);//--set multiplex ratio(1 to 64)
	oledCmd(0x3f);//--1/64 duty
	oledCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	oledCmd(0x00);//-not offset
	oledCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	oledCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	oledCmd(0xd9);//--set pre-charge period
	oledCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	oledCmd(0xda);//--set com pins hardware configuration
	oledCmd(0x12);
	oledCmd(0xdb);//--set vcomh
	oledCmd(0x40);//Set VCOM Deselect Level
	oledCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	oledCmd(0x02);//
	oledCmd(0x8d);//--set Charge Pump enable/disable
	oledCmd(0x14);//--set(0x10) disable
	oledCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	oledCmd(0xa6);// Disable Inverse Display On (0xa6/a7)
	oledCmd(0xaf);//--turn on oled panel
	oledClr(); //初始清屏
}
//显示字符
void oledChar(uchar x,uchar y,uchar start,uchar num,const uchar *data){
	for (uchar i=0;i<num;i++){
		oledPos(x+8*i+2, y);
		for(uchar j=0;j<8;j++){
		    oledData(data[(start+i)*16+j]);
		}
		oledPos(x+8*i+2, y+1);
		for(uchar j=0;j<8;j++){
		    oledData(data[(start+i)*16+j+8]);
		}
	}
}
//反色显示字符
void oledCharInverse(uchar x,uchar y,uchar start,uchar num,const uchar *data){
	for (uchar i=0;i<num;i++){
		oledPos(x+8*i+2, y);
		for(uchar j=0;j<8;j++){
		    oledData(~data[(start+i)*16+j]);
		}
		oledPos(x+8*i+2, y+1);
		for(uchar j=0;j<8;j++){
		    oledData(~data[(start+i)*16+j+8]);
		}
	}
}
//显示汉字
void oledZh(uchar x,uchar y,uchar start,uchar num,const uchar *data){
	for (uchar i=0;i<num;i++){
		oledPos(x+16*i+2, y);
		for(uchar j=0;j<16;j++){
		    oledData(data[(start+i)*32+j]);
		}
		oledPos(x+16*i+2, y+1);
		for(uchar j=0;j<16;j++){
		    oledData(data[(start+i)*32+j+16]);
		}
	}
}
//反色显示汉字
void oledZhInverse(uchar x,uchar y,uchar start,uchar num,const uchar *data){
	for (uchar i=0;i<num;i++){
		oledPos(x+16*i+2, y);
		for(uchar j=0;j<16;j++){
		    oledData(~data[(start+i)*32+j]);
		}
		oledPos(x+16*i+2, y+1);
		for(uchar j=0;j<16;j++){
		    oledData(~data[(start+i)*32+j+16]);
		}
	}
}