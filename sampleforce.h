#ifndef SAMPLEFORCE_H
#define SAMPLEFORCE_H

#include <QThread>
#include "USB3102A.h"
#include "USB3102ARSV.h"
#include "conio.h"
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QFileDialog>
#include <QFile>


/*通道0接触发电平，通道1接指捏力，通道2手握力，通道3旋转力，通道4插拔力，通道5接开关*/


class Sampleforce : public QThread
{
    Q_OBJECT
public:
    explicit Sampleforce(QObject *parent = nullptr);

    double fAnlgArray[600];   //32768
    //bool ac_sample_flag = true;//采集过程的标志位
    double force_data[100];
    QString save_aa;
    bool ac_sample_flag;//采集过程的标志位
    int force_type;

protected:
    void run();

signals:
    void force_send(double *ccc);

public slots:
};

#endif // SAMPLEFORCE_H
