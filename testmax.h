#ifndef TESTMAX_H
#define TESTMAX_H

#include <QThread>
#include <QDateTime>
#include "USB3102A.h"
#include "USB3102ARSV.h"
#include "conio.h"

class testMax : public QThread
{
    Q_OBJECT
public:
    explicit testMax(QObject *parent = nullptr);
    QDateTime startTime, currentTime;
    double fAnlgArray [1000];
    double xaxis_Time;
    double yaxis_Voltage;
    double maxForce;
    int testCount;


protected:
    void run();
};

#endif // TESTMAX_H
