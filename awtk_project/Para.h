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
	uint8_t state;	    //0:未按下  //1：up    //2:down
	uint16_t x_input;   /*控制标志*/
	uint16_t y_input;   /*读写数据的长度			*/
}StructTouch;  

PARA_EXT StructTouch StructTouchInfo; 
//PARA_EXT StructCommandInfo CommandInfo[8];//开关信息

#endif 
