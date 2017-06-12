#include "headfile.h"
#include "data.h"
#include "math.h"

#define THRESHOLD 130


int dir[][2]=
{
  {-1,-1},{0,-1},
  {1,-1},{-1,0},
  {1,0},{-1,1},
  {0,1},{1,1}
};
Node head[10];
uint8 tempimage[ROW][COL]; //用于处理数据 的临时数组
uint8 binary_image[ROW][COL]; //二值化后的数组
uint16 light_num; //亮点的数目

uint16 xmax,ymax,xmin,ymin;

/*

*COL     188//图像宽度  
*ROW     120//图像高度

*/


/*
*函数名：gray_binary
*返回值：0错误，1，成功
*参数:image 图像数组,binimage 二值化数组
*作者：杨迪
*最后修改时间：2017.5.6
*/
/*
uint8 gray_binary(uint8 (*image)[ROW],uint8 (*binimage)[ROW])
{
   uint8 i,j;
   
   for(i=0;i<COL;i++)
   {
     for(j=0;j<ROW;j++)
     {
       if(image[i][j] > THRESHOLD)
       {
          binimage[i][j] = 1;
       }
       else
       {
          binimage[i][j] = 0;
       }
     
     }
   }
    
}
*/
uint8 gray_binary(uint8 *image,uint8 *binimage)
{
   uint32 i;
   
   for(i=0;i<COL*ROW;i++)
   {
     
     if(image[i]>THRESHOLD)
     {
        binimage[i] = 1;
     }
     else
     {
       binimage[i] = 0;
     }
     
   }
   
   return 1;    
}

/*
*函数名：find_size
*功能：发现一个亮点后找到与这个亮点相连通的所有亮点，统计这些亮点的数目
*参数：i  点的x坐标，j   点的y坐标
*说明“由于采用了全局变量，find_position函数只可被调用一次，且调用后image[][]数组内数据将被全部置0
*该函数在其它函数被调用
*最后修改时间：2017-5-6
*/
void find_size(int i,int j){//返回连通块大小
    light_num++;
    if(i>xmax)xmax = i;
    if(i<xmin)xmin = i;
    
    if(j>ymax)ymax = j;
    if(j<ymin)ymin = j;
    
    tempimage[i][j]=0;
    if(i+1<ROW && tempimage[i+1][j]==1)//注意有特殊情况不能统计到
        find_size(i+1,j);
    if(i-1>=0 && tempimage[i-1][j]==1)
        find_size(i-1,j);
    if(j+1<COL && tempimage[i][j+1]==1)
        find_size(i,j+1);
    if(j-1>=0 && tempimage[i][j-1]==1)
        find_size(i,j-1);
    if(i-1>0&&j-1>=0 && tempimage[i-1][j-1]==1)
        find_size(i,j-1);
    if(i+1<ROW&&j-1>=0 && tempimage[i+1][j-1]==1)
        find_size(i,j-1);
    if(i-1>0 && j+1<COL && tempimage[i-1][j+1]==1)
        find_size(i,j-1);
    if(i+1<ROW&&j+1<COL && tempimage[i+1][j+1]==1)
        find_size(i,j-1);
    
}

