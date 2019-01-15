/* 
 * File:   rn8302.h
 * Author: godart
 *
 * Created on 2018年12月25日, 下午6:11
 */

#ifndef RN8302_H
#define	RN8302_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "comm.h"
    
#define RN8302_CS (1<<PB0)
#define RN8302_CS_L   PORTB&=~RN8302_CS
#define RN8302_CS_H   PORTB|=RN8302_CS
#define RN8302_SCK (1<<PB1)
#define RN8302_SCK_L  PORTB&=~RN8302_SCK
#define RN8302_SCK_H  PORTB|=RN8302_SCK
#define RN8302_SDO (1<<PB2)
#define RN8302_SDO_L  PORTB&=~RN8302_SDO
#define RN8302_SDO_H  PORTB|=RN8302_SDO
#define RN8302_SDI (1<<PB3)
#define RN8302_SDI_IN PINB&RN8302_SDI
    
#define	UAWAV		0x0000		//  A相电压采样数据 
#define	UBWAV		0x0001		// 	B相电压采样数据 
#define	UCWAV		0x0002		// 	C相电压采样数据 
 
#define	IAWAV		0x0003      // 	A相电流采样数据 
#define	IBWAV		0x0004		// 	B相电流采样数据 
#define	ICWAV		0x0005		// 	C相电流采样数据 
#define	INWAV		0x0006		// 	零线电流采样数据 
 
//电压有效值 
#define	UA		    0x0007		// 	A相电流有效值 
#define	UB	        0x0008		// 	B相电流有效值 
#define	UC	        0x0009		// 	C相电流有效值 
#define	USUM		0x000A		// 	电压矢量和有效值 
 
 
//电流有效值 
#define	IA			0x000B		// 	A相电流有效值 
#define	IB			0x000C		// 	B相电流有效值 
#define	IC			0x000D		// 	C相电流有效值 
#define	IN			0x000E		// 	零线电流有效值 
#define	ISUM		0x0010		//	电流矢量和有效值 
 
#define	IA_NVM1		0x0011		//	NVM1 A 相电流有效值	 
#define	IB_NVM1		0x0012		//	NVM1 B相电流有效值	 
#define	IC_NVM1		0x0013		//	NVM1 C 相电流有效值 
 
#define	PA		    0x0014		//	A 相有功功率 
#define	PB		    0x0015		//	B 相有功功率 
#define	PC		    0x0016		//	C 相有功功率 
#define	PT		    0x0017		// 合相有功功率 
 
#define	QA		    0x0018		//	A 相无功功率 
#define	QB		    0x0019		//	B 相无功功率 
#define	QC		    0x001A		//	C 相无功功率 
#define	QT	        0x001B		//  合相无功功率 
 
#define	SA		    0x001C		//	A 相视在功率 
#define	SB		    0x001D		//	B 相视在功率 
#define SC		    0x001E		//	C 相视在功率 
#define	STA	        0x001F		// RMS合相视在功率 
 
#define	PfA		    0x0020		//	A 相功率因数 
#define	PfB			0x0021		//	B 相功率因数 
#define	PfC			0x0022		//	C 相功率因数 
#define	PfTA		0x0023		//  RMS 合相功率因数 
 
#define	PAFCnt		0x0024		//	A 相有功快速脉冲计数 
#define	PBFCnt	    0x0025		//	B 相有功快速脉冲计数 
#define PCFCnt		0x0026		//	C 相有功快速脉冲计数 
#define	PTFCnt	    0x0027		//  合相有功快速脉冲计数 
 
 
#define	QAFCnt	    0x0028		//	A 相无功快速脉冲计数 
#define	QBFCnt		0x0029		//	B 相无功快速脉冲计数 
#define	QCFCnt		0x002A		//	C 相无功快速脉冲计数 
#define	QTFCnt		0x002B		//  合相无功快速脉冲计数 
 
#define	SAFCnt		0x002C		//	A 相视在快速脉冲计数 
#define	SBFCnt	    0x002D		//	B 相视在快速脉冲计数 
#define SCFCnt		0x002E		//	C 相视在快速脉冲计数 
#define	STFACnt	    0x002F		//  RMS合相视在快速脉冲计数 
 
