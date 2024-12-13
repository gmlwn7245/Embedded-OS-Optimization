#include "device_driver.h"
#define	printf	Uart1_Printf

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();
}

/***********************************************************/
// [EX-1-1] printf 함수 동작 분석 1
/***********************************************************/

#if 0

int add(int a, int b)
{
	return a+b;
}

void Main(void)
{
	Sys_Init();
	Uart_Printf("Argument 전달\n");

	printf("%d\n", add(3));
	printf("%d\n", add(3,4,5));
}

#endif

/***********************************************************/
// [EX-1-2] printf 함수 동작 분석 2
/***********************************************************/

#if 0

void Main(void)
{
	int a = 1, b = 2, c = 3;

	Sys_Init();
	Uart_Printf("printf 함수의 이해\n");

	printf("남는 Argument : %d %d \n", a, b, c);
	printf("적은 Argument : %d %d %d\n", a, b);
}

#endif

/***********************************************************/
// [EX-2] UART Device Driver 설계
/***********************************************************/

#if 01

void Main(void)
{
	volatile int i;

	Sys_Init();
	Uart_Printf("UART Echo-Back Test\n");

	for(;;)
	{
		Uart1_Printf("\n키보드로 받는 글자 10개를 echo-back\n");
		Uart1_Printf("\n키보드를 누르면 다시 PC로 글자를 전송한다 (10글자)\n");

		for(i=0; i<10; i++)
		{
			Uart1_Printf("\n>");
			Uart1_Printf("%c", Uart1_Get_Char());
		}

		Uart1_Printf("\n계속 LED Toggling하고 있으며 키보드의 x를 누르면 종료 함");

		do
		{
			LED_Display(0x1);
			for(i=0; i<0x100000; i++);
			LED_Display(0x2);
			for(i=0; i<0x100000; i++);
		}while(Uart1_Get_Pressed() != 'x');
	}
}

#endif
