#include "device_driver.h"

/***********************************************************/
// [EX-1] ��Ʈ���꿡 ���� LED ON
/***********************************************************/

#if 0

void Main(void)
{
	Uart_Init(115200);
	
	/* �� �κ��� ���Ƿ� �ٲ��� ���ÿ� */
	RCC->APB2ENR |= (1<<3);

	/* ��Ʈ ������ �̿��Ͽ� LED0�� ON, LED1�� OFF�� �ϴ� �ڵ带 �����Ͻÿ� */
	GPIOB->CRH &=0xffffff00;
	GPIOB->ODR &=0xfffffcff;

	GPIOB->ODR	|= 0x2 << 8;
	GPIOB->CRH	|= 0x66 << 0;

}

#endif

/**************************************a*********************/
// [EX-2] ��Ʈ ó�� Macro �м�
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
	Uart_Init(115200);
		
	int a = 0xcc3355aa;

	Macro_Set_Bit(a, 0);
	bdisp(a);
	Macro_Clear_Bit(a, 3);
	bdisp(a);
	Macro_Invert_Bit(a, 6);
	bdisp(a);
}

#endif

/**************************************a*********************/
// [EX-3] ��Ƽ��Ʈ ó�� Macro �м�
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
	Uart_Init(115200);
	
	int a = 0xcc3355aa;

	Macro_Clear_Area(a, 0x3, 2);
	bdisp(a);
	Macro_Set_Area(a, 0x7, 8);
	bdisp(a);
	Macro_Invert_Area(a, 0x1F, 12);
	bdisp(a);
}

#endif

/**************************************a*********************/
// [EX-4] Block Write Macro �м�
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
	Uart_Init(115200);
	
	int a = 0xcc3355aa;

	Macro_Write_Block(a, 0x7, 0x5, 2);
	Macro_Write_Block(a, 0xFFFF, 0x1234, 8);

	bdisp(a);
}

#endif

/***********************************************************/
// [EX-5-1] Macro�� Ȱ���� LED ����
/***********************************************************/

#if 0

void Main(void)
{
	Uart_Init(115200);
		
	/* �� �κ��� �������� �� �� */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	/* Macro�� �̿��Ͽ� LED0�� ON, LED1�� OFF�� �ϴ� �ڵ带 �����Ͻÿ� */
	Macro_Write_Block(GPIOB->CRH,0xFF,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x2,8);


}

#endif

/***********************************************************/
// [EX-5-2] Macro�� Ȱ���� LED Toggling
/***********************************************************/

#if 0

void Main(void)
{
	volatile int i;
	Uart_Init(115200);	

	/* �� �κ��� �������� �� �� */
	Macro_Set_Bit(RCC->APB2ENR, 3);

	/* �ʱ⿡ LED ��� OFF => PB[9:8]�� OUTPUT���� �ϰ� 1�� �ʱ⿡ ��� */
	Macro_Write_Block(GPIOB->CRH,0xFF,0x66,0);
	Macro_Write_Block(GPIOB->ODR,0x3,0x3,8);


	for(;;)
	{
		/* LED ��(PB[9:8])�� ��Ʈ ������Ų�� */
	Macro_Invert_Area(GPIOB->ODR,0x3,8);


		for(i=0; i<0x80000; i++);


	}
}

#endif
