#include	"main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Geometry *createQuad(const osg::Vec3 &pos, float w, float h)
{
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
    vertices->push_back( pos + osg::Vec3( w / 2, 0.0f, -h / 2) );
    vertices->push_back( pos + osg::Vec3( w / 2, 0.0f,  h / 2) );
    vertices->push_back( pos + osg::Vec3(-w / 2, 0.0f,  h / 2) );
    vertices->push_back( pos + osg::Vec3(-w / 2, 0.0f, -h / 2) );

    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

    osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array;
    texcoords->push_back( osg::Vec2(1.0f, 1.0f) );
    texcoords->push_back( osg::Vec2(1.0f, 0.0f) );
    texcoords->push_back( osg::Vec2(0.0f, 0.0f) );
    texcoords->push_back( osg::Vec2(0.0f, 1.0f) );

    osg::ref_ptr<osg::Geometry> quad = new osg::Geometry;
    quad->setVertexArray(vertices.get());
    quad->setNormalArray(normals.get());
    quad->setNormalBinding(osg::Geometry::BIND_OVERALL);
    quad->setTexCoordArray(0, texcoords.get());
    quad->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));

    return quad.release();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Node> sub_model = osgDB::readNodeFile("../data/cessna.osg");

    osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform;
    transform1->setMatrix(osg::Matrix::rotate(0.0, osg::Vec3(0.0f, 0.0f, 1.0f)));
    transform1->addChild(sub_model.get());

    osg::ref_ptr<osg::Geode> model = new osg::Geode;
    model->addChild(createQuad(osg::Vec3(0.0f, 0.0f, 0.0f), 2.0f, 2.0f));

    int tex_widht = 1024;
    int tex_height = 1024;

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setTextureSize(tex_widht, tex_height);
    texture->setInternalFormat(GL_RGBA);
    texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
    texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);

    model->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());    

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setViewport(0, 0, tex_widht, tex_height);
    camera->setClearColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->setRenderOrder(osg::Camera::PRE_RENDER);
    camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
    camera->attach(osg::Camera::COLOR_BUFFER, texture.get());

    camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
    camera->addChild(transform1.get());

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(model.get());
    root->addChild(camera.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);
    viewer.setUpViewOnSingleScreen(0);

    camera->setProjectionMatrixAsPerspective(30.0, static_cast<double>(tex_widht) / static_cast<double>(tex_height), 0.1, 1000.0);

    float dist = 100.0f;
    float alpha = 10.0f * 3.14f / 180.0f;

    osg::Vec3 eye(0.0f, -dist * cosf(alpha), dist * sinf(alpha));
    osg::Vec3 center(0.0f, 0.0f, 0.0f);
    osg::Vec3 up(0.0f, 0.0f, -1.0f);
    camera->setViewMatrixAsLookAt(eye, center, up);

    float phi = 0.0f;
    float delta = -0.01f;

    while (!viewer.done())
    {
        transform1->setMatrix(osg::Matrix::rotate(static_cast<double>(phi), osg::Vec3(0.0f, 0.0f, 1.0f)));
        viewer.frame();
        phi += delta;
    }

    return 0;
}
