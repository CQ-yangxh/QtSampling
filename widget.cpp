#include "widget.h"
#include "ui_widget.h"
#include <iostream>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setupPlot();

    actestmax = new testMax;
    acsamp = new samplingForce;

    //最大力实时绘制函数timerSlot1
    connect(&mDataTimer1, SIGNAL(timeout()), this, SLOT(timerSlot1()));
    //采集力实时绘制函数timerSlot2
    connect(&mDataTimer2, SIGNAL(timeout()), this, SLOT(timerSlot2()));

}

Widget::~Widget()
{
    delete ui;
}

//*******************显示界面初始化函数******************//
void Widget::setupPlot()
{

    mGraph1=ui->mplot->addGraph();//添加第一条曲线，用于指示
    mGraph2=ui->mplot->addGraph();//添加第二条曲线，用于指示

    //设置图表
    ui->mplot->xAxis->setLabel(QStringLiteral("时间/s"));//设置x坐标轴名称
    ui->mplot->xAxis->setLabelColor(QColor(20,20,20));//设置x坐标轴名称颜色
    ui->mplot->xAxis->setRange(0,15);//设定x轴的范围

    ui->mplot->yAxis->setLabel(QStringLiteral("电压/N"));//设置y坐标轴名称
    ui->mplot->yAxis->setLabelColor(QColor(20,20,20));//设置y坐标轴名称颜色

    ui->mplot->axisRect()->setupFullAxesBox(true);//设置缩放，拖拽，设置图表的分类图标显示位置
    ui->mplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom| QCP::iSelectAxes);
    ui->mplot->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop | Qt::AlignRight);//图例显示位置右上
    ui->mplot->legend->setVisible(true);//显示图例

    QPen pen1,pen2;
    pen1.setWidth(1); //设置画笔线条宽度
    pen2.setWidth(2);
    pen1.setColor(Qt::red);//设置画笔颜色
    pen2.setColor(Qt::blue);
    mGraph1->setPen(pen1);
    mGraph2->setPen(pen2);
    mGraph1->setName("目标曲线");
    mGraph2->setName("测量曲线");

    mGraph1->setAntialiasedFill(false);
    mGraph1->setLineStyle((QCPGraph::LineStyle)1);//曲线画笔
    mGraph1->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssNone,5));//曲线形状

    //初始化目标曲线
    QVector<double> x(6),y(6);
    for(int i = 0 ; i < 6; i ++) x[i] = 3 * i;
    y[2] = 0.2 * 10;
    y[3] = 0.2 * 10;
    mGraph1->addData(x,y);

    ui->mplot->replot();
}

//*******************测试按钮的槽函数**********************//
void Widget::on_maxTest_clicked()
{
    mGraph1->data()->clear();
    mGraph2->data()->clear();
    actestmax->maxForce = 0;
    actestmax->startTime = QDateTime::currentDateTime();
    actestmax->start();
    mDataTimer1.start(10);
}

//*******************开始按钮的槽函数********************//
void Widget::on_startButton_clicked()
{
    mGraph2->data()->clear();
    acsamp->startTime = QDateTime::currentDateTime();
    acsamp->start();
    mDataTimer2.start(10);
}

//*****************定时器1的槽函数*******************//
void Widget::timerSlot1()
{
    QString max;
    if(actestmax->startTime.msecsTo(actestmax->currentTime) > 15000)
    {
        actestmax->testCount ++;
        switch(actestmax->testCount){
        case 1:
            ui->textEdit_1->setPlainText(max.number(actestmax->maxForce));
             maxAve += actestmax->maxForce;
            mDataTimer1.stop();
            break;
        case 2:
              ui->textEdit_2->setPlainText(max.number(actestmax->maxForce));
               maxAve += actestmax->maxForce;
              mDataTimer1.stop();
            break;
        case 3:
              ui->textEdit_3->setPlainText(max.number(actestmax->maxForce));
               maxAve += actestmax->maxForce;
              mDataTimer1.stop();
              //求平均值，重置参数
              maxAve = maxAve / 3;
              actestmax->testCount = 0;
              ui->textEdit_4->setPlainText(max.number(maxAve));
            break;
        default :
            break;
        }
    }
    else
    {
        mGraph2->addData(actestmax->xaxis_Time,actestmax->yaxis_Voltage);
        mGraph2->rescaleValueAxis(true);
        ui->mplot->replot();
    }
}

//*****************定时器2的槽函数*******************//
void Widget::timerSlot2()
{
    QString max;
    if(acsamp->startTime.msecsTo(acsamp->currentTime) > 15000)
    {
        mDataTimer2.stop();
    }
    else
    {
        mGraph2->addData(acsamp->xaxis_Time,acsamp->yaxis_Voltage);
        mGraph2->rescaleValueAxis(true);
        ui->mplot->replot();
    }
}

//******************力曲线切换槽函数*********************//
void Widget::on_curveBox_currentIndexChanged(int index)
{
    mGraph1->data()->clear();
    switch( index){
    case 0:{
        QVector<double> x(6),y(6);
        for(int i = 0 ; i < 6; i ++) x[i] = 3 * i;
        y[2] = coe * maxAve;
        y[3] = coe * maxAve;
        mGraph1->addData(x,y);
        ui->mplot->replot();
        break;
    }
    case 1:{
        QVector<double> x(16),y(16);
        for(int i = 0 ; i < 16; i ++) x[i] = i;
        for(int i = 3; i <= 5; i ++ ) y[i] = 0.5 * coe * maxAve *(x[i] - 3);
        for(int i = 6; i <= 8; i ++) y[i] = coe * maxAve;
        for(int i = 9; i <= 11; i ++ ) y[i] = 0.5 * coe * maxAve *(11 - x[i]);
        mGraph1->addData(x,y);
        ui->mplot->replot();
        break;
    }
    case 2:{
        QVector<double> x(5),y(5);
        x[1] = 3;
        x[2] = 8;
        x[3] = 13;
        x[4] = 15;
        y[2] = coe * maxAve;
        mGraph1->addData(x,y);
        ui->mplot->replot();
        break;
    }
    default:{
        break;
    }
    }
}

//*******************力水平切换槽函数*******************//
void Widget::on_forceBox_currentIndexChanged(int index)
{
    switch( index){//switch语句用于判断当前的索引
    case 0:
        coe = 0.2;
        break;
    case 1:
        coe = 0.5;
        break;
    case 2:
        coe = 0.8;
        break;
    }
    ui->mplot->yAxis->setRange(0, maxAve * coe + 1);//设定y轴范围
    on_curveBox_currentIndexChanged(ui->curveBox->currentIndex());
}

//*****************清空按钮的槽函数*********************//
void Widget::on_clearButton_clicked()
{
    mGraph2->data()->clear();
    ui->mplot->replot();
}

//*****************路径选取按钮的槽函数*********************//
void Widget::on_pathSelect_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(NULL,"路径选择",".","*.txt");
    ui->pathPrint->setText(file_name);
    acsamp->getFileName(file_name);
}

