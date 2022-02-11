#ifndef INSTRUTION_H
#define INSTRUTION_H

#include <QThread>
#include <QDebug>



class Instruction : public QThread
{
    Q_OBJECT
public:
    explicit Instruction(QObject *parent = nullptr);
    //~Instrution();
    bool ins_flag;

protected:
    void run();

signals:
    void send_kaishi();
    void send_xiuxi();
    void send_cishu(int cishu);

public slots:
};

#endif // INSTRUTION_H
