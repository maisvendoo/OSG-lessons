#include	"main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class InfoVisitor : public osg::NodeVisitor
{
public:

    InfoVisitor() : _level(0)
    {
        setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
    }

    std::string spaces()
    {
        return std::string(_level * 2, ' ');
    }

    virtual void apply(osg::Node &node);

    virtual void apply(osg::Geode &geode);

protected:

    unsigned int _level;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void InfoVisitor::apply(osg::Node &node)
{
    std::cout << spaces() << node.libraryName() << "::"
              << node.className() << std::endl;

    _level++;
    traverse(node);
    _level--;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void InfoVisitor::apply(osg::Geode &geode)
{
    std::cout << spaces() << geode.libraryName() << "::"
              << geode.className() << std::endl;

    _level++;

    for (unsigned int i = 0; i < geode.getNumDrawables(); ++i)
    {
        osg::Drawable *drawable = geode.getDrawable(i);

        std::cout << spaces() << drawable->libraryName() << "::"
                  << drawable->className() << std::endl;
    }

    traverse(geode);
    _level--;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    osg::ArgumentParser args(&argc, argv);
    osg::ref_ptr<osg::Node> root = osgDB::readNodeFiles(args);

    if (!root.valid())
    {
        OSG_FATAL << args.getApplicationName() << ": No data leaded. " << std::endl;
        return -1;
    }
    
    InfoVisitor infoVisitor;
    root->accept(infoVisitor);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
