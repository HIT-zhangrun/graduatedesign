/*
 * radar_recv.c
 *
 *  Created on: 2022年5月19日:>
 *      Author: zhangrun
 */

#include "radar_recv.h"
#include "fft.h"
#include "usbd_cdc_if.h"

static uint8_t buff[5210];
static uint8_t recv_flag = 0;
static uint8_t recv_flag2 = 0;
static uint8_t ready_signal[] = {0xAB, 0xCD, 0x0A, 0x00, 0x00, 0x00, 0x6C, 0xEF, 0xAA, 0xEE};
static uint8_t ask_data[] = {0xAB, 0xCD, 0x0C, 0x00, 0x05, 0x00, 0x6A, 0xEF, 0xAA, 0x63, 0xC9, 0xEE};
static uint8_t ask_data2[] = {0x2A, 0x2A, 0x41, 0x4B, 0x0A, 0x0D};
static float range = 0;
static uint8_t buff2[20];
uint8_t init_radar()
{
	HAL_Delay(1000);
	for(uint8_t i = 0; i < 5; i++)
	{
		HAL_UART_Transmit(&huart2, ready_signal, sizeof(ready_signal), 0xFFFF);
		//HAL_UART_Transmit(&huart3, ask_data2, 6, 0xFFFF);
		HAL_Delay(100);
	}
	HAL_UART_Receive_IT(&huart3, buff2, 8);
    HAL_UART_Receive_IT(&huart2, buff, sizeof(recv_msg_s));
    return 0;
}

float *trig_recv_data()
{
    HAL_UART_Transmit(&huart2, ask_data, sizeof(ask_data), 0xFFFF);
    HAL_Delay(100);
    if(!recv_flag)
    {
    	HAL_UART_Receive_IT(&huart2, buff, sizeof(recv_msg_s));
    	return NULL;
    }
    recv_flag = 0;
    range = recv_data_process();
    memset(buff, 0, sizeof(buff));
    return &range;
}

float *trig_recv_data2()
{
    HAL_UART_Transmit(&huart3, ask_data2, 6, 0xFFFF);
    HAL_Delay(100);
    if(!recv_flag2)
    {
    	HAL_UART_Receive_IT(&huart3, buff2, 8);
    	return NULL;
    }
    recv_flag2 = 0;
    uint8_t val1 = buff2[3] & 0x0F;
    uint8_t val2 = ((buff2[4] >> 4) & 0x0F);
    uint8_t val3 = (buff2[4] & 0x0F);
    uint8_t val4 = ((buff2[5] >> 4) & 0x0F);
    uint8_t val5 = (buff2[5] & 0x0F);

    uint32_t val = (val1 * 10000) + (val2 * 1000) + (val3 * 100) + (val4 * 10) + val5;
    float val_f = (float)val;
    range = val_f / 1000;

    return &range;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2)
	{
		 if (HAL_UART_GetError(huart) & HAL_UART_ERROR_ORE)
		 {
		     __HAL_UART_FLUSH_DRREGISTER(huart);
		     __HAL_UART_CLEAR_OREFLAG(&huart2);
		     HAL_UART_Receive_IT(&huart2, buff, sizeof(recv_msg_s));
		 }
	}
	if (huart->Instance == USART3)
	{
	    if (HAL_UART_GetError(huart) & HAL_UART_ERROR_ORE)
		{
			 __HAL_UART_FLUSH_DRREGISTER(huart);
			 __HAL_UART_CLEAR_OREFLAG(&huart3);
			 HAL_UART_Receive_IT(&huart3, buff, 8);
	    }
    }
}

float recv_data_process()
{
    recv_msg_s recv_msg;
    recv_msg_s *recv_msg_p = &recv_msg;
    memcpy(recv_msg_p, buff, sizeof(recv_msg));

    //打印原始数据
    //for(uint32_t i = 0; i < 460; i++)
    //{
    //	usb_debug("%d\r\n", recv_msg_p->recv_pack_1.data[i]);
    //	HAL_Delay(10);
    //}



    range = just_fft(recv_msg_p->recv_pack_1);
    range += just_fft(recv_msg_p->recv_pack_2);
    range += just_fft(recv_msg_p->recv_pack_3);
    range += just_fft(recv_msg_p->recv_pack_4);

    range /= 4;
    //range = phase_diff(recv_msg_p->recv_pack_2);
    //usb_debug("%f", a);
    //usb_debug("range:%dmm\r\n", (uint32_t)(range * 1000));



    return range;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) //回调函数
{
    if (huart->Instance == USART2)
    {
        if (buff[0] == 0xAB && buff[1] == 0xCD)
        {
            recv_flag = 1;
            return;
        }
    }
    if (huart->Instance == USART3)
    {
        if (buff2[0] == 0x2A && buff2[1] == 0x2A)
        {
            recv_flag2 = 1;
            return;
        }
    }
}
