/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QCustomPlot *mplot;
    QGroupBox *groupBox_1;
    QLabel *label;
    QPushButton *maxTest;
    QLabel *label_2;
    QTextEdit *textEdit_4;
    QTextEdit *textEdit_3;
    QLabel *label_3;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_1;
    QLabel *label_4;
    QPushButton *startButton;
    QLabel *title;
    QPushButton *clearButton;
    QGroupBox *groupBox_2;
    QComboBox *gestureBox;
    QComboBox *forceBox;
    QComboBox *curveBox;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pathSelect;
    QLineEdit *pathPrint;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(840, 600);
        mplot = new QCustomPlot(Widget);
        mplot->setObjectName(QString::fromUtf8("mplot"));
        mplot->setGeometry(QRect(10, 70, 591, 451));
        groupBox_1 = new QGroupBox(Widget);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        groupBox_1->setGeometry(QRect(630, 60, 181, 221));
        QFont font;
        font.setBold(true);
        groupBox_1->setFont(font);
        label = new QLabel(groupBox_1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 70, 61, 20));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        label->setFont(font1);
        maxTest = new QPushButton(groupBox_1);
        maxTest->setObjectName(QString::fromUtf8("maxTest"));
        maxTest->setGeometry(QRect(80, 20, 93, 29));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(false);
        maxTest->setFont(font2);
        label_2 = new QLabel(groupBox_1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 110, 61, 20));
        label_2->setFont(font1);
        textEdit_4 = new QTextEdit(groupBox_1);
        textEdit_4->setObjectName(QString::fromUtf8("textEdit_4"));
        textEdit_4->setGeometry(QRect(80, 180, 91, 31));
        textEdit_4->setReadOnly(true);
        textEdit_3 = new QTextEdit(groupBox_1);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setGeometry(QRect(80, 140, 91, 31));
        textEdit_3->setReadOnly(true);
        label_3 = new QLabel(groupBox_1);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 150, 61, 20));
        label_3->setFont(font1);
        textEdit_2 = new QTextEdit(groupBox_1);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(80, 100, 91, 31));
        textEdit_2->setReadOnly(true);
        textEdit_1 = new QTextEdit(groupBox_1);
        textEdit_1->setObjectName(QString::fromUtf8("textEdit_1"));
        textEdit_1->setGeometry(QRect(80, 60, 91, 31));
        textEdit_1->setReadOnly(true);
        label_4 = new QLabel(groupBox_1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 190, 61, 20));
        label_4->setFont(font1);
        startButton = new QPushButton(Widget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        startButton->setGeometry(QRect(680, 490, 131, 31));
        title = new QLabel(Widget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(300, 20, 251, 31));
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(true);
        title->setFont(font3);
        clearButton = new QPushButton(Widget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(630, 490, 41, 31));
        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(630, 290, 181, 141));
        gestureBox = new QComboBox(groupBox_2);
        gestureBox->addItem(QString());
        gestureBox->addItem(QString());
        gestureBox->setObjectName(QString::fromUtf8("gestureBox"));
        gestureBox->setGeometry(QRect(80, 100, 91, 26));
        gestureBox->setFont(font2);
        forceBox = new QComboBox(groupBox_2);
        forceBox->addItem(QString());
        forceBox->addItem(QString());
        forceBox->addItem(QString());
        forceBox->setObjectName(QString::fromUtf8("forceBox"));
        forceBox->setGeometry(QRect(80, 20, 91, 26));
        curveBox = new QComboBox(groupBox_2);
        curveBox->addItem(QString());
        curveBox->addItem(QString());
        curveBox->addItem(QString());
        curveBox->setObjectName(QString::fromUtf8("curveBox"));
        curveBox->setGeometry(QRect(80, 60, 91, 26));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 69, 20));
        label_5->setFont(font);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 60, 69, 20));
        label_6->setFont(font);
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 100, 69, 20));
        label_7->setFont(font);
        pathSelect = new QPushButton(Widget);
        pathSelect->setObjectName(QString::fromUtf8("pathSelect"));
        pathSelect->setGeometry(QRect(630, 440, 41, 31));
        pathPrint = new QLineEdit(Widget);
        pathPrint->setObjectName(QString::fromUtf8("pathPrint"));
        pathPrint->setGeometry(QRect(680, 440, 131, 31));
        pathPrint->setReadOnly(true);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox_1->setTitle(QCoreApplication::translate("Widget", "\346\234\200\345\244\247\345\212\233", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\347\254\254\344\270\200\346\254\241\357\274\232", nullptr));
        maxTest->setText(QCoreApplication::translate("Widget", "\346\265\213\350\257\225", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\347\254\254\344\272\214\346\254\241\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\347\254\254\344\270\211\346\254\241\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\345\271\263\345\235\207\345\200\274\357\274\232", nullptr));
        startButton->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213", nullptr));
        title->setText(QCoreApplication::translate("Widget", "\350\202\214\347\224\265\346\225\260\346\215\256\351\207\207\351\233\206\344\270\212\344\275\215\346\234\272", nullptr));
        clearButton->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
        groupBox_2->setTitle(QString());
        gestureBox->setItemText(0, QCoreApplication::translate("Widget", "\346\211\213\346\217\241", nullptr));
        gestureBox->setItemText(1, QCoreApplication::translate("Widget", "\346\217\222\346\213\224", nullptr));

        forceBox->setItemText(0, QCoreApplication::translate("Widget", "20%", nullptr));
        forceBox->setItemText(1, QCoreApplication::translate("Widget", "50%", nullptr));
        forceBox->setItemText(2, QCoreApplication::translate("Widget", "80%", nullptr));

        curveBox->setItemText(0, QCoreApplication::translate("Widget", "\346\233\262\347\272\2771", nullptr));
        curveBox->setItemText(1, QCoreApplication::translate("Widget", "\346\233\262\347\272\2772", nullptr));
        curveBox->setItemText(2, QCoreApplication::translate("Widget", "\346\233\262\347\272\2773", nullptr));

        label_5->setText(QCoreApplication::translate("Widget", "\345\212\233\346\260\264\345\271\263\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "\345\212\233\346\233\262\347\272\277\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "\345\212\250  \344\275\234\357\274\232", nullptr));
        pathSelect->setText(QCoreApplication::translate("Widget", "\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
