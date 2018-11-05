#include	"main.h"

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::DisplaySettings::instance()->setNumMultiSamples(0);

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("../data/cessna.osg");

    osgViewer::Viewer viewer;
    viewer.setSceneData(model.get());

    return viewer.run();
}
