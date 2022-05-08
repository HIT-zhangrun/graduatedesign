/*
 * oled_128x32.h
 *
 *  Created on: May 7, 2022
 *      Author: zhangrun
 */

#ifndef OLED_128X32_H_
#define OLED_128X32_H_

#include "i2c.h"
#include "font_lib.h"

#define OLED_ADDR       0x78//OLED IIC 地址

#define SEND_CMD        0x00//表示发送指令
#define SEND_DATA       0x40//表示发送数据

#define OLED_WIDTH      128 //OLED宽度128像素
#define OLED_LENGTH     32  //OLED高度32像素
#define OLED_PAGE       4   //OLED的页数
#define OLED_PAGE_PIX   8   //OLED每页纵向的像素点

#define OLED_BOOL_Replace ((uint8_t)0x00)  //替换
#define OLED_BOOL_ADD ((uint8_t)0x01)      //加
#define OLED_BOOL_Subtract ((uint8_t)0x02) //减


HAL_StatusTypeDef oled_write_cmd(uint8_t cmd);
HAL_StatusTypeDef oled_write_data(uint8_t data);
void oled_init(void);
void oled_fill(uint8_t data);
void oled_set_vertical_pos(uint8_t x_start, uint8_t page_start, uint8_t page_end);
void oled_area_refresh(uint8_t x_start, uint8_t x_end);
void oled_refresh();
uint8_t oled_draw_bmp(uint8_t pos_x, uint8_t pos_y, uint8_t width, uint8_t length, uint8_t *data);
void oled_draw_column(uint8_t pos_x, uint8_t pos_y, uint8_t *data, uint8_t length);
void buf_transform(uint8_t *buf, uint8_t *data, uint8_t offset, uint8_t page_num);


#endif /* OLED_128X32_H_ */
