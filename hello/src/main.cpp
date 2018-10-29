#include    "main.h"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile("../data/cessna.osg");
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
