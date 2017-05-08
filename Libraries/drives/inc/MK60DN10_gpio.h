/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		MK60DN10_gpio.h
 * @brief      		gpio函数库
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.2 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 ********************************************************************************************************************/



#ifndef _MK60DN10_gpio_h
#define _MK60DN10_gpio_h

#include "MK60D10.h"
#include "common.h"

// 位带操作 内存偏移计算 详见 Cortex-M4 Generic User Guide 2.25 
// CM4中有2块bitband区域 0x2000_0000-0x200F_FFFF 映射至 0x2200_0000-0x23FF_FFFF
//                       0x4000_0000-0x4000_FFFF 映射至 0x4200_0000-0x43FF_FFFF

#define PAout(n)   BITBAND_REG(PTA->PDOR, n)
#define PAin(n)    BITBAND_REG(PTA->PDIR, n)
  
#define PBout(n)   BITBAND_REG(PTB->PDOR, n)
#define PBin(n)    BITBAND_REG(PTB->PDIR, n)

#define PCout(n)   BITBAND_REG(PTC->PDOR, n)
#define PCin(n)    BITBAND_REG(PTC->PDIR, n)

#define PDout(n)   BITBAND_REG(PTD->PDOR, n)
#define PDin(n)    BITBAND_REG(PTD->PDIR, n)

#define PEout(n)   BITBAND_REG(PTE->PDOR, n)
#define PEin(n)    BITBAND_REG(PTE->PDIR, n)


//定义PTA的8位输入端口地址
#define A_IN_DATA(x)    *(uint8 *)(PTA_BASE+0x10+x)
//#define A_B1_IN       *(uint8 *)(PTA_BASE+0x10+x)
//#define A_B2_IN       (&(PTA->PDIR))+2
//#define A_B3_IN       (&(PTA->PDIR))+3

//定义PTB的8位输入端口地址
#define B_IN_DATA(x)    *(uint8 *)(PTB_BASE+0x10+x)
//#define B_B0_IN       (&(PTB->PDIR))
//#define B_B1_IN       (&(PTB->PDIR))+1
//#define B_B2_IN       (&(PTB->PDIR))+2
//#define B_B3_IN       (&(PTB->PDIR))+3


//定义PTC的8位输入端口地址
#define C_IN_DATA(x)    *(uint8 *)(PTC_BASE+0x10+x)
//#define C_B0_IN       (&(PTC->PDIR))
//#define C_B1_IN       (&(PTC->PDIR))+1
//#define C_B2_IN       (&(PTC->PDIR))+2
//#define C_B3_IN       (&(PTC->PDIR))+3

//定义PTD的8位输入端口地址
#define D_IN_DATA(x)    *(uint8 *)(PTD_BASE+0x10+x)
//#define D_B0_IN       (&(PTC->PDIR)) 
//#define D_B1_IN       (&(PTC->PDIR))+1
//#define D_B2_IN       (&(PTC->PDIR))+2
//#define D_B3_IN       (&(PTC->PDIR))+3

//定义PTE的8位输入端口地址
#define E_IN_DATA(x)    *(uint8 *)(PTE_BASE+0x10+x)
//#define E_B0_IN       (&(PTC->PDIR))
//#define E_B1_IN       (&(PTC->PDIR))+1
//#define E_B2_IN       (&(PTC->PDIR))+2
//#define E_B3_IN       (&(PTC->PDIR))+3

void    gpio_init(PTX_n ptx_n, GPIO_MOD ddr, uint8 dat);//初始化gpio
void    gpio_ddr(PTX_n ptx_n, GPIO_MOD ddr);            //设置引脚方向
uint8   gpio_get(PTX_n ptx_n);                          //获取引脚状态
void    gpio_set(PTX_n ptx_n, uint8 dat);               //设置引脚状态
void    gpio_turn(PTX_n ptx_n);                         //翻转引脚状态

#endif
