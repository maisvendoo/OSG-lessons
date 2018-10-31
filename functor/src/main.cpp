#include    "main.h"

std::string vec2str(const osg::Vec3 &v)
{
    std::string tmp = std::to_string(v.x());
    tmp += " ";
    tmp += std::to_string(v.y());
    tmp += " ";
    tmp += std::to_string(v.z());

    return tmp;
}

struct FaceCollector
{
    void operator()(const osg::Vec3 &v1,
                    const osg::Vec3 &v2,
                    const osg::Vec3 &v3)
    {
        std::cout << "Face vertices: "
                  << vec2str(v1)
                  << "; " << vec2str(v2)
                  << "; " << vec2str(v3) << std::endl;
    }
};

int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back( osg::Vec3(0.0f, 0.0f, 0.0f) );
    vertices->push_back( osg::Vec3(0.0f, 0.0f, 1.0f) );
    vertices->push_back( osg::Vec3(1.0f, 0.0f, 0.0f) );
    vertices->push_back( osg::Vec3(1.0f, 0.0f, 1.5f) );
    vertices->push_back( osg::Vec3(2.0f, 0.0f, 0.0f) );
    vertices->push_back( osg::Vec3(2.0f, 0.0f, 1.0f) );
    vertices->push_back( osg::Vec3(3.0f, 0.0f, 0.0f) );
    vertices->push_back( osg::Vec3(3.0f, 0.0f, 1.5f) );
    vertices->push_back( osg::Vec3(4.0f, 0.0f, 0.0f) );
    vertices->push_back( osg::Vec3(4.0f, 0.0f, 1.0f) );

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back( osg::Vec3(0.0f, -1.0f, 0.0f) );

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(vertices.get());
    geom->setNormalArray(normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    geom->addPrimitiveSet(new osg::DrawArrays(GL_QUAD_STRIP, 0, 10));

    osg::ref_ptr<osg::Geode> root = new osg::Geode;
    root->addDrawable(geom.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    osg::TriangleFunctor<FaceCollector> functor;
    geom->accept(functor);

    return viewer.run();
}
