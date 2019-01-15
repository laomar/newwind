#include "at93c46.h"
//写字节
void at93c46WriteByte(uchar Data,uchar bytes){
    uchar i;
    for(i=0;i<bytes;i++){
		AT93C46_SCK_LOW;
        if(Data&0x80) AT93C46_SDI_HIGH;
		else AT93C46_SDI_LOW;
        AT93C46_SCK_HIGH;
        _delay_us(10);
        Data<<=1;
    }
}
//读字节
uchar at93c46ReadByte(){
    uchar TmpData=0x00;
	uchar i;
	AT93C46_SCK_LOW;
    for(i=0;i<8;i++){
        AT93C46_SCK_HIGH;
		TmpData<<=1;
        _delay_us(10);
        if(AT93C46_DATA) TmpData|=1;
        AT93C46_SCK_LOW;
    }
    return TmpData;
}
//写使能
void at93c46EWEN(){
    AT93C46_CS_HIGH;
    at93c46WriteByte(0x98,10);
    AT93C46_CS_LOW;
}
//写保护
void at93c46EWDS(){
    AT93C46_CS_HIGH;
    at93c46WriteByte(0x80,10);
    AT93C46_CS_LOW;
}
//读数据
uchar at93c46Read(uchar addr){
    uchar TmpData;
    addr<<=1;
    at93c46EWEN();
    AT93C46_CS_HIGH;
    at93c46WriteByte(0xC0,3);
    at93c46WriteByte(addr,7);
    TmpData=at93c46ReadByte();
    AT93C46_CS_LOW;
    at93c46EWDS();
    return TmpData;
}
//写数据
void at93c46Write(uchar addr,uchar data){
    addr<<=1;
    at93c46EWEN();
    AT93C46_CS_HIGH;
    at93c46WriteByte(0xA0,3);
    at93c46WriteByte(addr,7);
    at93c46WriteByte(data,8);
    AT93C46_CS_LOW;
    AT93C46_CS_HIGH;
    while(!(AT93C46_DATA)){
      AT93C46_SCK_LOW;
      _delay_us(10);
	  AT93C46_SCK_HIGH;
	}
    AT93C46_CS_LOW;
    at93c46EWDS();
    _delay_ms(10);
}