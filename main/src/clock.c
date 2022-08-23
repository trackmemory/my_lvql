#include "../../lvgl/lvgl.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../../lvgl/examples/lv_examples.h"
#include "../../lv_examples/lv_demo.h"
#include "my.h"
static lv_obj_t * time_label;
static lv_obj_t * hour_label;
static lv_obj_t * min_label;
static lv_obj_t * sec_label;
static int hour_set=-1;
static int min_set=-1;
static int sec_set=-1;
static int dropdown_w=30;
void *create_time(lv_obj_t * clock_btn){
    while(1){
        time_t tmpcal_ptr;
        time(&tmpcal_ptr);
        lv_label_set_text(time_label, ctime(&tmpcal_ptr));  
        if(hour_set!=-1){
            char hour_str[3]="";
            strncpy(hour_str,ctime(&tmpcal_ptr)+11,2);
            char min_str[3]="";
            strncpy(min_str,ctime(&tmpcal_ptr)+14,2);
            char sec_str[3]="";
            strncpy(sec_str,ctime(&tmpcal_ptr)+17,2);
            int hour;
            sscanf(hour_str, "%d", &hour);
            int min;
            sscanf(min_str, "%d", &min);
            int sec;
            sscanf(sec_str, "%d", &sec);
            if(hour==hour_set && min==min_set && sec==sec_set){
                hour_set=-1;
                lv_obj_set_style_bg_color(clock_btn,lv_color_white(),0);
                static const char * btns[] = {"", "", ""};
                lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Hello", "Time arrive.", btns, true);
                lv_obj_add_event_cb(mbox1, NULL, LV_EVENT_VALUE_CHANGED, NULL);
                lv_obj_center(mbox1);
            }
        }
        sleep(1);
    }
}
static void dropdown_event(lv_event_t * e){
    lv_obj_t * obj = lv_event_get_target(e);
    lv_obj_t * label = lv_obj_get_child(obj,0);
    char buff[2]="";
    sprintf(buff,"%d",lv_dropdown_get_selected(obj));
    lv_label_set_text(label,buff);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, -5);
}

static void clock_event(lv_event_t * e){
    lv_obj_t * obj = lv_event_get_target(e);
    static const char * btns[] = {"", "", ""};
    if(hour_set==-1){
        sscanf(lv_label_get_text(hour_label), "%d", &hour_set);
        sscanf(lv_label_get_text(min_label), "%d", &min_set);
        sscanf(lv_label_get_text(sec_label), "%d", &sec_set);
        lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Hello", "Clock set.", btns, true);
        lv_obj_add_event_cb(mbox1, NULL, LV_EVENT_VALUE_CHANGED, NULL);
        lv_obj_center(mbox1);
        lv_obj_set_style_bg_color(obj,lv_color_make(0xF5,0xDE,0xB3),0);
    }
    else{
        hour_set=-1;
        lv_obj_t * mbox1 = lv_msgbox_create(NULL, "Hello", "Cancel clock.", btns, true);
        lv_obj_add_event_cb(mbox1, NULL, LV_EVENT_VALUE_CHANGED, NULL);
        lv_obj_center(mbox1);
        lv_obj_set_style_bg_color(obj,lv_color_white(),0);
    }
}
void myclock(lv_obj_t * win){
    lv_obj_t * header = lv_win_get_header(win);

    lv_obj_t * hour_dropdown = lv_dropdown_create(header);
    lv_obj_set_size(hour_dropdown, dropdown_w, LV_PCT(100));
    hour_label = lv_label_create(hour_dropdown);
    lv_label_set_text(hour_label,"0");
    lv_obj_align(hour_label, LV_ALIGN_TOP_MID, 0, -7);
    lv_dropdown_set_text(hour_dropdown,"");
    lv_dropdown_set_symbol(hour_dropdown, NULL);
    char hour_options[72]="";
    for(int i=0;i<24;i=i+1){
        char temp[3]="";
        sprintf(temp,"%d",i);
        strcat(temp,"\n");
        strcat(hour_options,temp);
    }
    lv_dropdown_set_options(hour_dropdown,hour_options);
    lv_obj_add_event_cb(hour_dropdown,dropdown_event,LV_EVENT_VALUE_CHANGED,NULL);

    lv_label_set_text(lv_label_create(header),":");

    lv_obj_t * min_dropdown = lv_dropdown_create(header);
    lv_obj_set_size(min_dropdown, dropdown_w, LV_PCT(100));
    min_label = lv_label_create(min_dropdown);
    lv_label_set_text(min_label,"0");
    lv_obj_align(min_label, LV_ALIGN_TOP_MID, 0, -7);
    lv_dropdown_set_text(min_dropdown,"");
    lv_dropdown_set_symbol(min_dropdown, NULL);
    char min_options[180]="";
    for(int i=0;i<60;i=i+1){
        char temp[3]="";
        sprintf(temp,"%d",i);
        strcat(temp,"\n");
        strcat(min_options,temp);
    }
    lv_dropdown_set_options(min_dropdown,min_options);
    lv_obj_add_event_cb(min_dropdown,dropdown_event,LV_EVENT_VALUE_CHANGED,NULL);

    lv_label_set_text(lv_label_create(header),":");

    lv_obj_t * sec_dropdown = lv_dropdown_create(header);
    lv_obj_set_size(sec_dropdown, dropdown_w, LV_PCT(100));
    sec_label = lv_label_create(sec_dropdown);
    lv_label_set_text(sec_label,"0");
    lv_obj_align(sec_label, LV_ALIGN_TOP_MID, 0, -7);
    lv_dropdown_set_text(sec_dropdown,"");
    lv_dropdown_set_symbol(sec_dropdown, NULL);
    char sec_options[180]="";
    for(int i=0;i<60;i=i+1){
        char temp[3]="";
        sprintf(temp,"%d",i);
        strcat(temp,"\n");
        strcat(sec_options,temp);
    }
    lv_dropdown_set_options(sec_dropdown,sec_options);
    lv_obj_add_event_cb(sec_dropdown,dropdown_event,LV_EVENT_VALUE_CHANGED,NULL);

    lv_obj_t * clock_btn = win_add_btn(win, NULL, 40,"Clock");
    lv_obj_add_event_cb(clock_btn, clock_event, LV_EVENT_CLICKED, NULL);

    lv_obj_t * time_label_b = lv_btn_create(header);
    time_label = lv_label_create(time_label_b);
    lv_obj_align(time_label, LV_ALIGN_CENTER, 0, 7);
    lv_obj_set_height(time_label_b,LV_PCT(100));
    lv_obj_set_style_bg_color(time_label_b,lv_color_white(),0);
    lv_obj_set_style_text_color(time_label_b,lv_color_black(),0);

    pthread_t t;
    pthread_create(&t, NULL, create_time, clock_btn);
}