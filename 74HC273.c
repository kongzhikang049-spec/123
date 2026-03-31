#include "stm32f10x.h"                  
#include "74HC273.h"
#include "Delay.h"

void HC273_Init(void)
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStructure;//????GPIO_InitStructure
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);			
	
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		GPIOA->ODR = 0x00;
		
}

void HC273_Test_V1(uint8_t state){
	
		if(state){
			GPIO_SetBits(GPIOA,GPIO_Pin_0);// 1 = ??
		}
		else{
			GPIO_ResetBits(GPIOA,GPIO_Pin_0);// !1 = ??
		}
		 
		
		//clock????
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		
		Delay_ms(1);
		
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		
		
}

void HC273_Test_V2(){
		uint8_t num = 0;
		int i;
		for(i=7;i>=0;i--){
			
			num |= (1 << i);
			HC273_Send(num);
			Delay_ms(3);//??????
			//?????? clock    
			// 0000 0001
			// 0000 0011
			// 0000 0111
			// .........
			// 1111 1111
			//??????????
		 
			
		}
	
		Delay_ms(3);
		
		for(i=7;i>=0;i--){
			num &=~(1 << i);
			HC273_Send(num);
			Delay_ms(3);
			
		}

}

void HC273_Send(uint8_t data){
			GPIOA->ODR = data;
			Delay_us(10);
			
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		
			GPIO_SetBits(GPIOB,GPIO_Pin_0);
		
			Delay_us(10);   //
		
			GPIO_ResetBits(GPIOB,GPIO_Pin_0);

}
  