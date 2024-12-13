#include "device_driver.h"
#define printf	Uart1_Printf

extern void User_Main(void);

void Main(void)
{
	Uart_Init(115200);
	User_Main();
}

/***********************************************************/
// [EX-1] 버퍼의 데이터 수량 계산
/***********************************************************/

#if 0

void User_Main(void)
{
	int a[10];
	int *start = &a[0];
	int *p = &a[3];

	printf("%d\n", sizeof(a)/sizeof(a[0]));
	printf("%d\n", (p-start)/sizeof(int));
}

#endif

/***********************************************************/
// [EX-2] 주소의 연산과 타입 승계
/***********************************************************/

#if 0

void User_Main(void)
{
	int *p, *q;

	p = (int *)0x1008;
	q = (int *)0x1000;

//	printf("%#x\n", p*q);
//	printf("%#x\n", p/q);
//	printf("%#x\n", p+q);
	printf("%#x\n", p-q);

//	printf("%#x\n", p*2);
//	printf("%#x\n", p/2);
	printf("%#x\n", p+2);
	printf("%#x\n", p-2);
}

#endif

/***********************************************************/
// [EX-3] 배열 등가포인터
/***********************************************************/

#if 0

void func(int *a)
{
	printf("a[3] = %d\n",a[3]);
}

void User_Main(void)
{
	int a[4] = {1,2,3,4};

	func(a);
}

#endif

/***********************************************************/
// [EX-4-1] 함수의 배열 리턴
/***********************************************************/

#if 0

int * func(void)
{
	static int a[4] = {1,2,3,4};//static안하면 func 터질때 사라짐.

	return a;
}

void User_Main(void)
{
	printf("a[3] = %d\n", *(func()+3));
	printf("a[3] = %d\n",   func()[3]);
}

#endif

/***********************************************************/
// [EX-4-2] 배열 Parameter
/***********************************************************/

#if 0

int sum(int b[4])
{
	int i, sum = 0;

	for(i=0; i<(sizeof(b)/sizeof(b[0])); i++)
	{
		sum += b[i];
	}

	return sum;
}

void User_Main(void)
{
	int a[4] = {1,2,3,4};

	printf("%d\n", sum(a));
}

#endif

/***********************************************************/
// [EX-5] 대치법의 이해
/***********************************************************/

#if 0

int x[4] = {1,2,3,4};

int *f1(void)
{
	return x;
}

void f2(int *p)
{
	printf("%d == %d == %d == %d\n", x[2], *(x+2), p[0], *p);
}

void User_Main(void)
{
	int *p;
	int *a[4] = {x+3, x+2, x+1, x};

	p=x;

	printf("%d == %d\n", x[2], p[2]);
	printf("%d == %d == %d == %d\n", x[2], *(x+2), a[3][2], *a[1]);
	printf("%d == %d == %d == %d\n", x[2], *(x+2), f1()[2], *(f1()+2));
	f2(x+2);
}

#endif

/***********************************************************/
// [EX-6] 대치법이 적용되지 않는 경우
/***********************************************************/

#if 0

void func(int b[4])
{
	printf("%x\n", b);
	printf("%x\n", &b[0]);
	printf("%d\n", sizeof(b));
}

void User_Main(void)
{
	int a[4] = {10,20,30,40};

	printf("%x\n", a);
	printf("%x\n", &a[0]);
	printf("%d\n", sizeof(a));
	func(a);
}

#endif

/***********************************************************/
// [EX-7] 배열 활용식을 이용한 요소 액세스
/***********************************************************/

#if 0

void User_Main(void)
{
	int a[4] = {1,2,3,4};

	printf("%d\n", a[0]);
	printf("%d\n", a[3]);
	printf("%d\n", a[4]);
	printf("%d\n", a[-1]);

	printf("%d\n", (a+1)[2]);
	printf("%d\n", a[3]);
}

#endif

/***********************************************************/
// [EX-8-1] 2차원배열을 전달 받은 1차 포인터
/***********************************************************/

#if 0

void draw_pixel(int y, int x, int value, int *p)
{
	p[y*3+x] = value;
}

void User_Main(void)
{
	int a[2][3] = {1,2,3,4,5,6};

	printf("%d\n", a[1][2]);
	draw_pixel(1, 2, 10, a);
	printf("%d\n", a[1][2]);
}

#endif

/***********************************************************/
// [EX-8-2] 2차원 배열의 전달
/***********************************************************/

#if 0

void draw_pixel(int y, int x, int value,int (*p)[3] )
{
	p[y][x] = value;
}

void User_Main(void)
{
	int a[2][3] = {{1,2,3},{4,5,6}};

	printf("%d\n", a[1][2]);
	draw_pixel(1, 2, 10, a);
	printf("%d\n", a[1][2]);
}

#endif

/***********************************************************/
// [EX-9] 2차원 배열의 리턴
/***********************************************************/

#if 0

typedef int (*AP)[4];

//int (*func(void))[4]
AP func(void)
{
	static int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
	return a;
}

void User_Main(void)
{
	printf("%d\n", func()[1][2] );
}

#endif

/***********************************************************/
// [EX-10] String Pool
/***********************************************************/

#if 0

char d1[3][10] = { "cola", "beer", "coffee" };
char * d2[3] = { "cola", "beer", "coffee" };

char * drink1(int n)
{
	return d1[n];
}

char * drink2(int n)
{
	return d2[n];
}

void User_Main(void)
{
	printf("%s\n", drink1(1));
	printf("%s\n", drink2(1));
	printf("%s\n", drink2(2));
}

#endif

/***********************************************************/
// [EX-11] 문자열 바꾸기
/***********************************************************/

#if 0

void swap_str(char **p, char **q)
{
	// 코드 작성
	char *k = *p;
	*p=*q;
	*q= k;
}

void User_Main(void)
{
	char * p = "Fighting";
	char * q = "Korea";

	printf("%s, %s\n", p, q);
	swap_str(&p, &q);
	printf("%s, %s\n", p, q);
}

#endif

/***********************************************************/
// [EX-12] 이중 포인터
/***********************************************************/

#if 01

int func(int **p)
{
	int i;
	int sum = 0;

	printf("=========%d\n", (*p)[0]);

	// 코드 작성
	i=**p;
	(*p)++;
	printf("%d\n\n",i);
	while (i>0){
	i--;
	sum = sum + **p;

	(*p)++;
	};

	return sum;
}

void User_Main(void)
{
	int i;
	int a[] = { 1,10,2,-5,-20,3,100,200,300,4,-10,-20,-30,-40 };
	int *p = a;

	for (i = 0; i < 4; i++)
	{
		printf("SUM=%d\n", func(&p));
	}
}

#endif
