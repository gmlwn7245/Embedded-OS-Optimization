/***********************************************************/
// [5-5] 가변인자의 전달 - SOL
/***********************************************************/
// Compiler 환경을 32비트(x86) 모드로 설정해야 함
/***********************************************************/

#if 0

#include <stdio.h>

int my_add(int cnt, ...)
{
	int i, sum = 0;

	for (i = 1; i <= cnt; i++)
	{
		sum += (&cnt)[i];
	}
	return sum;
}

void main(void)
{
	printf("%d\n", my_add(3, 7, 5, 4));
	printf("%d\n", my_add(5, 1, 2, 6, 9, 10));
}

#endif

/***********************************************************/
// [5-6] 가변인자의 access
/***********************************************************/
// Compiler 환경을 32비트(x86) 모드로 설정해야 함
/***********************************************************/

#if 01

#include <stdio.h>

void my_ellipsis(int a, ...)
{
	printf("%d\n", a);
	printf("%u\n", *(unsigned int *)(&a + 1));
	printf("%c\n", *(unsigned char *)(&a + 2));
	printf("%f\n", *(double *)(&a + 3));
	printf("%f\n", *(double *)(&a + 5));
}

void main(void)
{
	int a = 10;
	unsigned char b = 100;
	unsigned char c = 'A';
	float d = 3.14f;
	double e = 5.125;

	my_ellipsis(a, b, c, d, e);
}

#endif

/* 가변인자 매크로 사용 */

#if 0

#include <stdio.h>
#include <stdarg.h>

void my_ellipsis(int a, ...)
{
	va_list ap;
	va_start(ap, a);

	printf("%d\n", a);
	printf("%u\n", va_arg(ap, unsigned int));
	printf("%c\n", va_arg(ap, unsigned int));
	printf("%f\n", va_arg(ap, double));
	printf("%lf\n", va_arg(ap, double));
	va_end(ap);
}

void main(void)
{
	int a = 10;
	unsigned char b = 100;
	unsigned char c = 'A';
	float d = 3.14f;
	double e = 5.125;

	my_ellipsis(a, b, c, d, e);
}

#endif

/***********************************************************/
// [5-8] 실수의 메모리 내용 dump
/***********************************************************/
// Compiler 환경을 32비트(x86) 모드로 설정해야 함
/***********************************************************/

#if 0

#include <stdio.h>

void main(void)
{
	float a = 3.5f;
	double b = 3.5;

	printf("float : %#.8x\n", *(unsigned int *)&a);
	printf("double: %#.8x : %.8x\n\n", *((unsigned int *)&b + 1), *(unsigned int *)&b);
}

#endif

/***********************************************************/
// [실습 7-6] 새로운 레지스터 정의의 활용
/***********************************************************/

#if 0

void Main(void)
{
	volatile int i;

	Clock_Init();
	Uart_Init(115200);
	Uart_Printf("CMSIS Based Register Define\n");

	RCC->APB2ENR |= (1 << 3);

	GPIOB->CRH = 0x66 << 0;

	for (;;)
	{
		GPIOB->ODR = 0x0 << 8;

		for (i = 0; i < 0x40000; i++);

		GPIOB->ODR = 0x3 << 8;

		for (i = 0; i < 0x40000; i++);
	}
}

#endif

/***********************************************************/
// [11-4] Assert Macro의 설계
/***********************************************************/

#if 0

#include <stdio.h>

#define DEBUG_MODE	1
        	
#if DEBUG_MODE
	#define _assert(x)	{if(!(x)) {printf("Error!\n"); for(;;);}}
#else
	#define _assert(x)
#endif        	

int func(int a)
{
	static int x[5] = {1,2,3,4,5};
	
	_assert((unsigned int)a <= 4);
	
	return x[a];
}

void main(void)
{
	printf("%d\n", func(5));
}

#endif

/***********************************************************/
// [11-5] 디버깅 정보의 출력
/***********************************************************/

#if 0

#include <stdio.h>

#define DEBUG_MODE	1
        	
#if DEBUG_MODE
	#define _assert(x) {if(!(x)) {printf("Error => (" #x ") @%d line, %s() of %s\n", __LINE__, __FUNCTION__, __FILE__); for(;;);}}
