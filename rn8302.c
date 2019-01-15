#include "rn8302.h"

void rn8302Init(){
    uchar buf[4];
    rn8302Read(DeviceID,buf,3);//读ID
    buf[0]=0xE5;
    rn8302Write(WREN,buf,1);//写使能
    buf[0]=0xA2;
    rn8302Write(WMSW,buf,1);//计量模式
    buf[0]=0xFA;
    rn8302Write(SOFTRST,buf,1);//复位
    _delay_ms(20);
    buf[0]=0xE5;
    rn8302Write(WREN,buf,1);//写使能
    buf[0]=0xA2;
    rn8302Write(WMSW,buf,1);//计量模式
    buf[0]=0xBF;
    buf[1]=0x0B;
    rn8302Write(HFCONST1,buf,2);//电表常数3200
    rn8302Write(HFCONST2,buf,2);
    
    //电压校正
    buf[0]=0x0B;
    buf[1]=0xFA;
    rn8302Write(GSUA,buf,2);//UA校正
    rn8302Write(GSUB,buf,2);//UB校正
    rn8302Write(GSUC,buf,2);//UC校正
    //电流校正
    buf[0]=0xFD;
    buf[1]=0x02;
    rn8302Write(GSIA,buf,2);//IA校正
    rn8302Write(GSIB,buf,2);//IB校正
    rn8302Write(GSIC,buf,2);//IC校正
    //功率相位校正
    buf[0]=0x84;
    buf[1]=0xFD;
    rn8302Write(PA_PHSL,buf,2);
    rn8302Write(QA_PHSL,buf,2);
    rn8302Write(PB_PHSL,buf,2);
    rn8302Write(QB_PHSL,buf,2);
    rn8302Write(PC_PHSL,buf,2);
    rn8302Write(QC_PHSL,buf,2);
    //电流OFFSET
    buf[0]=0x13;
    buf[1]=0xF1;
    rn8302Write(IA_OS,buf,2);
    rn8302Write(IB_OS,buf,2);
    rn8302Write(IC_OS,buf,2);
    //功率OFFSET
    buf[0]=0x00;
    buf[1]=0xE4;
    rn8302Write(PA_OS,buf,2);
    rn8302Write(PB_OS,buf,2);
    rn8302Write(PC_OS,buf,2);
    //脉冲输出
    buf[0]=0x10;
    buf[1]=0x77;
    buf[2]=0x04;
    rn8302Write(CFCFG,buf,3);
    buf[0]=0x00;
    rn8302Write(MODSEL,buf,1);//三相四线
    buf[0]=0x00;
    buf[1]=0x00;
    buf[2]=0x40;
    rn8302Write(EMUCFG,buf,3);//计量不累加
    buf[0]=0x77;
    buf[1]=0x77;
    buf[2]=0x77;
    rn8302Write(EMUCON,buf,3);//计量使能
    buf[0]=0xDC;
    rn8302Write(WREN,buf,1);//写保护
}

//写一个字节   
void rn8302WriteByte(uchar data){
    uchar i;       
    for(i=0;i<8;i++){   
        RN8302_SCK_H;
        if(data&0x80)   
        {   
            RN8302_SDO_H;              
        }   
        else   
        {   
            RN8302_SDO_L;               
        }   
        RN8302_SCK_L;
        _delay_us(10);
        data <<= 1;
    }   
}   
   
//读一个字节   
uchar rn8302ReadByte(){
    uchar i,data=0;   
    for(i=0;i<8;i++){   
        data<<=1;   
        RN8302_SCK_H;
        RN8302_SCK_L;
        _delay_us(10);           
        if(RN8302_SDI_IN) data|=0x01;     
    }   
    return  data;   
}

void rn8302Write(uint wReg,uchar *pBuf,uchar ucLen){
    uchar i,temp,chksum;   
    RN8302_CS_L;      
    temp = (uchar)(wReg & 0x00ff);   
    chksum = temp;   
    rn8302WriteByte( temp); //目标地址低八位   
    temp = (((uchar)(wReg >> 4)) & 0xf0) + 0x80;   
    chksum += temp;          //ADDR+CMD   
    rn8302WriteByte( temp);  //CMD   
       
    for(i = ucLen; i > 0;i-- )   
    {   
        rn8302WriteByte(pBuf[i-1]);  // first write high data   
        chksum +=pBuf[i-1];           //ADDR+CMD+DATA   
    }   
    chksum = ~chksum;    //取反   
    rn8302WriteByte(chksum);                               
    RN8302_CS_H;      
}

uchar rn8302Read(uint wReg,uchar *pBuf,uchar ucLen){
    uchar i,temp,chksum;   
    RN8302_CS_L;      
    temp = (uchar)(wReg & 0x00ff);   
    chksum = temp;   
    rn8302WriteByte( temp);              //写目标地址低八位ADDR   
    temp = (((uchar)(wReg >> 4)) & 0xf0) ;   
    chksum += temp;                      //ADDR+CMD   
    rn8302WriteByte( temp);   
       
    for(i = ucLen; i > 0;i--)   
    {   
        pBuf[i-1] = rn8302ReadByte();    
        chksum += pBuf[i-1];   
    }   
    chksum = ~chksum ;   
    if(rn8302ReadByte()==chksum)   
        chksum = 1;    
    else   
        chksum = 0;    
   
    RN8302_CS_H;
    return chksum;   
}