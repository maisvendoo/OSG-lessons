#ifndef     KEY_HANDLER_H
#define     KEY_HANDLER_H

#include    <osgGA/GUIEventHandler>
#include    <QObject>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class KeyboardHandler : public QObject, public osgGA::GUIEventHandler
{
    Q_OBJECT

public:

    KeyboardHandler(QObject *parent = Q_NULLPTR)
        : QObject(parent)
        , osgGA::GUIEventHandler ()
    {

    }

    bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
    {
        switch (ea.getEventType())
        {
        case osgGA::GUIEventAdapter::KEYDOWN:

            emit sendMessage("Pressed key " + QString(ea.getKey()));

            break;

        default:

            break;
        }


        return false;
    }

signals:

    void sendMessage(QString msg);

private:
};

#endif // KEY_HANDLER_H
