#ifndef SERIALLIST_H
#define SERIALLIST_H

#include <QWidget>
#include <QComboBox>
#include <QMouseEvent>
#include "serial.h"

class SerialList : public QComboBox
{
    Q_OBJECT
public:
    explicit SerialList(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void serial_list_display(void);
    void set_current_com(void);
    QString get_current_com(void);
private:
    static QString *current_com;

signals:

};

#endif // SERIALLIST_H
