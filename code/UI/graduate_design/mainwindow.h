#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include "serial/serial.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    uint8_t init_color(void);
    QImage left;
    QImage right;
    QImage top;
    void paintEvent(QPaintEvent *);
    void paint_left();
    void paint_right();
    void paint_top();
    uint8_t open_close_serial();
    void display();
    static float left_buf[20];
    static float right_buf[20];
    static float top_buf[20];
    static int left_p;
    static int right_p;
    static int top_p;
    static float WARNING;
    void warning();



    Serial *serial;
};
#endif // MAINWINDOW_H
