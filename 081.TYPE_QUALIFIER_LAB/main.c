#include "device_driver.h"

/***********************************************************/
// [EX-1] LED Toggling
/***********************************************************/

#if 0

#define RCC_APB2ENR   (*(unsigned long*)0x40021018)

#define GPIOB_CRH      (*(unsigned long*)0x40010C04)
#define GPIOB_ODR      (*(unsigned long*)0x40010C0C)

void Main(void)
{
	int i;

	Uart_Init(115200);
	Uart_Printf("LED Toggling Test #1\n");
	RCC_APB2ENR |= (1<<3);

	GPIOB_CRH = 0x66 << 0;

	for(;;)
	{
		GPIOB_ODR = 0x0 << 8;
		for(i=0; i<0x40000; i++);
		GPIOB_ODR = 0x3 << 8;
		for(i=0; i<0x40000; i++);
	}
}

#endif

/***********************************************************/
// [EX-2-1] System Timer의 액세스  1
/***********************************************************/

#if 0

#define TIMER   (*(unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Uart_Init(115200);
	Uart_Printf("Timer Access #1\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
		Uart_Printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

/***********************************************************/
// [EX-2-2] System Timer의 액세스 2
/***********************************************************/

#if 0

#define TIMER   (*(unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Uart_Init(115200);
	Uart_Printf("Timer Access #2\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
	}

	for(i=0; i<10; i++)
	{
		Uart_Printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

/***********************************************************/
// [EX-3] 최적화와 volatile의 사용
/***********************************************************/

#if 0

#define TIMER   (*(volatile unsigned long *)0xE000E018)

void Main(void)
{
	int i;
	unsigned long a[10];

	Uart_Init(115200);
	Uart_Printf("Timer Access #3\n");

	SysTick_Run();

	for(i=0; i<10; i++)
	{
		a[i] = TIMER;
	}

	for(i=0; i<10; i++)
	{
		Uart_Printf("%d => %#.8X\n", i, a[i]);
	}
}

#endif

/***********************************************************/
// [EX-4] LED Toggling 코드의 개선
/***********************************************************/

#if 01

#define RCC_APB2ENR    (*(volatile unsigned long*)0x40021018)

#define GPIOB_CRH      (*(volatile unsigned long*)0x40010C04)
#define GPIOB_ODR      (*(volatile unsigned long*)0x40010C0C)

void Main(void)
{
	volatile int i;

	Uart_Init(115200);
	Uart_Printf("LED Toggling Test #2\n");
//	RCC_APB2ENR |= (1<<3);
	RCC->APB2ENR |=1<<3;
//	GPIOB_CRH = 0x66 << 0;
	GPIOB->CRH= 0x66 << 0;
	for(;;)
	{
//		GPIOB_ODR = 0x0 << 8;
		GPIOB->ODR= 0x0 << 8;
		for(i=0; i<0x40000; i++);
//		GPIOB_ODR = 0x3 << 8;
		GPIOB->ODR= 0x3 << 8;
		for(i=0; i<0x40000; i++);

	}
}

#endif

/***********************************************************/
// [EX-5] 새로운 레지스터 정의의 활용
/***********************************************************/

#if 0

void Main(void)
{
	volatile int i;

	Uart_Init(115200);
	Uart_Printf("CMSIS Based Register Define\n");

	RCC_APB2ENR |= (1<<3);

	GPIOB_CRH = 0x66 << 0;

	for(;;)
	{
		GPIOB_ODR = 0x0 << 8;
		for(i=0; i<0x40000; i++);
		GPIOB_ODR = 0x3 << 8;
		for(i=0; i<0x40000; i++);
	}
}

#endif
