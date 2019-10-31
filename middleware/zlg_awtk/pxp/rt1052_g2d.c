
#include "driver/pxp/awbl_imx1050_pxp.h"
#include "base/g2d.h"
#include "stdint.h"
//#include "aw_cache.h"
//#include "aw_mem.h"
//#include "aw_emwin_fb.h"
#include "base/pixel.h"
#include "driver/pxp/awbl_imx1050_pxp.h"
#include "driver/pxp/imx1050_pxp_regs.h"



ret_t g2d_fill_rect(bitmap_t* fb, rect_t* dst, color_t c)
{

    //��ʱ���ã�Ч�ʲ������ʵ��
    return RET_NOT_IMPL;
/*
    return_value_if_fail(fb != NULL && dst != NULL, RET_BAD_PARAMS);
    return_value_if_fail(c.rgba.a > 0xf8, RET_NOT_IMPL);
    return_value_if_fail(fb->format == BITMAP_FMT_BGR565, RET_NOT_IMPL);
    return_value_if_fail(dst->w != 0 && dst->h != 0, RET_BAD_PARAMS);

    pxp_output_buffer_config_t pxp_output_config = {0};
    pxp_ps_buffer_config_t     ps_buffer_config = {0};

    uint32_t out_addr = 0;
    uint8_t  out_pixsize = 2;

    // ��λpxp 
    pxp_hard_reset();

    // ����PS��ʼ��ַ 
    out_addr = (uint32_t)fb->data + (fb->w * dst->y + dst->x) * out_pixsize;
    uint32_t fb_flush_size = ((dst->h - 1) * fb->w + dst->w) * out_pixsize;
    aw_cache_flush((void *)out_addr,  fb_flush_size);

    // ����������� 
    pxp_output_config.pixel_format = kPXP_OutputPixelFormatRGB565;
    pxp_output_config.interlaced_mode = kPXP_OutputProgressive;
    pxp_output_config.buffer0_addr = out_addr;
    pxp_output_config.pitch_bytes = fb->w * out_pixsize;
    pxp_output_config.width  = dst->w;
    pxp_output_config.height = dst->h;
    pxp_set_output_buffer_config(&pxp_output_config);

    // ����PS buffer 
    ps_buffer_config.pixel_format = kPXP_PsPixelFormatRGB888;
    ps_buffer_config.buffer_addr  = out_addr;
    ps_buffer_config.pitch_bytes  = fb->w * out_pixsize;
    pxp_set_process_surface_buffer_config(&ps_buffer_config);
    pxp_set_process_surface_position(0, 0, dst->w - 1, dst->h - 1);
    pxp_set_alpha_surface_position(1, 1, 0, 0);

    pxp_set_process_surface_color_key(0, 0xFFFFFF);

    // ����������ɫ 
    pxp_set_process_surface_back_ground_color((uint32_t)c.color & (0xFFFFFF));
    pxp_start();

    // Wait for process complete. 
    pxp_complete_status_sync();
    aw_cache_invalidate((void *)out_addr, fb_flush_size);*/

    return RET_OK;
}


