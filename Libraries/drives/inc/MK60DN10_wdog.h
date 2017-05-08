/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		MK60DN10_wdog.h
 * @brief      		看门狗函数库
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.2 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 ********************************************************************************************************************/
 
#ifndef _MK60DN10_rtc_h
#define _MK60DN10_rtc_h

#include "misc.h"
#include "MK60D10.h"
#include "common.h"
#include "stdlib.h"


//wdog 代码，采用 LPO 时钟，不分频。

extern void wdog_init_ms(uint32 ms);   //初始化看门狗，设置喂狗时间 ms
extern void wdog_feed(void);           //喂狗


extern void wdog_disable(void);        //禁用看门狗
extern void wdog_enable(void);         //启用看门狗

#endif 
