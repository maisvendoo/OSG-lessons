#include    "main.h"

int main(int argc, char *argv[])
{
    osg::ArgumentParser args(&argc, argv);
    std::string filename;
    args.read("--model", filename);

    osg::ref_ptr<osg::Node> root = osgDB::readNodeFile(filename);
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
