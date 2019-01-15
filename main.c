#include <math.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include "comm.h"
#include "char.h"
#include "i2c.h"
#include "oled.h"
#include "ds1302.h"
#include "rn8302.h"
#include "at93c46.h"

long item,otem;//内外温度
uchar ihum,ohum;//内外湿度
uchar maxtem=25;//温度上限
uchar mintem=20;//温度下限
uchar temdiff=3;//温差
uchar minhum=0;//最小湿度
uchar maxhum=80;//最大湿度
uchar wind=0;//新风状态
uchar air=0;//空调状态
uchar airswitch=0;//空调开关方式
uchar iswind=0;//新风标志
uchar isair=0;//空调标志
uchar isdelay=0;//是否延时
uchar delay=5;//延时启动时间
ulong delaynum=0;//延时中断次数
uint  time0num=0;//T0中断次数
uchar istem=0;//测温标志
uchar istime=0;//新风空调计时标志
uchar time[6]={18,1,1,0,0,0};//时间数据
uchar max=59;//时间最大值
uchar min=0;//时间最小值
uchar year=0;//年标志
uchar month=0;//月标志
uchar day=0;//天标志
uchar hour=24;//小时标志
uchar confbuf[10];//配置缓存区
uint  windday=0;//新风运行时间
uchar windhour=0;
uchar windmin=0;
uint  airday=0;//空调运行时间
uchar airhour=0;
uchar airmin=0;
ulong es=0;//累计耗电
ulong ey=0;//本年耗电
uint  em=0;//本月耗电
uint  et=0;//今日耗电*100
uchar disbuf[8];//显示缓存区
uchar isrn=0;//读电表标志
uchar isclr=1;//清屏标志
ulong ua,ub,uc,ia,ib,ic,pt;//电表电压电流功率
ulong ept=0;//电表电量读数
uint  er=0;//耗电读数余数
uint  efr=0;//耗电0.01读数余数
uchar databuf[16];//数据缓存区
uchar isalarm=0;//是否开启报警
uchar editbuf[18];//编辑缓存区
uchar editnum=0;//编辑位数
uchar isif=0;//是否
uchar addr[9]={0,0,0,0,0,0,0,0,0};//设备地址

#define TIMEOUT  15;//操作超时时间
uchar timeout=TIMEOUT;

#define KEYTIME  10;//按键间隔时间
uchar keytime=0;

#define PASS      0x0000//操作员密码
#define ADMINPASS 0x0000//管理员密码
#define PASSTIME  10//登录超时时间
uchar islogin=0;//是否登录
uchar isadmin=0;//是否是管理员
uchar passnum=0;//密码输入个数
uchar passtime=0;//登录超时计时
uchar passinput[4]={0,0,0,0};//输入的密码

#define HOME     0
#define MENU     1
#define LOGIN    2
#define ALARM    3
#define MENUS    4
uchar page=HOME;//页面索引
uchar pagenum=1;//页码
uchar menunum=0;//菜单索引

#define UP    0xE0
#define DOWN  0xD0
#define OK    0xB0
#define RET   0x70
#define UPRET 0x60
#define NIL   0xF0
uchar key=NIL;//键值

#define ENIL  0x00//无错误
#define EMEM  0xE0//存储器故障
#define EISHT 0xE1//内温传感器故障
#define EOSHT 0xE2//外温传感器故障
#define EAIRU 0xE3//空调电压故障
#define EAIRI 0xE4//空调电流故障
#define EAIRS 0xE5//空调控制故障
uchar err=ENIL;//错误码