ret_t g2d_copy_image(bitmap_t* fb, bitmap_t* img, rect_t* src, xy_t dx, xy_t dy)
{

    //��ʱ���ã�Ч�ʲ������ʵ��
    return RET_NOT_IMPL;
/*
    return_value_if_fail(fb != NULL && img != NULL && src != NULL, RET_BAD_PARAMS);
    return_value_if_fail(fb->format == img->format, RET_BAD_PARAMS);
    return_value_if_fail(src->w != 0 && src->h != 0, RET_BAD_PARAMS);
    return_value_if_fail(fb->format == BITMAP_FMT_BGR565 || fb->format == BITMAP_FMT_BGR888,
                         RET_NOT_IMPL);

    pxp_output_buffer_config_t pxp_output_config = {0};
    pxp_ps_buffer_config_t     ps_buffer_config = {0};

    uint32_t out_addr, ps_addr;
    uint16_t ps_format, out_format;
    uint32_t out_pixsize, ps_pixsize;

    if (fb->format == BITMAP_FMT_BGR565) {
        out_pixsize = 2;
        ps_pixsize = 2;
        out_format = kPXP_OutputPixelFormatRGB565;
        ps_format = kPXP_PsPixelFormatRGB565;
    }  else {
        out_pixsize = 4;
        ps_pixsize = 4;
        out_format = kPXP_OutputPixelFormatRGB888;
        ps_format = kPXP_PsPixelFormatRGB888;
    }

    // ��λpxp 
    pxp_hard_reset();

    // ��������������ʼ��ַ 
    out_addr = (uint32_t)fb->data + (fb->w * dy + dx) * out_pixsize;
    uint32_t fb_flush_size = ((src->h - 1) * fb->w + src->w) * out_pixsize;
    aw_cache_flush((void *)out_addr, fb_flush_size);

    // ����PS��ʼ��ַ 
    ps_addr = ((uint32_t)img->data + ps_pixsize * (img->w * src->y + src->x));
    uint32_t img_flush_size = ((src->h - 1) * img->w + src->w) * ps_pixsize;
    aw_cache_flush((void *)ps_addr, img_flush_size);

    // Output configure. 
    pxp_output_config.pixel_format = out_format;
    pxp_output_config.interlaced_mode = kPXP_OutputProgressive;
    pxp_output_config.buffer0_addr = out_addr;
    pxp_output_config.pitch_bytes = fb->w * out_pixsize;
    pxp_output_config.width  = src->w;
    pxp_output_config.height = src->h;
    pxp_set_output_buffer_config(&pxp_output_config);

    // PS configure. 
    ps_buffer_config.pixel_format = ps_format;
    ps_buffer_config.buffer_addr  = (uint32_t)ps_addr;
    ps_buffer_config.pitch_bytes  = img->w * ps_pixsize,

    pxp_set_process_surface_buffer_config(&ps_buffer_config);
    pxp_set_process_surface_position(0, 0, src->w - 1, src->h - 1);
    pxp_set_alpha_surface_position(1, 1, 0, 0);
    pxp_enable_csc1(0);
    pxp_start();

    // Wait for process complete. 
    pxp_complete_status_sync();
    aw_cache_invalidate((void *)out_addr, fb_flush_size);*/

    return RET_OK;
}


