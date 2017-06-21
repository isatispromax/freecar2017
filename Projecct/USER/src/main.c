/********************************************
逐飞科技 总钻风-摄像头  历程
Designed by Fly Sir
软件版本:V1.1
最后更新:2016年5月3日
相关信息参考下列地址：
淘宝店：https://seekfree.taobao.com/
------------------------------------
软件版本： IAR 7.2 or MDK 5.17
目标核心： MK60DN512VLL10
============================================
MT9V032接线定义：
------------------------------------ 
    模块管脚            单片机管脚
    SDA(51的RX)         C17
    SCL(51的TX)         C16
	场中断(VSY)         
\
    像素中断(PCLK)      PTC18
    数据口(D0-D7)       PTC8-PTC15 

    TFT1.8液晶                
    SCL                 PTA15
    SDA                 PTA16        
    RES                 PTB17    
    DC                  PTB16
	CS					PTA14
============================================

分辨率是                188*120
摄像头参数设置可以到    SEEKFREE-->h_file-->SEEKFREE_MT9V032.h

总钻风-摄像头测试步骤：
1.下载程序到开发板
2.插上串口线或者USB转TTL
3.接好MT9V032模块接线
4.打开上位机设置好参数，即可观看 
*********************************************/  
#include "headfile.h"


int main(void)
{
  
  
    uint8 gy273buff[8]={0};
    double angle[5]={0};
    int i,j;
    
    //gpio_init(C13,GPO,0);
    get_clk();//上电后必须运行一次这个函数，获取各个频率信息，便于后面各个模块的参数设置
    my_delay(9999999);                                     //上电延时以便于摄像头初始化
    uart_init (uart0, 115200);                          //初始换串口与电脑通信
    camera_init();
    NRF_Dev_Init();
    //Gy273Init();
    uart_putchar(uart0,'a');
    
    for(;;)
	{
          if(mt9v032_finish_flag)
          {
          
            mt9v032_finish_flag = 0;
         
           //seekfree_sendimg_032();
           // NRF_send_image_buff();
           // NRF_sendimg();
            get_position_size();
         
          }
          //Multiple_read_HMC5883_Hard(gy273buff);
          //Read_HMC5883(gy273buff,angle);      
         // printf("angle0:    %f \n",angle[0]);
         // my_delay(9999999);
       
          
	}
  
 
//    uint8 buff[32]={0};
//  
//  NRF_Dev_Init();
//
//  while(1)
//  {
//    buff[1] = 'a';
//    buff[2] = 'b';
//    buff[3] = 'c';
//    buff[0] = 3;
//    NRF_Send_Packet(buff);
//    for(int i = 0;i<1000;i++)
//      for(int j=0;j<1000;j++);
//  
//  }
//  
  
  
}

