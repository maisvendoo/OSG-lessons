#include	"main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Node *createLODNode(const std::string &filepath, const osg::Vec3 &pos)
{
    osg::ref_ptr<osg::PagedLOD> pagedLOD = new osg::PagedLOD;
    pagedLOD->setFileName(0, filepath);
    pagedLOD->setRange(0, 0.0f, FLT_MAX);

    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
    mt->setMatrix(osg::Matrix::translate(pos));
    mt->addChild(pagedLOD.get());

    return mt.release();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Group> root = new osg::Group;

    float dist = 50.0f;
    int N = 100;

    for (int i = 0; i < N; ++i)
    {
        float x = i * dist;

        for (int j = 0; j < N; ++j)
        {
            float y = j * dist;
            osg::Vec3 pos(x, y, 0.0f);
            osg::ref_ptr<osg::Node> node = createLODNode("../data/cessna.osg", pos);
            root->addChild(node.get());
        }
    }

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
