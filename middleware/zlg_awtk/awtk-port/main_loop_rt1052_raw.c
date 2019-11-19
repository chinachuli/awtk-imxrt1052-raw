/**
 * file:   main_loop_stm32_raw.c
 * author: li xianjing <xianjimli@hotmail.com>
 * brief:  main loop for stm32
 *
 * copyright (c) 2018 - 2018 Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * license file for more details.
 *
 */

/**
 * history:
 * ================================================================
 * 2018-05-11 li xianjing <xianjimli@hotmail.com> created
 *
 */


#include "base/g2d.h"
#include "base/idle.h"
#include "base/timer.h"
#include "main_loop/main_loop_simple.h"
#include "bsp_i2c_touch.h"
#include "para.h"

extern void GTP_TouchProcess(void);

uint8_t platform_disaptch_input(main_loop_t* loop) {
      
  GTP_TouchProcess();
  if(StructTouchInfo.state>0) {//触摸中断中有按下后有置位
    main_loop_post_pointer_event(loop, StructTouchInfo.state-1, StructTouchInfo.x_input, StructTouchInfo.y_input);//不触摸时都进
    StructTouchInfo.state=0;
  }

  return 0;
}


extern lcd_t* rt1052_create_lcd(wh_t w, wh_t h);

lcd_t* platform_create_lcd(wh_t w, wh_t h) {
  return rt1052_create_lcd(w, h);
}

#include "main_loop/main_loop_raw.inc"
