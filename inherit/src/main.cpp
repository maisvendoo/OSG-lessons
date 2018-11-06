#include	"main.h"

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("../data/glider.osg");

    osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform;
    transform1->setMatrix(osg::Matrix::translate(-0.5f, 0.0f, 0.0f));
    transform1->addChild(model.get());

    osg::ref_ptr<osg::MatrixTransform> transform2 = new osg::MatrixTransform;
    transform2->setMatrix(osg::Matrix::translate(0.5f, 0.0f, 0.0f));
    transform2->addChild(model.get());

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(transform1.get());
    root->addChild(transform2.get());

    transform1->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    transform2->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
    root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
