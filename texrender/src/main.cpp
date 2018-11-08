#include	"main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class FindTextureVisitor : public osg::NodeVisitor
{
public:

    FindTextureVisitor( osg::Texture *tex )
        : _texture(tex)
        , _first_call(true)
    {
        setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN);
    }

    virtual void apply(osg::Node &node);
    virtual void apply(osg::Geode &geode);

    void replaceTexture(osg::StateSet *ss);

protected:

    osg::ref_ptr<osg::Texture>  _texture;
    bool _first_call;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void FindTextureVisitor::apply(osg::Node &node)
{
    replaceTexture(node.getStateSet());
    traverse(node);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void FindTextureVisitor::apply(osg::Geode &geode)
{
    replaceTexture(geode.getStateSet());

    for (unsigned int i = 0; i < geode.getNumDrawables(); ++i)
    {
        replaceTexture(geode.getDrawable(i)->getStateSet());
    }

    traverse(geode);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void FindTextureVisitor::replaceTexture(osg::StateSet *ss)
{
    if (ss)
    {
        osg::Texture *oldTexture = dynamic_cast<osg::Texture *>(ss->getTextureAttribute(0, osg::StateAttribute::TEXTURE));

        if ( (oldTexture) || _first_call )
        {
            _first_call = false;
            ss->setTextureAttribute(0, _texture.get());
        }
    }
}

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

    osg::ref_ptr<osg::Node> sub_model = osgDB::readNodeFile("../data/glider.osg");

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

    FindTextureVisitor ftv(texture.get());
    if (model.valid())
        model->accept(ftv);

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setViewport(0, 0, tex_widht, tex_height);
    camera->setClearColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->setRenderOrder(osg::Camera::PRE_RENDER);
    camera->setRenderTargetImplementation(osg::Camera::FRAME_BUFFER_OBJECT);
    camera->attach(osg::Camera::COLOR_BUFFER, texture.get());

    camera->setReferenceFrame(osg::Camera::ABSOLUTE_RF);
    camera->addChild(sub_model.get());

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(model.get());
    root->addChild(camera.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    float delta = 0.1f;
    float bias = 0.0f;
    osg::Vec3 eye(0.0f, -1.0f, 1.0f);

    while (!viewer.done())
    {
        if (bias < -1.0f)
            delta = 0.1f;
        else
        {
            if (bias > 1.0f)
                delta = -0.1f;
        }

        bias += delta;

        camera->setViewMatrixAsLookAt(eye, osg::Vec3(), osg::Vec3(bias, 1.0f, 1.0f));

        viewer.frame();
    }
    
    return 0;
}
