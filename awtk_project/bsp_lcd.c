/**
  ******************************************************************
  * @file    bsp_lcd.c
  * @author  fire
  * @version V2.0
  * @date    2018-xx-xx
  * @brief   lcdӦ�ú����ӿ�
  ******************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  i.MXRT1052������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************
  */
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"  
#include "fsl_elcdif.h" 
#include "fsl_clock.h"
#include "fsl_pxp.h"

	
#include "pad_config.h"  
#include "bsp_lcd.h" 

//awtk
#include "base/g2d.h"
#include "base/idle.h"
#include "base/timer.h"
#include "main_loop/main_loop_simple.h"
#include "tkc/mem.h"
#include "base/lcd.h"
#include "lcd/lcd_mem_bgr565.h"
#include "lcd/lcd_mem_rgba8888.h"
    

/*******************************************************************************
 * ����
 ******************************************************************************/

/* ֡�жϱ�־ */
volatile bool s_frameDone = false;

/* ֡����������ʹ��֡�жϲ���Ч */
__IO uint32_t s_frame_count = 0;

/* �Դ� */
AT_NONCACHEABLE_SECTION_ALIGN( pixel_t s_psBufferLcd[3][LCD_PIXEL_HEIGHT][LCD_PIXEL_WIDTH], FRAME_BUFFER_ALIGN);




/* ָ��ǰ���Դ棬�����ǵ�ַ��������32λ���� */
static uint32_t CurrentFrameBuffer = (uint32_t)s_psBufferLcd[0];

/*******************************************************************************
 * ��
 ******************************************************************************/
/* �������ž�ʹ��ͬ����PAD���� */
#define LCD_PAD_CONFIG_DATA            (SRE_1_FAST_SLEW_RATE| \
                                        DSE_6_R0_6| \
                                        SPEED_3_MAX_200MHz| \
                                        ODE_0_OPEN_DRAIN_DISABLED| \
                                        PKE_1_PULL_KEEPER_ENABLED| \
                                        PUE_0_KEEPER_SELECTED| \
                                        PUS_0_100K_OHM_PULL_DOWN| \
                                        HYS_0_HYSTERESIS_DISABLED)   
    /* ����˵�� : */
    /* ת������: ת�����ʿ�
        ����ǿ��: R0/6 
        �������� : max(200MHz)
        ��©����: �ر� 
        ��/����������: ʹ��
        ��/������ѡ��: ������
        ����/����ѡ��: 100Kŷķ����(ѡ���˱�������������Ч)
        �ͻ�������: ��ֹ */
        
/*******************************************************************************
 * ����
 ******************************************************************************/
static void LCD_IOMUXC_MUX_Config(void);
static void LCD_IOMUXC_PAD_Config(void);
static void LCD_ELCDIF_Config(void);


/**
* @brief  ��ʼ��LCD���IOMUXC��MUX��������
* @param  ��
* @retval ��
*/
static void LCD_IOMUXC_MUX_Config(void)
{
    /* �������ž�������SION���� */
    /* ʱ������ź��� */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_00_LCD_CLK, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_01_LCD_ENABLE, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_02_LCD_HSYNC, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_03_LCD_VSYNC, 0U);
  
    /* RGB565�����ź��ߣ�
     DATA0~DATA4:B3~B7
     DATA5~DATA10:G2~G7
     DATA11~DATA15:R3~R7 */
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_04_LCD_DATA00, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_05_LCD_DATA01, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_06_LCD_DATA02, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_07_LCD_DATA03, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_08_LCD_DATA04, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_09_LCD_DATA05, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_10_LCD_DATA06, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_11_LCD_DATA07, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_12_LCD_DATA08, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_13_LCD_DATA09, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_14_LCD_DATA10, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B0_15_LCD_DATA11, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_00_LCD_DATA12, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_01_LCD_DATA13, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_02_LCD_DATA14, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_03_LCD_DATA15, 0U); 

		/* ��ʹ��24λ�����ź�����Ҫ��ʼ�����������ź��� */