#define	EPA	       	0x0030		//	A 相有功能量寄存器 
#define	EPB		   	0x0031		//	B 相有功能量寄存器 
#define	EPC		   	0x0032		//	C 相有功能量寄存器 
#define	EPT		  	0x0033		//  合相有功能量寄存器 
 
#define	PosEPA		0x0034		//	A 相正向有功能量寄存器 
#define	PosEPB	    0x0035		//	B 相正向有功能量寄存器 
#define PosEPC		0x0036		//	C相正向有功能量寄存器 
#define	PosEPT	    0x0037		//	合相正向有功能量寄存器 
 
#define	NegEPA      0x0038		//	A 相反向有功能量寄存器 
#define	NegEPB	   	0x0039		//	B 相反向有功能量寄存器 
#define	NegEPC		0x003A		//	C 相反向有功能量寄存器 
#define	NegEPT		0x003B		// 合相反向有功能量寄存器 
 
#define	EQA			0x003C		//	A 相反向无功能量寄存器 
#define	EQB	    	0x003D		//	B 相反向无功能量寄存器 
#define EQC			0x003E		//	C 相反向无功能量寄存器 
#define	EQT    		0x003F		//	合相反向无功能量寄存器 
 
#define	PosEQA      0x0040		//	A 相正向无功能量寄存器 
#define	PosEQB 	   	0x0041		//	B 相正向无功能量寄存器 
#define	PosEQC		0x0042		//	C 相正向无功能量寄存器 
#define	PosEQT 		0x0043		//  合相正向无功能量寄存器 
 
#define	NegEQA		0x0044		//	A 相反向无功能量寄存器 
#define	NegEQB		0x0045		//	B 相反向无功能量寄存器 
#define NegEQC		0x0046		//	C 相反向无功能量寄存器 
#define	NegEQT	   	0x0047		//	合相反向无功能量寄存器 
 
#define	ESA    		0x0048		//	A 相视在能量寄存器 
#define	ESB	   		0x0049		//	B 相视在能量寄存器 
#define	ESC			0x004A		//	C 相视在能量寄存器 
#define	ESTA 		0x004B		//  RMS合相视在能量寄存器 
 
#define	STV			0x004C		//	PQS 合相视在功率 
#define	PfTV		0x004D		//	PQS 合相功率因数 
#define STFVCnt		0x004E		//	PQS 合相视在快速脉冲计数 
#define	ESTV	   	0x004F		//	PQS 合相视在能量寄存器 
 
#define	YUA    		0x0050		//	采样通道 UA 基波相角寄存器 
#define	YUB	   		0x0051		//	采样通道 UB 基波相角寄存器 
#define	YUC		    0x0052		//	采样通道 UC 基波相角寄存器 
 
#define	YIA			0x0053		//  采样通道 IA 基波相角寄存器 
#define	YIB			0x0054		//	采样通道 IB 基波相角寄存器 
#define	YIC			0x0055		//	采样通道 IC 基波相角寄存器 
#define YIN			0x0056		//	采样通道 IN 基波相角寄存器 
 
#define	UFreq	   	0x0057		//	电压线频率 
 
#define	FUA    		0x0058		//	A 相基波电压有效值 
#define	FUB	   		0x0059		//	B 相基波电压有效值 
#define	FUC		    0x005A		//	C 相基波电压有效值 
 
#define	FIA			0x005B		//  A 相基波电流有效值 
#define	FIB			0x005C		//	B 相基波电流有效值 
#define	FIC			0x005D		//	C 相基波电流有效值 
 
#define	FPA    		0x005E		//	A 相基波有功功率 
#define	FPB	   		0x005F		//	B 相基波有功功率 
#define	FPC	        0x0060		//	C 相基波有功功率 
#define	FPT         0x0061		//	合相基波有功功率 
 
#define	FQA			0x0062		//  A 相基波无功功率 
#define	FQB			0x0063		//	B 相基波无功功率 
#define	FQC			0x0064		//	C 相基波无功功率 
#define	FQT         0x0065		//	合相基波无功功率 
 
 
#define	FSA			0x0066		//  A 相基波视在功率 
#define	FSB			0x0067		//	B 相基波视在功率 
#define	FSC			0x0068		//	C相基波视在功率 
#define	FSTA    	0x0069		//  RMS合相基波视在功率 
 
