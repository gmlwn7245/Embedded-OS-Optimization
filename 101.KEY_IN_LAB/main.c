#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
}

/***********************************************************/
// [EX-1] 비트 Check Macro 분석
/***********************************************************/

#if 0

#include "macro.h"

void Main(void)
{
	Sys_Init();
	int a = 0xcc3355aa;

	if(Macro_Check_Bit_Set(a,7))
	{
		Uart_Printf("SET\n");
	}
	else
	{
		Uart_Printf("CLEAR\n");
	}

	if(Macro_Check_Bit_Clear(a,2))
	{
		Uart_Printf("CLEAR\n");
	}
	else
	{
		Uart_Printf("SET\n");
	}
}

#endif

/***********************************************************/
// [EX-2] Extract Macro 분석
/***********************************************************/

#if 0

#include "macro.h"

void bdisp(int a)
{
	int i;

	for(i = 31; i >= 0; i--)
	{
		Uart_Printf("%d", a >> i & 1);
		if((i%4 == 0) && (i != 0))
		{
			Uart_Printf("-");
		}
	}
	Uart_Printf("\n");
}

void Main(void)
{
	Sys_Init();

	int a = 0xcc3355aa;
	int b;

	b = Macro_Extract_Area(a, 0x7, 2);
	bdisp(b);
	Uart_Printf("%d\n", b);

	b = Macro_Extract_Area(a, 0xFF, 4);
	bdisp(b);
	Uart_Printf("0x%X\n", b);
}

#endif

/***********************************************************/
// [EX-3] Key 인식
/***********************************************************/

#if 0

void Main(void)
{
	Sys_Init();
//	int b;
	Uart_Printf("KEY Input Test #1\n");
	Macro_Write_Block(GPIOB->CRL,0xFF,0x44,24);


	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언
//	Macro_Write_Block(GPIOB->IDR,0x3,0x3,6);


	for(;;)
	{
//		b = Macro_Extract_Area(GPIOB->IDR, 0x3, 6);
//		// KEY0이 눌렸으면 LED0를 ON, 안 눌렸으면 OFF
//		if(b==0x1 || b==0x3 ){
//		Macro_Write_Block(GPIOB->ODR,0x1,0x1,8);}
//		else 	Macro_Write_Block(GPIOB->ODR,0x1,0x0,8);
//
//
//
//
//		// KEY1이 눌렸으면 LED1를 ON, 안 눌렸으면 OFF
//		if(b==0x3 || b==0x2){
//				Macro_Write_Block(GPIOB->ODR,0x1,0x1,9);}
//		else 	Macro_Write_Block(GPIOB->ODR,0x1,0x0,9);
		Macro_Write_Block(GPIOB->ODR,0x3,Macro_Extract_Area(GPIOB->IDR, 0x3, 6),8);

	}
}

#endif

/***********************************************************/
// [EX-4] KEY에 의한 LED Toggling
/***********************************************************/

#if 0

void Main(void)
{
	Sys_Init();
	int b=1;
	Uart_Printf("KEY Input Toggling #1\n");


	// KEY[1:0], GPB[7:6]을 GPIO 입력으로 선언



	for(;;)
	{
		// KEY0가 눌릴때마다 LED0의 값을 Toggling
		if (b==1){ b=Macro_Extract_Area(GPIOB->IDR, 0x1, 6);
			if(b==0){Macro_Invert_Bit(GPIOB->ODR,8);}}

		if((b==0)& Macro_Extract_Area(GPIOB->IDR, 0x1, 6)) b=1;

	}




#endif
