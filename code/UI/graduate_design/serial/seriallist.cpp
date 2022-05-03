#include "seriallist.h"

QString *SerialList::current_com = new QString;

SerialList::SerialList(QWidget *parent)
    : QComboBox{parent}
{
    this->addItem("选择设备");
    connect(this, &QComboBox::activated, this, &SerialList::set_current_com);
}

void SerialList::serial_list_display(void)
{
    Serial serial;
    if(serial.get_serial_status() == serial_close)
    {
    this->clear();
    this->addItems(Serial::update_serial_list());
    showPopup();
    }
}

void SerialList::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        serial_list_display();
    }
}

void SerialList::set_current_com(void)
{
    *current_com = this->currentText().mid(0, this->currentText().indexOf(":"));
}

QString SerialList::get_current_com(void)
{
    return *current_com;
}
