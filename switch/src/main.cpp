#include    "main.h"

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("../data/cessna.osg");
    osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("../data/cessnafire.osg");

    osg::ref_ptr<osg::Switch> root = new osg::Switch;

    root->addChild(model1.get(), false);
    root->addChild(model2.get(), true);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
