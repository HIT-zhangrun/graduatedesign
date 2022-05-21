/*
 * radar_recv.h
 *
 *  Created on: 2022年5月19日
 *      Author: zhangrun
 */

#ifndef RADAR_RECV_H_
#define RADAR_RECV_H_

#include "usart.h"

typedef struct recv_head_s
{
    uint8_t head_a;
    uint8_t head_b;
    uint16_t msg_size;
    uint8_t pack_type;
    uint8_t reserved;
    uint8_t xor_check;
    uint8_t end;
} __attribute__((packed)) recv_head_s;

typedef struct recv_pack_signal_s
{
    uint8_t head;
    uint8_t reserved;
    uint8_t total_part;
    uint8_t current_part;
    uint16_t total_size;
    uint16_t data[512];
    uint8_t xor_check;
    uint8_t end;
} __attribute__((packed)) recv_pack_signal_s;

typedef struct recv_msg_s
{
    recv_head_s        recv_head_1;
    recv_pack_signal_s recv_pack_1;
    recv_head_s        recv_head_2;
    recv_pack_signal_s recv_pack_2;
    recv_head_s        recv_head_3;
    recv_pack_signal_s recv_pack_3;
    recv_head_s        recv_head_4;
    recv_pack_signal_s recv_pack_4;
    recv_head_s        recv_head_5;
    recv_pack_signal_s recv_pack_5;
} __attribute__((packed)) recv_msg_s;


uint8_t init_radar();
float *trig_recv_data();
float *trig_recv_data2();
float recv_data_process();


#endif /* RADAR_RECV_H_ */
