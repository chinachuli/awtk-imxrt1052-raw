#ifndef __BSP_LCD_H
#define	__BSP_LCD_H

#include "fsl_common.h"
//#include "fonts.h"

/* 此宏为真时，显存像素点使用RGB888 或XRGB8888 格式，
   为假时使用RGB565格式，推荐值为0 
*/
#define LCD_RGB_888 			0	

/* 此宏为真时，使用24根数据线驱动屏幕，
	 为假时，使用16根数据线，
	 本开发板网络接口使用了部分LCD数据信号线，
	 所以本硬件设计仅支持LCD使用16根数据线，
	 若像素格式配置为RGB888格式24位，数据线为16位，
	 eLCDIF输出时会自动转换，此时显存像素点使用24位浪费空间，
   所以推荐使用RGB565格式
 */
#define LCD_BUS_24_BIT			0


#if LCD_BUS_24_BIT
	/* LCD数据线宽度 */
	#define LCD_DATA_BUS_WIDTH    kELCDIF_DataBus24Bit
#else
	/* LCD数据线宽度 */
	#define LCD_DATA_BUS_WIDTH    kELCDIF_DataBus16Bit
#endif


/* LCD背光引脚，高电平点亮 */
#define LCD_BL_GPIO 				      GPIO1
#define LCD_BL_GPIO_PIN 		      (15U)
#define LCD_BL_IOMUXC			        IOMUXC_GPIO_AD_B0_15_GPIO1_IO15

/* LCD 分辨率 */
#define LCD_PIXEL_WIDTH     800
#define LCD_PIXEL_HEIGHT    480

/* LCD时序 */
/* 根据液晶数据手册配置 */
#define LCD_HSW 	1
#define LCD_HFP 	22
#define LCD_HBP 	46
#define LCD_VSW 	1
#define LCD_VFP 	22
#define LCD_VBP 	23
#define LCD_POLARITY_FLAGS	(kELCDIF_DataEnableActiveHigh |	\
															kELCDIF_VsyncActiveLow | 			\
															kELCDIF_HsyncActiveLow | 			\
															kELCDIF_DriveDataOnRisingClkEdge)



/* 缓冲区对齐配置, 为了提高性能, LCDIF缓冲区要64B对齐 */
#define FRAME_BUFFER_ALIGN    64

/* 配置是否使用中断的标志 */
#define LCD_INTERRUPT_DISABLE   0
#define LCD_INTERRUPT_ENABLE    (!LCD_INTERRUPT_DISABLE)

/* 绘制横线和垂线的标志 */
#define LINE_DIR_HORIZONTAL       0x0
#define LINE_DIR_VERTICAL         0x1

/*
	LCD 颜色代码，CL_是Color的简写
	16Bit由高位至低位， RRRR RGGG GGGB BBBB

	下面的RGB 宏将24位的RGB值转换为16位格式。
	启动windows的画笔程序，点击编辑颜色，选择自定义颜色，可以获得的RGB值。

	推荐使用迷你取色器软件获得你看到的界面颜色。
*/
#if LCD_RGB_888

	/* eLCDIF 像素格式配置 */
	#define ELCDIF_PIXEL_FORMAT 	kELCDIF_PixelFormatXRGB8888
	
  /* 像素点的字节数 */
	/* 使用 24-bit RGB888 或 XRGB8888 格式. */
	#define LCD_BPP 				4U 

	/* 像素点使用32位类型 */
	typedef uint32_t				pixel_t;

	/* RGB888颜色转换 */
	/* 将8位R,G,B转化为 24位RGB888格式 */
	#define RGB(R,G,B)	( (R<< 16) | (G << 8) | (B))	

#else 
	/* eLCDIF 像素格式配置 */
	#define ELCDIF_PIXEL_FORMAT 	kELCDIF_PixelFormatRGB565

	/* 像素点的字节数 */
	/* 使用 16-bit RGB565 格式. */
	#define LCD_BPP 	2U 

	/* 像素点使用16位类型 */
	typedef uint16_t	pixel_t;

	/*RGB565 颜色转换*/
	/* 将8位R,G,B转化为 16位RGB565格式 */
	#define RGB(R,G,B)	(((R >> 3) << 11) | ((G >> 2) << 5) | (B >> 3))	
	#define RGB565_R(x)  ((x >> 8) & 0xF8)
	#define RGB565_G(x)  ((x >> 3) & 0xFC)
	#define RGB565_B(x)  ((x << 3) & 0xF8)

#endif

/* 常用颜色表 */
enum
{
	CL_WHITE    = RGB(255,255,255),	/* 白色 */
	CL_BLACK    = RGB(  0,  0,  0),	/* 黑色 */
	CL_RED      = RGB(255,	0,  0),	/* 红色 */
	CL_GREEN    = RGB(  0,255,  0),	/* 绿色 */
	CL_BLUE     = RGB(  0,	0,255),	/* 蓝色 */
	CL_YELLOW   = RGB(255,255,  0),	/* 黄色 */

	CL_GREY    = RGB( 98, 98, 98), 	/* 深灰色 */
	CL_GREY1		= RGB( 150, 150, 150), 	/* 浅灰色 */
	CL_GREY2		= RGB( 180, 180, 180), 	/* 浅灰色 */
	CL_GREY3		= RGB( 200, 200, 200), 	/* 最浅灰色 */
	CL_GREY4		= RGB( 230, 230, 230), 	/* 最浅灰色 */

	CL_BUTTON_GREY	= RGB( 220, 220, 220), /* WINDOWS 按钮表面灰色 */

	CL_MAGENTA      = RGB(255, 0, 255),	/* 红紫色，洋红色 */
	CL_CYAN         = RGB( 0, 255, 255),	/* 蓝绿色，青色 */

	CL_BLUE1        = RGB(  0,  0, 240),		/* 深蓝色 */
	CL_BLUE2        = RGB(  0,  0, 128),		/* 深蓝色 */
	CL_BLUE3        = RGB(  68, 68, 255),		/* 浅蓝色1 */
	CL_BLUE4        = RGB(  0, 64, 128),		/* 浅蓝色1 */

	/* UI 界面 Windows控件常用色 */
	CL_BTN_FACE		  = RGB(236, 233, 216),	/* 按钮表面颜色(灰) */
	CL_BOX_BORDER1	= RGB(172, 168,153),	/* 分组框主线颜色 */
	CL_BOX_BORDER2	= RGB(255, 255,255),	/* 分组框阴影线颜色 */

	CL_MASK			    = 0x7FFF	/* RGB565颜色掩码，用于文字背景透明 */
};
/*******************************************************************************
 * 全局变量声明
 ******************************************************************************/
extern volatile bool s_frameDone;
extern pixel_t s_psBufferLcd[3][LCD_PIXEL_HEIGHT][LCD_PIXEL_WIDTH];

/*******************************************************************************
 * 函数声明
 ******************************************************************************/
void LCD_BackLight_ON(void);
void fLCD_Init(bool enableInterrupt);
void LCD_InterruptConfig(void);





#endif /* __BSP_LCD_H */
