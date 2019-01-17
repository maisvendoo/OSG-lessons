#include    "qosgapp.h"



QOSGApplication::QOSGApplication(int argc, char *argv[], QObject *parent)
    : QObject (parent)
{
    osg::ref_ptr<osgQt::QWidgetImage> widgetImage = new osgQt::QWidgetImage(createWidget());

    osg::ref_ptr<osgViewer::InteractiveImageHandler> handler = new osgViewer::InteractiveImageHandler(widgetImage.get());

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage(widgetImage.get());

    osg::ref_ptr<osg::Geometry> quad =
    osg::createTexturedQuadGeometry(osg::Vec3(), osg::X_AXIS, osg::Z_AXIS);
    quad->setEventCallback( handler.get() );
    quad->setCullCallback( handler.get() );

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( quad.get() );
    geode->getOrCreateStateSet()->setTextureAttributeAndModes( 0, texture.get() );
    geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    geode->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( geode.get() );

    viewer.setSceneData(root.get());
    viewer.addEventHandler(new QtEventsHandler);
}

QOSGApplication::~QOSGApplication()
{

}

int QOSGApplication::exec()
{
    return viewer.run();
}

QWidget *QOSGApplication::createWidget()
{
    QWidget *widget = new QWidget;

    widget->setGeometry(1, 1, 500, 500);
    widget->setLayout(new QVBoxLayout);

    QPushButton *button = new QPushButton("Нажми!");
    button->setGeometry(10, 10, 100, 50);
    widget->layout()->addWidget(button);

    return widget;
}
