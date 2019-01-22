#ifndef     QOSG_APP_H
#define     QOSG_APP_H

#include    <QApplication>
#include    <QWidget>
#include    <QMainWindow>
#include    <QPushButton>
#include    <QVBoxLayout>
#include    <osgViewer/ViewerEventHandlers>
#include    <osgViewer/Viewer>
#include    <osgQt/QWidgetImage>
#include    <osg/Texture2D>

#include    "qt-events.h"

class QOSGApplication : public QObject
{
    Q_OBJECT

public:

    QOSGApplication(int argc, char *argv[], QObject *parent = Q_NULLPTR);
    ~QOSGApplication();

    int exec();

private:

    osgViewer::Viewer   viewer;

    QWidget *createWidget();

private slots:


};

#endif // QOSG_APP_H