#define	FPfA   		0x006A		//	A 相基波功率因数 
#define	FPfB 	    0x006B		//	B相基波功率因数 
#define	FPfC        0x006C		//	C 相基波功率因数 
#define	FPfTA       0x006D	   //  RMS合相基波功率因数 
 
#define	FPAFCnt		0x006E	  //  A 相基波有功快速脉冲计数 
#define	FPBFCnt		0x006F	  //  B 相基波有功快速脉冲计数 
#define	FPCFCnt		0x0070	  //  C 相基波有功快速脉冲计数 
#define	FPTFCnt	    0x0071	  //  合相基波有功快速脉冲计数 
 
#define	FQAFCnt		0x0072		//  A 相基波无功快速脉冲计数 
#define	FQBFCnt		0x0073		//	B 相基波无功快速脉冲计数 
#define	FQCFCnt		0x0074		//	C 相基波无功快速脉冲计数 
#define	FQTFCnt	   	0x0075		//  合相基波无功快速脉冲计数 
 
#define	FSAFCnt  	0x0076		//	A 相基波视在快速脉冲计数 
#define	FSBFCnt	    0x0077		//	B 相基波视在快速脉冲计数 
#define	FSCFCnt     0x0078	    //	C 相基波视在快速脉冲计数 
#define	FSTAFCnt    0x0079	   //  RMS合相基波视在快速脉冲计数 
 
#define	FEPA		0x007A	  //  A 相基波有功电能 
#define	FEPB	    0x007C	  //  B 相基波有功电能 
#define	FEPC		0x007B	  //  C 相基波有功电能 
#define	FEPT	    0x007D	  //  合相基波有功电能 
 
#define	PosFEPA		0x007E		//  A 相基波正向有功能量寄存器 
#define	PosFEPB		0x007F		//	B 相基波正向有功能量寄存器 
#define	PosFEPC		0x0080		//	C 相基波正向有功能量寄存器 
#define	PosFEPT     0x0081		//	合相基波正向有功能量寄存器 
 
 
#define	NegFEPA 	0x0082		//  A 相基波反向有功能量寄存器 
#define	NegFEPB 	0x0083		//	B 相基波反向有功能量寄存器 
#define	NegFEPC 	0x0084		//	C 相基波反向有功能量寄存器 
#define	NegFEPT     0x0085		//  合相基波反向有功能量寄存器 
 
#define	FEQA    	0x0086		//	A 相基波无功电能 
#define	FEQB 	    0x0087	   //	B 相基波无功电能 
#define	FEQC        0x0088		//	C 相基波无功电能 
#define	FEQT        0x0089	   //  合相基波无功电能 
 
#define	PosFEQA		0x008A	  //  A 相正向基波无功能量寄存器 
#define	PosFEQB		0x008B	  //  B 相正向基波无功能量寄存器 
#define	PosFEQC	    0x008C   //   C 相正向基波无功能量寄存器 
#define	PosFEQT	    0x008D	  //  合相正向基波无功能量寄存器 
 
#define	NegFEQA		0x008E		//  A 相反向基波无功能量寄存 
#define	NegFEQB		0x008F		//	B 相反向基波无功能量寄存 
#define	NegFEQC		0x0090		//	C 相反向基波无功能量寄存 
#define	NegFEQT	   	0x0091		//  合相反向基波无功能量寄存器 
 
#define	FESA 		0x0092		//	A 相基波视在能量寄存器 
#define	FESB    	0x0093		//	B 相基波视在能量寄存器 
#define	FESC     	0x0094	    //	C 相基波视在能量寄存器 
#define	FESTA       0x0095	   //  RMS 合相基波视在能量寄存器 
 
#define	HUA		    0x0096	  //  A 相谐波电压有效值 
#define	HUB	        0x0097	  //  B 相谐波电压有效值 
#define	HUC		    0x0098	  //  C 相谐波电压有效值 
 
