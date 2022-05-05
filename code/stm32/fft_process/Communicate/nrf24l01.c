/*
 * nrf24l01.c
 *
 *  Created on: May 4, 2022
 *      Author: zhangrun
 */

#include "nrf24l01.h"

const uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01};//发送地址
const uint8_t RX_ADDRESS[RX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01};//接收地址
uint8_t test_buf[33] = "test";

/**
  * @brief  初始化NRF24l01
  * @retval none
  */
void NRF24L01_Init(void)
{
    NRF24L01_CE_LOW;          //使能24L01
    NRF24L01_SPI_CSN_DISABLE; // SPI片选取消
}

/**
  * @brief  检测nrf24l01是否存在
  * @retval 0 检测到;1 未检测到
  */
uint8_t nrf_check(void)
{
    uint8_t buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
    uint8_t i;
/*
    nrf_write_buf(NRF_WRITE + TX_ADDR, buf, 5); //写入5个字节的地址.
    nrf_read_buf(TX_ADDR, buf, 5);                  //读出写入的地址
    for (i = 0; i < 5; i++)
    {
        if (buf[i] != 0XA5)
        {
            break;
        }
    }
    if (i != 5)
    {
        return 1; //检测24L01错误
    }
*/
    return 0; //检测到24L01
}

uint8_t read_write_byte(uint8_t send_byte)
{
  uint8_t read_byte;
  if(HAL_SPI_TransmitReceive(&hspi1, &send_byte, &read_byte, sizeof(uint8_t), 0xFF) != HAL_OK)
  {
    read_byte = NRF_ERROR;
  }

  return read_byte;
}

/**
 * 函数功能: 启动NRF24L01发送一次数据
 * 输入参数: 无
 * 返 回 值: 发送完成状况
 * 说    明：txbuf:待发送数据首地址
 *
 */
/*
uint8_t nrf_tx_pkg(uint8_t *txbuf)
{
    uint8_t sta;

    NRF24L01_CE_LOW;
    nrf_write_buf(WR_TX_PLOAD, txbuf, TX_PLOAD_WIDTH); //写数据到TX BUF  32个字节
    NRF24L01_CE_HIGH;                                  //启动发送

    while (NRF24L01_IRQ_PIN_READ != 0)
        ; //等待发送完成

    sta = nrf_read_reg(STATUS);                 //读取状态寄存器的值
    nrf_write_reg(NRF_WRITE_REG + STATUS, sta); //清除TX_DS或MAX_RT中断标志
    if (sta & MAX_TX)                           //达到最大重发次数
    {
        nrf_write_reg(FLUSH_TX, 0xff); //清除TX FIFO寄存器
        return MAX_TX;
    }
    if (sta & TX_OK) //发送完成
    {
        return TX_OK;
    }
    return 0xff; //其他原因发送失败
}*/

/**
 * 函数功能:启动NRF24L01接收一次数据
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 *
 */
/*uint8_t nrf_rx_pkg(uint8_t *rxbuf)
{
    uint8_t sta;
    sta = nrf_read_reg(STATUS);                 //读取状态寄存器的值
    nrf_write_reg(NRF_WRITE_REG + STATUS, sta); //清除TX_DS或MAX_RT中断标志
    if (sta & RX_OK)                            //接收到数据
    {
        nrf_read_buf(RD_RX_PLOAD, rxbuf, RX_PLOAD_WIDTH); //读取数据
        nrf_write_reg(FLUSH_RX, 0xff);                    //清除RX FIFO寄存器
        return 0;
    }

    return 1; //没收到任何数据
}
*/

nrf24l01_status_e nrf_read(uint8_t reg, uint8_t *buf, uint8_t len)
{
    if(buf == NULL)
    {
        return NRF_ERROR;
    }

    if(read_write_byte(NRF_READ + reg) == NRF_ERROR)
    {
        return NRF_ERROR;
    }

    for (uint8_t num = 0; num < len - 1; num++)
    {
        *(buf + num) = read_write_byte(NRF_NOP);
        if(*(buf + num) == NRF_ERROR)
        {
            return NRF_ERROR;
        }
    }

    return NRF_OK;
}

nrf24l01_status_e nrf_write(uint8_t reg, uint8_t *buf, uint8_t len)
{
    if(buf == NULL)
    {
        return NRF_ERROR;
    }

    if(read_write_byte(NRF_WRITE + reg) == NRF_ERROR)
    {
        return NRF_ERROR;
    }

    for (uint8_t num = 0; num < len - 1; num++)
    {
        if(read_write_byte(*(buf + num)) == NRF_ERROR)
        {
            return NRF_ERROR;
        }
    }

    return NRF_OK;
}

