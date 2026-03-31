#include "stm32f10x.h"                  
#include "Delay.h"
#include "74HC273.h"

int main(void)
{
	HC273_Init();
	Delay_ms(10);
	//uint8_t state = 1; 
	
	while (1)
	{
		//state = !state;   
		
		//HC273_Test_V1(state);

		HC273_Test_V2();
		GPIOA->ODR = 0x00;//high level

//		GPIOA->ODR = 0xFF;
//		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
//		
//		GPIO_SetBits(GPIOB,GPIO_Pin_0);
//		
//		Delay_ms(1);
//		
//		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
//			
//		Delay_ms(100);
//		
//		GPIOA->ODR = 0x00;//high level
//		
//		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
//		
//		GPIO_SetBits(GPIOB,GPIO_Pin_0);
//		
//		Delay_ms(1);
//		
//		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
//			
//		Delay_ms(100); 
		
	}
}