ret_t g2d_blend_image(bitmap_t* fb, bitmap_t* img, rect_t* dst, rect_t* src, uint8_t global_alpha)
{
    return RET_NOT_IMPL;
/*
    return_value_if_fail(fb != NULL && fb->data != NULL, RET_BAD_PARAMS);
    return_value_if_fail(img != NULL && img->data != NULL && src != NULL && dst != NULL,
                         RET_BAD_PARAMS);
    return_value_if_fail(fb->format == BITMAP_FMT_BGR565 || fb->format == BITMAP_FMT_BGRA8888,
                         RET_BAD_PARAMS);
    return_value_if_fail(img->format == BITMAP_FMT_BGR565 || img->format == BITMAP_FMT_BGRA8888,
                         RET_BAD_PARAMS);

    if (((src->w != dst->w) || (src->h != dst->h)) && (img->format == BITMAP_FMT_BGRA8888)) {
        return RET_NOT_IMPL;    //Ӳ����֧��BGRA8888���ݵ����� 
    }

    uint16_t as_format   = 0;
    uint16_t as_pixsize  = 0;
    uint16_t ps_format   = 0;
    uint16_t ps_pixsize  = 0;
    uint16_t out_format  = 0;
    uint16_t out_pixsize = 0;

    uint16_t as_x  = 0;
    uint16_t as_y  = 0;
    uint16_t as_w  = 0;
    uint32_t as_addr = 0;

    uint16_t ps_x  = 0;
    uint16_t ps_y  = 0;
    uint16_t ps_w  = 0;
    uint32_t ps_addr = 0;
    uint32_t out_addr = 0;

    uint8_t *p_scale_buf = NULL;

    pxp_output_buffer_config_t pxp_output_config = {0};
    pxp_ps_buffer_config_t     ps_buffer_config  = {0};

    if (img->format == BITMAP_FMT_BGR565) {
        as_pixsize = 2;
        as_format = kPXP_AsPixelFormatRGB565;
        ps_pixsize = 2;
        ps_format = kPXP_PsPixelFormatRGB565;

    } else {
        as_pixsize = 4;
        as_format = kPXP_AsPixelFormatARGB8888;
        ps_pixsize = 4;
        ps_format = kPXP_PsPixelFormatRGB888;
    }

    if (fb->format == BITMAP_FMT_BGR565) {
        out_pixsize = 2;
        out_format = kPXP_OutputPixelFormatRGB565;
    } else {
        out_pixsize = 4;
        out_format = kPXP_OutputPixelFormatRGB888;
    }

    as_x = src->x;
    as_y = src->y;
    as_w = img->w;

    // ����AS��ʼ��ַ 
    as_addr = ((uint32_t)img->data + as_pixsize * (as_w * as_y + as_x));
    uint32_t img_flush_size = ((src->h - 1) * img->w + src->w) * as_pixsize;
    aw_cache_flush((void *)as_addr, img_flush_size);

    // ��λpxp 
    pxp_hard_reset();

    // �ж��Ƿ���Ҫ���� 
    if ((src->w != dst->w) || (src->h != dst->h)) {

        ps_x = src->x;
        ps_y = src->y;
        ps_w = img->w;

        // ����һƬdstĿ����ͬ����Ļ���
        p_scale_buf = (uint8_t *)aw_mem_align(dst->w * dst->h * out_pixsize, 32);
        return_value_if_fail(p_scale_buf != NULL, RET_FAIL);

        // ����PS��ʼ��ַ 
        ps_addr = ((uint32_t)img->data + ps_pixsize * (ps_w * ps_y + ps_x));

        // PS configure. 
        ps_buffer_config.pixel_format  = ps_format;
        ps_buffer_config.buffer_addr   = (uint32_t)ps_addr;
        ps_buffer_config.pitch_bytes   = ps_w * ps_pixsize;

        // ����PS buffer 
        pxp_set_process_surface_buffer_config(&ps_buffer_config);

        // ����AS 
        pxp_set_alpha_surface_position(0xFFFF, 0xFFFF, 0, 0);

        // Output config. 
        pxp_output_config.pixel_format = out_format;
        pxp_output_config.interlaced_mode = kPXP_OutputProgressive;
        pxp_output_config.buffer0_addr = (uint32_t) p_scale_buf;
        pxp_output_config.pitch_bytes = dst->w * out_pixsize;
        pxp_output_config.width  = dst->w;
        pxp_output_config.height = dst->h;

        pxp_set_output_buffer_config(&pxp_output_config);

        // Disable CSC1, it is enabled by default. 
        pxp_enable_csc1(0);

        // �������ŵ���������ͼ��ĳ�����  
        pxp_set_process_surface_scaler(src->w, src->h, dst->w, dst->h);

        // ����PSͼ�δ�СΪĿ�괰�ڵĴ�С 
        pxp_set_process_surface_position(0, 0, dst->w - 1, dst->h - 1);

        // ��ʼ���Ŵ��� 
        pxp_start();

        // Wait for process complete. 
        pxp_complete_status_sync();

        // ���ˣ����Ŵ����ͼ���Ѿ������p_scale_buf�������� ����ʱ���¸�ֵAS��ʼ��ַ�� ���ڽ�������blend��

        as_addr = (uint32_t)p_scale_buf;
        as_x = dst->x;
        as_y = dst->y;
        as_w = dst->w;

        as_format  = out_format;
        as_pixsize = out_pixsize;

        // ��λһ��PXP��ʹ���Ź���ʧЧ�������Ų���Ӱ���������blend 
        pxp_hard_reset();
        //aw_cache_invalidate((void *)p_scale_buf, dst->w * dst->h * out_pixsize);
    }

    uint32_t fb_flush_size = ((dst->h - 1) * fb->w + dst->w) * out_pixsize;

    // ���������������ʼ��ַ 
    out_addr = (uint32_t)fb->data + (fb->w * dst->y + dst->x) * out_pixsize;
    aw_cache_flush((void *)out_addr,  fb_flush_size);

    // BGR565 ����Ҫ��Ⱦ����� 
    if ((img->format == BITMAP_FMT_BGR565) && (global_alpha  > 0xfb)) {
        // PS configure. 
        ps_buffer_config.pixel_format  = ps_format;
        ps_buffer_config.buffer_addr   = (uint32_t)as_addr;
        ps_buffer_config.pitch_bytes   = as_w * ps_pixsize;

        pxp_set_process_surface_buffer_config(&ps_buffer_config);
        pxp_set_process_surface_position(0, 0, dst->w - 1,  dst->h - 1);
        pxp_set_alpha_surface_position(1, 1, 0, 0);

    } else {

        // PS configure. 
        ps_buffer_config.pixel_format  = out_format;
        ps_buffer_config.buffer_addr   = (uint32_t)out_addr;
        ps_buffer_config.pitch_bytes   = fb->w * out_pixsize;

        //����PS buffer 
        pxp_set_process_surface_buffer_config(&ps_buffer_config);

        // AS ���ò������� 
        pxp_as_buffer_config_t as_buffer_config = {
            .pixel_format = as_format,
            .buffer_addr  = (uint32_t)as_addr,
            .pitch_bytes  = as_w * as_pixsize,
        };

        // AS���� 
        pxp_set_alpha_surface_buffer_config(&as_buffer_config);

        // ����͸���ȵ�һЩ���� 
        pxp_as_blend_config_t as_blend_config = {
            .alpha = global_alpha,   // ����͸���� 
            .invert_alpha = 0,
            .alpha_mode = kPXP_AlphaMultiply,
            .rop_mode = kPXP_RopMergeAs        // �����ɫ 
        };
        pxp_set_alpha_surface_blend_config(&as_blend_config);

        // ����AS��λ�� 
        pxp_set_alpha_surface_position(0, 0, dst->w - 1, dst->h - 1);

        // ����PS��λ�� 
        pxp_set_process_surface_position(0, 0, dst->w - 1, dst->h - 1);
    }

    // Output config. 
    pxp_output_config.pixel_format = out_format;
    pxp_output_config.interlaced_mode = kPXP_OutputProgressive;
    pxp_output_config.buffer0_addr = (uint32_t)out_addr;
    pxp_output_config.buffer1_addr = 0;
    pxp_output_config.pitch_bytes = fb->w * out_pixsize;
    pxp_output_config.width  = dst->w;
    pxp_output_config.height = dst->h;

    pxp_set_output_buffer_config(&pxp_output_config);

    // Disable CSC1, it is enabled by default. 
    pxp_enable_csc1(0);

    // ��ʼblend 
    pxp_start();

    // Wait for process complete. 
    pxp_complete_status_sync();
    aw_cache_invalidate((void *)out_addr, fb_flush_size);

    // �ͷ��ڴ� 
    if (p_scale_buf != NULL) {
        aw_mem_free(p_scale_buf);
    }*/

    return RET_OK;
}




