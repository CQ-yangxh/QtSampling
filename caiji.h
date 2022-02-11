#ifndef CAIJI_H
#define CAIJI_H

#include <QThread>
#include "USB3102A.h"
#include "USB3102ARSV.h"
#include "conio.h"

class Caiji : public QThread
{
    Q_OBJECT
public:


     void AI_Init_Task();//初始化函数
     void AI_Start_Task();//开始采集
     void AI_Release_Task();//释放采集卡


signals:

public slots:

private:
     explicit Caiji(QObject *parent = nullptr);
     //申明一些变量
     USB3102A_AI_PARAM AIParam;
     U32 nReadSampsPerChan = 1024,
         nSampsPerChanRead = 0;
     F64 fTimeout = 10.0; // 10秒钟超时
     U32 nAvailSampsPerChan = 0;
     HANDLE hDevice = INVALID_HANDLE_VALUE;

     int kkk=1;
     int jj=1;

     F64 fAnlgArray[32768];



};

#endif // CAIJI_H
