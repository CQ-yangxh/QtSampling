#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QThread>
#include "qcustomplot.h"
#include "sampling.h"
#include "testmax.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setupPlot();

private:
    Ui::Widget *ui;
    QPointer<QCPGraph> mGraph1;
    QPointer<QCPGraph> mGraph2;
    QTimer mDataTimer1;
    QTimer mDataTimer2;
    samplingForce *acsamp;
    testMax *actestmax;
    double maxAve;
    double max = 10;
    double coe = 0.2;

private slots:
  void timerSlot1();
  void timerSlot2();
  void on_curveBox_currentIndexChanged(int index);
  void on_maxTest_clicked();
  void on_forceBox_currentIndexChanged(int index);
  void on_startButton_clicked();
  void on_clearButton_clicked();
  void on_pathSelect_clicked();
};
#endif // WIDGET_H
