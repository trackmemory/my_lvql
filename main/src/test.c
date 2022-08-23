#include "../../lvgl/lvgl.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../../lvgl/examples/lv_examples.h"
#include "../../lv_examples/lv_demo.h"
#include "my.h";
lv_obj_t *  create_imgbtn(lv_obj_t * parent,char text[],int file_num)
{
    LV_IMG_DECLARE(img_mid);

    static lv_style_t style_pr;
    lv_style_init(&style_pr);
    lv_style_set_img_recolor_opa(&style_pr, LV_OPA_30);
    lv_style_set_img_recolor(&style_pr, lv_color_black());

    /*Create an image button*/
    lv_obj_t * imgbtn = lv_imgbtn_create(parent);
    lv_obj_set_width(imgbtn,50);
    lv_imgbtn_set_src(imgbtn, LV_IMGBTN_STATE_RELEASED, 0, &img_mid, 0);
    lv_obj_add_style(imgbtn, &style_pr, LV_STATE_PRESSED);


    lv_obj_align(imgbtn, LV_ALIGN_OUT_LEFT_TOP, file_num*60, 0);

    /*Create a label on the image button*/
    lv_obj_t * label = lv_label_create(parent);
    lv_obj_set_style_text_font(label,&lv_font_montserrat_12,0);
    lv_label_set_text(label,text);
    lv_obj_align(label, LV_ALIGN_OUT_LEFT_TOP, (50-strlen(text)*7)/2, 35);
    file_num++;

    lv_obj_t * name = lv_label_create(imgbtn);
    lv_label_set_text(name,text);
    lv_obj_set_width(name,0);
    return imgbtn;
}

static void delete_handler(lv_event_t * e){
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", lv_obj_get_child_id(obj));
    lv_obj_del(lv_obj_get_parent(lv_obj_get_parent(obj)));
}
static void event_handler(lv_event_t * e)

{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", lv_obj_get_child_id(obj));

}

lv_obj_t * win_add_btn(lv_obj_t * win, const void * icon, lv_coord_t btn_w,lv_obj_t * text[])
{
    lv_obj_t * header = lv_win_get_header(win);
    lv_obj_set_style_bg_color(header,lv_color_white(),0);
    lv_obj_t * btn = lv_btn_create(header);
    lv_obj_set_size(btn, btn_w, LV_PCT(100));
    lv_obj_set_style_bg_color(btn,lv_color_white(),0);
    lv_obj_set_style_text_color(btn,lv_color_black(),0);
    if (icon==NULL){
        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text(label, text);
        lv_obj_center(label);
    }
    else{
        lv_obj_t * img = lv_img_create(btn);
        lv_img_set_src(img, icon);
        lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
    }

    return btn;
}
lv_obj_t * create_win(char text[]){
    lv_obj_t * win = lv_win_create(lv_scr_act(), 40);
    lv_obj_t * header = lv_win_get_header(win);
    lv_obj_set_style_border_width(header,1,0);
    lv_obj_t * cont = lv_win_get_content(win);
    lv_obj_set_style_bg_color(cont,lv_color_make(0xff,0xff,0xff),0);
    lv_obj_t * btn = win_add_btn(win, NULL, 40,"Close");

    lv_obj_t * white_space = lv_label_create(header);
    lv_label_set_text(white_space," ");
    lv_obj_set_width(white_space,280);
    lv_obj_t * title = lv_label_create(header);
    lv_label_set_text(title,text);
    lv_obj_set_flex_grow(title, 1);

    lv_obj_add_event_cb(btn, delete_handler, LV_EVENT_CLICKED, NULL);
    return cont;
}
static void event_handler_1(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", lv_obj_get_child_id(obj));
    lv_obj_t * cont = create_win(lv_label_get_text(lv_obj_get_child(obj,0)));
    lv_obj_t * btn = create_imgbtn(cont,"button",0);
}
    
static void event_handler_3(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", lv_obj_get_child_id(obj));
    lv_obj_t * win = lv_win_create(lv_scr_act(), 0);
    lv_obj_t * cont = create_win("");
    lv_demo_music();
}


void lv_create(lv_obj_t * parent){
    lv_obj_t * win = lv_win_create(parent, 40);
    lv_obj_t * header = lv_win_get_header(win);
    lv_obj_set_style_border_width(header,1,0);
    lv_obj_t * btn;
    btn = win_add_btn(win, NULL, 40,"File");
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

    // lv_win_add_title(win, "Main page");

    btn = win_add_btn(win, NULL, 40,"Edit");
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

    lv_win_add_title(win,"");


    myclock(win);


    
    lv_obj_t * cont = lv_win_get_content(win);  /*Content can be added here*/
    lv_obj_set_style_bg_color(cont,lv_color_make(0xCC,0xD5,0xE4),0);
    lv_obj_t * label;

    lv_obj_t * btn1 = create_imgbtn(cont,"new window",0);
    lv_obj_add_event_cb(btn1, event_handler_1, LV_EVENT_SHORT_CLICKED, NULL);

    lv_obj_t * btn3 = lv_btn_create(cont);
    lv_obj_add_event_cb(btn3, event_handler_3, LV_EVENT_CLICKED, NULL);
    lv_obj_align(btn3, LV_ALIGN_CENTER, 0, 40);
    label = lv_label_create(btn3);
    lv_label_set_text(label, "Music");
    lv_obj_center(label);
}
void my(void)
{
    lv_create(lv_scr_act());
    
}