//计算校验和
uchar checksum(uchar *buf,uchar bytes){
    uchar sum=0;
    uchar i;
    for(i=0;i<bytes;i++){
		sum+=buf[i];
	}
	sum=0xFF-sum;
    return sum;
}
//10进制BCD
void DecBcd(long digit,uchar *buf,uchar len){
    uchar i;
    ulong mul=1;
    digit=fabs(digit);
    for(i=0;i<=len;i++){
        buf[i]=digit%(mul*10)/mul;
        mul*=10;
    }
}
//16进制BCD
void HexBcd(long digit,uchar *buf,uchar len){
    uchar i;
    ulong mul=1;
    for(i=0;i<=len;i++){
        buf[i]=digit%(mul*16)/mul;
        mul*=16;
    }
}
//配置缓存区存入变量
void readConfig(){
    maxtem=confbuf[0];
    mintem=confbuf[1];
    temdiff=confbuf[2];
    airswitch=confbuf[3];
    delay=confbuf[4];
    maxhum=confbuf[5];
    isalarm=confbuf[6];
}
//配置变量存入缓存区
void writeConfig(){
    confbuf[0]=maxtem;
    confbuf[1]=mintem;
    confbuf[2]=temdiff;
    confbuf[3]=airswitch;
    confbuf[4]=delay;
    confbuf[5]=maxhum;
    confbuf[6]=isalarm;
    confbuf[7]=checksum(confbuf,7);
}
//保存配置
uchar saveConfig(){
    uchar i;
    writeConfig();
    for(i=0;i<8;i++) at93c46Write(0x00+i,confbuf[i]);//存入当前配置
    for(i=0;i<8;i++) confbuf[i]=at93c46Read(0x00+i);
    if(checksum(confbuf,7)!=confbuf[7]){
        err=EMEM;
        return 0;
    }else{
        if(err==EMEM) err=ENIL;
        return 1;
    }
}
//初始化配置
void initConfig(){
    uchar i;
    writeConfig();
    for(i=0;i<8;i++) at93c46Write(0x08+i,confbuf[i]);//存入默认配置
    for(i=0;i<8;i++) confbuf[i]=at93c46Read(0x00+i);//读取当前配置
    if(checksum(confbuf,7)==confbuf[7]){//校验正确载入
        readConfig();
        if(airswitch==2) AIR_ON;
        for(i=0;i<10;i++) confbuf[i]=at93c46Read(0x16+i);
        if(checksum(confbuf,9)==confbuf[9]){
            for(i=0;i<9;i++) addr[i]=confbuf[i];
        }
    }else{
        saveConfig();
    }
}
//空调新风数据写入
void saveData(){
    uchar i;
    databuf[0]=windday/256;
    databuf[1]=windday%256;
    databuf[2]=windhour;
    databuf[3]=windmin;
    databuf[4]=airday/256;
    databuf[5]=airday%256;
    databuf[6]=airhour;
    databuf[7]=airmin;
    databuf[15]=checksum(databuf,8);
    for(i=0;i<16;i++) at93c46Write(0x20+i,databuf[i]);
    for(i=0;i<16;i++) databuf[i]=at93c46Read(0x20+i);
    if(checksum(databuf,8)!=databuf[15]) err=EMEM;
    else{
        if(err==EMEM) err=ENIL;
    }
    databuf[0]=er%256;
    databuf[1]=er/256;
    databuf[2]=et%256;
    databuf[3]=et/256;
    databuf[4]=em%256;
    databuf[5]=em/256;
    databuf[6]=ey;
    databuf[7]=ey>>8;
    databuf[8]=ey>>16;
    databuf[9]=ey>>24;
    databuf[10]=es;
    databuf[11]=es>>8;
    databuf[12]=es>>16;
    databuf[13]=es>>24;
    databuf[15]=checksum(databuf,14);
    for(i=0;i<16;i++) at93c46Write(0x30+i,databuf[i]);
    for(i=0;i<16;i++) databuf[i]=at93c46Read(0x30+i);
    if(checksum(databuf,14)!=databuf[15]) err=EMEM;
    else{
        if(err==EMEM) err=ENIL;
    }
}
//空调新风数据读取
void initData(){
    uchar i;
    for(i=0;i<16;i++) databuf[i]=at93c46Read(0x20+i);
    if(checksum(databuf,8)==databuf[15]){
        windday=databuf[0]*256+databuf[1];
        windhour=databuf[2];
        windmin=databuf[3];
        airday=databuf[4]*256+databuf[5];
        airhour=databuf[6];
        airmin=databuf[7];
    }
    for(i=0;i<16;i++) databuf[i]=at93c46Read(0x30+i);
    if(checksum(databuf,14)==databuf[15]){
        er=databuf[1]*256+databuf[0];
        et=databuf[3]*256+databuf[2];
        em=databuf[5]*256+databuf[4];
        ey=databuf[9]*pow(2,24)+databuf[8]*pow(2,16)+databuf[7]*pow(2,8)+databuf[6];
        es=databuf[13]*pow(2,24)+databuf[12]*pow(2,16)+databuf[11]*pow(2,8)+databuf[10];
    }
}
//端口初始化
void initPort(){
    //继电器复位
    PORTG|=0x03;
    DDRG|=0x03;
    PORTC|=0x07;
    DDRC|=0x07;
    DDRD|=0xE0;
    
    DDRE|=0x0C;
    RUN_ON;//运行指示灯开
    ALARM_OFF;//报警指示灯关
    PORTE|=0xF0;//使能上拉电阻
    EICRB=0xAA;//按键下降沿中断
    EIMSK=0xF0;//按键开中断
    DDRF|=0X0F;
    DDRB|=0x77;
}
//定时器0初始化
void initTimer0(){
    TIMSK=0x01;//允许T0溢出中断
    TCNT0=256-0.01/(1024.0/F_CPU);//定时器初值10ms
    TCCR0=0x07;//普通计数模式，1024分频
}
//定时器1初始化
void initTimer1(){
	TCCR1B=0x02;//8分频 计一个数为1us
}
//USART0初始化函数
void initUsart0(){
	UCSR0B=(1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);//使能串口0接收和发送 使能接收中断
	UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);//8位数据
	UBRR0L=0x5F;//波特率9600
	UBRR0H=0x00;
}
//USART1初始化函数
void initUsart1(){
	UCSR1B=(1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1);//使能串口1接收和发送 使能接收中断
	UCSR1C=(1<<UCSZ11)|(1<<UCSZ10);//8位数据
	UBRR1L=0x5F;//波特率9600
	UBRR1H=0x00;
}
//串口0接收中断处理程序
ISR(USART0_RX_vect){
	PORTA=UDR0;
}
//串口1接收中断处理程序
ISR(USART1_RX_vect){
	PORTA=UDR1;
}
//定时器0溢出中断
ISR(TIMER0_OVF_vect){
    TCNT0=256-0.01/(1024.0/F_CPU);//定时器重设初值10ms
    if(keytime>0) keytime--;
    time0num++;
    if(time0num>=6000){
        time0num=0;
        istime=1;//分钟标志
        if(passtime>0){//登录倒计时
            passtime--;
            if(passtime==0){
                islogin=0;
                isadmin=0;
            }
        }
        if(timeout>0){//操作倒计时
            timeout--;
            if(timeout==0){
                page=HOME;
                pagenum=1;
                isclr=1;
            }
        }
    }
    if(time0num%100==0) istem=1;//测温标志
    if(time0num%60==0) isrn=1;//读电表标志
    if(time0num%40==0){//灯闪烁
        RUN_ON;
        if(err&&isalarm) ALARM_ON;
        else ALARM_OFF;
    }
    //动作延时
	delaynum++;
	if(delaynum>delay*6000){
		isdelay=0;
		delaynum=0;
	}
}
//温度湿度测量
uchar readSht(uchar isout){
	uchar sht[6];
	uchar address=0x88;
	if(isout==0) address+=2;
	i2cStart();
    if ((TWSR & 0xF8) != 0x08&&(TWSR & 0xF8) != 0x10) return 0;
	i2cWriteByte(address);
    if ((TWSR & 0xF8) != 0x18) return 0;
	i2cWriteByte(0x21);
    if ((TWSR & 0xF8) != 0x28) return 0; 
	i2cWriteByte(0x26);
    if ((TWSR & 0xF8) != 0x28) return 0;
	_delay_ms(10);
	i2cStart();
    if ((TWSR & 0xF8) != 0x10) return 0; 
	i2cWriteByte(address+1);
    if ((TWSR & 0xF8) != 0x40) return 0;
	for(uchar i=0;i<6;i++){
		if(i==5){
            i2cNoAck();//发送NoAck应答
            if ((TWSR & 0xF8) != 0x58) return 0; 
		}else{
            i2cAck();//发送Ack应答
            if ((TWSR & 0xF8) != 0x50) return 0; 
        }
		sht[i]=TWDR;
	}
	i2cStop();
	if(isout){
		otem=175.0*(sht[0]*256.0+sht[1])/6553.5-450;
	    ohum=(sht[3]*256.0+sht[4])/655.35;
	}else{
	    item=175.0*(sht[0]*256.0+sht[1])/6553.5-450;
	    ihum=(sht[3]*256.0+sht[4])/655.35;	
	}
    return 1;
}
//读取时间
void readTime(){
    time[0]=BcdToDec(ds1302Read(0x8C));
    time[1]=BcdToDec(ds1302Read(0x88));
    time[2]=BcdToDec(ds1302Read(0x86));
    time[3]=BcdToDec(ds1302Read(0x84));
    time[4]=BcdToDec(ds1302Read(0x82));
    time[5]=BcdToDec(ds1302Read(0x80)&0x7F);
    if(year==0) year=time[0];
    if(month==0) month=time[1];
    if(day==0) day=time[2];
    if(hour==24) hour=time[3];
    if(year!=time[0]&&month==1){//过年
        year=time[0];
        ey=0;
    }
    if(month!=time[1]&&day==1){//过月
        month=time[1];
        em=0;
    }
    if(day!=time[2]&&hour==1){//过天
        day=time[2];
        et=0;
    }
    if(hour!=time[3]){//过时
        hour=time[3];
        saveData();
    }
}
//读电表数据
void readRn8302(){
    rn8302Read(UA,(uchar*)&ua,4);
    ua=(long)(ua*Kv);
    rn8302Read(UB,(uchar*)&ub,4);
    ub=(long)(ub*Kv);
    rn8302Read(UC,(uchar*)&uc,4);
    uc=(long)(uc*Kv);
    if(ua+ub+uc<10*200){//空调电压低
        if(err==0||err==EAIRI||err==EAIRS) err=EAIRU;
    }else{
        if(err==EAIRU) err=0;
    }
    rn8302Read(IA,(uchar*)&ia,4);
    ia=(long)(ia*Ki);
    rn8302Read(IB,(uchar*)&ib,4);
    ib=(long)(ib*Ki);
    rn8302Read(IC,(uchar*)&ic,4);
    ic=(long)(ic*Ki);
    if(ia+ib+ic<1000*0.01){//空调静态电流低
        if(err==0||err==EAIRS) err=EAIRI;
    }else{
        if(err==EAIRI) err=0;
    }
    rn8302Read(PT,(uchar*)&pt,4);
    if(pt&0x80000000) pt=0;
    pt=(long)(pt*Kp);
    if(pt>10*200){//空调开机状态
        air=1;
    }else{
        air=0;
    }
    if(air!=isair){
        if(err==0) err=EAIRS;
    }else{
        if(err==EAIRS) err=0;
    }
    
}
//空调操作
void airAction(uchar ison){
    //485空调
	uchar buf[15]={0xAA,0x00,0x80,0x20};
	if(ison){
        buf[2]=0x10;
        //air=1;
    }//else{
        //air=0;
    //}
	buf[4]=(maxtem+20)*2;
	uchar sum=0;
	uchar i;
	for(i=0;i<14;i++){
		sum+=buf[i];
	}
	buf[14]=0xFF-sum;
	for(i=0;i<15;i++){
		while(!(UCSR0A&(1<<UDRE0)));
		UDR0=buf[i];
	}
    //空调开关
    switch(airswitch){
        case 0:{//按钮方式
            AIR_ON;
            _delay_ms(500);
            AIR_OFF;
            break;
        }
        case 1:{//接通开机
            if(ison) AIR_ON;
            else AIR_OFF;
            break;
        }
        case 2:{//断开开机
            if(ison) AIR_OFF;
            else AIR_ON;
            break;
        }
    }
    isdelay=1;
    delaynum=0;
}
//风机操作
void windAction(uchar ison){
    if(ison){
        WIND_CCW;
        WIND_ON;
        wind=1;
    }else{
        WIND_OFF;
        wind=0;
    }
    isdelay=1;
    delaynum=0;
}
//空调风机条件判断
void airwind(){
	if(isdelay==0){
	    //风机开机
		if(item>=mintem*10&&item<maxtem*10&&item-otem>=temdiff*10&&ohum<maxhum){
			iswind=1;
		}
		//风机关机
		if(item<mintem*10||item>maxtem*10||ohum>=maxhum){
			iswind=0;
		}
		//空调开机
		if(item>=maxtem*10){
			isair=1;
			iswind=0;
		}
		//关闭空调
		if(item<maxtem*10){
			isair=0;
		}
		if(wind!=iswind){
            if(iswind) windAction(1);
			else windAction(0);
		}
		if(air!=isair){
			if(isair) airAction(1);
			else airAction(0);
		}
	}
}
//空调新风计时计量
void airwindtime(){
    uchar e;
    rn8302Read(EPT,(uchar*)&ept,3);
    efr+=ept;
    if(efr*100>=EC){//0.01度计数
        et+=ept*100/EC;
        efr=ept*100%EC;
    }
    er+=ept;
    if(er>=EC){//1度计数
        e=er/EC;
        er=er%EC;
        es+=e;
        ey+=e;
        em+=e;
    }
    if(wind){
        windmin++;
        if(windmin>=60){
            windmin=0;
            windhour++;
        }
        if(windhour>=24){
            windhour=0;
            windday++;
        }
    }
    if(air){
        airmin++;
        if(airmin>=60){
            airmin=0;
            airhour++;
        }
        if(airhour>=24){
            airhour=0;
            airday++;
        }
    }
}
//键盘中断处理程序
ISR(INT7_vect){//返回键
    if(keytime==0){
        keytime=KEYTIME;
        key=PINE&0xF0;
        if(islogin) passtime=PASSTIME;
        timeout=TIMEOUT;
    }
}
ISR(INT6_vect){//确认键
    if(keytime==0){
        keytime=KEYTIME;
        key=PINE&0xF0;
        if(islogin) passtime=PASSTIME;
        timeout=TIMEOUT;
    }
}
ISR(INT5_vect){//下键
    if(keytime==0){
        keytime=KEYTIME;
        key=PINE&0xF0;
        if(islogin) passtime=PASSTIME;
        timeout=TIMEOUT;
    }
}
ISR(INT4_vect){//上键
    if(keytime==0){
        keytime=KEYTIME;
        key=PINE&0xF0;
        if(islogin) passtime=PASSTIME;
        timeout=TIMEOUT;
    }
}
//主页
void home(){
    switch(key){
        case UP:{//上一页
            key=NIL;
            if(pagenum>1){
                pagenum--;
                isclr=1;
            }
            break;
        }
        case DOWN:{//下一页
            key=NIL;
            if(pagenum<4){
                pagenum++;
                isclr=1;
            }
            break;
        }
        case RET:{//查看报警或返回第一页
            key=NIL;
            if(err&&isalarm){
                page=ALARM;
                isclr=1;
                return;
            }else{
                if(pagenum!=1){
                    pagenum=1;
                    isclr=1;
                }
            }
            break;
        }
        case OK:{//进入菜单
            key=NIL;
            page=MENU;
            pagenum=1;
            isclr=1;
            return;
            break;
        }
    }
    switch(pagenum){
        case 1:{
            if(isclr){
                oledClr();
                isclr=0;
                oledZh(0,0,5,2,ch);//空调
	            oledChar(32,0,1,1,symbol);//:
                oledZh(72,0,7,2,ch);//新风
	            oledChar(104,0,1,1,symbol);//:
                oledZh(0,2,0,2,ch);//内温
	            oledChar(32,2,1,1,symbol);//:
                oledZh(88,2,4,1,ch);//内湿
	            oledChar(104,2,1,1,symbol);//:
                oledZh(0,4,2,2,ch);//外温
	            oledChar(32,4,1,1,symbol);//:
                oledZh(88,4,4,1,ch);//外湿
	            oledChar(104,4,1,1,symbol);//:
            }
	        if(air) oledZh(40,0,9,1,ch);//空调状态
	        else oledZh(40,0,10,1,ch);
	        if(wind) oledZh(112,0,9,1,ch);//新风状态
	        else oledZh(112,0,10,1,ch);
	
            DecBcd(item,disbuf,4);//内温
            if(item<0){
			    oledChar(40,2,0,1,symbol);
		    }else{
			    if(disbuf[3]>0) oledChar(40,2,disbuf[3],1,digit);
                else oledChar(40,2,3,1,symbol);
		    }
		    oledChar(48,2,disbuf[2],1,digit);
		    oledChar(56,2,disbuf[1],1,digit);
		    oledChar(64,2,2,1,symbol);
		    oledChar(72,2,disbuf[0],1,digit);

            oledChar(112,2,ihum/10,1,digit);//内湿度
		    oledChar(120,2,ihum%10,1,digit);
            
            DecBcd(otem,disbuf,4);//外温
            if(otem<0){
			    oledChar(40,4,0,1,symbol);
		    }else{
			    if(disbuf[3]>0) oledChar(40,4,disbuf[3],1,digit);
                else oledChar(40,4,3,1,symbol);
		    }
		    oledChar(48,4,disbuf[2],1,digit);
		    oledChar(56,4,disbuf[1],1,digit);
		    oledChar(64,4,2,1,symbol);
		    oledChar(72,4,disbuf[0],1,digit);
            
            oledChar(112,4,ohum/10,1,digit);//外湿度
		    oledChar(120,4,ohum%10,1,digit);
            
            oledChar(0,6,2,1,digit);//2
            oledChar(8,6,0,1,digit);//0
            oledChar(16,6,time[0]/10,1,digit);//年
            oledChar(24,6,time[0]%10,1,digit);
            oledChar(32,6,0,1,symbol);//-
            oledChar(40,6,time[1]/10,1,digit);//月
            oledChar(48,6,time[1]%10,1,digit);
            oledChar(56,6,0,1,symbol);//-
            oledChar(64,6,time[2]/10,1,digit);//日
            oledChar(72,6,time[2]%10,1,digit);
            oledChar(88,6,time[3]/10,1,digit);//时
            oledChar(96,6,time[3]%10,1,digit);
            if(time[5]%2==0){
                oledChar(104,6,1,1,symbol);//:
            }else{
                oledChar(104,6,3,1,symbol);//
            }
            oledChar(112,6,time[4]/10,1,digit);//分
            oledChar(120,6,time[4]%10,1,digit);
            break;
        }
        case 2:{
            if(isclr){
                oledClr();
                isclr=0;
                oledZh(0,0,7,2,ch);//新风
                oledZh(32,0,12,2,ch);//运行
                oledZh(64,0,22,2,ch);//时间
                oledChar(96,0,1,1,symbol);//:
                oledZh(40,2,24,1,ch);//天
                oledZh(72,2,22,1,ch);//时
                oledZh(104,2,25,1,ch);//分
                oledZh(0,4,5,2,ch);//空调
                oledZh(32,4,12,2,ch);//运行
                oledZh(64,4,22,2,ch);//时间
                oledChar(96,4,1,1,symbol);//:
                oledZh(40,6,24,1,ch);//天
                oledZh(72,6,22,1,ch);//时
                oledZh(104,6,25,1,ch);//分
            }
            
            DecBcd(windday,disbuf,5);//新风运行时间
            oledChar(0,2,disbuf[4],1,digit);
            oledChar(8,2,disbuf[3],1,digit);
            oledChar(16,2,disbuf[2],1,digit);
		    oledChar(24,2,disbuf[1],1,digit);
		    oledChar(32,2,disbuf[0],1,digit);
            oledChar(56,2,windhour/10,1,digit);
		    oledChar(64,2,windhour%10,1,digit);
            oledChar(88,2,windmin/10,1,digit);
		    oledChar(96,2,windmin%10,1,digit);

            DecBcd(airday,disbuf,5);//空调运行时间
            oledChar(0,6,disbuf[4],1,digit);
            oledChar(8,6,disbuf[3],1,digit);
            oledChar(16,6,disbuf[2],1,digit);
		    oledChar(24,6,disbuf[1],1,digit);
		    oledChar(32,6,disbuf[0],1,digit);
            oledChar(56,6,airhour/10,1,digit);
		    oledChar(64,6,airhour%10,1,digit);
            oledChar(88,6,airmin/10,1,digit);
		    oledChar(96,6,airmin%10,1,digit);
            break;
        }
        case 3:{
            if(isclr){
                oledClr();
                isclr=0;
                oledZh(32,0,5,2,ch);//空调
                oledZh(64,0,48,2,ch);//耗电
                oledZh(0,2,50,2,ch);//本年
                oledChar(32,2,1,1,symbol);//:
                oledChar(96,2,1,3,letter);//KWH
                oledZh(0,4,50,1,ch);//本
                oledZh(16,4,52,1,ch);//月
                oledChar(32,4,1,1,symbol);//:
                oledChar(96,4,1,3,letter);//KWH
                oledZh(0,6,53,2,ch);//今日
                oledChar(32,6,1,1,symbol);//:
                oledChar(96,6,1,3,letter);//KWH
            }
            DecBcd(ey,disbuf,6);
            oledChar(40,2,disbuf[5],1,digit);
            oledChar(48,2,disbuf[4],1,digit);
            oledChar(56,2,disbuf[3],1,digit);
            oledChar(64,2,disbuf[2],1,digit);
            oledChar(72,2,disbuf[1],1,digit);
            oledChar(80,2,disbuf[0],1,digit);
            DecBcd(em,disbuf,6);
            oledChar(40,4,disbuf[5],1,digit);
            oledChar(48,4,disbuf[4],1,digit);
            oledChar(56,4,disbuf[3],1,digit);
            oledChar(64,4,disbuf[2],1,digit);
            oledChar(72,4,disbuf[1],1,digit);
            oledChar(80,4,disbuf[0],1,digit);
            DecBcd(et,disbuf,5);
            oledChar(40,6,disbuf[4],1,digit);
            oledChar(48,6,disbuf[3],1,digit);
            oledChar(56,6,disbuf[2],1,digit);
            oledChar(64,6,2,1,symbol);//.
            oledChar(72,6,disbuf[1],1,digit);
            oledChar(80,6,disbuf[0],1,digit);
            break;
        }
        case 4:{
            if(isclr){
                oledClr();
                isclr=0;
            }
            oledChar(0,0,10,1,digit);//A
            oledChar(8,0,1,1,symbol);//:
            DecBcd(ua,disbuf,4);
            oledChar(16,0,disbuf[3],1,digit);
            oledChar(24,0,disbuf[2],1,digit);
            oledChar(32,0,disbuf[1],1,digit);
            oledChar(40,0,2,1,symbol);//.
            oledChar(48,0,disbuf[0],1,digit);
            oledChar(56,0,0,1,letter);//V
            DecBcd(ia,disbuf,5);
            if(disbuf[4]>0) oledChar(72,0,disbuf[4],1,digit);
            else oledChar(72,0,3,1,symbol);
            oledChar(80,0,disbuf[3],1,digit);
            oledChar(88,0,2,1,symbol);//.
            oledChar(96,0,disbuf[2],1,digit);
            oledChar(104,0,disbuf[1],1,digit);
            oledChar(112,0,disbuf[0],1,digit);
            oledChar(120,0,10,1,digit);//A
            
            oledChar(0,2,11,1,digit);//B
            oledChar(8,2,1,1,symbol);//:
            DecBcd(ub,disbuf,4);
            oledChar(16,2,disbuf[3],1,digit);
            oledChar(24,2,disbuf[2],1,digit);
            oledChar(32,2,disbuf[1],1,digit);
            oledChar(40,2,2,1,symbol);//.
            oledChar(48,2,disbuf[0],1,digit);
            oledChar(56,2,0,1,letter);//V
            DecBcd(ib,disbuf,5);
            if(disbuf[4]>0) oledChar(72,2,disbuf[4],1,digit);
            else oledChar(72,2,3,1,symbol);
            oledChar(80,2,disbuf[3],1,digit);
            oledChar(88,2,2,1,symbol);//.
            oledChar(96,2,disbuf[2],1,digit);
            oledChar(104,2,disbuf[1],1,digit);
            oledChar(112,2,disbuf[0],1,digit);
            oledChar(120,2,10,1,digit);//A
            
            oledChar(0,4,12,1,digit);//C
            oledChar(8,4,1,1,symbol);//:
            DecBcd(uc,disbuf,4);
            oledChar(16,4,disbuf[3],1,digit);
            oledChar(24,4,disbuf[2],1,digit);
            oledChar(32,4,disbuf[1],1,digit);
            oledChar(40,4,2,1,symbol);//.
            oledChar(48,4,disbuf[0],1,digit);
            oledChar(56,4,0,1,letter);//V
            DecBcd(ic,disbuf,5);
            if(disbuf[4]>0) oledChar(72,4,disbuf[4],1,digit);
            else oledChar(72,4,3,1,symbol);
            oledChar(80,4,disbuf[3],1,digit);
            oledChar(88,4,2,1,symbol);//.
            oledChar(96,4,disbuf[2],1,digit);
            oledChar(104,4,disbuf[1],1,digit);
            oledChar(112,4,disbuf[0],1,digit);
            oledChar(120,4,10,1,digit);//A
            
            DecBcd(pt,disbuf,6);//功率
            oledChar(0,6,disbuf[5],1,digit);
            oledChar(8,6,disbuf[4],1,digit);
            oledChar(40,6,2,1,symbol);
            oledChar(16,6,disbuf[3],1,digit);
            oledChar(24,6,disbuf[2],1,digit);
            oledChar(32,6,disbuf[1],1,digit);
            oledChar(48,6,disbuf[0],1,digit);
            oledChar(56,6,2,1,letter);//W

            break;
        }
    }
}
//菜单页
void menu(){
    if(islogin==0){
        page=LOGIN;
        isclr=1;
        return;
    }
    switch(key){
        case UP:{//上一菜单
            key=NIL;
            if(menunum>0){
                oledChar(0,(menunum%4)*2,3,1,symbol);
                oledChar(8,(menunum%4)*2,3,1,symbol);
                menunum--;
                if((menunum+1)%4==0){
                    pagenum--;
                    isclr=1;
                }
            }
            break;
        }
        case DOWN:{//下一菜单
            key=NIL;
            if(menunum<11||(menunum<13&&isadmin)){
                oledChar(0,(menunum%4)*2,3,1,symbol);
                oledChar(8,(menunum%4)*2,3,1,symbol);
                menunum++;
                if(menunum%4==0){
                    pagenum++;
                    isclr=1;
                }
            }
            break;
        }
        case RET:{//返回主页
            key=NIL;
            page=HOME;
            pagenum=1;
            menunum=0;
            isclr=1;
            return;
            break;
        }
        case OK:{//选择菜单
            key=NIL;
            page=MENUS;
            isclr=1;
            return;
            break;
        }
    }
    switch(pagenum){
        case 1:{
            if(isclr){
                oledClr();
                isclr=0;
                oledZh(16,0,7,2,ch);//0新风
                oledZh(48,0,14,4,ch);//启动温度
                oledZh(16,2,7,2,ch);//1新风
                oledZh(48,2,14,2,ch);//启动
                oledZh(80,2,18,2,ch);//温差
                oledZh(16,4,5,2,ch);//2空调
                oledZh(48,4,14,4,ch);//启动温度
                oledZh(16,6,5,2,ch);//3空调
                oledZh(48,6,9,2,ch);//开关
                oledZh(80,6,63,2,ch);//方式
            }
            break;
        }
        case 2:{
            if(isclr){
                oledClr();
                isclr=0;
                oledZh(16,0,7,2,ch);//4新风
                oledZh(48,0,4,1,ch);//湿
                oledZh(64,0,17,1,ch);//度
                oledZh(80,0,55,2,ch);//上限
                oledZh(16,2,65,3,ch);//5防频繁
                oledZh(64,2,14,2,ch);//启动
                oledZh(96,2,22,2,ch);//时间
                oledZh(16,4,20,2,ch);//6设置
                oledZh(48,4,68,4,ch);//设备地址
                oledZh(16,6,57,6,ch);//7是否开启报警
            }
            break;
        }
        case 3:{
            if(isclr){
                oledClr();
                isclr=0;
                oledZh(16,0,20,2,ch);//8设置
                oledZh(48,0,26,2,ch);//系统
                oledZh(80,0,22,2,ch);//时间
                oledZh(16,2,26,2,ch);//9系统
                oledZh(48,2,72,4,ch);//运行测试
                oledZh(16,4,76,4,ch);//10恢复默认
                oledZh(80,4,20,2,ch);//设置
                oledZh(16,6,36,2,ch);//11修改
                oledZh(48,6,80,3,ch);//操作员
                oledZh(96,6,34,2,ch);//密码
            }
            break;
        }
        case 4:{
            if(isclr){
                oledClr();
                isclr=0;
                oledZh(16,0,36,2,ch);//12修改
                oledZh(48,0,83,2,ch);//管理
                oledZh(80,0,82,1,ch);//员
                oledZh(96,0,34,2,ch);//密码
                oledZh(16,2,85,2,ch);//13清零
                oledZh(48,2,26,2,ch);//系统
                oledZh(80,2,87,2,ch);//数据
            }
            break;
        }
    }
    oledZh(0,(menunum%4)*2,11,1,ch);//→
}
//登录页面
void login(){
    uchar i;
    uchar pass[3];
    if(isclr){
        oledClr();
        isclr=0;
        key=NIL;
        passnum=0;
        oledZh(8,0,31,3,ch);//请输入
        oledZh(56,0,26,2,ch);//系统
        oledZh(88,0,34,2,ch);//密码
    }
    switch(key){
        case UP:{
            key=NIL;
            if(passinput[passnum]==9){
                passinput[passnum]=0;
            }else{
                passinput[passnum]++;
            }
            break;
        }
        case DOWN:{
            key=NIL;
            if(passinput[passnum]==0){
                passinput[passnum]=9;
            }else{
               passinput[passnum]--;
            }
            break;
        }
        case OK:{
            key=NIL;
            passnum++;
            if(passnum==4){
                passnum=0;
                for(i=0;i<3;i++) pass[i]=at93c46Read(0x13+i);
                if(checksum(pass,2)==pass[2]){
                    if(pass[0]==(passinput[0]*16+passinput[1])&&pass[1]==(passinput[2]*16+passinput[3])){
                        islogin=1;
                        isadmin=1;
                    }
                }else{
                    if(passinput[0]*pow(2,12)+passinput[1]*pow(2,8)+passinput[2]*pow(2,4)+passinput[3]==ADMINPASS){
                        islogin=1;
                        isadmin=1;
                    }
                }
                if(islogin==0){
                    for(i=0;i<3;i++) pass[i]=at93c46Read(0x10+i);
                    if(checksum(pass,2)==pass[2]){
                        if(pass[0]==(passinput[0]*16+passinput[1])&&pass[1]==(passinput[2]*16+passinput[3])){
                            islogin=1;
                            isadmin=0;
                        }
                    }else{
                        if(passinput[0]*pow(2,12)+passinput[1]*pow(2,8)+passinput[2]*pow(2,4)+passinput[3]==PASS){
                            islogin=1;
                            isadmin=0;
                        }
                    }
                }
                for(i=0;i<4;i++) passinput[i]=0;
                if(islogin){//登录成功
                    passtime=PASSTIME;
                    page=MENU;
                    pagenum=1;
                    menunum=0;
                    isclr=1;
                    return;
                }else{//密码错误
                    oledZh(32,6,34,2,ch);//密码
                    oledZh(64,6,29,2,ch);//错误
                }
            }
            break;
        }
        case RET:{
            key=NIL;
            if(passnum==0){
                page=HOME;
                pagenum=1;
                isclr=1;
                passinput[0]=0;
                return;
            }else{
                passinput[passnum]=0;
                passnum--;
            }
            break;
        }
    }
    for(i=0;i<4;i++){
        if(i<passnum) oledChar(36+16*i,3,5,1,symbol);//*
        if(i==passnum) oledCharInverse(36+16*i,3,passinput[i],1,digit);//0
        if(i>passnum) oledChar(36+16*i,3,4,1,symbol);//_
    }
}
//新风启动温度
void windtem(){
    switch(key){
        case UP:{
            key=NIL;
            if(editbuf[0]<maxtem){
                editbuf[0]++;
            }
            break;
        }
        case DOWN:{
            key=NIL;
            if(editbuf[0]>0){
                editbuf[0]--;
            }
            break;
        }
        case OK:{
            key=NIL;
            mintem=editbuf[0];
            if(saveConfig()) oledZh(64,6,89,2,ch);//成功
            else oledZh(64,6,91,2,ch);//失败
            oledZh(32,6,93,2,ch);//保存
            _delay_ms(500);
            page=MENU;
            isclr=1; 
            return;
            break;
        }
        case RET:{
            key=NIL;
            page=MENU;
            isclr=1;
            return;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        editbuf[0]=mintem;
        oledZh(16,0,7,2,ch);//新风
        oledZh(48,0,14,4,ch);//启动温度
        oledZh(64,3,95,1,ch);//度
    }
    DecBcd(editbuf[0],disbuf,2);
    oledCharInverse(48,3,disbuf[1],1,digit);
    oledCharInverse(56,3,disbuf[0],1,digit);
}
//新风启动温差
void winddiff(){
    switch(key){
        case UP:{
            key=NIL;
            if(editbuf[0]<9){
                editbuf[0]++;
            }
            break;
        }
        case DOWN:{
            key=NIL;
            if(editbuf[0]>0){
                editbuf[0]--;
            }
            break;
        }
        case OK:{
            key=NIL;
            temdiff=editbuf[0];
            if(saveConfig()) oledZh(64,6,89,2,ch);//成功
            else oledZh(64,6,91,2,ch);//失败
            oledZh(32,6,93,2,ch);//保存
            _delay_ms(500);
            page=MENU;
            isclr=1; 
            return;
            break;
        }
        case RET:{
            key=NIL;
            page=MENU;
            isclr=1;
            return;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        editbuf[0]=temdiff;
        oledZh(16,0,7,2,ch);//新风
        oledZh(48,0,14,2,ch);//启动
        oledZh(80,0,18,2,ch);//温差
        oledZh(60,3,95,1,ch);//度
    }
    oledCharInverse(52,3,editbuf[0],1,digit);
}
//空调启动温度
void airtem(){
    switch(key){
        case UP:{
            key=NIL;
            if(editbuf[0]<30){
                editbuf[0]++;
            }
            break;
        }
        case DOWN:{
            key=NIL;
            if(editbuf[0]>mintem){
                editbuf[0]--;
            }
            break;
        }
        case OK:{
            key=NIL;
            maxtem=editbuf[0];
            if(saveConfig()) oledZh(64,6,89,2,ch);//成功
            else oledZh(64,6,91,2,ch);//失败
            oledZh(32,6,93,2,ch);//保存
            _delay_ms(500);
            page=MENU;
            isclr=1; 
            return;
            break;
        }
        case RET:{
            key=NIL;
            page=MENU;
            isclr=1;
            return;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        editbuf[0]=maxtem;
        oledZh(16,0,5,2,ch);//空调
        oledZh(48,0,14,4,ch);//启动温度
        oledZh(64,3,95,1,ch);//度
    }
    DecBcd(editbuf[0],disbuf,2);
    oledCharInverse(48,3,disbuf[1],1,digit);
    oledCharInverse(56,3,disbuf[0],1,digit);
}
//空调启动方式
void airmode(){
    switch(key){
        case UP:{
            key=NIL;
            if(editbuf[0]<2) editbuf[0]++;
            break;
        }
        case DOWN:{
            key=NIL;
            if(editbuf[0]>0) editbuf[0]--;
            break;
        }
        case OK:{
            key=NIL;
            airswitch=editbuf[0];
            if(saveConfig()) oledZh(64,6,89,2,ch);//成功
            else oledZh(64,6,91,2,ch);//失败
            oledZh(32,6,93,2,ch);//保存
            _delay_ms(500);
            page=MENU;
            isclr=1; 
            return;
            break;
        }
        case RET:{
            key=NIL;
            page=MENU;
            isclr=1;
            return;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        editbuf[0]=airswitch;
        oledZh(16,0,5,2,ch);//3空调
        oledZh(48,0,9,2,ch);//开关
        oledZh(80,0,63,2,ch);//方式  
    }
    if(editbuf[0]==0){
        oledZhInverse(32,2,96,2,ch);//按钮
        oledZhInverse(64,2,63,2,ch);//方式
    }else{
        oledZh(32,2,96,2,ch);//按钮
        oledZh(64,2,63,2,ch);//方式
    }
    if(editbuf[0]==1){
        oledZhInverse(32,4,98,4,ch);//接通开机
    }else{
        oledZh(32,4,98,4,ch);//接通开机
    }
    if(editbuf[0]==2){
        oledZhInverse(32,6,102,2,ch);//断开
        oledZhInverse(64,6,100,2,ch);//开机
    }else{
        oledZh(32,6,102,2,ch);//断开
        oledZh(64,6,100,2,ch);//开机
    }
}
//新风湿度上限
void windhum(){
    switch(key){
        case UP:{
            key=NIL;
            if(editbuf[0]<99){
                editbuf[0]++;
            }
            break;
        }
        case DOWN:{
            key=NIL;
            if(editbuf[0]>minhum){
                editbuf[0]--;
            }
            break;
        }
        case OK:{
            key=NIL;
            maxhum=editbuf[0];
            if(saveConfig()) oledZh(64,6,89,2,ch);//成功
            else oledZh(64,6,91,2,ch);//失败
            oledZh(32,6,93,2,ch);//保存
            _delay_ms(500);
            page=MENU;
            isclr=1; 
            return;
            break;
        }
        case RET:{
            key=NIL;
            page=MENU;
            isclr=1;
            return;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        editbuf[0]=maxhum;
        oledZh(16,0,7,2,ch);//4新风
        oledZh(48,0,4,1,ch);//湿
        oledZh(64,0,17,1,ch);//度
        oledZh(80,0,55,2,ch);//上限
        oledChar(68,3,6,1,symbol);//%
    }
    DecBcd(editbuf[0],disbuf,2);
    oledCharInverse(52,3,disbuf[1],1,digit);
    oledCharInverse(60,3,disbuf[0],1,digit);
}
//防频繁启动时间
void startdelay(){
    switch(key){
        case UP:{
            key=NIL;
            if(editbuf[0]<99){
                editbuf[0]++;
            }
            break;
        }
        case DOWN:{
            key=NIL;
            if(editbuf[0]>1){
                editbuf[0]--;
            }
            break;
        }
        case OK:{
            key=NIL;
            delay=editbuf[0];
            if(saveConfig()) oledZh(64,6,89,2,ch);//成功
            else oledZh(64,6,91,2,ch);//失败
            oledZh(32,6,93,2,ch);//保存
            _delay_ms(500);
            page=MENU;
            isclr=1; 
            return;
            break;
        }
        case RET:{
            key=NIL;
            page=MENU;
            isclr=1;
            return;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        editbuf[0]=delay;
        oledZh(16,0,65,3,ch);//5防频繁
        oledZh(64,0,14,2,ch);//启动
        oledZh(96,0,22,2,ch);//时间
        oledZh(64,3,25,1,ch);//分
    }
    DecBcd(editbuf[0],disbuf,2);
    oledCharInverse(48,3,disbuf[1],1,digit);
    oledCharInverse(56,3,disbuf[0],1,digit);
}
//设置设备地址
void setaddr(){
    uchar i,x,y;
    switch(key){
        case UP:{
            key=NIL;
            if(editbuf[editnum]<9) editbuf[editnum]++;
            break;
        }
        case DOWN:{
            key=NIL;
            if(editbuf[editnum]>0) editbuf[editnum]--;
            break;
        }
        case OK:{
            key=NIL;
            if(editnum>=17){
                for(i=0;i<9;i++) confbuf[i]=editbuf[2*i]*16+editbuf[2*i+1];
                confbuf[9]=checksum(confbuf,9);
                for(i=0;i<10;i++) at93c46Write(0x16+i,confbuf[i]);
                for(i=0;i<10;i++) confbuf[i]=at93c46Read(0x16+i);
                if(checksum(confbuf,9)==confbuf[9]){
                    for(i=0;i<9;i++) addr[i]=confbuf[i];
                    oledZh(64,6,89,2,ch);//成功
                }else{
                    oledZh(64,6,91,2,ch);//失败
                }
                oledZh(32,6,93,2,ch);//保存
                _delay_ms(500);
                page=MENU;
                isclr=1; 
                return;
            }else{
                editnum++;
            }
            break;
        }
        case RET:{
            key=NIL;
            if(editnum>0){
                editnum--;
            }else{
                page=MENU;
                isclr=1;
                return;
            }
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        editnum=0;
        for(i=0;i<9;i++){
            editbuf[2*i]=addr[i]/16;
            editbuf[2*i+1]=addr[i]%16;
        }
        oledZh(16,0,20,2,ch);//6设置
        oledZh(48,0,68,4,ch);//设备地址
    }
    y=2;
    for(i=0;i<18;i++){
        x=20+10*i;
        if(i>8){
            x-=90;
            y=4;
        }
        if(i==editnum) oledCharInverse(x,y,editbuf[i],1,digit);
        else oledChar(x,y,editbuf[i],1,digit);
    }
}
//是否开启报警
void startalarm(){
    switch(key){
        case UP:{
            key=NIL;
            if(!isif) isif=1;
            break;
        }
        case DOWN:{
            key=NIL;
            if(isif) isif=0;
            break;
        }
        case OK:{
            key=NIL;
            isalarm=isif;
            if(saveConfig()) oledZh(64,6,89,2,ch);//成功
            else oledZh(64,6,91,2,ch);//失败
            oledZh(32,6,93,2,ch);//保存
            _delay_ms(500);
            page=MENU;
            isclr=1; 
            return;
            break;
        }
        case RET:{
            key=NIL;
            page=MENU;
            isclr=1;
            return;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        isif=isalarm;
        oledZh(16,0,57,6,ch);//7是否开启报警
    }
    if(isif) oledZhInverse(32,3,57,1,ch);//是
    else oledZh(32,3,57,1,ch);
    if(isif) oledZh(80,3,58,1,ch);//否
    else oledZhInverse(80,3,58,1,ch);
}
//设置系统时间
void settime(){
    switch(key){
        case UP:{
            key=NIL;
            if(editbuf[editnum]<max) editbuf[editnum]++;
            else editbuf[editnum]=min;
            break;
        }
        case DOWN:{
            key=NIL;
            if(editbuf[editnum]>min) editbuf[editnum]--;
            else editbuf[editnum]=max;
            break;
        }
        case OK:{
            key=NIL;
            switch(editnum){
                case 0:
                {
                    ds1302Write(0x8C, DecToBcd(editbuf[editnum]));
                    break;
                }
                case 1:
                {
                    ds1302Write(0x88, DecToBcd(editbuf[editnum]));
                    break;
                }
                case 2:
                {
                    ds1302Write(0x86, DecToBcd(editbuf[editnum]));
                    break;
                }
                case 3:
                {
                    ds1302Write(0x84, DecToBcd(editbuf[editnum]));
                    break;
                }
                case 4:
                {
                    ds1302Write(0x82, DecToBcd(editbuf[editnum]));
                    break;
                }
                case 5:
                {
                    ds1302Write(0x80, DecToBcd(editbuf[editnum]));
                    break;
                }
            }
            if(editnum>=5){
                page=MENU;
                isclr=1;
                return;
            }else{
                editnum++;
                editbuf[editnum]=time[editnum];
            }
            break;
        }
        case RET:{
            key=NIL;
            if(editnum>0){
                editnum--;
                editbuf[editnum]=time[editnum];
            }else{
                page=MENU;
                isclr=1;
                return;
            }
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        editnum=0;
        editbuf[editnum]=time[editnum];
        oledZh(16,0,20,2,ch);//8设置
        oledZh(48,0,26,2,ch);//系统
        oledZh(80,0,22,2,ch);//时间
        oledChar(56,3,0,1,symbol);//-
        oledChar(80,3,0,1,symbol);//-
        oledChar(48,6,1,1,symbol);//:
        oledChar(72,6,1,1,symbol);//:
    }
    if(editnum==0){
        min=0;
        max=99;
        oledCharInverse(24,3,2,1,digit);//2
        oledCharInverse(32,3,0,1,digit);//0
        oledCharInverse(40,3,editbuf[editnum]/10,1,digit);//年
        oledCharInverse(48,3,editbuf[editnum]%10,1,digit);
    }else{
        oledChar(24,3,2,1,digit);//2
        oledChar(32,3,0,1,digit);//0
        oledChar(40,3,time[0]/10,1,digit);//年
        oledChar(48,3,time[0]%10,1,digit);
    }
    if(editnum==1){
        min=1;
        max=12;
        oledCharInverse(64,3,editbuf[editnum]/10,1,digit);//月
        oledCharInverse(72,3,editbuf[editnum]%10,1,digit);
    }else{
        oledChar(64,3,time[1]/10,1,digit);//月
        oledChar(72,3,time[1]%10,1,digit);
    }
    if(editnum==2){
        min=1;
        if(time[1]==2){
            if(time[0]%4==0) max=29;
            else max=28;
        }
        if(time[1]==1&&time[1]==3&&time[1]==5&&time[1]==7&&time[1]==8&&time[1]==10&&time[1]==12) max=31;
        if(time[1]==4&&time[1]==6&&time[1]==9&&time[1]==11) max=30;
        oledCharInverse(88,3,editbuf[editnum]/10,1,digit);//日
        oledCharInverse(96,3,editbuf[editnum]%10,1,digit);
    }else{
        oledChar(88,3,time[2]/10,1,digit);//日
        oledChar(96,3,time[2]%10,1,digit);
    }
    if(editnum==3){
        min=0;
        max=23;
        oledCharInverse(32,6,editbuf[editnum]/10,1,digit);//时
        oledCharInverse(40,6,editbuf[editnum]%10,1,digit);
    }else{
        oledChar(32,6,time[3]/10,1,digit);//时
        oledChar(40,6,time[3]%10,1,digit);
    }
    if(editnum==4){
        min=0;
        max=59;
        oledCharInverse(56,6,editbuf[editnum]/10,1,digit);//分
        oledCharInverse(64,6,editbuf[editnum]%10,1,digit);
    }else{
        oledChar(56,6,time[4]/10,1,digit);//分
        oledChar(64,6,time[4]%10,1,digit);
    }
    if(editnum==5){
        min=0;
        max=59;
        oledCharInverse(80,6,editbuf[editnum]/10,1,digit);//秒
        oledCharInverse(88,6,editbuf[editnum]%10,1,digit);
    }else{
        oledChar(80,6,time[5]/10,1,digit);//秒
        oledChar(88,6,time[5]%10,1,digit);
    }
}
//恢复默认设置
void recover(){
    uchar i;
    switch(key){
        case UP:{
            key=NIL;
            if(!isif) isif=1;
            break;
        }
        case DOWN:{
            key=NIL;
            if(isif) isif=0;
            break;
        }
        case OK:{
            key=NIL;
            if(isif){
                for(i=0;i<8;i++) confbuf[i]=at93c46Read(0x08+i);//读取默认配置
                if(checksum(confbuf,7)==confbuf[7]){
                    readConfig();
                    oledZh(64,6,89,2,ch);//成功
                }else oledZh(64,6,91,2,ch);//失败
                oledZh(32,6,80,2,ch);//操作
                _delay_ms(500);
            }
            page=MENU;
            isclr=1; 
            return;
            break;
        }
        case RET:{
            key=NIL;
            page=MENU;
            isclr=1;
            return;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        isif=0;
        oledZh(16,0,76,4,ch);//10恢复默认
        oledZh(80,0,20,2,ch);//设置
    }
    if(isif) oledZhInverse(32,3,57,1,ch);//是
    else oledZh(32,3,57,1,ch);
    if(isif) oledZh(80,3,58,1,ch);//否
    else oledZhInverse(80,3,58,1,ch);
}
//修改管理员密码
void passadmin(){
    switch(key){
        case UP:{
            key=NIL;
            break;
        }
        case DOWN:{
            key=NIL;
            break;
        }
        case OK:{
            key=NIL;
            break;
        }
        case RET:{
            key=NIL;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        oledZh(8,0,36,2,ch);//12修改
        oledZh(40,0,83,2,ch);//管理
        oledZh(72,0,82,1,ch);//员
        oledZh(88,0,34,2,ch);//密码
    }
}
//清零系统数据
void cleardata(){
    uchar i;
    switch(key){
        case UP:{
            key=NIL;
            if(!isif) isif=1;
            break;
        }
        case DOWN:{
            key=NIL;
            if(isif) isif=0;
            break;
        }
        case OK:{
            key=NIL;
            if(isif){
                for(i=0;i<15;i++) databuf[i]=0;
                databuf[15]=checksum(databuf,15);
                for(i=0;i<16;i++) at93c46Write(0x20+i,databuf[i]);
                for(i=0;i<16;i++) at93c46Write(0x30+i,databuf[i]);
                initData();
                oledZh(32,6,80,2,ch);//操作
                oledZh(64,6,89,2,ch);//成功
                _delay_ms(500);
            }
            page=MENU;
            isclr=1; 
            return;
            break;
        }
        case RET:{
            key=NIL;
            page=MENU;
            isclr=1;
            return;
            break;
        }
    }
    if(isclr){
        oledClr();
        isclr=0;
        isif=0;
        oledZh(16,0,85,2,ch);//13清零
        oledZh(48,0,26,2,ch);//系统
        oledZh(80,0,87,2,ch);//数据
    }
    if(isif) oledZhInverse(32,3,57,1,ch);//是
    else oledZh(32,3,57,1,ch);
    if(isif) oledZh(80,3,58,1,ch);//否
    else oledZhInverse(80,3,58,1,ch);
}
//启动显示
void start(){
    //oledZh(32,3,44,4,ch);//友控电子
    //_delay_ms(1000);
}
//测试显示
void test(){
    ulong data=0;
    rn8302Read(PfB,(uchar*)&data,3);
    data=(long)(data/83886.08);//功率因素
    
    DecBcd(data,disbuf,8);
    oledChar(64,6,disbuf[7],1,digit);
    oledChar(72,6,disbuf[6],1,digit);
    oledChar(80,6,disbuf[5],1,digit);
    oledChar(88,6,disbuf[4],1,digit);
    oledChar(96,6,disbuf[3],1,digit);
    oledChar(104,6,disbuf[2],1,digit);
    oledChar(112,6,disbuf[1],1,digit);
    oledChar(120,6,disbuf[0],1,digit);
}
//报警页
void alarm(){
    switch(key){
        case RET:{
            key=NIL;
            page=HOME;
            pagenum=1;
            isclr=1;
            return;
            break;
        }
    }
    key=NIL;
    if(isclr){
        oledClr();
        isclr=0;
        oledZh(32,1,26,2,ch);//系统
        oledZh(64,1,29,2,ch);//错误
    }
    oledChar(56,4,err/16,1,digit);
    oledChar(64,4,err%16,1,digit);
}
int main(){
    initPort();//初始化端口
    oledInit();//初始化显示
    start();//开机画面
    initConfig();//初始化配置
    initData();//初始化数据
	initUsart0();//初始化串口1
	initUsart1();//初始化串口1
	initTimer0();//初始化定时器0
    ds1302Init();//初始化时钟
    rn8302Init();//初始化电表
    i2cInit();//初始化TWI
    wdt_enable(WDTO_2S);//打开看门狗
	sei();//开中断
    while(1){
        readTime();//读时间
        if(istem){//测温
            istem=0;
		    if(readSht(0)){//室内传感器
                if(err==EISHT) err=ENIL;
            }else{
                if(err==ENIL||err>EISHT) err=EISHT;
            }
            if(readSht(1)){//室外传感器
                if(err==EOSHT) err=ENIL;
            }else{
                if(err==ENIL||err>EOSHT) err=EOSHT;
            }
		    airwind();//判断开关条件
        }
        if(istime){//空调新风计时
            istime=0;
            airwindtime();
        }
        if(isrn){//读电表
            isrn=0;
            readRn8302();
        }
        //显示界面切换
		switch(page){
            case HOME:{//主页
                home();
                break;
            }
            case MENU:{//菜单页
                menu();
                break;
            }
            case ALARM:{//报警页
                alarm();
                break;
            }
            case LOGIN:{//登录页
                login();
                break;
            }
            case MENUS:{//菜单设置页
                switch(menunum){
                    case 0:{//新风启动温度
                        windtem();
                        break;
                    }
                    case 1:{//新风启动温差
                        winddiff();
                        break;
                    }
                    case 2:{//空调启动温度
                        airtem();
                        break;
                    }
                    case 3:{//空调开关方式
                        airmode();
                        break;
                    }
                    case 4:{//新风最大湿度
                        windhum();
                        break;
                    }
                    case 5:{//防频繁启动时间
                        startdelay();
                        break;
                    }
                    case 6:{//设置设备地址
                        setaddr();
                        break;
                    }
                    case 7:{//是否开启报警
                        startalarm();
                        break;
                    }
                    case 8:{//设置系统时间
                        settime();
                        break;
                    }
                    case 10:{//恢复默认设置
                        recover();
                        break;
                    }
                    case 11:{//修改操作员密码
                        //passuser();
                        break;
                    }
                    case 12:{//修改管理员密码
                        passadmin();
                        break;
                    }
                    case 13:{//清零系统数据
                        cleardata();
                        break;
                    }
                    default:{
                        page=MENU;
                        break;
                    }
                }
                break;
            }
        }
        wdt_reset();
	}
	return 0;
}
