#include	"main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osgViewer::View *createView(int x, int y, int w, int h,
                            osg::Node *scene)
{
    osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
    view->setSceneData(scene);
    view->setUpViewInWindow(x, y, w, h);

    return view.release();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    (void) argc; (void) argv;

    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("../data/cessna.osg");
    osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("../data/cow.osg");
    osg::ref_ptr<osg::Node> model3 = osgDB::readNodeFile("../data/glider.osg");

    osgViewer::View *view1 = createView(50, 50, 320, 240, model1);
    osgViewer::View *view2 = createView(380, 50, 320, 240, model2);
    osgViewer::View *view3 = createView(185, 330, 320, 240, model3);

    osgViewer::CompositeViewer viewer;
    viewer.addView(view1);
    viewer.addView(view2);
    viewer.addView(view3);
    
    return viewer.run();
}
