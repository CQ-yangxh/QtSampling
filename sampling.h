#ifndef SAMPLING_H
#define SAMPLING_H


#include <QThread>
#include <QDebug>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QDateTime>
#include "USB3102A.h"
#include "USB3102ARSV.h"
#include "conio.h"

class samplingForce : public QThread
{
    Q_OBJECT
    QString fileName;

public:
    explicit samplingForce(QObject *parent = nullptr);
    QDateTime startTime, currentTime;
    double fAnlgArray [1000];
    double xaxis_Time;
    double yaxis_Voltage;
    bool openFile(QString);
    void getFileName(QString);


protected:
    void run();

signals:

public slots:
};

#endif // SAMPLING_H
