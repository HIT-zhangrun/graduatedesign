/*
 * oled_128x32.c
 *
 *  Created on: May 7, 2022
 *      Author: zhangrun
 */

#include "oled_128x32.h"

static uint8_t oled_buff[4][128];   // 缓冲区
static uint8_t oled_buff_flag[128]; // 刷新标志

/**
 * @description: 发送指令至OLED
 * @param cmd   指令
 * @return      状态
 */
HAL_StatusTypeDef oled_write_cmd(uint8_t cmd)
{
    return HAL_I2C_Mem_Write(&hi2c1, OLED_ADDR, SEND_CMD, I2C_MEMADD_SIZE_8BIT, &cmd, sizeof(uint8_t), 0xff);
}

/**
 * @description: 发送数据至OLED
 * @param data  数据
 * @return      状态
 */
HAL_StatusTypeDef oled_write_data(uint8_t data)
{
    return HAL_I2C_Mem_Write(&hi2c1, OLED_ADDR, SEND_DATA, I2C_MEMADD_SIZE_8BIT, &data, sizeof(uint8_t), 0xff);
}

/**
 * @description:  以硬件I2C方式初始化OLED
 * @return {*}
 */
void oled_init(void)
{
    oled_write_cmd(0xae); //关闭显示器
    oled_write_cmd(0xa8); //设置多路复用比(1-64)
    oled_write_cmd(0x1f); //设定值128*64 0x3f 128*32 0x1f
    oled_write_cmd(0xda); //设置com引脚配置 set com pin configuartion
    oled_write_cmd(0x02); // 0x12 0.96 128*64 0x02 0.91 128*32
    oled_write_cmd(0x20); //设置内存寻址模式Set Memory Addressing Mode
    oled_write_cmd(0x01); // 00,水平寻址模式 01,垂直寻址模式 02,页面寻址模式(复位)
    oled_write_cmd(0x81); //设置对比度
    oled_write_cmd(0xff); //对比度,数值越大对比度越高
    oled_write_cmd(0xc8); //扫描方向 不上下翻转Com scan direction
    oled_write_cmd(0xa1); //设置段重新映射 不左右翻转set segment remap
    oled_write_cmd(0xd3); //设置显示偏移 set display offset
    oled_write_cmd(0x00); //
    oled_write_cmd(0xd5); //设置osc分区 set osc division
    oled_write_cmd(0x80); //
    oled_write_cmd(0xd8); //关闭区域颜色模式 set area color mode off
    oled_write_cmd(0x05); //
    oled_write_cmd(0xd9); //设置预充电期 Set Pre-Charge Period
    oled_write_cmd(0x11); //
    oled_write_cmd(0xdb); //设置vcomh set Vcomh
    oled_write_cmd(0x30); //
    oled_write_cmd(0x8d); //设置电源泵启用 set charge pump enable
    oled_write_cmd(0x14); //
    oled_write_cmd(0xa4); //设置全局显示  bit0，1白，0黑
    // oled_write_cmd(0xa7);  //反相显示
    oled_write_cmd(0xa6); //正常显示
    oled_fill(0x00);      //清屏
    oled_write_cmd(0xaf); //打开显示器
}

/**
 * @description: 清空缓存，并更新屏幕
 * @param data 全局写入的数据
 * @return {*}
 */
void oled_fill(uint8_t data)
{
    uint16_t i;
    oled_set_vertical_pos(0, 0, OLED_PAGE - 1);

    for (i = 0; i < 8 * OLED_WIDTH; i++)
    {
        oled_write_data(data);
    }
    //更新缓存
    memset(oled_buff, data, sizeof(oled_buff));
    memset(oled_buff_flag, 0, sizeof(oled_buff_flag));
}

/**
 * @description: 设置垂直寻址模式的坐标
 * @param x_start       起始列地址
 * @param page_start    起始页地址
 * @param page_end     结束页地址
 * @return {*}
 */
void oled_set_vertical_pos(uint8_t x_start, uint8_t page_start, uint8_t page_end)
{
    oled_write_cmd(0x22);       //设置页地址
    oled_write_cmd(page_start); //起始
    oled_write_cmd(page_end);   //结束
    oled_write_cmd(0x21);       //设置列地址
    oled_write_cmd(x_start);    //起始
    oled_write_cmd(0x7f);       //结束
}

/**
 * @description: 区域刷新
 * @param x_start  起始列地址
 * @param x_end    结束列地址
 * @return {*}
 */
void oled_area_refresh(uint8_t x_start, uint8_t x_end)
{
    for (uint8_t num = x_start; num <= x_end; num++)
    {
        if (oled_buff_flag[num])
        {
            oled_set_vertical_pos(num, 0, OLED_PAGE - 1);
            for (uint8_t page_num = 0; page_num < 4; page_num++)
            {
                oled_write_data(oled_buff[page_num][num]);
            }
            oled_buff_flag[num] = 0;
        }
    }
}

/**
 * @description: 全屏刷新
 * @param {*}
 * @return {*}
 */
void oled_refresh()
{
    oled_area_refresh(0, OLED_WIDTH - 1);
}



uint8_t oled_draw_bmp(uint8_t pos_x, uint8_t pos_y, uint8_t width, uint8_t length, uint8_t *data)
{
    for (uint8_t x = pos_x; x < pos_x + width; x++)
    {
        if (x == OLED_WIDTH)
        {
            break;
        }
        oled_draw_column(x, pos_y, data, length);
        data += length / 8;
    }
}

void oled_draw_column(uint8_t pos_x, uint8_t pos_y, uint8_t *data, uint8_t length)
{
    uint32_t column_data = 0;
    uint8_t page_start = pos_y / 8;
    uint8_t *column_data_p;
    uint8_t offset = pos_y % 8 - 1;
    uint8_t page_length = length / 8;
    column_data_p = (uint8_t *)(&column_data);

    for (uint8_t num = 0; num < page_length; num++)
    {
        *(column_data_p + num + page_start) = *(data + num);
    }
    column_data = column_data << offset;
    column_data_p = (uint8_t *)(&column_data);
    for (uint8_t num = 0; num < 4; num++)
    {
        oled_buff[page_start + num][pos_x] |= *((uint8_t *)(column_data_p + num));
    }
    oled_buff_flag[pos_x] = 1;
}
