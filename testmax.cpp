#include "testmax.h"
#include <iostream>
using namespace std;
TestMax::TestMax(QObject *parent) : QThread(parent)
{
    testCount = 0;
    maxForce = 0;
    fAnlgArray_Test.resize(600);
    time_Test.resize(600);
}

void TestMax::GetMax()
{
    //暂时没用
}

void TestMax::run()
{
    while(1)
    {
        currentTime = QDateTime::currentDateTime();
        for(int i = 0; i < 600; i++)
        {
            fAnlgArray_Test[i] = 1 + (double)(rand() % 1000) / 1000;
            time_Test[i] = (double)startTime.msecsTo(currentTime) / 1000;
            //求取最大值
            if(fAnlgArray_Test[i] > maxForce) maxForce = fAnlgArray_Test[i];
        }
        cout<<time_Test[0]<<"     "<<fAnlgArray_Test[0]<<endl;
        msleep(50);
    }
}