#else
	#define _assert(x)
#endif        	

int func(int a)
{
	static int x[5] = {1,2,3,4,5};
	
	_assert((unsigned int)a <= 4);
	
	return x[a];
}

void main(void)
{
	printf("%d\n", func(5));
}

#endif

/***********************************************************/
// [11-6] 부가 정보의 인쇄
/***********************************************************/
// C99 표준이며 컴파일러의 지원 여부를 확인해야 한다
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_MODE	1
        	
#if DEBUG_MODE
	#define _assert(x, ...) \
			{	\
				if(!(x)) \
				{	\
					printf("Error => (" #x ") @%d line, %s() of %s\n", __LINE__, __FUNCTION__, __FILE__); 	\
					printf(""__VA_ARGS__); 	\
					for(;;);	\
				}	\
			}	
#else
	#define _assert(x, ...)
#endif        	

int func(int a)
{
	static int x[5] = {1,2,3,4,5};
	
	_assert((unsigned int)a <= 4, "Range Over: a=%d", a);
	return x[a];
}

void main(void)
{
	int *p;

	p = malloc(1 * sizeof(int));
	_assert(p, "Malloc Fail");
	*p = 5;
	printf("%d\n", func(*p));
	free(p);
}

#endif 

/***********************************************************/
// [11-7] 부가 정보의 인쇄 매크로 개선
/***********************************************************/
// C99 표준이며 컴파일러의 지원 여부를 확인해야 한다
/***********************************************************/

#if 0

#include <stdio.h>
#include <stdlib.h>

#define DEBUG_MODE	1

#if DEBUG_MODE
#define _assert(x, ...) \
			{	\
				if(!(x)) \
				{	\
					printf("Error => (" #x ") @%d line, %s() of %s\n", __LINE__, __FUNCTION__, __FILE__); 	\
					printf(""__VA_ARGS__); 	\
					for(;;);	\
				}	\
			}	
#else
#define _assert(x, ...)
#endif  

int func(int a)
{
	static int x[5] = {1,2,3,4,5};
	
	/* 아래와 같이 아무런 디버깅 정보를 인쇄하지 않을 경우도 인쇄가 잘 되어야 한다 */

	_assert((unsigned int)a <= 4);

	return x[a];
}

void main(void)
{
	int *p;

	p = malloc(1 * sizeof(int));
	_assert(p, "Malloc Fail");
	*p = 5;
	printf("%d\n", func(*p));
	free(p);
}

#endif 

/***********************************************************/
// [13-1] 배열의 전달과 리턴
/***********************************************************/

#if 0

#include <stdio.h>

void func(int *p)
{
	printf("a[3] = %d\n", p[3]);
}

void main(void)
{
	int a[4] = { 1,2,3,4 };

	func(a);
}

#endif

#if 0

#include <stdio.h>

int * func(void)
{
	static int a[4] = { 1,2,3,4 };

	return a;
}

void main(void)
{
	printf("a[3] = %d\n", func()[3]);
}

#endif

/**********************************************************/
// [13-4] 2차원배열의 전달
/**********************************************************/

#if 0

#include <stdio.h>

void draw_pixel(int y, int x, int value, int(*p)[3])
{
	p[y][x] = value;
}

void main(void)
{
	int a[2][3] = { 1,2,3,4,5,6 };

	printf("%d\n", a[1][2]);
	draw_pixel(1, 2, 10, a);
	printf("%d\n", a[1][2]);
}

#endif

/**********************************************************/
// [13-5] 2차원배열의 리턴
/**********************************************************/

#if 0

#include <stdio.h>

int(*func(void))[4]
{
	static int a[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
	return a;
}

void main(void)
{
	printf("%d\n", func()[1][2]);
}

#endif

/**********************************************************/
// [13-6] 배열의 액세스
/**********************************************************/

#if 0

#include <stdio.h>

int a[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
int *b[3] = { a[2], a[1], a[0] };

void main(void)
{
	printf("%d\n", a[2][3]);

	printf("%d\n", b[0][3]);
}

#endif

/**********************************************************/
// [13-7] 환산법의 적용
/**********************************************************/

#if 0

#include <stdio.h>

int a[3][4] = { {1,2,3,4},{5,6,7,8},{9,10,11,12} };
int *p = a[0];

void main(void)
{
	printf("%d\n", a[2][3]);

	printf("%d\n", p[11]);
}

#endif

/***********************************************************/
// [13-8] 함수 parameter의 직관적 설계
/***********************************************************/

#if 0

#include <stdio.h>

void f1(int *p)
{
	printf("%d\n", p[17]);
}

void main(void)
{
	int a[2][3][4] = { {{1,2,3,4},{5,6,7,8},{9,10,11,12}},{{10,20,30,40},{50,60,70,80},{90,100,110,120}} };
	f1(*(a[0] + 1));
}

#endif

#if 0

#include <stdio.h>

void f2(int(*p)[4])
{
	printf("%d\n", p[-1][1]);
}

void main(void)
{
	int a[2][3][4] = { {{1,2,3,4},{5,6,7,8},{9,10,11,12}},{{10,20,30,40},{50,60,70,80},{90,100,110,120}} };
	f2(*(a + 2));
}

#endif

#if 0



#endif

#if 0

#include <stdio.h>

void f3(int(*p)[3][4])
{
	printf("%d\n", p[1][2][1]);
}

void main(void)
{
	int a[2][3][4] = { {{1,2,3,4},{5,6,7,8},{9,10,11,12}},{{10,20,30,40},{50,60,70,80},{90,100,110,120}} };
	f3(a);
}

#endif

#if 0

#include <stdio.h>

void f4(int(*p)[3][4])
{
	printf("%d\n", p[-2][2][1]);
}

void main(void)
{
	int a[2][3][4] = { {{1,2,3,4},{5,6,7,8},{9,10,11,12}},{{10,20,30,40},{50,60,70,80},{90,100,110,120}} };
	f4(a + 3);
}

#endif

#if 0

#include <stdio.h>

void f5(int(*p)[2][3][4])
{
	printf("%d\n", (*p)[1][2][1]);
}

void main(void)
{
	int a[2][3][4] = { {{1,2,3,4},{5,6,7,8},{9,10,11,12}},{{10,20,30,40},{50,60,70,80},{90,100,110,120}} };
	f5(&a);
}

#endif

#if 0

#include <stdio.h>

void f6(int(*p)[2][3][4])
{
	printf("%d\n", p[1][1][2][1]);
}

void main(void)
{
	int a[2][3][4] = { {{1,2,3,4},{5,6,7,8},{9,10,11,12}},{{10,20,30,40},{50,60,70,80},{90,100,110,120}} };
	f6(&a - 1);
}

#endif

/***********************************************************/
// [13-9] 함수 리턴의 직관적 설계
/***********************************************************/

#if 0

#include <stdio.h>

int a[2][3] = { {1,2,3},{4,5,6} };
int b[2][3] = { {10,20,30},{40,50,60} };
int(*c[2])[3] = { b, a };
int(**p)[3] = c;

int(*f1(void))[3]
{
	return c[1];
}

void main(void)
{
	printf("6=%d\n", f1()[1][2]);
}

#endif

#if 0

#include <stdio.h> 

int a[2][3] = { {1,2,3},{4,5,6} };
int b[2][3] = { {10,20,30},{40,50,60} };
int(*c[2])[3] = { b, a };
int(**p)[3] = c;

int(**f2(void))[3]
{
	return c + 1;
}

void main(void)
{
	printf("6=%d\n", (*f2())[1][2]);
}

#endif

#if 0

#include <stdio.h> 

int a[2][3] = { {1,2,3},{4,5,6} };
int b[2][3] = { {10,20,30},{40,50,60} };
int(*c[2])[3] = { b, a };
int(**p)[3] = c;

int *f3(void)
{
	return a[0] - 1;
}

void main(void)
{
	printf("6=%d\n", (f3() + 1)[5]);
}

#endif

#if 0

#include <stdio.h> 

int a[2][3] = { {1,2,3},{4,5,6} };
int b[2][3] = { {10,20,30},{40,50,60} };
int(*c[2])[3] = { b, a };
int(**p)[3] = c;

int(**f4(void))[3]
{
	return p;
}

void main(void)
{
	printf("6=%d\n", f4()[1][1][2]);
}

#endif

#if 0

#include <stdio.h> 

int a[2][3] = { {1,2,3},{4,5,6} };
int b[2][3] = { {10,20,30},{40,50,60} };
int(*c[2])[3] = { b, a };
int(**p)[3] = c;

int(*(*f5(void))[2])[3]
{
	return &c;
}

void main(void)
{
	printf("6=%d\n", (*f5())[1][1][2]);
}

#endif

/***********************************************************/
// [13-10] 함수에 함수를 전달
/***********************************************************/

#if 0

#include <stdio.h> 

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

void func(int(*p)(int a, int b))
{
	printf("%d\n", p(3, 4));
}

void main(void)
{
	func(add);
	func(sub);
}

#endif

/***********************************************************/
// [13-11] Parameter 미지정형
/***********************************************************/

#if 0

#include <stdio.h> 

int add(int a, int b)
{
	return a + b;
}

int sqr(int a)
{
	return a * a;
}

int func(void)
{
	return 100;
}

int(*p)();

void main(void)
{
	p = add;
	printf("%d\n", p(3, 4));

	p = sqr;
	printf("%d\n", p(3));

	p = func;
	printf("%d\n", p());
}

#endif

/***********************************************************/
// [실습 13-2] 함수 포인터를 이용한 호출 엔진
/***********************************************************/

#if 0 

void func1(void)
{
	printf("func1\n");
}

void func2(void)
{
	printf("func2\n");
}

void func3(void)
{
	printf("func3\n");
}

void(*fa[])(void) = { func1, func2, func3 };

void Main(void)
{
	unsigned char num;

	Clock_Init();
	Uart_Init(115200);

	printf("함수 포인터를 이용한 함수 호출 엔진\n");

	for (;;)
	{
		printf("실행할 함수 번호를 입력하시오(1~3)\n");

		num = Uart1_Get_Char() - '1';

		if ((num >= 0) && (num < (sizeof(fa) / sizeof(fa[0]))))
		{
			fa[num]();
		}
	}
}

#endif

/***********************************************************/
// [실습 13-3] typedef을 이용한 가독성 증대
/***********************************************************/

#if 0

void func1(void)
{
	printf("func1\n");
}

void func2(void)
{
	printf("func2\n");
}

void func3(void)
{
	printf("func3\n");
}

typedef void(*FPTR)(void);

static FPTR fa[] = { func1, func2, func3 };

void Main(void)
{
	unsigned char num;

	Clock_Init();
	Uart_Init(115200);

	printf("typedef을 이용한 가독성 증대\n");

	for (;;)
	{
		printf("실행할 함수 번호를 입력하시오(1~3)\n");

		num = Uart1_Get_Char() - '1';

		if ((num >= 0) && (num < (sizeof(fa) / sizeof(fa[0]))))
		{
			fa[num]();
		}
	}
}

#endif


/***********************************************************/
// [실습 13-4] Heap에 동적 배열 만들기 연습
/***********************************************************/

#if 0

void Main(void)
{
	Clock_Init();
	Uart_Init(115200);

	printf("등가 포인터를 이용한 힙에 배열 만들기 연습 #1\n");

	int(*p)[3][4];

	p = malloc(2 * sizeof(int[3][4]));

	p[0][0][0] = 100;
	p[1][2][3] = 500;

	printf("p[0][0][0] = %d, p[1][2][3] = %d\n", p[0][0][0], p[1][2][3]);
}

#endif

#if 0

void Main(void)
{
	Clock_Init();
	Uart_Init(115200);
	printf("등가 포인터를 이용한 힙에 배열 만들기 연습 #2\n");

	char(**p)[4];

	p = malloc(3 * sizeof(char(*)[4]));

	p[0] = &"SUN", p[1] = &"MON", p[2] = &"MON";

	printf("*p[0] = %s, *p[1] = %s, *p[2] = %s\n", *p[0], *p[1], *p[2]);
}

#endif

/***********************************************************/
// [실습 13-5] Free Memory에 배열 만들기
/***********************************************************/

#if 0

#define FREE_BASE Get_Heap_Base()

void Main(void)
{
	Clock_Init();
	Uart_Init(115200);
	printf("등가포인터를 이용한 Free Memory에 배열 만들기 #1\n");

	int * p;

	p = (int *)FREE_BASE;

	p[0] = 1, p[9] = 50;

	printf("p = 0x%.8X, p[0] = %d, p[9] = %d\n", p, p[0], p[9]);
}

#endif

#if 0

#define FREE_BASE Get_Heap_Base()

void Main(void)
{
	Clock_Init();
	Uart_Init(115200);
	printf("등가포인터를 이용한 Free Memory에 배열 만들기 #2\n");

	int(*p)[4];

	p = (int(*)[4])FREE_BASE;

	p[0][0] = 1, p[2][3] = 50;

	printf("p = 0x%.8X, p[0][0] = %d, p[2][3] = %d\n", p, p[0][0], p[2][3]);
}

#endif

/***********************************************************/
// [실습 13-6] Free Memory 영역 직접 액세스
/***********************************************************/

#if 0

#define FREE_BASE Get_Heap_Base()
#define IMG		((int (*)[64])FREE_BASE)

void Main(void)
{
	Clock_Init();
	Uart_Init(115200);
	printf("Free Memory 직접 Access #2\n");

	IMG[0][0] = 1;
	IMG[32 - 1][64 - 1] = 50;

	printf("IMG = 0x%.8X, IMG[0][0] = %d, IMG[32-1][64-1] = %d\n", IMG, IMG[0][0], IMG[32 - 1][64 - 1]);
}

#endif

/***********************************************************/
// [실습 13-7] Graphic Frame Buffer
/***********************************************************/

#if 0

#define	FBptr	((unsigned short (*)[20])FREE_BASE)

#endif

/***********************************************************/
// [14-5] 연속한 구조체 데이터
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  info     ((struct st *)buf)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned short length;
};

void main(void)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		printf("0x%x, 0x%x, 0x%x\n", (info + i)->x, (info + i)->y, (info + i)->length);
	}
}

#endif

/***********************************************************/
// [14-6] 연속한 구조체는 구조체 배열이다
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  info     ((struct st *)buf)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned short length;
};

