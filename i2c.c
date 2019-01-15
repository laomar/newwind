#include "i2c.h"
//初始化I2c
void i2cInit(){
	TWSR= 0x00;//不分频
	TWBR=(char)(F_CPU/FSCL-16)/2;//设置波特率
}
//I2C起始条件
void i2cStart(){
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}
//I2C停止条件
void i2cStop(){
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
//发ACK应答
void i2cAck(){
	TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}
//发NOACK应答
void i2cNoAck(){
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}
//发送1字节
void i2cWriteByte(uchar Data){
	TWDR=Data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
}
//I2C写数据
void i2cWrite(uchar deviceAddress,uchar address,uchar *data,uchar bytes){
	i2cStart();//启动总线
	i2cWriteByte(deviceAddress);//发送器件地址
	i2cWriteByte(address);//发送地址
	while(bytes--){
		i2cWriteByte(*data);//发送数据
		data++;
	}
	i2cStop();//停止总线
	//delayMS(10);
}
//I2C读数据
void i2cRead(uchar deviceAddress,uchar address,uchar *data,uchar bytes){
	uchar i;
	i2cStart();//启动总线
	i2cWriteByte(deviceAddress);//发送器件写地址
	i2cWriteByte(address);//发送器件子地址
	i2cStart();//启动总线
	i2cWriteByte(deviceAddress+1);//发送器件读地址
	for(i=0;i<bytes;i++){
		if(i==bytes-1) i2cNoAck();//发送NoAck应答
		else i2cAck();//发送Ack应答
		*data=TWDR;
		data++;
	}
	i2cStop();//停止总线
	//delayMS(10);
}
