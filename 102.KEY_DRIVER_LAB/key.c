#include "device_driver.h"

void Key_Poll_Init(void)
{
	Macro_Set_Bit(RCC->APB2ENR, 3);
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 24);
}

int Key_Get_Pressed(void)
{
	return 3-Macro_Extract_Area(GPIOB->IDR, 0x3, 6);

}

void Key_Wait_Key_Released(void)
{
	while(Key_Get_Pressed());

}

int Key_Wait_Key_Pressed(void)
{
	int Key;

	do {
		Key=Key_Get_Pressed();
	}while (Key==0);
	return Key;
}
