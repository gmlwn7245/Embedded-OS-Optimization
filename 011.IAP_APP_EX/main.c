#include "device_driver.h"

#if 0

void Main(void)
{
	int value;

	Uart_Init(115200);

	for(value = 0; value <= 15; value++)
	{
		Uart_Printf("%d\n", value);
	}

	Uart_Printf("END\n");
}

#endif

#if 01

void Main(void)
{
	int value = 10;

	Uart_Init(115200);

	Uart_Printf("WILLTEK\n");
	Uart_Printf("VALUE=%d\n", value = 10);
	Uart_Printf("%d, %c \n", 100, 'A');
	Uart_Printf("Bye~\n");
}

#endif