#define	HIA 		0x0099	  //  A 相谐波电流有效值  
#define	HIB 	    0x009A	  //  B 相谐波电流有效值  
#define	HIC 		0x009B	  //  C 相谐波电流有效值  
 
#define	FSTV 		0x009C	  //  PQS 合相基波视在功率 
#define	FPfTV 	    0x009D	  //  PQS 合相基波功率因数 
#define	FSTVFcnt 	0x009E	  //  PQS 合相基波视在快速脉冲计数 
#define	FESTV		0x009F	  //  PQS 合相基波视在能量寄存器 
 
 
//EMM校表寄存器1 
#define	HFCONST1	0x0100  	//高频脉冲计数寄存器 1 
#define	HFCONST2	0x0101		//高频脉冲计数寄存器 2 
#define	IStart_PS	0x0102		//有功视在启动电流阈值寄存器 
#define	IStart_Q 	0x0103		//无功启动电流阈值寄存器 
#define	LostVoltT	0x0104		//失压阈值寄存器 
#define	ZXOT		0x0105		//过零阈值寄存器 
 
#define	PRTH1L		0x0106		//相位分段校正电流阈值 1 下限 
#define	PRTH1H		0x0107		//相位分段校正电流阈值 1 上限 
#define	PRTH2L		0x0108		//相位分段校正电流阈值 2 下限 
#define	PRTH2H		0x0109		//相位分段校正电流阈值 2 上限 
 
#define	IRegion3L	0x010A		//电流阈值 3 下限 
#define	IRegion3H	0x010B		//电流阈值 3 上限 
 
//相位校正 
#define	PHSUA		0x010C		//采样通道 UA 相位校正寄存器 
#define	PHSUB		0x010D		//采样通道 UB 相位校正寄存器 
#define	PHSUC		0x010E		//采样通道 UC 相位校正寄存器 
#define	PHSIA		0x010F		//采样通道 IA 分段相位校正寄存器 
#define	PHSIB		0x0110		//采样通道 IB 分段相位校正寄存器 
#define	PHSIC		0x0111		//采样通道 IC 分段相位校正寄存器 
#define	PHSIN		0x0112		//采样通道 IN 相位校正 
 
//电压校正 
#define	GSUA		0x0113		//采样通道 UA 通道增益 
#define	GSUB		0x0114		//采样通道 UB 通道增益 
#define	GSUC		0x0115		//采样通道 UC 通道增益 
 
#define	GSIA		0x0116		//采样通道 IA 通道增益 
#define	GSIB		0x0117		//采样通道 IB 通道增益 
#define	GSIC		0x0118		//采样通道 IC 通道增益 
#define	GSIN		0x0119		//采样通道 IN 通道增益 
 
#define	DCOS_UA 	0x011A    	//采样通道 UA 直流 Offset 校正 
#define	DCOS_UB 	0x011B		//采样通道 UB 直流 Offset 校正 
#define	DCOS_UC 	0x011C		//采样通道 UC 直流 Offset 校正 
 
#define	DCOS_IA		0x011D		//采样通道 IA 直流 Offset 校正 
#define	DCOS_IB		0x011E		//采样通道 IB 直流 Offset 校正 
#define	DCOS_IC		0x011F		//采样通道 IC 直流 Offset 校正 
#define	DCOS_IN		0x0120		//采样通道 IN 直流 Offset 校正 
 
#define	UA_OS		0x0121		//A 相电压有效值 Offset 
#define	UB_OS		0x0122		//B 相电压有效值 Offset 
#define	UC_OS		0x0123		//C 相电压有效值 Offset 
 
#define	IA_OS		0x0124		//A 相电流有效值 Offset  
#define	IB_OS		0x0125		//B 相电流有效值 Offset  
#define	IC_OS		0x0126		//C 相电流有效值 Offset  
#define	IN_OS		0x0127		//零线电流 1 有效值 Offset  
 
#define	GPA			0x0128		//A 相有功功率增益 
#define	GPB			0x0129		//B相有功功率增益 
#define GPC     	0x012A		//C 相有功功率增益 
 
#define	GQA			0x012B		//A 相无功功率增益 
#define	GQB	  		0x012C		//B 相无功功率增益 
#define	GQC			0x012D		//C 相无功功率增益 
 
