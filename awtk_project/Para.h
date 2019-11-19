#ifndef __PARA_H__
#define __PARA_H__

#ifdef   PARA_GLOBALS
#define  PARA_EXT 
#else
#define  PARA_EXT  extern 
#endif


#define LCD_WIDTH 800
#define LCD_HEIGHT 480



typedef struct Touch{
	uint8_t state;	    //0:δ����  //1��up    //2:down
	uint16_t x_input;   /*���Ʊ�־*/
	uint16_t y_input;   /*��д���ݵĳ���			*/
}StructTouch;  

PARA_EXT StructTouch StructTouchInfo; 
//PARA_EXT StructCommandInfo CommandInfo[8];//������Ϣ

#endif 
