#include	"main.h"

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::ProxyNode> root = new osg::ProxyNode;
    root->setFileName(0, "../data/cow.osg");

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
