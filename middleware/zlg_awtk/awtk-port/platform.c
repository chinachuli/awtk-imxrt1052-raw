/**
 * file:   platform.c
 * author: li xianjing <xianjimli@hotmail.com>
 * brief:  platform dependent function of stm32
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
 * 2018-05-12 li xianjing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "base/timer.h"
#include "tkc/platform.h"
#include "bsp_systick.h"
#include "tkc/mem.h"
   
/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"

uint64_t get_time_ms64() {
 // return HAL_GetTick();
  return xTaskGetTickCount();
}

void sleep_ms(uint32_t ms) {
  vTaskDelay(ms);
 // delay_ms(ms);
}


ret_t platform_prepare(void) {

  return RET_OK;
}
