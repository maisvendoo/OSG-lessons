#include    "main.h"

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Node> modelL3 = osgDB::readNodeFile("../data/cessna.osg");

    osg::ref_ptr<osg::Node> modelL2 = dynamic_cast<osg::Node *>(modelL3->clone(osg::CopyOp::DEEP_COPY_ALL));
    osg::ref_ptr<osg::Node> modelL1 = dynamic_cast<osg::Node *>(modelL3->clone(osg::CopyOp::DEEP_COPY_ALL));

    osgUtil::Simplifier simplifer;
    simplifer.setSampleRatio(0.5f);
    modelL2->accept(simplifer);

    simplifer.setSampleRatio(0.1f);
    modelL1->accept(simplifer);

    osg::ref_ptr<osg::LOD> root = new osg::LOD;
    root->addChild(modelL1.get(), 200.0f, FLT_MAX);
    root->addChild(modelL2.get(), 50.0f, 200.0f);
    root->addChild(modelL3.get(), 0.0f, 50.0f);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
