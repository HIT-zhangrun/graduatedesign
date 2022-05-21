#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


typedef enum
{
    serial_close = 0,
    serial_open,
} serial_status_e;

class Serial : public QSerialPort
{
    Q_OBJECT
public:
    explicit Serial(QWidget *parent = nullptr);
    static QStringList update_serial_list();
    static serial_status_e get_serial_status();
    uint8_t open_serial();
    uint8_t close_serial();
    uint8_t read_data();
    qint32 set_serial_baud(QString baud_text);
    uint8_t send_data(QString tx_data);
    static QByteArray *rx_data_buf;
    QByteArray *get_buf();
private:
    static serial_status_e serial_status;
    static QByteArray *rx_data_buf_send;
signals:
    void data_ready();

};

#endif // SERIAL_H
