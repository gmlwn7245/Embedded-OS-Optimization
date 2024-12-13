#include "device_driver.h"

/***********************************************************/
// [EX-1] 비트연산에 의한 LED ON
/***********************************************************/

#if 0

void Main(void)
{
	Uart_Init(115200);
	
	/* 이 부분은 임의로 바꾸지 마시오 */
	RCC->APB2ENR |= (1<<3);

	/* 비트 연산을 이용하여 LED0을 ON, LED1을 OFF로 하는 코드를 설계하시오 */
	GPIOB->CRH &=0xffffff00;
	GPIOB->ODR &=0xfffffcff;

	GPIOB->ODR	|= 0x2 << 8;
	GPIOB->CRH	|= 0x66 << 0;

}

#endif

/**************************************a*********************/
// [EX-2] 비트 처리 Macro 분석
/***********************************************************/

#if 0

#include "macro.h"

void bdisp(int a)
{
	int i;

	for(i = 31; i >= 0; i--)
	{
		Uart_Printf("%d", a >> i & 1);
		if((i%4 == 0) && (i != 0))
		{
			Uart_Printf("-");
		}
	}
	Uart_Printf("\n");
}

void Main(void)
{
	Uart_Init(115200);
		
	int a = 0xcc3355aa;

	Macro_Set_Bit(a, 0);
	bdisp(a);
	Macro_Clear_Bit(a, 3);
	bdisp(a);
	Macro_Invert_Bit(a, 6);
	bdisp(a);
}

#endif

/**************************************a*********************/
// [EX-3] 멀티비트 처리 Macro 분석
/***********************************************************/

#if 0

#include "macro.h"

void bdisp(int a)
{
	int i;

	for(i = 31; i >= 0; i--)
	{
		Uart_Printf("%d", a >> i & 1);
		if((i%4 == 0) && (i != 0))
		{
			Uart_Printf("-");
		}
	}
	Uart_Printf("\n");
}

void Main(void)
{
	Uart_Init(115200);
	
	int a = 0xcc3355aa;

	Macro_Clear_Area(a, 0x3, 2);
	bdisp(a);
	Macro_Set_Area(a, 0x7, 8);
	bdisp(a);
	Macro_Invert_Area(a, 0x1F, 12);
	bdisp(a);
}

#endif

/**************************************a*********************/
// [EX-4] Block Write Macro 분석
/***********************************************************/

#if 0

#include "macro.h"

void bdisp(int a)
{
	int i;

	for(i = 31; i >= 0; i--)
	{
		Uart_Printf("%d", a >> i & 1);
		if((i%4 == 0) && (i != 0))
		{
			Uart_Printf("-");
		}
	}
	Uart_Printf("\n");
}

void Main(void)
{
	Uart_Init(115200);
	
	int a = 0xcc3355aa;

	Macro_Write_Block(a, 0x7, 0x5, 2);
	Macro_Write_Block(a, 0xFFFF, 0x1234, 8);

	bdisp(a);
}

#endif

/***********************************************************/
// [EX-5-1] Macro를 활용한 LED 제어
/***********************************************************/

#if 0

void Main(void)
{
	Uart_Init(115200);
		
	/* 이 부분은 수정하지 말 것 */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	/* Macro를 이용하여 LED0을 ON, LED1을 OFF로 하는 코드를 설계하시오 */
	Macro_Write_Block(GPIOB->CRH,0xFF,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x2,8);


}

#endif

/***********************************************************/
// [EX-5-2] Macro를 활용한 LED Toggling
/***********************************************************/

#if 0

void Main(void)
{
	volatile int i;
	Uart_Init(115200);	

	/* 이 부분은 수정하지 말 것 */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	/* 초기에 LED 모두 OFF => PB[9:8]을 OUTPUT으로 하고 1을 초기에 출력 */
	Macro_Write_Block(GPIOB->CRH,0xFF,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x3,8);


	for(;;)
	{
		/* LED 값(PB[9:8])을 비트 반전시킨다 */
	Macro_Invert_Area(GPIOB->ODR,0x3,8);


		for(i=0; i<0x80000; i++);


	}
}

#endif
