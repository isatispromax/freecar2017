/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2016,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：179029047
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		MK60DN10_flash.h
 * @brief      		flash函数库
 * @company	   		成都逐飞科技有限公司
 * @author     		Go For It(1325536866)
 * @version    		v1.0
 * @Software 		IAR 7.2 or MDK 5.17
 * @Target core		MK60DN512VLL10
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2016-02-25
 ********************************************************************************************************************/
 
 
#ifndef _MK60DN10_flash_h
#define _MK60DN10_flash_h

#include "misc.h"
#include "MK60D10.h"
#include "common.h"



#define FTF    						FTFL
#define PROGRAM_CMD      			PGM4
#define SECTOR_SIZE     			(2048)
#define FLASH_SECTOR_NUM        	(256)                   //扇区数
#define FLASH_ALIGN_ADDR        	4                       //地址对齐整数倍
typedef uint32                  	FLASH_WRITE_TYPE;       //flash_write 函数写入 的数据类型


//-------------------------------------------------------------------------------------------------------------------
//  @brief      使用宏定义对flash进行数据读取
//  @param      SectorNum 		需要写入的扇区编号
//  @param      offset	 		地址偏移
//  @param      type		 	读取的数据类型
//  @return     				返回给定地址的数据
//  @since      v1.0
//  Sample usage:               flash_read(20,0,uint32);//读取20号扇区偏移0数据类型为uint32
//-------------------------------------------------------------------------------------------------------------------
#define     flash_read(SectorNum,offset,type)        (*(type *)((uint32)(((SectorNum)*SECTOR_SIZE) + (offset))))


void FLASH_Init(void);
uint32 FLASH_GetSectorSize(void);
uint8 FLASH_EraseSector(uint32 SectorNum);
uint8 FLASH_WriteSector(uint32 SectorNum, const uint8 *buf, uint32 len, uint32 offset);







#endif
