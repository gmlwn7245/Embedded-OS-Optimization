#include "device_driver.h"
#define printf	Uart1_Printf

extern void User_Main(void);

void Main(void)
{
	Uart_Init(115200);
	User_Main();
}

/***********************************************************/
// [EX-1] 변수 생성 시기와 가시성(Visibility)
/***********************************************************/

#if 0

int a = 100;
int b = 10 * 2;
int c = a + 1;
int d = sizeof(int);

int add(int a, int b)
{
	return a + b;
}

void User_Main(void)
{
	int a = b;
	int b = c;
	int c = d * 2;
	int d = add(a, b);
	static int s = d;

	printf("a=%d\n", a);
	printf("b=%d\n", b);
	printf("c=%d\n", c);
	printf("d=%d\n", d);
}

#endif

/***********************************************************/
// [EX-2] Global extern => runtime.c와 함께 사용
/***********************************************************/

#if 0

extern void func(void);

int a;
extern int b;

void User_Main(void)
{
	func();

	a++;
	b++;

	printf("a=%d\n", a);
	printf("b=%d\n", b);
}

#endif

/***********************************************************/
// [EX-3] Global static => runtime.c와 함께 사용
/***********************************************************/

#if 0

extern void func(void);

int a;
static int b = 10;
extern int c;

void User_Main(void)
{
	func();

	c++;
	a++;
	b++;

	printf("a=%d\n", a);
	printf("b=%d\n", b);
}

#endif

/***********************************************************/
// [EX-4] Local static
/***********************************************************/

#if 0

int a;
static int b = 10;

void func(void)
{
	static int b = 20;

	a++; b++;
	printf("a=%d, b=%d\n", a, b);
}

void User_Main(void)
{
	a++; b++;
	func();
	func();
	printf("a=%d, b=%d\n", a, b);
}

#endif

/***********************************************************/
// [EX-5-1] 함수의 extern 선언 - 1
/***********************************************************/

#if 0

int add(int a, int b);

void User_Main(void)
{
	printf("%d\n", add(3, 4));
}

int add(int a, int b)
{
	return a + b;
}

#endif

/***********************************************************/
// [EX-5-2] 함수의 extern 선언 - 2
/***********************************************************/

#if 0

extern int add(int a, int b);

void User_Main(void)
{
	printf("%d\n", add(3, 4));
}

int add(int a, int b)
{
	return a + b;
}

#endif

/***********************************************************/
// [EX-6] 함수의 static 선언 => runtime.c와 함께 사용
/***********************************************************/

#if 0

extern void func(void);

static int sqr(int a)
{
	return a * a;
}

void User_Main(void)
{
	func();
	printf("%d\n", sqr(3));
}

#endif

/***********************************************************/
// [EX-7] 재귀호출 함수의 지역 변수
/***********************************************************/

#if 0

void func(int x)
{
	int a = 10;
	static int b = 20;

	if (x == 0) return;
	else func(x - 1);

	a++;
	b++;

	printf("a=%d b=%d x=%d\n", a, b, x);
}

void User_Main(void)
{
	func(6);
}

#endif

/***********************************************************/
// [EX-8] typedef은 무엇인가?
/***********************************************************/

#if 0

typedef unsigned int UI;
typedef UI * UIP;

UI a[4] = {1,2,3,4};

void User_Main(void)
{
	int i ;

	UIP b[4] = {a, a+1, a+2, a+3};

	for(i=0; i<3; i++)
	{
		printf("%d\n", b[i]);
	}
}

#endif
