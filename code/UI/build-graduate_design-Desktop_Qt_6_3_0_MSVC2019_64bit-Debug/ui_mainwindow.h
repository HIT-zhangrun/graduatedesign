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
    QPushButton *pushButton;
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        status_display = new QPushButton(centralwidget);
        status_display->setObjectName(QString::fromUtf8("status_display"));
        status_display->setEnabled(false);
        status_display->setGeometry(QRect(680, 0, 121, 71));
        QFont font;
        font.setPointSize(17);
        status_display->setFont(font);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(679, 60, 123, 71));
        QFont font1;
        font1.setPointSize(13);
        pushButton->setFont(font1);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 570, 53, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(190, 570, 81, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(110, 170, 53, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(370, 170, 53, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(100, 420, 53, 16));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(400, 570, 81, 16));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(700, 300, 81, 16));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(700, 340, 101, 16));
        current_time = new QLineEdit(centralwidget);
        current_time->setObjectName(QString::fromUtf8("current_time"));
        current_time->setEnabled(false);
        current_time->setGeometry(QRect(60, 570, 113, 21));
        start_time = new QLineEdit(centralwidget);
        start_time->setObjectName(QString::fromUtf8("start_time"));
        start_time->setEnabled(false);
        start_time->setGeometry(QRect(270, 570, 113, 21));
        start_num = new QLineEdit(centralwidget);
        start_num->setObjectName(QString::fromUtf8("start_num"));
        start_num->setEnabled(false);
        start_num->setGeometry(QRect(480, 570, 41, 21));
        set_auto_time = new QSpinBox(centralwidget);
        set_auto_time->setObjectName(QString::fromUtf8("set_auto_time"));
        set_auto_time->setGeometry(QRect(700, 360, 42, 22));
        set_warming_value = new QSpinBox(centralwidget);
        set_warming_value->setObjectName(QString::fromUtf8("set_warming_value"));
        set_warming_value->setGeometry(QRect(700, 320, 42, 22));
        comboBox = new SerialList(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(720, 160, 69, 22));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\272\225\344\270\213\345\233\264\345\262\251\345\217\230\345\275\242\346\216\242\346\265\213\347\263\273\347\273\237", nullptr));
        status_display->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\346\234\252\350\277\236\346\216\245", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\350\256\276\345\244\207", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\346\227\266\351\227\264\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\350\277\220\350\241\214\346\227\266\351\227\264\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\267\246\344\276\247", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\217\263\344\276\247", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\276\247", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\244\207\350\277\220\350\241\214\346\254\241\346\225\260\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\346\212\245\350\255\246\345\200\274", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\277\220\350\241\214\351\227\264\351\232\224", nullptr));
        start_num->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
