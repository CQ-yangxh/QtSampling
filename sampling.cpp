#include "sampling.h"
#include <iostream>
using namespace std;

//用户数据缓冲区,大小定义为1000


samplingForce::samplingForce(QObject *parent) : QThread(parent)
{

}

void samplingForce::getFileName(QString file_name)
{
    fileName = file_name;
}

void samplingForce::run()
{
    USB3102A_AI_PARAM AIParam;
    U32 nReadSampsPerChan = 50, nSampsPerChanRead = 0;
    F64 fTimeout = 10.0; // 10秒钟超时
    U32 nAvailSampsPerChan = 0;
    HANDLE hDevice = INVALID_HANDLE_VALUE;
    QFile file(fileName);
    QTextStream out(&file);

    // 第一步 创建设备对象
    hDevice = USB3102A_DEV_Create(0, 0);
    if(hDevice == INVALID_HANDLE_VALUE)
    {
        printf("DEV_Create Error\n");
        getch();
    }

    memset(&AIParam, 0, sizeof(USB3102A_AI_PARAM));

    // 通道参数
    AIParam.nSampChanCount		= 1;
    for(int nChannel=0; nChannel<USB3102A_AI_MAX_CHANNELS; nChannel++)
    {
        AIParam.CHParam[nChannel].nChannel		= nChannel;
        AIParam.CHParam[nChannel].nSampleRange	= USB3102A_AI_SAMPRANGE_N10_P10V;
        AIParam.CHParam[nChannel].nRefGround	= USB3102A_AI_REFGND_RSE;
        AIParam.CHParam[nChannel].nReserved0	= 0;
        AIParam.CHParam[nChannel].nReserved1	= 0;
        AIParam.CHParam[nChannel].nReserved2	= 0;
    }

    AIParam.nSampleSignal			= USB3102A_AI_SAMPSIGNAL_AI;

    // 时钟参数
    AIParam.nSampleMode				= USB3102A_AI_SAMPMODE_CONTINUOUS;
    AIParam.nSampsPerChan			= 50;
    AIParam.fSampleRate				= 2000.0;
    AIParam.nClockSource			= USB3102A_AI_CLKSRC_LOCAL;
    AIParam.bClockOutput			= FALSE;

    // 开始触发参数
    AIParam.bDTriggerEn				= TRUE;
    AIParam.nDTriggerDir			= USB3102A_AI_TRIGDIR_FALLING;
    AIParam.bATriggerEn				= TRUE;
    AIParam.nATriggerDir			= USB3102A_AI_TRIGDIR_FALLING;
    AIParam.nATrigChannel			= 0;
    AIParam.fTriggerLevel			= 0.0;
    AIParam.nTriggerSens			= 5;
    AIParam.nDelaySamps				= 0;

    // 其他参数
    AIParam.nReserved1				= 0;
    AIParam.nReserved2				= 0;
    AIParam.nReserved3				= 0;

    if(!USB3102A_AI_VerifyParam(hDevice, &AIParam))
    {
        printf("参数有错，已被调整为合法值，请注意查看日志文件USB3102A.log, 按任意键继续...\n");
        getch();
    }

    // 第二步 初始化AI采集任务
    if(!USB3102A_AI_InitTask(hDevice, &AIParam, NULL))
    {
        printf("AI_InitTask Error\n");
        getch();
    }

    // 第三步 开始AI采集任务
    if(!USB3102A_AI_StartTask(hDevice))
    {
        printf("AI_StartTask Error\n");
        getch();
    }

    // 第四步 发送软件触发事件(硬件外触发时不需要)
    if(!USB3102A_AI_SendSoftTrig(hDevice))
    {
        printf("AI_SendSoftTrig Error\n");
        getch();
    }

    // 第五步 打开文件读写(只有当点击开始时才进行文件读写)
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        printf("File Open Error\n");
        getch();
    }

    // 第六步 循环读取AI数据
    while(1)
    {
        currentTime = QDateTime::currentDateTime();
        if(startTime.msecsTo(currentTime) > 15000) goto Exit;


        if(!USB3102A_AI_ReadAnalog(hDevice, fAnlgArray, nReadSampsPerChan, &nSampsPerChanRead, &nAvailSampsPerChan, fTimeout))
        {
            printf("Timeout nSampsPerChanRead=%d\n", nSampsPerChanRead);
            getch();
        }

        //把数据写入txt文本
        for (U32 nIndex = 0; nIndex < 50; nIndex++)
        {
            for (U32 nChannel = 0; nChannel < 1; nChannel++)
            {
                out<<"AI"<<nChannel<<"="<<fAnlgArray[nChannel + nIndex ];
            }
            out<<"\n";
        }


        xaxis_Time = (double)startTime.msecsTo(currentTime) / 1000;
        yaxis_Voltage = fAnlgArray[0];//取第一个数据用于画图

    }

Exit:
    printf("\nPress any key to quit...\n");
    getch();

    //清空残留数据
    xaxis_Time = 0;
    yaxis_Voltage = 0;

    // 第七步 关闭文件
    if(file.isOpen())
    {
        file.close();
        printf("open");
    }
    else printf("close");

    // 第八步 停止AI采集任务
    if(!USB3102A_AI_StopTask(hDevice))
    {
        printf("AI_StopTask Error\n");
        getch();
    }

    // 第九步 释放AI采集任务
    if(!USB3102A_AI_ReleaseTask(hDevice))
    {
        printf("AI_ReleaseTask Error\n");
        getch();
    }

    // 第十步 释放设备对象
    if(!USB3102A_DEV_Release(hDevice))
    {
        printf("DEV_Release Error\n");
        getch();
    }
}
