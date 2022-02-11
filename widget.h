#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QString>
#include <QThread>
#include "qcustomplot.h"
#include "testmax.h"
#include "sampleforce.h"

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
    QTimer mDataTimer;
    TestMax *actestmax;
    Sampleforce *acforce;
    double maxAve;
    double max = 10;
    double coe = 0.2;

private slots:
  void timerSlot();
  void on_curveBox_currentIndexChanged(int index);
  void on_maxTest_clicked();
  void on_forceBox_currentIndexChanged(int index);
  void on_startButton_clicked();
  void on_clearButton_clicked();
};
#endif // WIDGET_H