/*
*函数名：find_position
*功能：遍历二值化图像，找到连通块位置并且将第一个点的位置及大小加入链表
*最后修改时间：2017.5.6
*/
uint8 finded_time = 0;
void find_position(){
   // head=malloc(sizeof(Node));
  //head.next = NULL;
    uint16 i=0,j=0;
    
    finded_time = 0;
    memcpy((uint8*)tempimage,(uint8*)binary_image,ROW*COL);
    
    for(i=0;i<ROW;i++)
    {
        for(j=0;j<COL;j++)
        {
            if(tempimage[i][j]==1)
            {
                light_num=0;
                
                xmax = i;
                ymax = j;
                xmin = i;
                ymin = j;
                
                find_size(i,j);
                if(light_num > 3)
                {
                  head[finded_time].x=(xmax + xmin)/2;
                  head[finded_time].y=(ymax + ymin)/2;
                  head[finded_time].size = light_num;                
                  finded_time++;
                }
                /*
                newpos.x=i,newpos.y=j;
                newpos.size=light_num;
                Node* temp=&head;
                while(temp->next!=NULL) //找到链表尾，然后把新节点插入进去
                    temp=temp->next;
                temp->next=&newpos;
                */
            }
        }
    }
    head[finded_time].size = 0;
}
/*
*函数名：fine_yes_no
*功能：确认是否找到亮点
*返回值：返回1表示找到亮点，返回0表示没有找到亮点
*最后修改时间：2017.5.6
*/
uint8 fine_yes_no()
{
  if((head[0].size ==0) || (finded_time != 2))
  {
    return 0;
  }
  else
  {
    return 1;
  }

}
/*
*函数名：find_fetch
*功能：提取数据
*/
void find_fetch()
{
   // Node* temp=&head;
   // while(temp->next!=NULL){
   //     temp=temp->next;
     //   printf("x %d  y %d   size %d\n",temp->x,temp->y,temp->size);
   // }
  uint8 i = 0;
  while(i<finded_time)
  {
    
    printf("i  %d x %d  y %d   size %d\n",i,head[i].x,head[i].y,head[i].size);
    i++;
  }
}
/*
void nrf_send_data(double dat)
{
  uint8 send_buff[32]={0};
  uint8 i =0;
  dat = dat/100;
  send_buff[0] = 0x00;
  for(i = 1;i<10;i++)
  {
    send_buff[i] = (int)dat%10;
    dat = dat * 10;
  }
  NRF_Send_Packet(send_buff);
  
}
*/
void nrf_send_data(double* dat)
{
  uint8 *p;
  uint8 i;
  uint8 send_buff[32]={0};
  
  p = (uint8 *)dat;
  
  send_buff[0] = 0x09;
  
  for(i = 1;i<9;i++)
  {
    send_buff[i] = *p;
    p++;
  }
  
  NRF_Send_Packet(send_buff);
}

/*
*处理采集的图像，找到亮点块，并且找到它的大小
*用到的全局变量：image:采集到的灰度图像，binimage:二值化后的图像，tempimage:用于处理数据的临时数组;
*/

void get_position_size()
{
  double image_angle;
  //二值化
  gray_binary((uint8*)image,(uint8*)binary_image);
  //找到亮点和位置
  find_position();
  if(fine_yes_no())
  {
   // find_fetch();
   // if(finded_time == 2)
    //{
      image_angle = get_image_angel(head[0],head[1]);
    //}
    //printf("%f\n",image_angle);
      
     nrf_send_data(&image_angle);//通过nrf发送数据
  }
}

/*
*函数名：void get_image_angel(Node pointa,Node pointb)
*参数：pointa,图像中的a亮点，pointb,图像中的b亮点,angle 计算出的角度
*/
double get_image_angel(Node pointa,Node pointb)
{
  //向量始终由车指向灯，也就是:小->大。向量（x,y）
  double angle=0;
  int x,y;

    if(pointa.size>pointb.size)
    {
      x = (int)(pointa.x) - (int)(pointb.x);
      y = (int)(pointa.y) - (int)(pointb.y);
    }
    else
    {
      x = (int)(pointb.x) - (int)(pointa.x);
      y = (int)(pointb.y) - (int)(pointa.y);
    }
    
    angle = atan2((double)x,(double)y) * (180 / PI)+180;  
    if(angle > 360)
    {
      x = 0;
    }
    if(angle>100)
    {
      x = 1;
    }
    return angle;
 
}

/*
*函数名：find_light_car
*返回值：0错误，1，成功
*参数:image 图像数组，width 图像宽度，longth 图像长度  
*/
uint8 find_light_car(uint8 *image,uint8 width,uint8 longth)
{
   uint8 i,j;
   
   for(i=0;i<width;i++)
   {
     for(j=0;j<longth;j++)
     {
      
     
     }
   }
   return 0;
    
}
