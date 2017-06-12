#ifndef _DATA_H
#define _DATA_H

typedef struct Node{
    uint16 x,y,size;
}Node;

uint8 find_light_car(uint8 *image,uint8 width,uint8 longth);
void get_position_size();
void find_fetch();
uint8 fine_yes_no();
void find_position();
void find_size(int i,int j);
uint8 gray_binary(uint8 *image,uint8 *binimage);
double get_image_angel(Node pointa,Node pointb);

#endif