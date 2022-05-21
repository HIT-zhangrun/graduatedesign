/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "serial/seriallist.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *status_display;
    QPushButton *serial_button;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *current_time;
    QLineEdit *start_time;
    QLineEdit *start_num;
    QSpinBox *set_auto_time;
    QSpinBox *set_warming_value;
    SerialList *comboBox;
    QWidget *widget_4;
    QWidget *widget;
    QWidget *widget_3;
    QLabel *label_9;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(940, 600);
        MainWindow->setMinimumSize(QSize(940, 600));
        MainWindow->setMaximumSize(QSize(940, 600));
        MainWindow->setSizeIncrement(QSize(800, 600));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        status_display = new QPushButton(centralwidget);
        status_display->setObjectName(QString::fromUtf8("status_display"));
        status_display->setEnabled(false);
        status_display->setGeometry(QRect(820, 530, 121, 71));
        QFont font;
        font.setPointSize(17);
        status_display->setFont(font);
        serial_button = new QPushButton(centralwidget);
        serial_button->setObjectName(QString::fromUtf8("serial_button"));
        serial_button->setGeometry(QRect(820, 460, 123, 71));
        serial_button->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 410, 101, 31));
        QFont font1;
        font1.setPointSize(15);
        label->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(40, 470, 141, 31));
        label_2->setFont(font1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(140, 240, 53, 31));
        label_3->setFont(font1);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(450, 240, 53, 31));
        label_4->setFont(font1);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(760, 240, 53, 41));
        label_5->setFont(font1);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(40, 520, 141, 31));
        label_6->setFont(font1);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(40, 300, 111, 31));
        label_7->setFont(font1);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(40, 350, 131, 31));
        label_8->setFont(font1);
        current_time = new QLineEdit(centralwidget);
        current_time->setObjectName(QString::fromUtf8("current_time"));
        current_time->setEnabled(false);
        current_time->setGeometry(QRect(140, 420, 261, 21));
        start_time = new QLineEdit(centralwidget);
        start_time->setObjectName(QString::fromUtf8("start_time"));
        start_time->setEnabled(false);
        start_time->setGeometry(QRect(180, 470, 113, 21));
        start_num = new QLineEdit(centralwidget);
        start_num->setObjectName(QString::fromUtf8("start_num"));
        start_num->setEnabled(false);
        start_num->setGeometry(QRect(190, 530, 41, 21));
        set_auto_time = new QSpinBox(centralwidget);
        set_auto_time->setObjectName(QString::fromUtf8("set_auto_time"));
        set_auto_time->setGeometry(QRect(240, 350, 42, 22));
        set_warming_value = new QSpinBox(centralwidget);
        set_warming_value->setObjectName(QString::fromUtf8("set_warming_value"));
        set_warming_value->setGeometry(QRect(240, 310, 42, 22));
        comboBox = new SerialList(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(820, 320, 121, 22));
        widget_4 = new QWidget(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(640, 50, 260, 180));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 50, 260, 180));
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(340, 50, 260, 180));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(730, 310, 81, 31));
        label_9->setFont(font1);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(820, 390, 123, 71));
        pushButton_2->setFont(font);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\272\225\344\270\213\345\233\264\345\262\251\345\217\230\345\275\242\346\216\242\346\265\213\347\263\273\347\273\237", nullptr));
        status_display->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\346\234\252\350\277\236\346\216\245", nullptr));
        serial_button->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\350\256\276\345\244\207", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\350\277\220\350\241\214\346\227\266\351\227\264\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\267\246\344\276\247", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\217\263\344\276\247", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\276\247", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\350\277\220\350\241\214\346\254\241\346\225\260\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\346\212\245\350\255\246\345\200\274", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\277\220\350\241\214\351\227\264\351\232\224", nullptr));
        start_num->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\350\256\276\345\244\207", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\350\277\220\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
