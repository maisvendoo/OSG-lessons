#ifndef     RECEIVER_H
#define     RECEIVER_H

#include    <QObject>
#include    <iostream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class Receiver : public QObject
{
    Q_OBJECT

public:

    Receiver(QObject *parent = Q_NULLPTR) : QObject(parent) {}

public slots:

    void printMessage(QString msg)
    {
        std::cout << msg.toStdString() << std::endl;
    }
};

#endif // RECEIVER_H
