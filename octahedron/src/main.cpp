#include    "main.h"

int main(int argc, char *argv[])
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(6);
    (*vertices)[0].set( 0.0f,  0.0f,  1.0f);
    (*vertices)[1].set(-0.5f, -0.5f,  0.0f);
    (*vertices)[2].set( 0.5f, -0.5f,  0.0f);
    (*vertices)[3].set( 0.5f,  0.5f,  0.0f);
    (*vertices)[4].set(-0.5f,  0.5f,  0.0f);
    (*vertices)[5].set( 0.0f,  0.0f, -1.0f);

    osg::ref_ptr<osg::DrawElementsUInt> indices = new osg::DrawElementsUInt(GL_TRIANGLES, 24);
    (*indices)[ 0] = 0; (*indices)[ 1] = 1; (*indices)[ 2] = 2;
    (*indices)[ 3] = 0; (*indices)[ 4] = 4; (*indices)[ 5] = 1;
    (*indices)[ 6] = 4; (*indices)[ 7] = 5; (*indices)[ 8] = 1;
    (*indices)[ 9] = 4; (*indices)[10] = 3; (*indices)[11] = 5;
    (*indices)[12] = 3; (*indices)[13] = 2; (*indices)[14] = 5;
    (*indices)[15] = 1; (*indices)[16] = 5; (*indices)[17] = 2;
    (*indices)[18] = 3; (*indices)[19] = 0; (*indices)[20] = 2;
    (*indices)[21] = 0; (*indices)[22] = 3; (*indices)[23] = 4;

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(vertices.get());
    geom->addPrimitiveSet(indices.get());
    osgUtil::SmoothingVisitor::smooth(*geom);

    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(geom.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
