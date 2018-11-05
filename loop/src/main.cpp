#include	"main.h"

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("../data/lz.osg");

    osgViewer::Viewer viewer;

    viewer.setSceneData(model.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    while (!viewer.done())
    {
        viewer.frame();
        std::cout << "Frame number: " << viewer.getFrameStamp()->getFrameNumber() << std::endl;
    }
    
    return 0;
}
