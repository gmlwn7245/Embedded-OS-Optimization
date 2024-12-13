#include "device_driver.h"

void Main(void)
{
	int *p, *q;

	Uart_Init(115200);
	Uart_Printf("RUNTIME ENVIRONMENT TEST\n");

	extern 	char __RO_BASE__;
	extern 	char __RO_LIMIT__;
	extern 	char __RW_BASE__;
	extern 	char __RW_LIMIT__;
	extern 	char __ZI_BASE__;
	extern 	char __ZI_LIMIT__;

	Uart_Printf("RO_BASE => %#.8X\n", &__RO_BASE__);
	Uart_Printf("RO_LIMIT => %#.8X\n", &__RO_LIMIT__);
	Uart_Printf("RW_BASE => %#.8X\n", &__RW_BASE__);
	Uart_Printf("RW_LIMIT => %#.8X\n", &__RW_LIMIT__);
	Uart_Printf("ZI_BASE => %#.8X\n", &__ZI_BASE__);
	Uart_Printf("ZI_LIMIT => %#.8X\n", &__ZI_LIMIT__);
	Uart_Printf("HEAP_BASE => %#.8X\n", HEAP_BASE);
	Uart_Printf("HEAP_LIMIT => %#.8X\n", HEAP_LIMIT);
	Uart_Printf("HEAP_SIZE => %#.8X\n", HEAP_LIMIT - HEAP_BASE);
	Uart_Printf("STACK_LIMIT => %#.8X\n", STACK_LIMIT);
	Uart_Printf("STACK_BASE => %#.8X\n", STACK_BASE);
	Uart_Printf("STACK_SIZE => %#.8X\n", STACK_BASE - STACK_LIMIT);

	p = malloc(4);
	q = malloc(4);

	Uart_Printf("p=%#.8X\n", p);
	Uart_Printf("q=%#.8X\n", q);

	free(p);
	free(q);

	for(;;)
	{
		static int i = 0;

		q = malloc(128);
		Uart_Printf("[%.3d]q=%#.8X\n", ++i, q);

		if(q==(void *)0x0)
		{
			Uart_Printf("Heap Over");
			for(;;);
		}
	}
}
