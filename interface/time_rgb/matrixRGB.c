/**
 * 
 * copyright
 * author: chenweipeng
 * time:20210511
 * 
 * 
 * 
 * ***/


#include "matrixRGB.h"
#include "rgbConverter.h"
#include "ws281x.h"

#define RGB_NUM  256
#define RGB_LINE_MAX 8
#define RGB_ROW_MAX 32


//rgb颜色值
static uint32_t rgbvalue[RGB_LINE_MAX*RGB_ROW_MAX] = {0};
//具体行点


/**
 * 
 * line ： 具体行
 * row  ： 具体列
 * colorVal: 颜色代码   brg—— bit24 ：bit 0
 * iLight ： 亮度值     50 -- 1000
 * **/
int setRGB(uint32_t line, uint32_t row, uint32_t colorVal, uint16_t iLight)
{
    if(line > RGB_LINE_MAX-1 || row > RGB_ROW_MAX-1)
        return -1;


    uint32_t index = 0;
    uint32_t val = rgbLedLight(colorVal, iLight);
    
    Led_rgb_byte_swap(&val);//颜色编码转码

    //计算具体在哪个像素点
    //0 15-16 31-32 47-48 63-64 79-80 95-96 111-112 127-128 133-134 149-150 165-166 181-196 211-212 227-228 243-244 
    //1 14-17 30-33
    // if(line == 0)
    {
        if(row%2)
        {
            index = (row/2)*16 + 15-line;
        }
        else
        {
            index = (row/2)*16 + line;
        }
    }
    if(colorVal == 0)
        val = 0;
    rgbvalue[index] = val;
}


int flushRGB(void)
{
    //reset
    int i;

    for(i = 0; i < RGB_NUM; i++)
    {
        Led4Send_24bits(rgbvalue[i]);
    }
    Led4Send_reset();
}
