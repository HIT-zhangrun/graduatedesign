/*
 * nrf24l01.c
 *
 *  Created on: May 4, 2022
 *      Author: zhangrun
 */

#include "nrf24l01.h"

const uint8_t TX_ADDRESS[TX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; //发送地址
const uint8_t RX_ADDRESS[RX_ADR_WIDTH] = {0x34, 0x43, 0x10, 0x10, 0x01}; //接收地址
uint8_t test_buf[33] = "test";

//初始化24L01的IO口
void NRF24L01_Init(void)
{
    NRF24L01_CE_LOW;          //使能24L01
    NRF24L01_SPI_CSN_DISABLE; // SPI片选取消
}

/**
 * 函数功能: 往串行Flash读取写入一个字节数据并接收一个字节数据
 * 输入参数: byte：待发送数据
 * 返 回 值: uint8_t：接收到的数据
 * 说    明：无
 */
uint8_t read_write_byte(uint8_t send_byte)
{
    uint8_t read_byte;
    if (HAL_SPI_TransmitReceive(&hspi1, &send_byte, &read_byte, sizeof(uint8_t), 0xFF) != HAL_OK)
    {
        read_byte = 0xFF;
    }

    return read_byte;
}

/**
 * 函数功能: 检测24L01是否存在
 * 输入参数: 无
 * 返 回 值: 0，成功;1，失败
 * 说    明：无
 */
uint8_t nrf_check(void)
{
    uint8_t buf[5] = {0XA5, 0XA5, 0XA5, 0XA5, 0XA5};
    uint8_t i;

    nrf_write_buf(NRF_WRITE_REG + TX_ADDR, buf, 5); //写入5个字节的地址.
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

    return 0; //检测到24L01
}

/**
 * 函数功能: SPI写寄存器
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：reg:指定寄存器地址
 *
 */
uint8_t nrf_write_reg(uint8_t reg, uint8_t value)
{
    uint8_t status;
    NRF24L01_SPI_CSN_ENABLE;       //使能SPI传输
    status = read_write_byte(reg); //发送寄存器号
    read_write_byte(value);        //写入寄存器的值
    NRF24L01_SPI_CSN_DISABLE;      //禁止SPI传输

    return status; //返回状态值
}

/**
 * 函数功能: 读取SPI寄存器值
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：reg:要读的寄存器
 *
 */
uint8_t nrf_read_reg(uint8_t reg)
{
    uint8_t reg_val;
    NRF24L01_SPI_CSN_ENABLE;         //使能SPI传输
    read_write_byte(reg);            //发送寄存器号
    reg_val = read_write_byte(0XFF); //读取寄存器内容
    NRF24L01_SPI_CSN_DISABLE;        //禁止SPI传输
    return reg_val;                  //返回状态值
}

/**
 * 函数功能: 在指定位置读出指定长度的数据
 * 输入参数: 无
 * 返 回 值: 此次读到的状态寄存器值
 * 说    明：无
 *
 */
uint8_t nrf_read_buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
    uint8_t status, uint8_t_ctr;
    NRF24L01_SPI_CSN_ENABLE;       //使能SPI传输
    status = read_write_byte(reg); //发送寄存器值(位置),并读取状态值
    for (uint8_t_ctr = 0; uint8_t_ctr < len; uint8_t_ctr++)
    {
        pBuf[uint8_t_ctr] = read_write_byte(0XFF); //读出数据
    }
    NRF24L01_SPI_CSN_DISABLE; //关闭SPI传输

    return status; //返回读到的状态值
}

/**
 * 函数功能: 在指定位置写指定长度的数据
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：reg:寄存器(位置)  *pBuf:数据指针  len:数据长度
 *
 */
uint8_t nrf_write_buf(uint8_t reg, uint8_t *pBuf, uint8_t len)
{
    uint8_t status, uint8_t_ctr;
    NRF24L01_SPI_CSN_ENABLE;       //使能SPI传输
    status = read_write_byte(reg); //发送寄存器值(位置),并读取状态值
    for (uint8_t_ctr = 0; uint8_t_ctr < len; uint8_t_ctr++)
    {
        read_write_byte(*pBuf++); //写入数据
    }
    NRF24L01_SPI_CSN_DISABLE; //关闭SPI传输

    return status; //返回读到的状态值
}

/**
 * 函数功能: 启动NRF24L01发送一次数据
 * 输入参数: 无
 * 返 回 值: 发送完成状况
 * 说    明：txbuf:待发送数据首地址
 *
 */
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
}

/**
 * 函数功能:启动NRF24L01接收一次数据
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 *
 */
uint8_t nrf_rx_pkg(uint8_t *rxbuf)
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

/**
 * 函数功能: 该函数初始化NRF24L01到RX模式
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 *
 */
void nrf_rx_mode(void)
{
    NRF24L01_CE_LOW;
    nrf_write_buf(NRF_WRITE_REG + RX_ADDR_P0, (uint8_t *)RX_ADDRESS, RX_ADR_WIDTH); //写RX节点地址
    nrf_write_reg(NRF_WRITE_REG + EN_AA, 0x01);
    nrf_write_reg(NRF_WRITE_REG + EN_RXADDR, 0x01);
    nrf_write_reg(NRF_WRITE_REG + RF_CH, 40);
    nrf_write_reg(NRF_WRITE_REG + RX_PW_P0, RX_PLOAD_WIDTH);
    nrf_write_reg(NRF_WRITE_REG + RF_SETUP, 0x07);
    nrf_write_reg(NRF_WRITE_REG + CONFIG, 0x0F);
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

    NRF24L01_CE_LOW;
    nrf_write_buf(NRF_WRITE_REG + TX_ADDR, (uint8_t *)TX_ADDRESS, TX_ADR_WIDTH);
    nrf_write_buf(NRF_WRITE_REG + RX_ADDR_P0, (uint8_t *)RX_ADDRESS, RX_ADR_WIDTH);
    nrf_write_buf(WR_TX_PLOAD, test_buf, TX_PLOAD_WIDTH);
    nrf_write_reg(NRF_WRITE_REG + EN_AA, 0x01);
    nrf_write_reg(NRF_WRITE_REG + EN_RXADDR, 0x01);
    nrf_write_reg(NRF_WRITE_REG + SETUP_RETR, 0x1a);
    nrf_write_reg(NRF_WRITE_REG + RF_CH, 40);
    nrf_write_reg(NRF_WRITE_REG + RF_SETUP, 0x07);
    nrf_write_reg(NRF_WRITE_REG + CONFIG, 0x0e);
    NRF24L01_CE_HIGH; // CE为高,10us后启动发送
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
    NRF24L01_CE_LOW;
    nrf_write_reg(NRF_WRITE_REG + CONFIG, 0x00); //配置工作模式:掉电模式
}
