#include "device_driver.h"

void Key_Poll_Init(void)
{
	Macro_Set_Bit(RCC->APB2ENR, 3);
	Macro_Write_Block(GPIOB->CRL, 0xff, 0x44, 24);
}

/* 0: 디버깅용 설정 */
/* 1: 정상 동작용 설정 */

#if 01
	#define N	20000
#else
	#define N	3000000
#endif

int Key_Get_Pressed(void)
{
	/* N 만큼 같은 값이 읽혀야 Key 값으로 판정 */
	int i,k;
	for(;;){
		k=Macro_Extract_Area(~GPIOB->IDR,0x3,6);
		for (i=0;i<N;i++){
			if(k != Macro_Extract_Area(~GPIOB->IDR,0x3,6))break;
		}
		if(i==N)break;
	}
	return k;
}

void Key_Wait_Key_Released(void)
{
	while(Key_Get_Pressed());
}

int Key_Wait_Key_Pressed(void)
{
	int k;

	while((k = Key_Get_Pressed()) == 0);
	return k;
}
