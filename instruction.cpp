#include "instruction.h"
#include "widget.h"



Instruction::Instruction(QObject *parent) : QThread(parent)
{

}

void Instruction::run()
{

  ins_flag = false;
   for(int i=0; i<=50; i++)
   {

     //qDebug() << "开启线程";
   qDebug() << i;
   emit send_cishu(i);
   msleep(7000);
   emit send_kaishi();
   msleep(6000);
   emit send_xiuxi();

   if(ins_flag) break;

   }

   emit send_xiuxi();

}
