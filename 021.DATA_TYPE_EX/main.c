#include "device_driver.h"
#define printf	Uart1_Printf

extern void User_Main(void);

void Main(void)
{
	Uart_Init(115200);
	User_Main();
}

/***********************************************************/
// [EX-1] 음수의 표현
/***********************************************************/

#if 0

void User_Main(void)
{
	int si = -1;
	unsigned int ui = 0xffffffff;

	printf("%d\n", si);
	printf("%u\n", si);
	printf("%#x\n", si);

	printf("%d\n", ui);
	printf("%u\n", ui);
	printf("%#x\n", ui);
}

#endif

/***********************************************************/
// [EX-2] char 비교
/***********************************************************/

#if 0

void User_Main(void)
{
	unsigned char c = 0xff;

	if(c == 0xff)
		printf("%x\n",c+1);
	else
		printf("%x\n",c-1);
}

#endif

#if 0

void User_Main(void)
{
	signed char c = 0xff;

	if(c == 0xff)
		printf("%x\n",c+1);
	else
		printf("%x\n",c-1);
}

#endif

#if 0

void User_Main(void)
{
	char c = 0xff;

	if(c == 0xff)
		printf("%x\n",c+1);
	else
		printf("%x\n",c-1);
}

#endif

/***********************************************************/
// [EX-3-1] sizeof 1
/***********************************************************/

#if 0

void User_Main(void)
{
	int a[4] = {1,2,3,4};

	if(a[0]-a[1] < sizeof(a))
		printf("%d\n", a[sizeof(char)]);
	else
		printf("%d\n", a[sizeof(short)]);
}

#endif

/***********************************************************/
// [EX-3-2] sizeof 2
/***********************************************************/

#if 0

void User_Main(void)
{
	int a = -1;

	printf("%d\n", sizeof(a));
	printf("%d\n", sizeof(int));
	printf("%d\n", sizeof(-1));
	printf("%d\n", sizeof a);
	printf("%d\n", sizeof - 1);
	printf("%d\n", sizeof int);
}

#endif

/***********************************************************/
// [EX-4] 16bit Timer Access
/***********************************************************/

#if 0

void User_Main(void)
{
	volatile int i;

	Uart1_Printf("16bit Timer Access Test #1\n");

	TIM2_Start(0xffff);
	for(i=0; i<0x100; i++);

	for(;;)
	{
		unsigned short cnt = TIM2->CNT;

		Uart1_Printf("cnt = %#.4X\n", cnt);

		if(cnt > 0x7FFF)
		{
			Uart1_Printf("HIGH\n", cnt);
			for(i=0; i<0x10000; i++);
		}

		else break;
	}

	Uart1_Printf("LOW\n");
	TIM2_Stop();
}

#endif

/***********************************************************/
// [EX-5] short type의 비교
/***********************************************************/

#if 01

void User_Main(void)
{
	signed short ss = -1;
	unsigned short us = -1;
	printf("%x \n %x",ss,us);
	if(ss < us) printf("UNSIGNED SHORT\n");
	else if(ss > us) printf("SIGNED SHORT\n");
	else printf("SAME\n");
}

#endif

/***********************************************************/
// [EX-6] Shift 연산자의 동작
/***********************************************************/

#if 0

void User_Main(void)
{
	unsigned int ux = 0x80000001;
	signed int sx = 0x80000001;

	printf("%#.8x, %#.8x\n\n", ux>>2, ux<<2);
	printf("%#.8x, %#.8x\n\n", sx>>2, sx<<2);
}

#endif

/***********************************************************/
// [EX-7] 실수의 유효범위
/***********************************************************/

#if 0

void User_Main(void)
{
	printf("a=%.20f\n", 100.f/3.f);
	printf("b=%.20f\n", 100./3.);
}

#endif

