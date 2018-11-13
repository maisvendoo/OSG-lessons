#include	"main.h"

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = 50;
    traits->y = 50;
    traits->width = 800;
    traits->height = 600;
    traits->windowName = "OSG application";
    traits->windowDecoration = true;
    traits->doubleBuffer = true;
    traits->samples = 4;

    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(gc);
    camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
    camera->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    camera->setClearColor( osg::Vec4(0.2f, 0.2f, 0.4f, 1.0f) );
    double aspect = static_cast<double>(traits->width) / static_cast<double>(traits->height);
    camera->setProjectionMatrixAsPerspective(30.0, aspect, 1.0, 1000.0);
    camera->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);

    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("../data/cessna.osg");

    osgViewer::Viewer viewer;
    viewer.setCamera(camera.get());
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
