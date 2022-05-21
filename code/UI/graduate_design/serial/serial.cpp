#include "serial.h"
#include "seriallist.h"
#include "QDebug"

serial_status_e Serial::serial_status = serial_close;
QByteArray *Serial::rx_data_buf = new QByteArray;
QByteArray *Serial::rx_data_buf_send = new QByteArray;


Serial::Serial(QWidget *parent)
    : QSerialPort{parent}
{
    setBaudRate(9600);
}

QStringList Serial::update_serial_list()
{
    QStringList serial_name;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        serial_name << info.portName() + ": " + info.description();
    }
    return serial_name;
}

serial_status_e Serial::get_serial_status()
{
    return serial_status;
}


uint8_t Serial::open_serial()
{
    SerialList serialportlist;

    setPortName(serialportlist.get_current_com());
    if(!open(QIODevice::ReadWrite))
    {
        return 1;
    }
    setDataBits(QSerialPort::Data8);
    setParity(QSerialPort::NoParity);
    setStopBits(QSerialPort::OneStop);
    setFlowControl(QSerialPort::NoFlowControl);
    serial_status = serial_open;

    connect(this, &QSerialPort::readyRead, this, &Serial::read_data);
    return 0;
}

uint8_t Serial::close_serial()
{
    close();
    serial_status = serial_close;

    disconnect(this, &QSerialPort::readyRead, this, &Serial::read_data);

    return 0;
}

uint8_t Serial::read_data()
{
    rx_data_buf->append(readAll());

    qDebug() << "enter" << rx_data_buf->data();
    if(rx_data_buf->at(0) == 'Z' && rx_data_buf->at(1) == 'R')
    {
        if(rx_data_buf->length() >= 14)
        {
            emit data_ready();
        }
    }
    rx_data_buf->clear();
    return 0;
}

qint32 Serial::set_serial_baud(QString baud_text)
{
    setBaudRate(baud_text.toInt());
    return 0;
}


uint8_t Serial::send_data(QString tx_data)
{
    write(tx_data.toUtf8());
    return 0;
}

QByteArray *Serial::get_buf()
{
    return Serial::rx_data_buf;
}