void main(void)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		printf("0x%x, 0x%x, 0x%x\n", info[i].x, info[i].y, info[i].length);
	}
}

#endif

/***********************************************************/
// [14-11] pack으로 원하는 구조체 만들기
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x4d,0x4d,0x55,0x5f,0x45,0x6e,0x61,0x62,0x6c,0x65,0x44,0x43,0x61,0x63,0x68,0x65 };

#define  info     ((struct st *)buf)

#pragma pack(push, 2)

struct st
{
	unsigned char x;
	unsigned char y;
	unsigned int length;
};

#pragma pack(pop)

void main(void)
{
	printf("0x%x, 0x%x, 0x%x\n", info[0].x, info[0].y, info[0].length);
	printf("0x%x, 0x%x, 0x%x\n", info[1].x, info[1].y, info[1].length);
}

#endif

/***********************************************************/
// [14-14] 비트필드 구조체의 활용
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x52,0x7a };

struct fat_time
{
	unsigned short sec : 5;
	unsigned short min : 6;
	unsigned short hour : 5;
};

void main(void)
{
	struct fat_time * time = (struct fat_time *)buf;

	printf("Time=%d:%d:%d\n", time->hour, time->min, time->sec * 2);
	printf("Sizeof Time=%d\n", sizeof(struct fat_time));
}

