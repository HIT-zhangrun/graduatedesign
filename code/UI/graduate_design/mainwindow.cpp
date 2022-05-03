#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_color();//初始化组件颜色

}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化组件颜色
uint8_t MainWindow::init_color(void)
{
    ui->status_display->setStyleSheet("background-color: rgb(0,255,0)");//状态绿色

    return 0;
}
