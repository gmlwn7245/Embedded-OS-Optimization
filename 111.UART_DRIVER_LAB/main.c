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
// [EX-1-1] printf �Լ� ���� �м� 1
/***********************************************************/

#if 0

int add(int a, int b)
{
	return a+b;
}

void Main(void)
{
	Sys_Init();
	Uart_Printf("Argument ����\n");

	printf("%d\n", add(3));
	printf("%d\n", add(3,4,5));
}

#endif

/***********************************************************/
// [EX-1-2] printf �Լ� ���� �м� 2
/***********************************************************/

#if 0

void Main(void)
{
	int a = 1, b = 2, c = 3;

	Sys_Init();
	Uart_Printf("printf �Լ��� ����\n");

	printf("���� Argument : %d %d \n", a, b, c);
	printf("���� Argument : %d %d %d\n", a, b);
}

#endif

/***********************************************************/
// [EX-2] UART Device Driver ����
/***********************************************************/

#if 01

void Main(void)
{
	volatile int i;

	Sys_Init();
	Uart_Printf("UART Echo-Back Test\n");

	for(;;)
	{
		Uart1_Printf("\nŰ����� �޴� ���� 10���� echo-back\n");
		Uart1_Printf("\nŰ���带 ������ �ٽ� PC�� ���ڸ� �����Ѵ� (10����)\n");

		for(i=0; i<10; i++)
		{
			Uart1_Printf("\n>");
			Uart1_Printf("%c", Uart1_Get_Char());
		}

		Uart1_Printf("\n��� LED Toggling�ϰ� ������ Ű������ x�� ������ ���� ��");

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