#endif

/***********************************************************/
// [14-19] 공용체와 구조체
/***********************************************************/

#if 0

#include <stdio.h>

union float_data
{
	float f;

	struct
	{
		unsigned int mant : 23;
		unsigned int exp : 8;
		unsigned int sign : 1;
	}bit;
}fdata;

void main(void)
{
	fdata.f = 13.625;

	printf("%f\n", fdata.f);
	printf("sign(1bit):%x\n", fdata.bit.sign);
	printf("exponent(8bit):%x\n", fdata.bit.exp);
	printf("mantissa(23bit):%x\n", fdata.bit.mant);

	fdata.bit.sign = 1;
	printf("%f\n", fdata.f);
}

#endif

/***********************************************************/
// [14-20] 파일시스템의 파일 종류 인식
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x25, 0x0f };

struct fat_file
{
	unsigned char r : 1;
	unsigned char h : 1;
	unsigned char s : 1;
	unsigned char v : 1;
	unsigned char d : 1;
	unsigned char a : 1;
};

#define fn ((struct fat_file *)buf)

void main(void)
{
	int i;

	for (i = 0; i < 2; i++)
	{
		if (fn[i].v && fn[i].s && fn[i].h && fn[i].r) printf("Long File Name\n");
		else printf("A[%d]D[%d]V[%d]S[%d]H[%d]R[%d]\n", fn[i].a, fn[i].d, fn[i].v, fn[i].s, fn[i].h, fn[i].r);
	}
}

