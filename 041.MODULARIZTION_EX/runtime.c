#include "device_driver.h"

char * _sbrk(int inc)
{
	extern unsigned char __ZI_LIMIT__;
	static char * heap = (char *)0;

	char * prevHeap;
	char * nextHeap;

	if(heap == (char *)0) heap = (char *)HEAP_BASE;

	prevHeap = heap;
	nextHeap = (char *)((((unsigned int)heap + inc) + 0x7) & ~0x7);

	if((unsigned int)nextHeap >= HEAP_LIMIT) return (char *)0;

	heap = nextHeap;
	return prevHeap;
}

/***********************************************************/
// [EX-2] Global extern
/***********************************************************/

#if 0

extern int a;
int b = 20;


void func(void)
{
	a++;
	b++;

	Uart1_Printf("a=%d\n", a);
	Uart1_Printf("b=%d\n", b);
}

#endif

/***********************************************************/
// [EX-3] Global static
/***********************************************************/

#if 0

extern int a;
static int b = 20;
static int c = 30;
int c = 30;

void func(void)
{
	a++;
	b++;
	c++;

	Uart1_Printf("a=%d\n", a);
	Uart1_Printf("b=%d\n", b);
	Uart1_Printf("c=%d\n", c);
}

#endif

/***********************************************************/
// [EX-6] 함수의 static 선언
/***********************************************************/

#if 0

static int sqr(int a)
{
	return a * a * 2;
}

void func(void)
{
	Uart1_Printf("%d\n", sqr(3));
}

#endif
