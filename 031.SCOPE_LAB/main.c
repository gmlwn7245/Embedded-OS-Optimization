#include "device_driver.h"
#define printf	Uart1_Printf

extern void User_Main(void);

void Main(void)
{
	Uart_Init(115200);
	User_Main();
}

/***********************************************************/
// [EX-1] 蹂�닔���좏슚踰붿쐞
/***********************************************************/

#if 0

int a = 1, b = 2, c = 3;

void func(void)
{
	int c = 3000;
	printf("%d %d %d\n", a, b, c);
}

void User_Main(void)
{
	int b = 20, c = 30, d = 40;
	printf("%d %d %d %d\n", a, b, c, d);

	func();

	{
		int c = 300, d = 400;
		printf("%d %d %d %d\n", a, b, c, d);
	}

	{
		int d = -400;
		printf("%d %d %d %d\n", a, b, c, d);
	}
}

#endif

/***********************************************************/
// [EX-2] �ㅽ깮 遺꾩꽍���듯븳 �좏슚踰붿쐞���댄빐
/***********************************************************/

#if 0

int r;

int add(int a, int b)
{
	int r;

	r = a + b;
	return r;
}

void User_Main(void)
{
	int a = 3, b = 4;

	r = add(a, b);
	printf("%d\n", r);
}

#endif

/***********************************************************/
// [EX-3] �먰뙆�쇰쭅 �곗뒿 ���꾩뿭蹂�닔 ��땳
/***********************************************************/

#if 0

int a = 10;
int b;
int c = 20;

void f2(void)
{
	int a = 100;

	printf("%d %d %d\n", a, b, c);
}

void f1(void)
{
	int a = 50;
	int b = 500;

	f2();
	printf("%d %d %d\n", a, b, c);
}

void User_Main(void)
{
	int c = 1000;

	f1();
	printf("%d %d %d\n", a, b, c);
}

#endif

/***********************************************************/
// [EX-4] �먰뙆�쇰쭅 �곗뒿 ��吏�뿭蹂�닔\ �좏슚 踰붿쐞
/***********************************************************/

#if 0

int a = 1;
int b;
int c = 2;

void User_Main(void)
{
	int a = 100;

	{
		int a = 20;
		int b = 10;

		{
			int c = 5;

			printf("%d %d %d\n", a, b, c);
		}

		printf("%d %d %d\n", a, b, c);
	}

	printf("%d %d %d\n", a, b, c);
}

#endif

/***********************************************************/
// [EX-5] �먰뙆�쇰쭅 �곗뒿 ���⑥닔���곗냽 �몄텧
/***********************************************************/

#if 0

int add(int a, int b)
{
	int c = a + b;

	return c;
}

void User_Main(void)
{
	int a = 10;
	int b = 3;
	int c;

	c = add(add(a, b), add(a + 1, b + 1));

	printf("%d\n", c);
}

#endif

/***********************************************************/
// [EX-6] �먰뙆�쇰쭅 �곗뒿 ���몄닔 �꾨떖怨�由ы꽩
/***********************************************************/

#if 0

int a = 1;
int b;
int c = 2;

int f2(int a, int b)
{
	int c = a + b % 2;

	return c * 3;
}

int f1(int a, int x)
{
	int d = 13;

	c = d + a - x;

	return b = f2(b = c + d, a) + 1;
}

void User_Main(void)
{
	int b = 10;
	int x = 3;
	int d = f1(x, a);

	printf("%d %d %d %d\n", a, b, c, d);

	f2(b, a = x + 1);

	printf("%d %d %d %d\n", a, b, c, d);
}

#endif

/***********************************************************/
// [EX-7] Recursive Call
/***********************************************************/

#if 0

int func(int x)
{
	if (x > 0)
	{
		return x + func(x - 2);
	}
	else
	{
		return 0;
	}
}

void User_Main(void)
{
	printf("%d\n", func(10));
}

#endif

/***********************************************************/
// [EX-8] 蹂듭옟���ш��몄텧
/***********************************************************/

#if 0

int prt(int x)
{
	if (x == 0) return x;

	else if (x % 2)
	{
		printf("%d\n", x + prt(x - 1)); //1:
		return x;
	}
	else
	{
		printf("%d\n", x + prt(x - 1)); //2:
		return x;
	}
}

void User_Main(void)
{
	int i;
	i = prt(5); //3:
}

#endif

/***********************************************************/
// [EX-9] �ш��몄텧濡�留뚮뱶���⑺넗由ъ뼹 �⑥닔
/***********************************************************/

#if 0

int fact(int n)
{
	if(n>0)
	return n * fact(n-1);
	else {
	return 1;
	}
}

void User_Main(void)
{
	printf("%d\n", fact(3));
	printf("%d\n", fact(4));
}

#endif

/***********************************************************/
// [EX-10] �ш��몄텧濡�留뚮뱶����닔 ���⑥닔
/***********************************************************/

#if 0

int odd_sum(int n)
{
	if (n<=0) return 0;

	else if (n%2==1){
		return n+odd_sum(n-1);
	}
	else if(n%2==0){
		return odd_sum(n-1);
	}

}

void User_Main(void)
{
	printf("%d\n", odd_sum(3));
	printf("%d\n", odd_sum(100));	
}

#endif