nrf24l01_status_e nrf_cmd(uint8_t cmd, uint8_t reg, uint8_t *buf, uint8_t len)
{
    nrf24l01_status_e nrf24l01_status;
    if(reg > FIFO_STATUS)
    {
        return NRF_ERROR;
    }

    if((cmd == NRF_READ) || (cmd == RD_RX_PLOAD))
    {
        NRF24L01_SPI_CSN_ENABLE;
        nrf24l01_status = nrf_read(reg, buf, len);
        NRF24L01_SPI_CSN_DISABLE;

        return nrf24l01_status;
    }

    if((cmd == NRF_WRITE) || (cmd == WR_TX_PLOAD))
    {
        NRF24L01_SPI_CSN_ENABLE;
        nrf24l01_status = nrf_write(reg, buf, len);
        NRF24L01_SPI_CSN_DISABLE;

        return nrf24l01_status;
    }

    if(read_write_byte(cmd) == NRF_ERROR)
    {
        return NRF_ERROR;
    }

    return NRF_OK;
}
/**
 * 函数功能: 该函数初始化NRF24L01到RX模式
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 *
 */
void nrf_rx_mode(void)
{
    uint8_t EN_AA_val = 0x01;
    uint8_t EN_RXADDR_val = 0x01;
    uint8_t RF_CH_val = 40;
    uint8_t RX_PW_P0_val = RX_PLOAD_WIDTH;
    uint8_t RF_SETUP_val = 0x07;
    uint8_t CONFIG_val = 0x0F;

    NRF24L01_CE_LOW;
    nrf_cmd(NRF_WRITE, RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);
    nrf_cmd(NRF_WRITE, EN_AA, &EN_AA_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, EN_RXADDR, &EN_RXADDR_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, RF_CH, &RF_CH_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, RX_PW_P0, &RX_PW_P0_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, RF_SETUP, &RF_SETUP_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, CONFIG, &CONFIG_val, sizeof(uint8_t));
    NRF24L01_CE_HIGH; // CE为高,进入接收模式
    HAL_Delay(1);
}

/**
 * 函数功能: 该函数初始化NRF24L01到TX模式
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 *
 */
void nrf_tx_mode(void)
{
    uint8_t buf[32] = {0};
    uint8_t EN_AA_val = 0x01;
    uint8_t EN_RXADDR_val = 0x01;
    uint8_t SETUP_RETR_val = 0x1a;
    uint8_t RF_CH_val = 40;
    uint8_t RF_SETUP_val = 0x07;
    uint8_t CONFIG_val = 0x0e;

    NRF24L01_CE_LOW;
    nrf_cmd(NRF_WRITE, TX_ADDR, TX_ADDRESS, TX_ADR_WIDTH);
    nrf_cmd(NRF_WRITE, RX_ADDR_P0, RX_ADDRESS, RX_ADR_WIDTH);
    nrf_cmd(WR_TX_PLOAD, 0x00, &buf, sizeof(buf));
    nrf_cmd(NRF_WRITE, EN_AA, &EN_AA_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, EN_RXADDR, &EN_RXADDR_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, SETUP_RETR, &SETUP_RETR_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, RF_CH, &RF_CH_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, RF_SETUP, &RF_SETUP_val, sizeof(uint8_t));
    nrf_cmd(NRF_WRITE, CONFIG, &CONFIG_val, sizeof(uint8_t));
    NRF24L01_CE_HIGH; // CE为高,进入发送模式
    HAL_Delay(1);
}

/**
 * 函数功能: 该函数NRF24L01进入低功耗模式
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 *
 */
void nrf_low_power_mode(void)
{
    uint8_t CONFIG_val = 0x00;
    NRF24L01_CE_LOW;
    nrf_cmd(NRF_WRITE, CONFIG, &CONFIG_val, sizeof(uint8_t));
}



nrf24l01_status_e nrf_send(uint8_t *buf, uint8_t len)
{
    if(buf == NULL)
    {
        return NRF_ERROR;
    }

    if(len > TX_PLOAD_WIDTH)
    {
        return NRF_ERROR;
    }

    uint8_t status;

    NRF24L01_CE_LOW;
    nrf_cmd(FLUSH_TX, 0x00, buf, len);
    nrf_cmd(WR_TX_PLOAD, 0x00, buf, len); //写数据到TX BUF  32个字节
    NRF24L01_CE_HIGH;                                  //启动发送

    /*while (NRF24L01_IRQ_PIN_READ != 0)
        ; //等待发送完成

    nrf_cmd(NRF_READ, STATUS, &status, sizeof(status));
    nrf_cmd(NRF_WRITE, STATUS, &status, sizeof(status));

    if (sta & MAX_TX)                           //达到最大重发次数
    {
        nrf_write_reg(FLUSH_TX, 0xff); //清除TX FIFO寄存器
        return MAX_TX;
    }
    if (sta & TX_OK) //发送完成
    {
        return TX_OK;
    }
    return 0xff; //其他原因发送失败*/
}