#endif

/***********************************************************/
// [14-21] 효율적인 long file name의 판단
/***********************************************************/

#if 0

#include <stdio.h>

unsigned char buf[] = { 0x25, 0x0f, 0x3f };

struct fat_file
{
	unsigned char r : 1;
	unsigned char h : 1;
	unsigned char s : 1;
	unsigned char v : 1;
	unsigned char d : 1;
	unsigned char a : 1;
	unsigned char : 0;
};

struct long_file
{
	unsigned char ln : 4;
	unsigned char : 0;
};

union file
{
	struct fat_file n;
	struct long_file l;
};

#define fn ((union file *)buf)

void main(void)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		if (fn[i].l.ln == 0xF) printf("Long File Name\n");
		else printf("A[%d]D[%d]V[%d]S[%d]H[%d]R[%d]\n", fn[i].n.a, fn[i].n.d, fn[i].n.v, fn[i].n.s, fn[i].n.h, fn[i].n.r);
	}
}

#endif

/***********************************************************/
// [실습 15-1] BMP 헤더, DIB 모델링
/***********************************************************/

typedef struct
{
	unsigned char magic[2];
	unsigned int size_of_file;
	unsigned char rsvd1[2];
	unsigned char rsvd2[2];
	unsigned int offset;
	unsigned int size_of_dib;
	unsigned int width;
	unsigned int height;
	unsigned short color_plane;
	unsigned short bpp;
	unsigned int compression;
	unsigned int size_of_image;
	unsigned int x_res;
	unsigned int y_res;
	unsigned int i_color;
}BMP_HDR;

