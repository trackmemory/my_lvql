#ifndef MY_H
#define MY_H
#include "../../lvgl/lvgl.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../../lvgl/examples/lv_examples.h"
#include "../../lv_examples/lv_demo.h"

lv_obj_t * win_add_btn(lv_obj_t * win, const void * icon, lv_coord_t btn_w,lv_obj_t * text[]);
#endif 