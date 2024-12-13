#include "device_driver.h"

void LED_Init(void)
{
	/* ���� �ڵ�� �������� ���ÿ� */
	Macro_Set_Bit(RCC->APB2ENR, 3);
	Macro_Write_Block(GPIOB->CRH,0xFF,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x3,8);


}

void LED_Display(unsigned int num)
{
	Macro_Write_Block(GPIOB->ODR,0x3,(~num&0x3),8);

}

void LED_All_On(void)
{
	Macro_Write_Block(GPIOB->ODR,0x3,0x0,8);


}

void LED_All_Off(void)
{
	Macro_Write_Block(GPIOB->ODR,0x3,0x3,8);

}
