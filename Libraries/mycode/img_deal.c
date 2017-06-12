#include "img_deal.h"
#include "headfile.h"

extern Node head[10];
extern uint8 finded_time;
Node head_pre;
uint8 get_img_car_err()
{
  //确定本次和上次的车的向量
  if(finded_time != 2)//找到的亮点数量不对，返回错误
  {
    return 0;
  }
    
  //计算向量角
  

}











