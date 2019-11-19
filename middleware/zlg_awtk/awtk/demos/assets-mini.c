#include "awtk.h"
#include "base/assets_manager.h"
#ifndef WITH_FS_RES
#include "assets/default/inc/fonts/default.data"
#include "assets/default/inc/images/bricks.data"
#include "assets/default/inc/images/checked.data"
#include "assets/default/inc/images/dialog_title.data"
#include "assets/default/inc/images/earth.data"
#include "assets/default/inc/images/green_btn_n.data"
#include "assets/default/inc/images/green_btn_o.data"
#include "assets/default/inc/images/green_btn_p.data"
#include "assets/default/inc/images/info.data"
#include "assets/default/inc/images/left_off.data"
#include "assets/default/inc/images/left_on.data"
#include "assets/default/inc/images/middle_off.data"
#include "assets/default/inc/images/middle_on.data"
#include "assets/default/inc/images/muted.data"
#include "assets/default/inc/images/question.data"
#include "assets/default/inc/images/radio_checked.data"
#include "assets/default/inc/images/radio_unchecked.data"
#include "assets/default/inc/images/red_btn_n.data"
#include "assets/default/inc/images/red_btn_o.data"
#include "assets/default/inc/images/red_btn_p.data"
#include "assets/default/inc/images/right_off.data"
#include "assets/default/inc/images/right_on.data"
#include "assets/default/inc/images/slider_bg.data"
#include "assets/default/inc/images/slider_drag.data"
#include "assets/default/inc/images/slider_drag_o.data"
#include "assets/default/inc/images/slider_drag_p.data"
#include "assets/default/inc/images/slider_fg.data"
#include "assets/default/inc/images/slider_v_bg.data"
#include "assets/default/inc/images/slider_v_fg.data"
#include "assets/default/inc/images/unchecked.data"
#include "assets/default/inc/images/unmuted.data"
#include "assets/default/inc/images/warn.data"
#include "assets/default/inc/styles/default.data"
#endif

ret_t assets_init(void) {
  assets_manager_t* am = assets_manager();

#ifdef WITH_FS_RES
  assets_manager_load(am, ASSET_TYPE_THEME, "default");
  assets_manager_load(am, ASSET_TYPE_FONT, "default_ttf");
#else
  assets_manager_add(am, font_default);
  assets_manager_add(am, image_bricks);
  assets_manager_add(am, image_checked);
  assets_manager_add(am, image_dialog_title);
  assets_manager_add(am, image_earth);
  assets_manager_add(am, image_green_btn_n);
  assets_manager_add(am, image_green_btn_o);
  assets_manager_add(am, image_green_btn_p);
  assets_manager_add(am, image_info);
  assets_manager_add(am, image_left_off);
  assets_manager_add(am, image_left_on);
  assets_manager_add(am, image_middle_off);
  assets_manager_add(am, image_middle_on);
  assets_manager_add(am, image_muted);
  assets_manager_add(am, image_question);
  assets_manager_add(am, image_radio_checked);
  assets_manager_add(am, image_radio_unchecked);
  assets_manager_add(am, image_red_btn_n);
  assets_manager_add(am, image_red_btn_o);
  assets_manager_add(am, image_red_btn_p);
  assets_manager_add(am, image_right_off);
  assets_manager_add(am, image_right_on);
  assets_manager_add(am, image_slider_bg);
  assets_manager_add(am, image_slider_drag);
  assets_manager_add(am, image_slider_drag_o);
  assets_manager_add(am, image_slider_drag_p);
  assets_manager_add(am, image_slider_fg);
  assets_manager_add(am, image_slider_v_bg);
  assets_manager_add(am, image_slider_v_fg);
  assets_manager_add(am, image_unchecked);
  assets_manager_add(am, image_unmuted);
  assets_manager_add(am, image_warn);
  assets_manager_add(am, style_default);
#endif

  tk_init_assets();
  return RET_OK;
}
