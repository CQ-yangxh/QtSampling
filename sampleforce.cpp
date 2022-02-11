#include "sampleforce.h"

Sampleforce::Sampleforce(QObject *parent) : QThread(parent)
{

}


void Sampleforce::run()
{

        USB3102A_AI_PARAM AIParam;
        U32 nReadSampsPerChan = 100,
            nSampsPerChanRead = 0;
        F64 fTimeout = 10.0; // 10秒钟超时
        U32 nAvailSampsPerChan = 0;
        HANDLE hDevice = INVALID_HANDLE_VALUE;


        // 第一步 创建设备对象
        hDevice = USB3102A_DEV_Create(0, 0);
        if(hDevice == INVALID_HANDLE_VALUE)
        {
            printf("DEV_Create Error\n");
            getch();
    //        return 0;
        }
//       int kkk=1;
//       int jj=1;

        memset(&AIParam, 0, sizeof(USB3102A_AI_PARAM));

        // 通道参数
        AIParam.nSampChanCount		= 6;
        for(int nChannel=0; nChannel<USB3102A_AI_MAX_CHANNELS; nChannel++)
        {
            AIParam.CHParam[nChannel].nChannel		= nChannel;
            AIParam.CHParam[nChannel].nSampleRange	= USB3102A_AI_SAMPRANGE_N5_P5V;
            AIParam.CHParam[nChannel].nRefGround	= USB3102A_AI_REFGND_RSE;
            AIParam.CHParam[nChannel].nReserved0	= 0;
            AIParam.CHParam[nChannel].nReserved1	= 0;
            AIParam.CHParam[nChannel].nReserved2	= 0;
        }

        AIParam.nSampleSignal			= USB3102A_AI_SAMPSIGNAL_AI;

        // 时钟参数
        AIParam.nSampleMode				= USB3102A_AI_SAMPMODE_CONTINUOUS;
        AIParam.nSampsPerChan			= 100;
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


        ///////////////////////////



        // 第五步 循环读取AI数据

        //int k=0;
        int jj=0;

//        while(kkk--)
        QFile file(save_aa); //参数就是读取文件的路径
        if(file.open(QIODevice::Append | QIODevice::Text)) //以文本文式写入
            {
                QTextStream out(&file);
        while(ac_sample_flag)
       //while(!kbhit())
        {


            //QTimer *ac_Timer = new QTimer;
            //QTimer *send_Timer = new QTimer;

//            connect(ac_Timer, &QTimer::timeout, [=]()
//            {
//                //ac_sample_flag = false;
//                send_flag();
//            });

            //connect(this,&sampleforce::send_flag,this, &sampleforce::change_flag);

            //ac_Timer->start(6000);     //定时器开启1min

            //printf("Wait...\n");
            if(!USB3102A_AI_ReadAnalog(hDevice, fAnlgArray, nReadSampsPerChan, &nSampsPerChanRead, &nAvailSampsPerChan, fTimeout))
            {
                //printf("Timeout nSampsPerChanRead=%d\n", nSampsPerChanRead);
                getch();

            }

            double piaoyi;
            if(force_type == 0)
            {
                piaoyi = -0.023;
            }
            else if(force_type == 1)
            {
                piaoyi = 0.06;
            }
            else if(force_type == 2)
            {
                piaoyi = -0.07;
            }
            else piaoyi = 0.24;
            //qDebug() << save_aa;
            for(U32 nIndex=0; nIndex<100; nIndex++)
            {
                for(U32 nChannel=0; nChannel<AIParam.nSampChanCount; nChannel++)
                {
                      //printf("%d,AI%02d=%6.4f(V) ",k++,nChannel, fAnlgArray[nChannel+nIndex*AIParam.nSampChanCount]);   // 数据结果*/
                      if(nChannel==force_type + 1)
                      {
                           jj++;
                           force_data[nIndex] = fAnlgArray[nChannel+nIndex*AIParam.nSampChanCount]-piaoyi;
out<<jj<<"  "<<fAnlgArray[nIndex*AIParam.nSampChanCount]<<"  "<<fAnlgArray[nChannel+nIndex*AIParam.nSampChanCount]<<"  "<<fAnlgArray[5+nIndex*AIParam.nSampChanCount]<<endl;

                      }
                }
                      //printf("\n");
            }

             //此处开始存储数据
//             QFile file(save_aa); //参数就是读取文件的路径
//             if(file.open(QIODevice::Append | QIODevice::Text)) //以文本文式写入
//                 {
//                     QTextStream out(&file);
//                     int set_Channel= 1;

//                     for(U32 nIndex=0; nIndex<100; nIndex++)
//                     {
//                         for(U32 nChannel=0; nChannel<AIParam.nSampChanCount; nChannel++)
//                         {
//                               if(nChannel==0)
//                               {
//                                   k++;
//        out<<k<<"  "<<fAnlgArray[nChannel+nIndex*AIParam.nSampChanCount]<<"  "<<fAnlgArray[set_Channel+nChannel+nIndex*AIParam.nSampChanCount]<<endl;

//                               }
//                           }
//                     }

//                     file.close();
//                 }



            //emit force_send(force_data);

//            if(ac_sample_flag) force_work();

            //if(!ac_sample_flag) goto Exit;
            if(kbhit()) goto Exit;
        }
        file.close();
    }




        Exit:
        printf("\nPress any key to quit...\n");
        getch();

        // 第六步 停止AI采集任务
        if(!USB3102A_AI_StopTask(hDevice))
        {
            printf("AI_StopTask Error\n");
            getch();
        }

        // 第七步 释放AI采集任务
        if(!USB3102A_AI_ReleaseTask(hDevice))
        {
            printf("AI_ReleaseTask Error\n");
            getch();
        }

        // 第八步 释放设备对象
        if(!USB3102A_DEV_Release(hDevice))
        {
            printf("DEV_Release Error\n");
            getch();
        }

}



