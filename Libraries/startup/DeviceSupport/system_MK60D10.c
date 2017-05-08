/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		system_MK60D10.c
 * @brief      		时钟初始化
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.2 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 ********************************************************************************************************************/

#include <stdint.h>
#include "MK60D10.h"
#include "MK60DN10_port.h"


void Disable_Wdog(void)
{
    // Disable the WDOG module 
    // WDOG_UNLOCK: WDOGUNLOCK=0xC520 
    WDOG->UNLOCK = (uint16_t)0xC520u;     // Key 1 
    // WDOG_UNLOCK : WDOGUNLOCK=0xD928 
    WDOG->UNLOCK  = (uint16_t)0xD928u;    // Key 2 
    // WDOG_STCTRLH: ??=0,DISTESTWDOG=0,BYTESEL=0,TESTSEL=0,TESTWDOG=0,??=0,STNDBYEN=1,WAITEN=1,STOPEN=1,DBGEN=0,ALLOWUPDATE=1,WINEN=0,IRQRSTEN=0,CLKSRC=1,WDOGEN=0 
    WDOG->STCTRLH = (uint16_t)0x01D2u;
}






void SYSTEM_CLK(void)
{
	// Switch to FBE Mode
	SIM->CLKDIV1 = (uint32_t)0xffffffffu;    			// 预分频寄存器，先都设置为1
	OSC->CR = (uint8_t)0x80u;                           // 启用外部晶振
	MCG->C2 &= ~MCG_C2_LP_MASK;							// 外部晶振是有源的时候不要置位MCG_C2_EREFS0_MASK ，这样才能使用A19引脚
	MCG->C2 |= MCG_C2_RANGE0(2);

	MCG->C1 = (uint8_t)0xBAu;                           // 选择外部时钟作为MCGOUTCLK的输入源，1536分频，FLL输入源为外部时钟，启用MCGIRCLK，内部参考时钟在停止模式下禁止
	MCG->C4 &= (uint8_t)~(uint8_t)0xE0u;
	MCG->C6 &= (uint8_t)( ~(uint8_t)MCG_C6_PLLS_MASK ); // MCG的输入源选择FLL
	while((MCG->S & MCG_S_IREFST_MASK) != 0u) {  }      // 等待，直到FLL的时钟源是外部时钟
	while((MCG->S & MCG_S_CLKST_MASK) != 0x08u) {  }    // 等待，MCGOUTCLK的时钟源被选择为外部时钟
	
	// Switch to PBE Mode 
	SIM->CLKDIV1 = (uint32_t)0x00330000u;               // 更新预分频器   //CORE_CLK = MCGOUTCLK  BUS_CLK = MCGOUTCLK     FLEXBUS_CLK = MCGOUTCLK/4     FLASH_CLK = MCGOUTCLK/4
	MCG->C5 = (uint8_t)0x18u;                           // PLL输入前分频系数为25,50/25=2
	MCG->C6 = (uint8_t)0x5Au;                           // 当CLKS[1:0]=00 选择PLL输出作为MCG的时钟源 倍频系数50
	
	while((MCG->S & MCG_S_PLLST_MASK) == 0u) {  }       // Wait until the source of the PLLS clock has switched to the PLL 
	while((MCG->S & MCG_S_LOCK0_MASK) == 0u) {  }       // Wait until locked 
	
	// Switch to PEE Mode 
	MCG->C1 = (uint8_t)0x1Au;
	while((MCG->S & 0x0Cu) != 0x0Cu) {  }               // Wait until output of the PLL is selected 
	while((MCG->S & MCG_S_LOCK0_MASK) == 0u) {  }       // Wait until locked
}

void Start (void) 
{
    Disable_Wdog();
    SYSTEM_CLK();
	gpio_init(A4,GPO,1);  //初始化为输出1，即 禁用了 NMI 中断
}



void NMI_Handler(void)
{
	
}


