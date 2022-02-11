#ifndef TESTMAX_H
#define TESTMAX_H


#include <QThread>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDateTime>
#include "USB3102A.h"
#include "USB3102ARSV.h"
#include "conio.h"

/*通道0接触发电平，通道1接指捏力，通道2手握力，通道3旋转力，通道4插拔力，通道5接开关*/
class TestMax : public QThread
{
    Q_OBJECT
public:
    explicit TestMax(QObject *parent = nullptr);
    void GetMax();
    QDateTime startTime, currentTime;
    QVector<double> fAnlgArray_Test;//存储了所有通道的数据
    QVector<double> time_Test;//存储了所有通道的数据
    double maxForce;
    int testCount;


protected:
    void run();

signals:

public slots:
};

#endif // TESTMAX_H