#if LCD_BUS_24_BIT
		IOMUXC_SetPinMux(IOMUXC_GPIO_B1_04_LCD_DATA16, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_05_LCD_DATA17, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_06_LCD_DATA18, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_07_LCD_DATA19, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_08_LCD_DATA20, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_09_LCD_DATA21, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_10_LCD_DATA22, 0U);                                    
    IOMUXC_SetPinMux(IOMUXC_GPIO_B1_11_LCD_DATA23, 0U);                                    
#endif 
		
    /* LCD_BL��������ź��� */
    IOMUXC_SetPinMux(LCD_BL_IOMUXC, 0U); 
}


/**
* @brief  ��ʼ��LCD���IOMUXC��PAD��������
* @param  ��
* @retval ��
*/
static void LCD_IOMUXC_PAD_Config(void)
{  
    /* �������ž�ʹ��ͬ����PAD���� */
    /* ʱ������ź��� */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_00_LCD_CLK,LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_01_LCD_ENABLE, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_02_LCD_HSYNC, LCD_PAD_CONFIG_DATA);  
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_03_LCD_VSYNC, LCD_PAD_CONFIG_DATA); 

    /* RGB565�����ź��ߣ�
     DATA0~DATA4:B3~B7
     DATA5~DATA10:G2~G7
     DATA11~DATA15:R3~R7 */
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_04_LCD_DATA00, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_05_LCD_DATA01, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_06_LCD_DATA02, LCD_PAD_CONFIG_DATA);  
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_07_LCD_DATA03, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_08_LCD_DATA04, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_09_LCD_DATA05, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_10_LCD_DATA06, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_11_LCD_DATA07, LCD_PAD_CONFIG_DATA);  
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_12_LCD_DATA08, LCD_PAD_CONFIG_DATA);  
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_13_LCD_DATA09, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_14_LCD_DATA10, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B0_15_LCD_DATA11, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_00_LCD_DATA12, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_01_LCD_DATA13, LCD_PAD_CONFIG_DATA);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_02_LCD_DATA14, LCD_PAD_CONFIG_DATA); 
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_03_LCD_DATA15, LCD_PAD_CONFIG_DATA); 
		
		/* ��ʹ��24λ�����ź�����Ҫ��ʼ�����������ź��� */
#if LCD_BUS_24_BIT
		IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_04_LCD_DATA16, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_05_LCD_DATA17, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_06_LCD_DATA18, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_07_LCD_DATA19, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_08_LCD_DATA20, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_09_LCD_DATA21, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_10_LCD_DATA22, LCD_PAD_CONFIG_DATA);                                    
    IOMUXC_SetPinConfig(IOMUXC_GPIO_B1_11_LCD_DATA23, LCD_PAD_CONFIG_DATA);                                    
#endif     
    /* LCD_BL��������ź��� */
    IOMUXC_SetPinConfig(LCD_BL_IOMUXC, LCD_PAD_CONFIG_DATA);
}

/**
* @brief  ��ʼ��ELCDIF����
* @param  ��
* @retval ��
*/
static void LCD_ELCDIF_Config(void)
{	
    const elcdif_rgb_mode_config_t config = {
        .panelWidth = LCD_PIXEL_WIDTH,
        .panelHeight = LCD_PIXEL_HEIGHT,
        .hsw = LCD_HSW,
        .hfp = LCD_HFP,
        .hbp = LCD_HBP,
        .vsw = LCD_VSW,
        .vfp = LCD_VFP,
        .vbp = LCD_VBP,
        .polarityFlags =  LCD_POLARITY_FLAGS,													
        .bufferAddr = (uint32_t)s_psBufferLcd[0],
        .pixelFormat = ELCDIF_PIXEL_FORMAT,
        .dataBus = LCD_DATA_BUS_WIDTH,
    };
 
  ELCDIF_RgbModeInit(LCDIF, &config);
  ELCDIF_RgbModeStart(LCDIF);
}



