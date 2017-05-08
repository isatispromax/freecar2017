/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		MK60DN10_ftm.h
 * @brief      		FTM函数库
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.2 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 ********************************************************************************************************************/
 
 
 
#ifndef _MK60DN10_ftm_h
#define _MK60DN10_ftm_h


#include "misc.h"
#include "MK60D10.h"
#include "common.h"
#include "MK60DN10_port.h"
#include "MK60DN10_gpio.h"
#include "MK60DN10_port_cfg.h"


typedef enum
{
    ftm0,
    ftm1,
    ftm2,
} FTMn;


typedef enum
{
    ftm_ch0,
    ftm_ch1,
    ftm_ch2,
    ftm_ch3,
    ftm_ch4,
    ftm_ch5,
    ftm_ch6,
    ftm_ch7,
} FTM_CHn;

//------------------------ PWM ------------------------

#define FTM0_PRECISON 1000u     //定义占空比精度，意思即使把一个周期分成多少分，分多越多这样精度越高，设置占空比的时候duty的范围就是0-FTM0_PRECISON
#define FTM1_PRECISON 1000u     //定义占空比精度，意思即使把一个周期分成多少分，分多越多这样精度越高，设置占空比的时候duty的范围就是0-FTM0_PRECISON
#define FTM2_PRECISON 1000u     //定义占空比精度，意思即使把一个周期分成多少分，分多越多这样精度越高，设置占空比的时候duty的范围就是0-FTM0_PRECISON


//------------------------ 输入捕捉 ------------------------
//FTM 输入捕捉配置
typedef enum
{
    FTM_Rising=0x01,               //上升沿捕捉
    FTM_Falling=0x10,              //下降沿捕捉
    FTM_Rising_or_Falling=0x11     //跳变沿捕捉
} FTM_Input_cfg;

void ftm_pwm_init(FTMn ftmn, FTM_CHn ch, uint32 freq, uint32 duty);
void ftm_pwm_duty(FTMn ftmn, FTM_CHn ch, uint32 duty);
void ftm_pwm_freq(FTMn ftmn, uint32 freq);
void ftm_input_init(FTMn ftmn, FTM_CHn ch, FTM_Input_cfg cfg,uint32 freq_max);
uint16 ftm_input_get (FTMn ftmn, FTM_CHn ch);
void ftm_input_clean (FTMn ftmn);
void ftm_quad_init(FTMn ftmn);
int16 ftm_quad_get(FTMn ftmn);
void ftm_quad_clean(FTMn ftmn);

#endif
