#ifndef     QVIEWER_WIDGET_H
#define     QVIEWER_WIDGET_H

#include    <QWidget>

#include    <osgViewer/Viewer>
#include    <osgQt/GraphicsWindowQt>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class QViewerWidget : public QWidget
{
public:

    QViewerWidget(const QRect &geometry);

    virtual ~QViewerWidget();

    osg::Group *getScene();

    osgViewer::Viewer *getViewer();

protected:

    osg::ref_ptr<osg::Group> scene;

    osgViewer::Viewer   viewer;

private:

    osgQt::GraphicsWindowQt *createGraphicsWindow(const QRect &geometry);

    void initCamera(const QRect &geometry);

    void paintEvent(QPaintEvent *);
};

#endif // QVIEWER_WIDGET_H