/**
* @brief  ��ʼ��ELCDIFʹ�õ�ʱ��
* @param  ��
* @retval ��
*/
void LCD_InitClock(void)
{
    /*
     * Ҫ��֡�����ó�60Hz����������ʱ��Ƶ��Ϊ:
     * ˮƽ����ʱ�Ӹ�����(LCD_IMG_WIDTH + LCD_HSW + LCD_HFP + LCD_HBP ) 
     * ��ֱ������(LCD_IMG_HEIGHT + LCD_VSW + LCD_VFP + LCD_VBP)
     * 
     * ����ʱ��Ƶ�ʣ�(800 + 1 + 22 + 46) * (480 + 1 + 22 + 23) * 60 = 27.4M.
     * ���������� LCDIF ����ʱ��Ƶ��Ϊ 27M.
     *	 LCD��֡����ʵ���Ϊ׼��
     */

    /*
     * ��ʼ�� Vedio PLL����PLL5
     * Video PLL ���Ƶ��Ϊ 
     * OSC24M * (loopDivider + (denominator / numerator)) / postDivider = 108MHz.
     */
    clock_video_pll_config_t config = {
        .loopDivider = 36, .postDivider = 8, .numerator = 0, .denominator = 0,
    };

    CLOCK_InitVideoPll(&config);

    /*
     * 000 derive clock from PLL2
     * 001 derive clock from PLL3 PFD3
     * 010 derive clock from PLL5
     * 011 derive clock from PLL2 PFD0
     * 100 derive clock from PLL2 PFD1
     * 101 derive clock from PLL3 PFD1
     */
    /* ѡ��Ϊvedio PLL����PLL5 */
    CLOCK_SetMux(kCLOCK_LcdifPreMux, 2);

    /* ����Ԥ��Ƶ */  
    CLOCK_SetDiv(kCLOCK_LcdifPreDiv, 1);

		/* ���÷�Ƶ */  
    CLOCK_SetDiv(kCLOCK_LcdifDiv, 1);
}

/**
* @brief  ��ʼ���������Ų�����
* @param  ��
* @retval ��
*/

/*
void LCD_BackLight_ON(void)
{    
    // ���⣬�ߵ�ƽ���� 
    gpio_pin_config_t config = {
      kGPIO_DigitalOutput, 
      1,
      kGPIO_NoIntmode
    };

    GPIO_PinInit(LCD_BL_GPIO, LCD_BL_GPIO_PIN, &config);
}
*/


/**
* @brief  ��ʼ��Һ����
* @param  enableInterrupt ���Ƿ�ʹ���ж�
*		@arg LCD_INTERRUPT_DISABLE ��ʹ��
*		@arg LCD_INTERRUPT_ENABLE  ʹ��
* @retval ��
*/
void fLCD_Init(bool enableInterrupt)
{
#if LCD_RGB_888	
	/* 
  * ����������LCD read_qos �� write_qos �Ĵ�����֧������ֵ�ķ�ΧΪ0x0-0xF��
  * �˴�����qosΪ0xF���ֵ��
	*	Qos��
  * The Quality of Service (QoS) tidemark value represents the maximum
	*	permitted number of active transactions before the QoS mechanism is
	*	activated��
	*  ��ϸ˵����
	* ��IMXRT1050RM�����ο��ֲᣩ���½ڡ�Network Interconnect Bus System (NIC-301)��
	* ����CoreLink  Network Interconnect (NIC-301)Technical Reference Manua r2p3��
	* @note 
  *  ����˵�������LCDʹ��RT1052�ڲ����ߵĴ�������������
	*  ����800*480@XRGB8888@60Hz����ʾ����Ҫ�������ã�
  *  ����800*480@RGB565@60Hz����ʾ����Ҫ���ã�����Ĭ�ϼ��ɣ��Ƽ���
	*/
  
  *((uint32_t *)0x41044100) = 0x0000000f;
  *((uint32_t *)0x41044104) = 0x0000000f;
        
#endif
	
	/* ��ʼ��eLCDIF���š�ʱ�� ��ģʽ�������Լ��ж�*/
  LCD_IOMUXC_MUX_Config();
  LCD_IOMUXC_PAD_Config();
  LCD_InitClock();
  LCD_ELCDIF_Config();
  LCD_BackLight_ON();
  
  if(enableInterrupt)
  {
    LCD_InterruptConfig();
  }
  
}

