/* 
 * File:   char.h
 * Author: godart
 *
 * Created on 2018年12月24日, 下午5:03
 */

#ifndef CHAR_H
#define	CHAR_H

#ifdef	__cplusplus
extern "C" {
#endif

//数字
const uchar digit[]={
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,//0
	0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00,//1
	0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00,//2
	0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00,//3
	0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00,//4
	0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00,//5
	0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00,//6
	0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00,//7
	0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00,//8
	0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00,//9
    0x00,0x00,0xC0,0x38,0xE0,0x00,0x00,0x00,0x20,0x3C,0x23,0x02,0x02,0x27,0x38,0x20,//A
    0x08,0xF8,0x88,0x88,0x88,0x70,0x00,0x00,0x20,0x3F,0x20,0x20,0x20,0x11,0x0E,0x00,//B
    0xC0,0x30,0x08,0x08,0x08,0x08,0x38,0x00,0x07,0x18,0x20,0x20,0x20,0x10,0x08,0x00,//C
    0x08,0xF8,0x08,0x08,0x08,0x10,0xE0,0x00,0x20,0x3F,0x20,0x20,0x20,0x10,0x0F,0x00,//D
    0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x20,0x23,0x20,0x18,0x00,//E
    0x08,0xF8,0x88,0x88,0xE8,0x08,0x10,0x00,0x20,0x3F,0x20,0x00,0x03,0x00,0x00,0x00,//F
    
};
const uchar letter[]={
    0x08,0x78,0x88,0x00,0x00,0xC8,0x38,0x08,0x00,0x00,0x07,0x38,0x0E,0x01,0x00,0x00,//V0
    0x08,0xF8,0x88,0xC0,0x28,0x18,0x08,0x00,0x20,0x3F,0x20,0x01,0x26,0x38,0x20,0x00,//K1
    0x08,0xF8,0x00,0xF8,0x00,0xF8,0x08,0x00,0x00,0x03,0x3E,0x01,0x3E,0x03,0x00,0x00,//W2
    0x08,0xF8,0x08,0x00,0x00,0x08,0xF8,0x08,0x20,0x3F,0x21,0x01,0x01,0x21,0x3F,0x20,//H3
};
//汉字
const uchar ch[]={
	0x00,0xF8,0x08,0x08,0x08,0x08,0x88,0x7F,0x88,0x08,0x08,0x08,0x08,0xF8,0x00,0x00,
    0x00,0xFF,0x00,0x08,0x04,0x02,0x01,0x00,0x00,0x01,0x02,0x4C,0x80,0x7F,0x00,0x00,//内0
	0x10,0x21,0x86,0x70,0x00,0x7E,0x4A,0x4A,0x4A,0x4A,0x4A,0x7E,0x00,0x00,0x00,0x00,
    0x02,0xFE,0x01,0x40,0x7F,0x41,0x41,0x7F,0x41,0x41,0x7F,0x41,0x41,0x7F,0x40,0x00,//温1
	0x00,0xC0,0x30,0x1F,0x10,0x10,0xF0,0x00,0x00,0xFF,0x20,0x40,0x80,0x00,0x00,0x00,
    0x81,0x40,0x21,0x12,0x0C,0x03,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x03,0x00,0x00,//外2
	0x10,0x21,0x86,0x70,0x00,0x7E,0x4A,0x4A,0x4A,0x4A,0x4A,0x7E,0x00,0x00,0x00,0x00,
    0x02,0xFE,0x01,0x40,0x7F,0x41,0x41,0x7F,0x41,0x41,0x7F,0x41,0x41,0x7F,0x40,0x00,//温3
	0x10,0x60,0x02,0x8C,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,
    0x04,0x04,0x7E,0x01,0x44,0x48,0x50,0x7F,0x40,0x40,0x7F,0x50,0x48,0x44,0x40,0x00,//湿4
	0x10,0x0C,0x44,0x24,0x14,0x04,0x05,0x06,0x04,0x04,0x14,0x24,0x44,0x14,0x0C,0x00,
    0x00,0x40,0x40,0x41,0x41,0x41,0x41,0x7F,0x41,0x41,0x41,0x41,0x40,0x40,0x00,0x00,//空5
    0x40,0x42,0xCC,0x00,0x00,0xFE,0x82,0x92,0x92,0xFE,0x92,0x92,0x82,0xFE,0x00,0x00,
    0x00,0x00,0x3F,0x10,0x88,0x7F,0x00,0x1E,0x12,0x12,0x12,0x5E,0x80,0x7F,0x00,0x00,//调6
    0x40,0x44,0x54,0x65,0xC6,0x64,0x54,0x44,0x00,0xFC,0x44,0x44,0xC4,0x42,0x40,0x00,
    0x20,0x12,0x4A,0x82,0x7F,0x02,0x0A,0x92,0x60,0x1F,0x00,0x00,0xFF,0x00,0x00,0x00,//新7
    0x00,0x00,0xFE,0x02,0x12,0x22,0xC2,0x02,0xC2,0x32,0x02,0xFE,0x00,0x00,0x00,0x00,
    0x80,0x60,0x1F,0x00,0x20,0x10,0x0C,0x03,0x0C,0x30,0x00,0x0F,0x30,0x40,0xF8,0x00,//风8
	0x80,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x80,0x00,
    0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,//开9
    0x00,0x00,0x10,0x11,0x16,0x10,0x10,0xF0,0x10,0x10,0x14,0x13,0x10,0x00,0x00,0x00,
    0x81,0x81,0x41,0x41,0x21,0x11,0x0D,0x03,0x0D,0x11,0x21,0x41,0x41,0x81,0x81,0x00,//关10
    0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x90,0xA0,0xE0,0xC0,0xC0,0x80,0x80,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x02,0x03,0x01,0x01,0x00,0x00,0x00,//→11
    0x40,0x40,0x42,0xCC,0x00,0x20,0x22,0x22,0xA2,0x62,0x22,0x22,0x22,0x20,0x00,0x00,
    0x00,0x40,0x20,0x1F,0x20,0x44,0x4E,0x45,0x44,0x44,0x44,0x45,0x46,0x4C,0x40,0x00,//运12
    0x00,0x10,0x88,0xC4,0x33,0x00,0x40,0x42,0x42,0x42,0xC2,0x42,0x42,0x42,0x40,0x00,
    0x02,0x01,0x00,0xFF,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,//行13
    0x00,0x00,0x00,0xFC,0x44,0x44,0x44,0x45,0x46,0x44,0x44,0x44,0x44,0x7C,0x00,0x00,
    0x40,0x20,0x18,0x07,0x00,0xFC,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFC,0x00,0x00,//启14
    0x40,0x44,0xC4,0x44,0x44,0x44,0x40,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
    0x10,0x3C,0x13,0x10,0x14,0xB8,0x40,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,//动15
    0x10,0x21,0x86,0x70,0x00,0x7E,0x4A,0x4A,0x4A,0x4A,0x4A,0x7E,0x00,0x00,0x00,0x00,
    0x02,0xFE,0x01,0x40,0x7F,0x41,0x41,0x7F,0x41,0x41,0x7F,0x41,0x41,0x7F,0x40,0x00,//温16
    0x00,0x00,0xFC,0x24,0x24,0x24,0xFC,0x25,0x26,0x24,0xFC,0x24,0x24,0x24,0x04,0x00,
    0x40,0x30,0x8F,0x80,0x84,0x4C,0x55,0x25,0x25,0x25,0x55,0x4C,0x80,0x80,0x80,0x00,//度17
    0x10,0x21,0x86,0x70,0x00,0x7E,0x4A,0x4A,0x4A,0x4A,0x4A,0x7E,0x00,0x00,0x00,0x00,
    0x02,0xFE,0x01,0x40,0x7F,0x41,0x41,0x7F,0x41,0x41,0x7F,0x41,0x41,0x7F,0x40,0x00,//温18
    0x00,0x04,0x24,0x24,0x25,0x26,0xE4,0x3C,0x24,0x26,0x25,0x24,0x24,0x04,0x00,0x00,
    0x41,0x21,0x11,0x89,0x85,0x8B,0x89,0x89,0xF9,0x89,0x89,0x89,0x89,0x81,0x01,0x00,//差19
    0x40,0x40,0x42,0xCC,0x00,0x40,0xA0,0x9E,0x82,0x82,0x82,0x9E,0xA0,0x20,0x20,0x00,
    0x00,0x00,0x00,0x3F,0x90,0x88,0x40,0x43,0x2C,0x10,0x28,0x46,0x41,0x80,0x80,0x00,//设20
    0x00,0x17,0x15,0xD5,0x55,0x57,0x55,0x7D,0x55,0x57,0x55,0xD5,0x15,0x17,0x00,0x00,
    0x40,0x40,0x40,0x7F,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x7F,0x40,0x40,0x40,0x00,//置21
    0x00,0xFC,0x84,0x84,0x84,0xFC,0x00,0x10,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0x00,
    0x00,0x3F,0x10,0x10,0x10,0x3F,0x00,0x00,0x01,0x06,0x40,0x80,0x7F,0x00,0x00,0x00,//时22
    0x00,0xF8,0x01,0x06,0x00,0xF0,0x12,0x12,0x12,0xF2,0x02,0x02,0x02,0xFE,0x00,0x00,
    0x00,0xFF,0x00,0x00,0x00,0x1F,0x11,0x11,0x11,0x1F,0x00,0x40,0x80,0x7F,0x00,0x00,//间23
    0x40,0x40,0x42,0x42,0x42,0x42,0x42,0xFE,0x42,0x42,0x42,0x42,0x42,0x40,0x40,0x00,
    0x80,0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x03,0x0C,0x10,0x20,0x40,0x80,0x80,0x00,//天24
    0x80,0x40,0x20,0x90,0x88,0x86,0x80,0x80,0x80,0x83,0x8C,0x10,0x20,0x40,0x80,0x00,
    0x00,0x80,0x40,0x20,0x18,0x07,0x00,0x40,0x80,0x40,0x3F,0x00,0x00,0x00,0x00,0x00,//分25
    0x00,0x00,0x22,0x32,0x2A,0xA6,0xA2,0x62,0x21,0x11,0x09,0x81,0x01,0x00,0x00,0x00,
    0x00,0x42,0x22,0x13,0x0B,0x42,0x82,0x7E,0x02,0x02,0x0A,0x12,0x23,0x46,0x00,0x00,//系26
    0x20,0x30,0xAC,0x63,0x30,0x00,0x88,0xC8,0xA8,0x99,0x8E,0x88,0xA8,0xC8,0x88,0x00,
    0x22,0x67,0x22,0x12,0x12,0x80,0x40,0x30,0x0F,0x00,0x00,0x3F,0x40,0x40,0x71,0x00,//统27
    0x00,0x00,0xF0,0x10,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x10,0xF0,0x00,0x00,0x00,
    0x00,0x00,0x0F,0x04,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x0F,0x00,0x00,0x00,//中28
    0x40,0x30,0xEF,0x24,0x64,0x48,0x48,0x7F,0x48,0x48,0x48,0x7F,0x48,0x48,0x40,0x00,
    0x01,0x01,0x7F,0x21,0x11,0x00,0xFF,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,//错29
    0x40,0x42,0xCC,0x00,0x00,0x80,0x9E,0x92,0x92,0x92,0x92,0x92,0x9E,0x80,0x00,0x00,
    0x00,0x00,0x7F,0x20,0x94,0x84,0x44,0x24,0x14,0x0F,0x14,0x24,0x44,0x84,0x84,0x00,//误30
    0x40,0x42,0xCC,0x00,0x00,0x44,0x54,0x54,0x54,0x7F,0x54,0x54,0x54,0x44,0x40,0x00,
    0x00,0x00,0x7F,0x20,0x10,0x00,0xFF,0x15,0x15,0x15,0x55,0x95,0x7F,0x00,0x00,0x00,//请31
    0x88,0x68,0x1F,0xC8,0x08,0x10,0xC8,0x54,0x52,0xD1,0x12,0x94,0x08,0xD0,0x10,0x00,
    0x09,0x19,0x09,0xFF,0x05,0x00,0xFF,0x12,0x92,0xFF,0x00,0x5F,0x80,0x7F,0x00,0x00,//输32
    0x00,0x00,0x00,0x00,0x00,0x01,0xE2,0x1C,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x03,0x0C,0x30,0x40,0x80,0x80,0x00,//入33
    0x10,0x8C,0x44,0x04,0xE4,0x04,0x95,0xA6,0x44,0x24,0x14,0x84,0x44,0x94,0x0C,0x00,
    0x02,0x02,0x7A,0x41,0x41,0x43,0x42,0x7E,0x42,0x42,0x42,0x43,0xF8,0x00,0x00,0x00,//密34
    0x04,0x84,0xE4,0x5C,0x44,0xC4,0x00,0x02,0xF2,0x82,0x82,0x82,0xFE,0x80,0x80,0x00,
    0x02,0x01,0x7F,0x10,0x10,0x3F,0x00,0x08,0x08,0x08,0x08,0x48,0x88,0x40,0x3F,0x00,//码35
    0x40,0x20,0xF8,0x07,0xF0,0xA0,0x90,0x4C,0x57,0x24,0xA4,0x54,0x4C,0x80,0x80,0x00,
    0x00,0x00,0xFF,0x00,0x1F,0x80,0x92,0x52,0x49,0x29,0x24,0x12,0x08,0x00,0x00,0x00,//修36
    0x04,0x84,0x84,0x84,0x84,0xFC,0x40,0x30,0xCC,0x0B,0x08,0x08,0xF8,0x08,0x08,0x00,
    0x00,0x7F,0x20,0x10,0x10,0x08,0x80,0x40,0x21,0x16,0x08,0x16,0x21,0x40,0x80,0x00,//改37
    0x40,0x44,0x54,0x65,0xC6,0x64,0x54,0x44,0x00,0xFC,0x44,0x44,0xC4,0x42,0x40,0x00,
    0x20,0x12,0x4A,0x82,0x7F,0x02,0x0A,0x92,0x60,0x1F,0x00,0x00,0xFF,0x00,0x00,0x00,//新38
    0x02,0xE2,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0xE2,0x02,0x00,
    0x00,0xFF,0x00,0x08,0x06,0x01,0x16,0x08,0x06,0x01,0x02,0x4C,0x80,0x7F,0x00,0x00,//两39
    0x00,0x02,0x0C,0x80,0x60,0x80,0x40,0x30,0x0F,0xC8,0x08,0x08,0x28,0x18,0x00,0x00,
    0x02,0x02,0x7E,0x01,0x80,0x40,0x20,0x18,0x06,0x01,0x06,0x18,0x20,0x40,0x80,0x00,//次40
    0x00,0x02,0x02,0x02,0x02,0x82,0x42,0xF2,0x0E,0x42,0x82,0x02,0x02,0x02,0x00,0x00,
    0x10,0x08,0x04,0x02,0x01,0x00,0x00,0xFF,0x00,0x00,0x00,0x01,0x02,0x0C,0x00,0x00,//不41
    0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//一42
    0x42,0x62,0x5A,0xC6,0x52,0x62,0xC2,0x20,0xD8,0x17,0x10,0x10,0xF0,0x10,0x10,0x00,
    0x40,0xC4,0x44,0x7F,0x24,0x24,0xA0,0x40,0x21,0x16,0x08,0x16,0x21,0x40,0x80,0x00,//致43
    0x08,0x08,0x08,0x08,0xC8,0x78,0xCF,0x48,0x48,0x48,0x48,0xC8,0x08,0x08,0x08,0x00,
    0x10,0x88,0x84,0x43,0x40,0x20,0x21,0x16,0x08,0x14,0x22,0x41,0x40,0x80,0x80,0x00,//友44
    0x10,0x10,0x10,0xFF,0x90,0x20,0x98,0x48,0x28,0x09,0x0E,0x28,0x48,0xA8,0x18,0x00,
    0x02,0x42,0x81,0x7F,0x00,0x40,0x40,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x40,0x00,//控45
    0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
    0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,//电46
    0x80,0x82,0x82,0x82,0x82,0x82,0x82,0xE2,0xA2,0x92,0x8A,0x86,0x82,0x80,0x80,0x00,
    0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//子47
    0x88,0xA8,0xA8,0xFF,0xA8,0xA8,0x88,0x00,0x44,0x44,0xFC,0x22,0x23,0x22,0x00,0x00,
    0x20,0x18,0x06,0xFF,0x02,0x0C,0x00,0x04,0x04,0x04,0x7F,0x82,0x82,0x82,0xF2,0x00,//耗48
    0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0xFF,0x88,0x88,0x88,0x88,0xF8,0x00,0x00,0x00,
    0x00,0x00,0x1F,0x08,0x08,0x08,0x08,0x7F,0x88,0x88,0x88,0x88,0x9F,0x80,0xF0,0x00,//电49
    0x00,0x10,0x10,0x10,0x10,0xD0,0x30,0xFF,0x30,0xD0,0x10,0x10,0x10,0x10,0x00,0x00,
    0x10,0x08,0x04,0x02,0x09,0x08,0x08,0xFF,0x08,0x08,0x09,0x02,0x04,0x08,0x10,0x00,//本50
    0x00,0x20,0x18,0xC7,0x44,0x44,0x44,0x44,0xFC,0x44,0x44,0x44,0x44,0x04,0x00,0x00,
    0x04,0x04,0x04,0x07,0x04,0x04,0x04,0x04,0xFF,0x04,0x04,0x04,0x04,0x04,0x04,0x00,//年51
    0x00,0x00,0x00,0xFE,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,0x00,
    0x80,0x40,0x30,0x0F,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x82,0x7F,0x00,0x00,0x00,//月52
    0x80,0x80,0x40,0x20,0x10,0x08,0x24,0xC3,0x04,0x08,0x10,0x20,0x40,0x80,0x80,0x00,
    0x00,0x00,0x00,0x02,0x02,0x02,0x02,0x82,0x42,0x22,0x1A,0x06,0x00,0x00,0x00,0x00,//今53
    0x00,0x00,0x00,0xFE,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0xFE,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0xFF,0x00,0x00,0x00,0x00,//日54
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x40,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00,
    0x40,0x40,0x40,0x40,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x00,/*"上",55*/
    0x00,0xFE,0x22,0x5A,0x86,0x00,0xFE,0x92,0x92,0x92,0x92,0x92,0xFE,0x00,0x00,0x00,
    0x00,0xFF,0x04,0x08,0x07,0x00,0xFF,0x40,0x20,0x03,0x0C,0x14,0x22,0x41,0x40,0x00,/*"限",56*/
    0x00,0x00,0x00,0x7F,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0x7F,0x00,0x00,0x00,0x00,
    0x81,0x41,0x21,0x1D,0x21,0x41,0x81,0xFF,0x89,0x89,0x89,0x89,0x89,0x81,0x81,0x00,/*"是",57*/
    0x00,0x02,0x82,0x82,0x42,0x22,0x12,0xFA,0x06,0x22,0x22,0x42,0x42,0x82,0x00,0x00,
    0x01,0x01,0x00,0xFC,0x44,0x44,0x44,0x45,0x44,0x44,0x44,0xFC,0x00,0x00,0x01,0x00,/*"否",58*/
    0x80,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x80,0x00,
    0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,/*"开",59*/
    0x00,0x00,0x00,0xFC,0x44,0x44,0x44,0x45,0x46,0x44,0x44,0x44,0x44,0x7C,0x00,0x00,
    0x40,0x20,0x18,0x07,0x00,0xFC,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0xFC,0x00,0x00,/*"启",60*/
    0x10,0x10,0x10,0xFF,0x10,0x90,0x00,0xFE,0x82,0x82,0x82,0x92,0xA2,0x9E,0x00,0x00,
    0x04,0x44,0x82,0x7F,0x01,0x00,0x00,0xFF,0x80,0x43,0x2C,0x10,0x2C,0x43,0x80,0x00,/*"报",61*/
    0x12,0xEA,0xAF,0xAA,0xEA,0x0F,0xFA,0x02,0x88,0x8C,0x57,0x24,0x54,0x8C,0x84,0x00,
    0x02,0x02,0xEA,0xAA,0xAA,0xAB,0xAA,0xAB,0xAA,0xAA,0xAA,0xAA,0xEA,0x02,0x02,0x00,/*"警",62*/
    0x08,0x08,0x08,0x08,0x08,0xF8,0x89,0x8E,0x88,0x88,0x88,0x88,0x08,0x08,0x08,0x00,
    0x00,0x80,0x40,0x20,0x18,0x07,0x00,0x00,0x40,0x80,0x40,0x3F,0x00,0x00,0x00,0x00,/*"方",63*/
    0x10,0x10,0x90,0x90,0x90,0x90,0x90,0x10,0x10,0xFF,0x10,0x10,0x11,0x16,0x10,0x00,
    0x00,0x20,0x60,0x20,0x3F,0x10,0x10,0x10,0x00,0x03,0x0C,0x10,0x20,0x40,0xF8,0x00,/*"式",64*/
    0x00,0xFE,0x02,0x22,0xDA,0x06,0x08,0x08,0xF8,0x89,0x8E,0x88,0x88,0x88,0x08,0x00,
    0x00,0xFF,0x08,0x10,0x08,0x87,0x40,0x30,0x0F,0x00,0x40,0x80,0x40,0x3F,0x00,0x00,/*"防",65*/
    0x40,0x7C,0x40,0x7F,0x48,0x48,0x40,0xF2,0x12,0x1A,0xD6,0x12,0x12,0xF2,0x02,0x00,
    0x90,0x8E,0x40,0x4F,0x20,0x1E,0x80,0x4F,0x20,0x18,0x07,0x10,0x20,0x4F,0x80,0x00,/*"频",66*/
    0x28,0xE4,0xBB,0xAA,0xFA,0xAA,0xFA,0xA2,0x10,0x08,0xB7,0x44,0xBC,0x04,0x04,0x00,
    0x00,0x00,0x90,0x54,0x16,0x55,0x9C,0x74,0x12,0x11,0x50,0x98,0x30,0x01,0x01,0x00,/*"繁",67*/
    0x40,0x40,0x42,0xCC,0x00,0x40,0xA0,0x9E,0x82,0x82,0x82,0x9E,0xA0,0x20,0x20,0x00,
    0x00,0x00,0x00,0x3F,0x90,0x88,0x40,0x43,0x2C,0x10,0x28,0x46,0x41,0x80,0x80,0x00,/*"设",68*/
    0x80,0x90,0x90,0x48,0x4C,0x57,0x24,0x24,0x24,0x54,0x4C,0x44,0x80,0x80,0x80,0x00,
    0x00,0x00,0x00,0xFF,0x49,0x49,0x49,0x7F,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,0x00,/*"备",69*/
    0x20,0x20,0x20,0xFF,0x20,0x20,0x80,0xF8,0x80,0x40,0xFF,0x20,0x10,0xF0,0x00,0x00,
    0x10,0x30,0x10,0x0F,0x08,0x08,0x00,0x3F,0x40,0x40,0x5F,0x42,0x44,0x43,0x78,0x00,/*"地",70*/
    0x20,0x20,0x20,0xFF,0x20,0x20,0x00,0xF8,0x00,0x00,0xFF,0x40,0x40,0x40,0x00,0x00,
    0x10,0x30,0x10,0x0F,0x08,0x48,0x40,0x7F,0x40,0x40,0x7F,0x40,0x40,0x40,0x40,0x00,/*"址",71*/
    0x40,0x40,0x42,0xCC,0x00,0x20,0x22,0x22,0xA2,0x62,0x22,0x22,0x22,0x20,0x00,0x00,
    0x00,0x40,0x20,0x1F,0x20,0x44,0x4E,0x45,0x44,0x44,0x44,0x45,0x46,0x4C,0x40,0x00,/*"运",72*/
    0x00,0x10,0x88,0xC4,0x33,0x00,0x40,0x42,0x42,0x42,0xC2,0x42,0x42,0x42,0x40,0x00,
    0x02,0x01,0x00,0xFF,0x00,0x00,0x00,0x00,0x40,0x80,0x7F,0x00,0x00,0x00,0x00,0x00,/*"行",73*/
    0x10,0x60,0x02,0x8C,0x00,0xFE,0x02,0xF2,0x02,0xFE,0x00,0xF8,0x00,0xFF,0x00,0x00,
    0x04,0x04,0x7E,0x01,0x80,0x47,0x30,0x0F,0x10,0x27,0x00,0x47,0x80,0x7F,0x00,0x00,/*"测",74*/
    0x40,0x40,0x42,0xCC,0x00,0x90,0x90,0x90,0x90,0x90,0xFF,0x10,0x11,0x16,0x10,0x00,
    0x00,0x00,0x00,0x3F,0x10,0x28,0x60,0x3F,0x10,0x10,0x01,0x0E,0x30,0x40,0xF0,0x00,/*"试",75*/
    0x00,0xE0,0x00,0xFF,0x10,0x20,0x08,0x88,0x78,0x0F,0x08,0xE8,0x08,0x08,0x88,0x00,
    0x01,0x00,0x00,0xFF,0x00,0x10,0x0C,0x83,0x44,0x23,0x18,0x07,0x18,0x62,0x81,0x00,/*"恢",76*/
    0x20,0x10,0x08,0xF7,0x54,0x54,0x54,0x54,0x54,0x54,0x54,0xF4,0x04,0x04,0x00,0x00,
    0x80,0x90,0x90,0x49,0x4D,0x57,0x25,0x25,0x25,0x55,0x4D,0x45,0x80,0x80,0x80,0x00,/*"复",77*/
    0x7E,0x4A,0x52,0xFE,0x52,0x4A,0x7E,0x20,0x20,0x20,0xFF,0x20,0x22,0x2C,0x20,0x00,
    0xE9,0x09,0x69,0x07,0x65,0x05,0xB5,0x40,0x30,0x0E,0x01,0x0E,0x30,0x40,0x80,0x00,/*"默",78*/
    0x40,0x40,0x42,0xCC,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x3F,0x90,0x48,0x20,0x18,0x07,0x00,0x07,0x18,0x20,0x40,0x80,0x00,/*"认",79*/
    0x10,0x10,0xFF,0x10,0x90,0xE0,0x2F,0x29,0xE9,0x09,0xE9,0x29,0x2F,0xE0,0x00,0x00,
    0x42,0x82,0x7F,0x41,0x44,0x25,0x15,0x0D,0x05,0xFE,0x0D,0x15,0x25,0x45,0x44,0x00,/*"操",80*/
    0x00,0x80,0x60,0xF8,0x07,0x40,0x30,0x0F,0xF8,0x88,0x88,0x88,0x88,0x08,0x08,0x00,
    0x01,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0xFF,0x08,0x08,0x08,0x08,0x08,0x00,0x00,/*"作",81*/
    0x00,0x00,0xC0,0x5E,0x52,0x52,0x52,0x52,0x52,0x52,0x52,0x5E,0xC0,0x00,0x00,0x00,
    0x80,0x80,0x8F,0x40,0x40,0x20,0x10,0x0E,0x10,0x10,0x20,0x20,0x4F,0x80,0x00,0x00,/*"员",82*/
    0x88,0x64,0x23,0xA2,0xA6,0xAA,0xA2,0xBA,0xA4,0xA3,0xA2,0x26,0x2A,0xA2,0x62,0x00,
    0x00,0x00,0x00,0xFF,0x4A,0x4A,0x4A,0x4A,0x4A,0x4A,0x4B,0xF8,0x00,0x00,0x00,0x00,/*"管",83*/
    0x04,0x84,0x84,0xFC,0x84,0x84,0x00,0xFE,0x92,0x92,0xFE,0x92,0x92,0xFE,0x00,0x00,
    0x20,0x60,0x20,0x1F,0x10,0x10,0x40,0x44,0x44,0x44,0x7F,0x44,0x44,0x44,0x40,0x00,/*"理",84*/
    0x10,0x60,0x02,0x8C,0x00,0x44,0x54,0x54,0x54,0x7F,0x54,0x54,0x54,0x44,0x40,0x00,
    0x04,0x04,0x7E,0x01,0x00,0x00,0xFF,0x15,0x15,0x15,0x55,0x95,0x7F,0x00,0x00,0x00,/*"清",85*/
    0x10,0x0C,0x05,0x55,0x55,0x55,0x85,0x7F,0x85,0x55,0x55,0x55,0x05,0x14,0x0C,0x00,
    0x04,0x04,0x02,0x0A,0x09,0x29,0x2A,0x4C,0x48,0xA9,0x19,0x02,0x02,0x04,0x04,0x00,/*"零",86*/
    0x90,0x52,0x34,0x10,0xFF,0x10,0x34,0x52,0x80,0x70,0x8F,0x08,0x08,0xF8,0x08,0x00,
    0x82,0x9A,0x56,0x63,0x22,0x52,0x8E,0x00,0x80,0x40,0x33,0x0C,0x33,0x40,0x80,0x00,/*"数",87*/
    0x10,0x10,0xFF,0x10,0x90,0x00,0xFE,0x92,0x92,0x92,0xF2,0x92,0x92,0x9E,0x80,0x00,
    0x42,0x82,0x7F,0x01,0x80,0x60,0x1F,0x00,0xFC,0x44,0x47,0x44,0x44,0xFC,0x00,0x00,/*"据",88*/
    0x00,0x00,0xF8,0x88,0x88,0x88,0x88,0x08,0x08,0xFF,0x08,0x09,0x0A,0xC8,0x08,0x00,
    0x80,0x60,0x1F,0x00,0x10,0x20,0x1F,0x80,0x40,0x21,0x16,0x18,0x26,0x41,0xF8,0x00,/*"成",89*/
    0x08,0x08,0x08,0xF8,0x08,0x08,0x08,0x10,0x10,0xFF,0x10,0x10,0x10,0xF0,0x00,0x00,
    0x10,0x30,0x10,0x1F,0x08,0x88,0x48,0x30,0x0E,0x01,0x40,0x80,0x40,0x3F,0x00,0x00,/*"功",90*/
    0x00,0x40,0x30,0x1E,0x10,0x10,0x10,0xFF,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00,
    0x81,0x81,0x41,0x21,0x11,0x0D,0x03,0x01,0x03,0x0D,0x11,0x21,0x41,0x81,0x81,0x00,/*"失",91*/
    0x00,0xFE,0x02,0xFA,0x02,0xFE,0x40,0x20,0xD8,0x17,0x10,0x10,0xF0,0x10,0x10,0x00,
    0x80,0x47,0x30,0x0F,0x10,0x67,0x80,0x40,0x21,0x16,0x08,0x16,0x21,0x40,0x80,0x00,/*"败",92*/
    0x00,0x80,0x60,0xF8,0x07,0x00,0x3E,0x22,0x22,0xE2,0x22,0x22,0x3E,0x00,0x00,0x00,
    0x01,0x00,0x00,0xFF,0x20,0x11,0x09,0x05,0x03,0xFF,0x03,0x05,0x09,0x11,0x20,0x00,/*"保",93*/
    0x04,0x04,0x84,0xE4,0x1C,0x07,0x24,0x24,0x24,0x24,0xA4,0x64,0x24,0x04,0x04,0x00,
    0x02,0x01,0x00,0xFF,0x00,0x02,0x02,0x42,0x82,0x7F,0x02,0x02,0x02,0x02,0x02,0x00,/*"存",94*/
    0x06,0x09,0x09,0xE6,0xF8,0x0C,0x04,0x02,0x02,0x02,0x02,0x02,0x04,0x1E,0x00,0x00,
    0x00,0x00,0x00,0x07,0x1F,0x30,0x20,0x40,0x40,0x40,0x40,0x40,0x20,0x10,0x00,0x00,/*"℃",95*/
    0x10,0x10,0x10,0xFF,0x90,0x20,0x98,0x88,0x88,0xE9,0x8E,0x88,0x88,0xA8,0x98,0x00,
    0x02,0x42,0x81,0x7F,0x00,0x00,0x80,0x84,0x4B,0x28,0x10,0x28,0x47,0x80,0x00,0x00,/*"按",96*/
    0x20,0x10,0x2C,0xE7,0x24,0x24,0x00,0x82,0x82,0xFE,0x82,0x82,0xFE,0x00,0x00,0x00,
    0x01,0x01,0x01,0x7F,0x21,0x11,0x40,0x40,0x7F,0x40,0x40,0x40,0x7F,0x40,0x40,0x00,/*"钮",97*/
    0x10,0x10,0x10,0xFF,0x10,0x50,0x44,0x54,0x65,0xC6,0x44,0x64,0x54,0x44,0x40,0x00,
    0x04,0x44,0x82,0x7F,0x01,0x82,0x82,0x4A,0x56,0x23,0x22,0x52,0x4E,0x82,0x02,0x00,/*"接",98*/
    0x40,0x42,0xCC,0x00,0x00,0xE2,0x22,0x2A,0x2A,0xF2,0x2A,0x26,0x22,0xE0,0x00,0x00,
    0x80,0x40,0x3F,0x40,0x80,0xFF,0x89,0x89,0x89,0xBF,0x89,0xA9,0xC9,0xBF,0x80,0x00,/*"通",99*/
    0x80,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x80,0x00,
    0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,/*"开",100*/
    0x10,0x10,0xD0,0xFF,0x90,0x10,0x00,0xFE,0x02,0x02,0x02,0xFE,0x00,0x00,0x00,0x00,
    0x04,0x03,0x00,0xFF,0x00,0x83,0x60,0x1F,0x00,0x00,0x00,0x3F,0x40,0x40,0x78,0x00,/*"机",101*/
    0x00,0xFC,0x20,0x24,0xA8,0xFF,0xA8,0x24,0x00,0xFC,0x44,0x44,0xC4,0x42,0x40,0x00,
    0x00,0x3F,0x22,0x21,0x20,0x2F,0x20,0xA3,0x60,0x1F,0x00,0x00,0xFF,0x00,0x00,0x00,/*"断",102*/
    0x80,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x82,0x82,0xFE,0x82,0x82,0x82,0x80,0x00,
    0x00,0x80,0x40,0x30,0x0F,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,/*"开",103*/
};
//符号
const uchar symbol[]={
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,//-/0
	0x00,0x00,0x00,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,//:/1
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x0C,0x00,0x00,//./2
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// /3
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,//_/4
    0x40,0x40,0x80,0xF0,0x80,0x40,0x40,0x00,0x02,0x02,0x01,0x0F,0x01,0x02,0x02,0x00,//*/5
    0xF0,0x08,0xF0,0x80,0x60,0x18,0x00,0x00,0x00,0x31,0x0C,0x03,0x1E,0x21,0x1E,0x00,//%/6
};


#ifdef	__cplusplus
}
#endif

#endif	/* CHAR_H */