#define	GSA			0x012E		//A 相视在功率增益  
#define	GSB	  		0x012F		//B 相视在功率增益  
#define	GSC			0x0130		//C 相视在功率增益  
 
#define	PA_PHSL		0x0131		//A 相有功分段相位校正寄存器-低段 
#define	PB_PHSL	  	0x0132		//B 相有功分段相位校正寄存器-低段 
#define	PC_PHSL		0x0133		//C 相有功分段相位校正寄存器-低段 
 
#define	QA_PHSL	    0x0134		//A 相无功分段相位校正寄存器-低段 
#define	QB_PHSL 	0x0135 		//B 相无功分段相位校正寄存器-低段 
#define	QC_PHSL 	0x0136		//C 相无功分段相位校正寄存器-低段 
 
#define	PA_OS	    0x0137		//A 相有功功率 Offset 
#define	PB_OS 		0x0138 		//B 相有功功率 Offse 
#define	PC_OS 		0x0139		//C 相有功功率 Offse 
 
#define	QA_OS	    0x013A		//A 相无功功率 Offset 
#define	QB_OS 		0x013B 		//B 相无功功率 Offset 
#define	QC_OS 		0x013C		//C 相无功功率 Offset 
 
#define	FUA_OS 		0x013D		//A 相基波电压有效值 Offset 
#define	FUB_OS		0x013E		//B 相基波电压有效值 Offset 
#define	FUC_OS		0x013F		//C 相基波电压有效值 Offset 
 
#define	FIA_OS		0x0140		//A 相基波电流有效值 Offset 
#define	FIB_OS		0x0141		//B 相基波电流有效值 Offset 
#define	FIC_OS		0x0142		//C 相基波电流有效值 Offset 
 
#define	GFPA  		0x0143		//A 相基波有功功率增益 
#define	GFPB  		0x0144		//B 相基波有功功率增益 
#define	GFPC  		0x0145		//C 相基波有功功率增益 
 
#define	GFQA   		0x0146		//A 相基波无功功率增益 
#define	GFQB 		0x0147		//B 相基波无功功率增益 
#define	GFQC 		0x0148		//C 相基波无功功率增益 
 
#define	GFSA		0x0149	    //A 相基波视在功率增益 
#define	GFSB		0x014A		//B 相基波视在功率增益 
#define GFSC        0x014B		//C 相基波视在功率增益 
 
#define	FPA_PHS 	0x014C		//A 相基波有功相位校正寄存器 
#define	FPB_PHS 	0x014D		//B相基波有功相位校正寄存器 
#define	FPC_PHS 	0x014E		//C 相基波有功相位校正寄存器 
 
#define	FQA_PHS		0x014F		//A 相基波无功相位校正寄存器 
#define	FQB_PHS		0x0150		//B 相基波无功相位校正寄存器 
#define FQC_PHS    	0x0151		//C 相基波无功相位校正寄存器 
 
#define	FPA_OS		0x0152		//A 相基波有功功率 Offset  
#define	FPB_OS  	0x0153		//B 相基波有功功率 Offset  
#define FPC_OS		0x0154		//C 相基波有功功率 Offset  
 
#define	FQA_OS		0x0155		//A 相基波无功功率 Offset 
#define	FQB_OS	  	0x0156		//B 相基波无功功率 Offset 
#define	FQC_OS		0x0157		//C 相基波无功功率 Offset 
 
#define	SAGCFG 		0x0158    	//电压暂降阈值配置 
#define	OVLVL	  	0x0159	  	//过压阈值配置 
#define	OILVL		0x015A	 	//过流阈值配置 
 
//EMM配置和状态寄存器 
#define	CFCFG	    0x0160	 	//CF 引脚配置寄存器 
#define	EMUCFG 	    0x0161	 	//EMU 配置寄存器 
#define	EMUCON 	    0x0162		//EMU 控制寄存器 
#define	WSAVECON	0x0163		//采样数据写缓存控制寄存器 
#define	EMMIE  		0x0164 		//EMM 中断允许寄存器，写保护 
#define	EMMIF 		0x0165		//EMM 中断标志和状态寄存器 
#define	PQSign	    0x0166		//有功无功功率方向寄存器 
#define	Noload  	0x0167		//潜动启动状态寄存器 
#define	IRegionS 	0x0168		//电流分区状态寄存器 
#define	PHASES	    0x0169		//相电压电流状态寄存器 
#define	CheckSum1 	0x016A		//EMM 校表和配置寄存器校验和 
 