/***************************�ж����******************************/
/**
* @brief  ����ELCDIF�ж�
* @param  ��
* @retval ��
*/
void LCD_InterruptConfig(void)
{
  /* ʹ���ж� */
  EnableIRQ(LCDIF_IRQn);
   
  /* ����ELCDIFΪCurFrameDoneInterrupt�ж� */
  ELCDIF_EnableInterrupts(LCDIF, kELCDIF_CurFrameDoneInterruptEnable);
  
}

static uint8_t* next_fb = NULL;
static uint8_t* online_fb = NULL;

//����ΪAWTK�е���ֲ
ret_t lcd_rt1052_begin_frame(lcd_t* lcd, rect_t* dirty_rect) {
  if (lcd_is_swappable(lcd)) {
    uint32_t i = 0;
    static uint32_t  countt;
    countt++;
    lcd_mem_t* mem = (lcd_mem_t*)lcd;

    mem->next_fb = NULL;		
    mem->online_fb = NULL;
    mem->offline_fb = NULL;
    
    
    for (i = 0; i < ARRAY_SIZE(s_psBufferLcd); i++) {
      uint8_t* iter = (uint8_t*)s_psBufferLcd[i];
      if (iter != online_fb && iter != next_fb) {
        mem->offline_fb = iter;
        break;
      }
    }
    
      s_frame_count++;
    
  }

  return RET_OK;
}

ret_t lcd_rt1052_swap(lcd_t* lcd) {
  lcd_mem_t* mem = (lcd_mem_t*)lcd;

  if(next_fb==NULL){
     next_fb = mem->offline_fb;
     ELCDIF_SetNextBufferAddr(LCDIF, (uint32_t)next_fb);
  }

  return RET_OK;
}


lcd_t* rt1052_create_lcd(wh_t w, wh_t h) {
  lcd_t* lcd = NULL;

#ifdef USE_THREE_FB
  lcd = lcd_mem_bgr565_create_three_fb(w, h, (uint8_t*)s_psBufferLcd[0], (uint8_t*)s_psBufferLcd[1], (uint8_t*)s_psBufferLcd[2] );
  lcd->swap = lcd_rt1052_swap;
  lcd->begin_frame = lcd_rt1052_begin_frame;
#else
  lcd = lcd_mem_bgr565_create_double_fb(w, h, (uint8_t*)s_psBufferLcd[0], (uint8_t*)s_psBufferLcd[1] );
#endif
  
  
  
  
  return lcd;
}

/**
* @brief  ELCDIF�жϷ�����
* @param  ��
* @retval ��---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
void LCDIF_IRQHandler(void)
{
    uint32_t intStatus;
static uint8_t* online_temp_fb = NULL;

    intStatus = ELCDIF_GetInterruptStatus(LCDIF);
    ELCDIF_ClearInterruptStatus(LCDIF, intStatus);
    
    if (intStatus & kELCDIF_CurFrameDone) {
      if (next_fb != NULL) {
        online_fb  = next_fb;
        next_fb = NULL;
      }
    }
    
    /* ���²�����Ϊ ARM �Ŀ���838869��ӵ�, �ô���Ӱ�� Cortex-M4, Cortex-M4F�ںˣ� �����洢�����ص��쳣�����·��ز������ܻ�ָ�������ж� CM7����Ӱ�죬�˴������ô��� */  
#if defined __CORTEX_M && (__CORTEX_M == 4U)
    __DSB();
#endif
}