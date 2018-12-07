#include	"main.h"

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("../data/cubic2.dmd");


    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("../data/Images/cubic.bmp");

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D(image.get());
    texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture::REPEAT);
    texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::REPEAT);
    texture->setUnRefImageDataAfterApply(true);

    model->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(model.get());
    viewer.setUpViewOnSingleScreen(0);
    
    return viewer.run();
}