ret_t g2d_rotate_image(bitmap_t* fb, bitmap_t* img, rect_t* src, lcd_orientation_t o)
{
      return RET_NOT_IMPL;
  
 /*   assert(src->x >= 0);
    assert(src->y >= 0);
    assert(src->w >= 0);
    assert(src->h >= 0);

    //return RET_NOT_IMPL;

    return_value_if_fail(o == LCD_ORIENTATION_90, RET_NOT_IMPL);
    return_value_if_fail(fb != NULL && img != NULL && src != NULL, RET_BAD_PARAMS);
    return_value_if_fail(fb->format == img->format, RET_BAD_PARAMS);
    return_value_if_fail(fb->w == img->h && fb->h == img->w, RET_BAD_PARAMS);
    return_value_if_fail(fb->format == BITMAP_FMT_RGBA8888 || fb->format == BITMAP_FMT_BGR565,
                         RET_NOT_IMPL);
    return_value_if_fail(src->w != 0 && src->h != 0, RET_NOT_IMPL);

    uint16_t ps_format   = 0;
    uint16_t ps_pixsize  = 0;
    uint16_t out_format  = 0;
    uint16_t out_pixsize = 0;
    uint32_t ps_addr  = 0;
    uint32_t out_addr = 0;

    int32_t ps_x = 0;
    int32_t ps_y = 0;
    int32_t ps_w = 0;

    pxp_output_buffer_config_t pxp_output_config = {0};
    pxp_ps_buffer_config_t     ps_buffer_config = {0};

    if (img->format == BITMAP_FMT_BGR565) {
        ps_pixsize = 2;
        ps_format = kPXP_PsPixelFormatRGB565;
    } else {
        ps_pixsize = 4;
        ps_format = kPXP_PsPixelFormatRGB888;
    }

    if (fb->format == BITMAP_FMT_BGR565) {
        out_pixsize = 2;
        out_format = kPXP_OutputPixelFormatRGB565;
    } else {
        out_pixsize = 4;
        out_format = kPXP_OutputPixelFormatRGB888;
    }

    ps_x = src->x;
    ps_y = src->y;
    ps_w = img->w;

    // ����ͼ�εı߳�Ϊ8��������,������ת���о�� 
    int re   = src->h % 8;
    int tmp  = src->h ;
    int diff = 0;
    if (re != 0) {
       diff = 8 - re;
       tmp += diff;
       if (src->y + tmp > img->h) {
           return RET_NOT_IMPL;  // ���أ�ʹ�������ת 
       } else {
           src->h = tmp;
       }
    }
    re  = src->w % 8;
    tmp = src->w;
    if (re != 0) {
        diff = 8 - re;
        tmp  += diff;
        if (src->x + tmp > img->w) {
           return RET_NOT_IMPL;  // ���أ�ʹ�������ת 
       } else {
           src->w = tmp;
       }
    }

    int32_t targ_x, targ_y;

    targ_x = src->y;
    targ_y = fb->h - src->x - src->w;

    // ���������������ʼ��ַ 
    uint32_t fb_flush_size = ((src->w - 1) * fb->w + src->h) * out_pixsize;
    out_addr = (uint32_t)fb->data + (fb->w * targ_y + targ_x) * out_pixsize;
    aw_cache_flush((void *)out_addr,  fb_flush_size);

    // ����PS��ʼ��ַ 
    ps_addr = ((uint32_t)img->data) + (ps_y * ps_w + ps_x)* ps_pixsize ;
    uint32_t img_flush_size = ((src->h - 1) * img->w + src->w) * ps_pixsize;
    aw_cache_flush((void *)ps_addr, img_flush_size);

    // ��λpxp 
    pxp_hard_reset();

    // ����PS buffer 
    ps_buffer_config.pixel_format  = ps_format;
    ps_buffer_config.buffer_addr   = (uint32_t)ps_addr;
    ps_buffer_config.pitch_bytes   = ps_w * ps_pixsize;
    pxp_set_process_surface_buffer_config(&ps_buffer_config);
    pxp_set_process_surface_position(0,
                                     0,
                                     src->h - 1,
                                     src->w - 1);
    // ����AS 
    pxp_set_alpha_surface_position(1, 1, 0, 0);

    // Output config. 
    pxp_output_config.pixel_format = out_format;
    pxp_output_config.interlaced_mode = kPXP_OutputProgressive;
    pxp_output_config.buffer0_addr = (uint32_t) out_addr;
    pxp_output_config.pitch_bytes = fb->w * out_pixsize;
    pxp_output_config.width  = src->h;
    pxp_output_config.height = src->w;
    pxp_set_output_buffer_config(&pxp_output_config);

    // Disable CSC1, it is enabled by default 
    pxp_enable_csc1(0);

    // ��ת270��(��ת��������ʵ�ֵ���ת90�ȵĽ����һ��) 
    pxp_set_rotate_config(kPXP_RotateProcessSurface, kPXP_Rotate270, kPXP_FlipDisable);

    // ��ʼ��ת 
    pxp_start();

    // Wait for process complete. 
    pxp_complete_status_sync();
    aw_cache_invalidate((void *)out_addr, fb_flush_size);*/

    return RET_OK;
}

/* end of file */