//NVM1 配置和状态寄存器  
#define	NVM1CFG		0x0170		//NVM1 配置寄存器 
#define	NVM1IF		0x0171		//NVM1 状态寄存器 
 
#define	NVM2CFG		0x0172		//NVM2 配置寄存器 
#define	NVM2CMPA 	0x0173		//NVM2 IA 比较器控制寄存器 
#define	NVM2CMPB	0x0174		//NVM2 IB 比较器控制寄存器 
#define	NVM2CMPC  	0x0175		//NVM2 IC 比较器控制寄存器 
#define	NVM2IF   	0x0176		//全失压状态寄存器 
 
//系统配置寄存器 
#define	WREN  		0x0180     //写使能寄存器 
#define	WMSW  		0x0181		//工作模式切换寄存器 
#define	SOFTRST  	0x0182		//软件复位寄存器 
#define	ADCCFG 		0x0183		//ADC 配置寄存器  
#define	MODSEL 		0x0186		//三相四线/三相三线模式选择寄存器 
 
//系统状态寄存器 
#define	SYSSR 		0x018A		//系统状态寄存器 
#define CheckSum2   0x018B		//NVM1、 NVM2、系统配置寄存器校验和 
#define	RData 	    0x018C		//上一次 SPI 读出的数据 
#define	WData 	    0x018D		//上一次 SPI 写入的数据 
#define	LRBufAddr 	0x018E		//最后一次读波形缓存的地址 
#define	DeviceID 	0x018F		//RN8302B Device ID 
 
//EMM 校表寄存器 II 
#define	ZXOTU 	    0x0190		//电压夹角及测频阈值寄存器 
#define	AUOTDC_EN  	0x0191		//直流 OFFSET 自动校正使能寄存器 
#define	ZXOTCFG  	0x0192		//过零计算配置及标志寄存器 
#define	IN_WaveEN 	0x0194		//IN 波形缓存使能寄存器 
#define	PA_PHSM   	0x01B0		//A 相有功分段相位校正寄存器-中段 
#define	PA_PHSH  	0x01B1		//A 相有功分段相位校正寄存器-高段 
#define	PB_PHSM 	0x01B2		//B 相有功分段相位校正寄存器-中段 
#define	PB_PHSH     0x01B3		//B 相有功分段相位校正寄存器-高段 
#define	PC_PHSM   	0x01B4      //C 相有功分段相位校正寄存器-中段 
#define	PC_PHSH   	0x01B5	    //C 相有功分段相位校正寄存器-高段 
#define	QA_PHSM    	0x01B6		//A 相无功分段相位校正寄存器-中段 
#define	QA_PHSH  	0x01B7		//A 相无功分段相位校正寄存器-高段 
#define	QB_PHSM 	0x01B8		//B 相无功分段相位校正寄存器-中段 
#define	QB_PHSH   	0x01B9      //B 相无功分段相位校正寄存器-中段 
#define	QC_PHSM    	0x01BA		//C 相无功分段相位校正寄存器-中段 
#define	QC_PHSH    	0x01BB		//C 相无功分段相位校正寄存器-中段 

#define EC          3200                  //电表常数
#define Kv		    0.00008920423028      //电压转换系数 1位小数
#define Ki          0.00059604644775      //电流转换系数 3位小数
#define Kp		    0.00044599418272	  //功率因数转换系数 1位小数

#define Ur	        22000000 	 //标准电压值 
#define Ir          10000000	 //标准电流值 
#define Pr          26226044     //PH=1, 标准功率值
    
void rn8302Init();
void rn8302WriteByte(uchar data);
uchar rn8302ReadByte();
void rn8302Write(uint wReg,uchar *pBuf,uchar ucLen);
uchar rn8302Read(uint wReg,uchar *pBuf,uchar ucLen);

#ifdef	__cplusplus
}
#endif

#endif	/* RN8302_H */

