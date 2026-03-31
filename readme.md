## 20260330 | 星期一 | markdown | 陈小白

## 今天学了什么
这次注意到了之前没有注意到的细节，就是E-2（TC7S08F）还有一个CLK引脚，也就是说08F本质上是一个与门电路，输出1给到7w74的一号引脚一个上升沿信号，因为7w74也是一个D触发器，就是把688 19号引脚的低电平信号锁存住。

## 心得体会
还有就是这次重新搞明白了 E2 和 E3 之前连他们两个都搞反了


## 简单写写代码基于STM32F103的，还得是用寄存器控制好点，不然用位操作太烦了

#include "stm32f10x.h"

#define ADDR_PORT GPIOA
#define DATA_PORT GPIOB

#define CLK_PORT GPIOC
#define CLK_PIN GPIO_Pin_10

void Init_GPIO()
{
    GPIO_InitTypeDef gpio;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

    //地址
    gpio.GPIO_Pin = 0xFF;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ADDR_PORT, &gpio);

    //数据
    GPIO_Init(DATA_PORT, &gpio);


    //时钟
    gpio.GPIO_Pin = CLK_PIN;
    GPIO_Init(CLK_PORT, &gpio);

    GPIO_ResetBits(CLK_PORT, CLK_PIN);
}

void Tester_Send(uint8_t addr, uint8_t data)
{
    GPIOA->ODR = addr;
    Delay_ms(1);

    GPIOB->ODR = data;
    Delay_ms(1);

    GPIO_SetBits(CLK_PORT, CLK_PIN);
    Delay_ms(1);
    GPIO_ResetBits(CLK_PORT, CLK_PIN);
    Delay_ms(1);

    ADDR_PORT->ODR = 0xFF;
    DATA_PORT->ODR = 0x00;
}


//1-144路选针器依次打上
int main()
{
    Init_GPIO();

    while (1)
    {
        int i;
        for (i = 0; i < 144; i++)
        {
            Tester_Send(i, 0xFF); //地址和数据相同
            Delay_ms(1000);
        }
    }

}


## 基于STC89C52的代码 ps:很久没写过51的了

#include <reg52.h>

sbit CLK = P3 ^ 0;

void main()
{
    unsigned char i;
    CLK = 0;
    while(1)
    {
        for(i = 1; i <= 144; i++)
        {
            P1 = i;
            Delay_ms(1);

            P1 = 0xFF;
            Delay_ms(1);

            CLK = 1;
            Delay_ms(1);
            CLK = 0;

            P1 = 0;

            Delay_ms(1000);
        }
    }
}


## 指定一路选针器跳动

#define Channel 1
sbit CLK = P3 ^ 0;
while(1)
{
    P1 = Channel;
    Delay_ms(1);
    P1 = 0xFF;
    Delay_ms(1);
    CLK = 1;
    Delay_ms(1);
    CLK = 0;
    Delay_ms(500);

    P1 = Channel;
    Delay_ms(1);
    P1 = 0x00;
    Delay_ms(1);
    CLK = 1;
    Delay_ms(1);
    CLK = 0;
    P1 = 0;
    Delay_ms(500);
}

## 8个刀头依次打上 打下

位操作?

void soloAction(unsigned char bit, unsigned char data)
{
    P1 = (1 << bit);
    Delay_ms(1);

    P1 = data;
    Delay_ms(1);

    CLK = 1;
    Delay_ms(1);
    CLK = 0;
    
    P1 = 0;
}

void main()
{
    unsigned char i;
    CLK = 0;
    while(1)
    {
        for(i = 0; i < 8; i++)
        {
            soloAction(i, 0xFF);
            Delay_ms(300);
        }
        for(i = 7; i >= 1; i--)
        {
            soloAction(i, 0x00);
            Delay_ms(300);
        }
        Delay_ms(1000);
    }
}