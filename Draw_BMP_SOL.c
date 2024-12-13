#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Key_Poll_Init();
	Uart_Init(115200);
}

#define BLACK	0x0000
#define WHITE	0xffff
#define BLUE	0x001f
#define GREEN	0x07E0
#define RED		0xf800

#pragma pack(push, 1)

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

#define PIX565(p, x)	((((p)[x].red & 0xF8) << 8)|(((p)[x].green & 0xFC) << 3)|(((p)[x].blue) >> 3))

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

#define IMG				((void *)0x0800E000) // √÷¥Î 8KB

void Main(void)
{
	Sys_Init();

	Uart_Printf("BMP Parser\n");
	Lcd_Init();
	Lcd_Clr_Screen(BLACK);

	Uart_Printf("0x%.8X\n", *(int *)IMG);
	Lcd_Print_BMP_Info(IMG);
	Lcd_Draw_BMP_File_24bpp(0, 0, IMG);
	
#if 0
	Lcd_Draw_BMP_File_24bpp(40, 0, IMG);
	Lcd_Draw_BMP_File_24bpp(80, 0, IMG);
	Lcd_Draw_BMP_File_24bpp(120, 0, IMG);
	Lcd_Draw_BMP_File_24bpp(0, 50, IMG);
	Lcd_Draw_BMP_File_24bpp(40, 50, IMG);
	Lcd_Draw_BMP_File_24bpp(80, 50, IMG);
	Lcd_Draw_BMP_File_24bpp(120, 50, IMG);
#endif
}
