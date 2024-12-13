#include "device_driver.h"
#define printf	Uart1_Printf

extern void User_Main(void);

void Main(void)
{
	Uart_Init(115200);
	User_Main();
}

/***********************************************************/
// [EX-1] 포인터(pointer)의 선언과 특성
/***********************************************************/

#if 0

void User_Main(void)
{
	int a = 10;
	int * p = &a;

	printf("0x%p 0x%p %d %d\n", &a, p, a, *p);
	printf("%d %d\n", sizeof(p), sizeof(*p));
}

#endif

/***********************************************************/
// [EX-2] 다양한 타입을 가리키는 포인터
/***********************************************************/

#if 0

void User_Main(void)
{
	char a = 'A';
	char *p = &a;

	double f = 3.14;
	double *q = &f;

	printf("%d, %c\n", sizeof(*p), *p);
	printf("%d, %f\n", sizeof(*q), *q);
	printf("0x%p, 0x%p\n", p, p + 1);
	printf("0x%p, 0x%p\n", q, q + 1);
}

#endif

/***********************************************************/
// [EX-3] Call by Value, Call by Address
/***********************************************************/

#if 0

void f1(int b)
{
	b = 100;
	printf("%d\n", b);
}

void f2(int *p)
{
	*p = 100;
	printf("%d\n", *p);
}

void User_Main(void)
{
	int a = 10;

	f1(a);
	printf("%d\n", a);

	f2(&a);
	printf("%d\n", a);
}

#endif

/***********************************************************/
// [EX-4-1] %s 포맷 지시자와 문자열
/***********************************************************/

#if 0

void User_Main(void)
{
	char a[] = "Hello";
	char *p = "Hello";

	printf("%s\n", "Hello");
	printf("%s, %s, %s\n", &a[0], a, p);
	printf("%s, %s, %s\n", "Hello" + 1, a + 1, p + 1);
}

#endif

/***********************************************************/
// [EX-4-2] 문자열의 정체
/***********************************************************/

#if 0

char * func(char * q)
{
	printf("%s, %c, %c\n", q, q[0], q[1]);
	printf("0x%p, 0x%p, %c, %c\n", q, q + 1, *q, *(q + 1));

	return q + 2;
}

void User_Main(void)
{
	char *p = "Hello";

	printf("%s, 0x%p, 0x%p\n", "Hello", "Hello", "Hello" + 1);
	printf("%c, %c, %c, %c\n", "Hello"[0], "Hello"[1], *"Hello", *("Hello" + 1));
	printf("%s\n", func("Hello"));
}

#endif

/***********************************************************/
// [EX-5-1] *p++, *++p의 동작
/***********************************************************/

#if 0

void User_Main(void)
{
	int cnt = 0;
	char *p = "Embedded";

	while (*p)
	{
		if (*p++ == 'd') cnt++;
	}

	printf("%d\n", cnt);
}

#endif

/***********************************************************/
// [EX-5-2] [] 연산자를 사용한 코드
/***********************************************************/

#if 0

void User_Main(void)
{
	int cnt = 0, i = 0;
	char *p = "Embedded";

	while (p[i])
	{
		if (p[i++] == 'd') cnt++;
	}

	printf("%d\n", cnt);
}

#endif

/***********************************************************/
// [EX-6] 문자열 복사 함수
/***********************************************************/

#if 0

void str_copy1(char * d, char * s)
{
	int i;

	for (i = 0; ; i++)
	{
		d[i] = s[i];
		if (d[i] == '\0') return;
	}
}

void str_copy2(char * d, char * s)
{
	while (*d++ = *s++);
}

void User_Main(void)
{
	char a[5], b[5];
	char c[5] = "ABCD";

	str_copy1(a, c);
	str_copy2(b, c);
	printf("%s %s %s\n", a, b, c);
}

#endif

/***********************************************************/
// [EX-7] 문자열 길이 측정 함수
/***********************************************************/

#if 0

unsigned int str_length(char * d)
{
	// 코드 작성
	int count=0;
	while(d[count]){
	count++;
	};
	return count;
}

void User_Main(void)
{
	char a[] = "Willtek";

	printf("%d\n", sizeof(a));
	printf("%d\n", str_length(a));
}

#endif

/***********************************************************/
// [EX-8] 문자열 연결 함수
/***********************************************************/

#if 01

void str_add(char * d, char * s)
{
	// 코드 작성
//	int count1=0;
//	int count2=0;

//	while(d[count1]){
//		count1++;
//	}
//	while(s[count2]){
//		d[count1]=s[count2];
//		count1++;
//		count2++;
//
//	}
	while(*d++);
	*d--;
	while(*d++=*s++);


}

void User_Main(void)
{
	char a[15] = "Willtek";
	char b[15] = " Corp.";

	str_add(a, b);

	printf("%s\n", a);
}

#endif
