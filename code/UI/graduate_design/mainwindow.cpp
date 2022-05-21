#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QTimer>
#include <QDateTime>



#define PAINT_WIDTH 260
#define PAINT_HEIGHT 180
#define PAINT_GAP 10
float MainWindow::WARNING = 0.01;

int MainWindow::left_p = 0;
int MainWindow::right_p = 0;
int MainWindow::top_p = 0;

float MainWindow::left_buf[20] = {0};
float MainWindow::right_buf[20] = {0};
float MainWindow::top_buf[20] = {0};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_color();//初始化组件颜色

    left = QImage(PAINT_WIDTH, PAINT_HEIGHT, QImage::Format_RGB32);  //画布的初始化大小设为600*500，使用32位颜色
    QColor backColor = qRgb(255, 255, 255);
    left.fill(backColor);

    right = QImage(PAINT_WIDTH, PAINT_HEIGHT, QImage::Format_RGB32);  //画布的初始化大小设为600*500，使用32位颜色
    backColor = qRgb(255, 255, 255);
    right.fill(backColor);

    top = QImage(PAINT_WIDTH, PAINT_HEIGHT, QImage::Format_RGB32);  //画布的初始化大小设为600*500，使用32位颜色
    backColor = qRgb(255, 255, 255);
    top.fill(backColor);

    paint_left();
    paint_right();
    paint_top();

    serial = new Serial;
    connect(ui->serial_button, &QPushButton::clicked, this, &MainWindow::open_close_serial);
    connect(serial, &Serial::data_ready, this, &MainWindow::display);
    connect(ui->set_warming_value, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=](int i){
            float temp = static_cast<float>(i);
            WARNING = temp/1000;
            });


    //显示时间
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::red);
    ui->current_time->setPalette(palette);
    //定时器
    QTimer *CurrentTime = new QTimer(this);
    CurrentTime->start(0);
    //使用定时器信号槽，尽快更新时间的显示
    connect(CurrentTime,&QTimer::timeout,[=](){
    QDateTime current_time = QDateTime::currentDateTime();
    //显示时间，格式为：年-月-日 时：分：秒 周几
    QString StrCurrentTime = current_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    //时间显示格式可自由设定，如hh:mm ddd 显示 时：分 周几
    //具体格式见函数QString QDateTime::​toString(const QString & format) const
    ui->current_time->setText(StrCurrentTime);
    });





}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化组件颜色
uint8_t MainWindow::init_color(void)
{
    ui->status_display->setStyleSheet("background-color: rgb(255, 0, 0)");//状态红色

    return 0;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(40, 50, left);
    painter.drawImage(340, 50, right);
    painter.drawImage(640, 50, top);
}


void MainWindow::paint_left()
{
    QPainter painter(&left);
    painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点
    int pointx = PAINT_GAP;
    int pointy = PAINT_HEIGHT - PAINT_GAP;//确定坐标轴起点坐标，
    int width = PAINT_WIDTH - PAINT_GAP * 2;
    int height = PAINT_HEIGHT - PAINT_GAP * 2;//确定坐标轴宽度跟高度
    //绘制坐标轴
    painter.drawRect(0, 0, PAINT_WIDTH, PAINT_HEIGHT);//外围的矩形
    painter.drawLine(pointx, pointy, width + pointx, pointy);//坐标轴x宽度为width
    painter.drawLine(pointx, pointy - height, pointx, pointy);//坐标轴y高度为height
}

void MainWindow::paint_right()
{
    QPainter painter(&right);
    painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点
    int pointx = PAINT_GAP;
    int pointy = PAINT_HEIGHT - PAINT_GAP;//确定坐标轴起点坐标，
    int width = PAINT_WIDTH - PAINT_GAP * 2;
    int height = PAINT_HEIGHT - PAINT_GAP * 2;//确定坐标轴宽度跟高度
    //绘制坐标轴
    painter.drawRect(0, 0, PAINT_WIDTH, PAINT_HEIGHT);//外围的矩形
    painter.drawLine(pointx, pointy, width + pointx, pointy);//坐标轴x宽度为width
    painter.drawLine(pointx, pointy - height, pointx, pointy);//坐标轴y高度为height1
}


void MainWindow::paint_top()
{
    QPainter painter(&top);
    painter.setRenderHint(QPainter::Antialiasing, true);//设置反锯齿模式，好看一点
    int pointx = PAINT_GAP;
    int pointy = PAINT_HEIGHT - PAINT_GAP;//确定坐标轴起点坐标，
    int width = PAINT_WIDTH - PAINT_GAP * 2;
    int height = PAINT_HEIGHT - PAINT_GAP * 2;//确定坐标轴宽度跟高度
    //绘制坐标轴
    painter.drawRect(0, 0, PAINT_WIDTH, PAINT_HEIGHT);//外围的矩形
    painter.drawLine(pointx, pointy, width + pointx, pointy);//坐标轴x宽度为width
    painter.drawLine(pointx, pointy - height, pointx, pointy);//坐标轴y高度为height
}

uint8_t MainWindow::open_close_serial()
{
    if(Serial::get_serial_status() == serial_close)
    {
        if(!serial->open_serial())
        {
            ui->serial_button->setText("断开设备");
            ui->status_display->setText("设备已连接");
            ui->status_display->setStyleSheet("background-color: rgb(0, 255, 0)");
            return 0;
        }
        return 1;
    }

    if(Serial::get_serial_status() == serial_open)
    {
        serial->close_serial();
        ui->serial_button->setText("连接设备");
        ui->status_display->setText("设备未连接");
        ui->status_display->setStyleSheet("background-color: rgb(255, 0, 0)");
        QPainter painter(&left);
        QPen penPoint;
        painter.eraseRect(QRect(15, 5, 250, 160));
        QPainter painter_1(&right);
        painter_1.eraseRect(QRect(15, 5, 250, 160));
        QPainter painter_2(&top);
        painter_2.eraseRect(QRect(15, 5, 250, 160));
        left_p = 0;
        right_p = 0;
        top_p  = 0;
        QWidget::update();
    }
    return 1;
}

