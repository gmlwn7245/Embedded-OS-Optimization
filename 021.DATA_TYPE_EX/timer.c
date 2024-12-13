#include "device_driver.h"

void TIM2_Start(unsigned short t)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);
  
	TIM2->CR1 = (1<<4)|(1<<3);
	TIM2->PSC = 1000-1;
	TIM2->ARR = t;

	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Set_Bit(TIM2->CR1, 0);
}

void TIM2_Stop(void)
{
	Macro_Clear_Bit(TIM2->CR1, 0);
}
