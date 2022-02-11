#include "caiji.h"



Caiji::Caiji(QObject *parent) : QThread(parent)
{



}

void Caiji::AI_Init_Task()
{

        // 第一步 创建设备对象
            hDevice = USB3102A_DEV_Create(0, 0);
            if(hDevice == INVALID_HANDLE_VALUE)
            {
                printf("DEV_Create Error\n");
                getch();
        //        return 0;
            }

            memset(&AIParam, 0, sizeof(USB3102A_AI_PARAM));

            // 通道参数
                   AIParam.nSampChanCount		= 4;
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
                   AIParam.nSampsPerChan			= 1024;
                   AIParam.fSampleRate				= 25000.0;
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






}

void Caiji::AI_Start_Task()
{
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

    //            QFile file(filepath);
    //            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    //                return ;

    //            QTextStream cc(&file);


            // 第五步 循环读取AI数据

    //        while(kkk--)
             while(!kbhit())
            {
                printf("Wait...\n");
                if(!USB3102A_AI_ReadAnalog(hDevice, fAnlgArray, nReadSampsPerChan, &nSampsPerChanRead, &nAvailSampsPerChan, fTimeout))
                {
                    printf("Timeout nSampsPerChanRead=%d\n", nSampsPerChanRead);
                    getch();
                }

                for(U32 nIndex=0; nIndex<64; nIndex++)
                {
                    for(U32 nChannel=0; nChannel<AIParam.nSampChanCount; nChannel++)
                    {
                             printf("AI%02d=%6.4f(V) ",nChannel, fAnlgArray[nChannel+nIndex*AIParam.nSampChanCount]);   // 数据结果*/
    //                                QTextStream out(&file);
    //                                out.setRealNumberPrecision(4);
    //                             file.write(fAnlgArray[nChannel+nIndex*AIParam.nSampChanCount]);
    //                             out <<"AI"<<nChannel<<"="<< fAnlgArray[nChannel+nIndex*AIParam.nSampChanCount]<<"(V)"<<"  ";
                    }
                          printf("\n");
    //                      QTextStream out(&file);
    //                      out<<"\n";

                }
                if(kbhit()) goto Exit;
            }

    //            file.close();


            Exit:
            printf("\nPress any key to quit...\n");
            getch();

}

void Caiji::AI_Release_Task()
{
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


