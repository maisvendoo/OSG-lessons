#include	"main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class ModelController : public osgGA::GUIEventHandler
{
public:

    ModelController( osg::MatrixTransform *node ) : _model(node) {}

    virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

protected:

    osg::ref_ptr<osg::MatrixTransform> _model;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool ModelController::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    (void) aa;

    if (!_model.valid())
        return false;

    osg::Matrix matrix = _model->getMatrix();

    switch (ea.getEventType())
    {
    case osgGA::GUIEventAdapter::KEYDOWN:
        switch (ea.getKey())
        {
        case 'a': case 'A':
            matrix *= osg::Matrix::rotate(-0.1, osg::Z_AXIS);
            break;

        case 'd': case 'D':
            matrix *= osg::Matrix::rotate( 0.1, osg::Z_AXIS);
            break;

        case 'w': case 'W':
            matrix *= osg::Matrix::rotate(-0.1, osg::X_AXIS);
            break;

        case 's': case 'S':
            matrix *= osg::Matrix::rotate( 0.1, osg::X_AXIS);
            break;

        default:

            break;
        }

        _model->setMatrix(matrix);

        break;

    default:

        break;
    }

    return false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("../data/cessna.osg");

    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
    mt->addChild(model.get());

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(mt.get());

    osg::ref_ptr<ModelController> mcontrol = new ModelController(mt.get());

    osgViewer::Viewer viewer;
    viewer.addEventHandler(mcontrol.get());
    viewer.getCamera()->setViewMatrixAsLookAt( osg::Vec3(0.0f, -100.0f, 0.0f), osg::Vec3(), osg::Z_AXIS );
    viewer.getCamera()->setAllowEventFocus(false);
    viewer.setSceneData(root.get());
    
    return viewer.run();
}