void MainWindow::display()
{

    QByteArray *buf = serial->get_buf();

    float left_val = 0;
    float right_val = 0;
    float top_val = 0;

    char* data_char = buf->data();
    char* p = (char*)&left_val;
    for(int index = 0; index < 4; index++)
    {
        *(p + index) = *(data_char + 2 + index);
    }
    p = (char*)&right_val;
    for(int index = 0; index < 4; index++)
    {
        *(p + index) = *(data_char + 6 + index);
    }
    p = (char*)&top_val;
    for(int index = 0; index < 4; index++)
    {
        *(p + index) = *(data_char + 10 + index);
    }

    left_buf[left_p] = left_val;
    right_buf[right_p] = right_val;
    top_buf[top_p] = top_val;
    left_p++;
    right_p++;
    top_p++;
    if(left_p >= 20)
    {
        left_p = 0;
        QPainter painter(&left);
        painter.eraseRect(QRect(15, 5, 250, 160));
    }
    if(right_p >= 20)
    {
        right_p = 0;
        QPainter painter(&right);
        painter.eraseRect(QRect(15, 5, 250, 160));
    }
    if(top_p >= 20)
    {
        top_p = 0;
        QPainter painter(&top);
        painter.eraseRect(QRect(15, 5, 250, 160));
    }

    float left_min = left_buf[0], left_max = left_buf[0];
    float right_min = right_buf[0], right_max = right_buf[0];
    float top_min = top_buf[0], top_max = top_buf[0];
    for(int i = 0; i < left_p; i++)
    {
        if(left_min > left_buf[i])
        {
            left_min = left_buf[i];
        }
        if(left_max < left_buf[i])
        {
            left_max = left_buf[i];
        }
    }
    for(int i = 0; i < right_p; i++)
    {
        if(right_min > right_buf[i])
        {
            right_min = right_buf[i];
        }
        if(right_max < right_buf[i])
        {
            right_max = right_buf[i];
        }
    }
    for(int i = 0; i < top_p; i++)
    {
        if(top_min > top_buf[i])
        {
            top_min = top_buf[i];
        }
        if(top_max < top_buf[i])
        {
            top_max = top_buf[i];
        }
    }

    if(left_p > 2)
    {
        if(abs(left_buf[left_p - 1] - left_buf[left_p - 2]) > WARNING)
        {
            warning();
            ui->status_display->setText("坍塌警报");
            ui->status_display->setStyleSheet("background-color: rgb(255, 0, 0)");
        }
        if(abs(right_buf[right_p - 1] - right_buf[right_p - 2]) > WARNING)
        {
            warning();
            ui->status_display->setText("坍塌警报");
            ui->status_display->setStyleSheet("background-color: rgb(255, 0, 0)");
        }
        if(abs(top_buf[top_p - 1] - top_buf[top_p - 2]) > WARNING)
        {
            warning();
            ui->status_display->setText("坍塌警报");
            ui->status_display->setStyleSheet("background-color: rgb(255, 0, 0)");
        }
    }
    float left_gap = 1;
    float right_gap = 1;
    float top_gap = 1;
    if(left_max != left_min)
    {
        left_gap = (left_max - left_min) / 50;
    }
    if(right_max != right_min)
    {
        right_gap = (right_max - right_min) / 50;
    }
    if(top_max != top_min)
    {
        top_gap = (top_max - top_min) / 50;
    }

    QPainter painter(&left);
    QPen penPoint;
    //penPoint.setColor(Qt::black);
    penPoint.setWidth(4);
    painter.setPen(penPoint);
    painter.eraseRect(QRect(15, 5, 250, 160));

    //qDebug()<<"max"<<left_max<<"min"<<left_min<<"val"<<left_val;
    qDebug()<<left_val<<right_val<<top_val;
    for(int i = 0; i < left_p ;i++)
    {
        painter.drawPoint(20 + (260 - 20) * i / 20, (left_max - left_buf[i]) / left_gap + 80);
        //qDebug() << (left_max - left_buf[i]) / left_gap + 10;
    }


    QPainter painter_1(&right);
    //penPoint.setColor(Qt::black);
    penPoint.setWidth(4);
    painter_1.setPen(penPoint);
    painter_1.eraseRect(QRect(15, 5, 250, 160));

    for(int i = 0; i < right_p ;i++)
    {
        painter_1.drawPoint(20 + (260 - 20) * i / 20, (right_max - right_buf[i]) / right_gap + 80);
    }

    QPainter painter_2(&top);
    //penPoint.setColor(Qt::black);
    penPoint.setWidth(4);
    painter_2.setPen(penPoint);
    painter_2.eraseRect(QRect(15, 5, 250, 160));

    for(int i = 0; i < top_p ;i++)
    {
        painter_2.drawPoint(20 + (260 - 20) * i / 20, (top_max - top_buf[i]) / top_gap + 80);
    }

    QWidget::update();
}

void MainWindow::warning()
{
    //播放警报
    QSoundEffect *effect=new QSoundEffect;
    effect->setSource(QUrl::fromLocalFile("C:\\Users\\zhangrun\\OneDrive\\my_doc\\project\\graduatedesign\\code\\UI\\graduate_design\\1.wav"));
    effect->setLoopCount(1);
    effect->setVolume(1); //音量  0~1之间
    effect->play();
}