typedef struct
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}PIXEL;

#pragma pack(pop)

/***********************************************************/
// [실습 15-2] BMP 파일 정보 인쇄
/***********************************************************/

#define BMP_FILE		((BMP_HDR *)fp)

void Lcd_Print_BMP_Info(void * fp)
{
	Uart_Printf("MAGIC = %c%c\n", BMP_FILE->magic[0], BMP_FILE->magic[1]);
	Uart_Printf("BMP SIZE = %d\n", BMP_FILE->size_of_file);
	Uart_Printf("RAW OFFSET = %d\n", BMP_FILE->offset);
	Uart_Printf("DIB SIZE = %d\n", BMP_FILE->size_of_dib);
	Uart_Printf("WIDTH = %d, HEIGHT = %d\n", BMP_FILE->width, BMP_FILE->height);
	Uart_Printf("BPP = %d\n", BMP_FILE->bpp);
}

/***********************************************************/
// [실습 15-3] Lcd_Draw_BMP_File_24bpp 함수 설계
/***********************************************************/

void Lcd_Draw_BMP_File_24bpp(int x, int y, void * fp)
{
	int xx, yy;
	unsigned int pad = (4 - ((BMP_FILE->width * 3) % 4))%4;
	unsigned char * pix = (unsigned char *)fp + BMP_FILE->offset;

	for(yy = (BMP_FILE->height-1); yy >= 0; yy--)
	{
		for(xx = 0; xx < BMP_FILE->width; xx++)
		{
		    Lcd_Put_Pixel(xx + x, yy + y, PIX565((PIXEL *)pix, xx));
		}

		pix = pix + (BMP_FILE->width * sizeof(PIXEL)) + pad;
	}
}