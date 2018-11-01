#include    "main.h"

int main(int argc, char *argv[])
{
    (void) argc, (void) argv;

    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("../data/cessna.osg");
    osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("../data/cow.osg");

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(model1.get());
    root->addChild(model2.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
