#include    "main.h"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    osg::ref_ptr<osg::ShapeDrawable> shape1 = new osg::ShapeDrawable;
    shape1->setShape(new osg::Box(osg::Vec3(-3.0f, 0.0f, 0.0f), 2.0f, 2.0f, 1.0f));

    osg::ref_ptr<osg::ShapeDrawable> shape2 = new osg::ShapeDrawable;
    shape2->setShape(new osg::Cone(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f));
    shape2->setColor(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::ShapeDrawable> shape3 = new osg::ShapeDrawable;
    shape3->setShape(new osg::Sphere(osg::Vec3(3.0f, 0.0f, 0.0f), 1.0f));
    shape3->setColor(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));

    osg::ref_ptr<osg::Geode> root = new osg::Geode;

    root->addDrawable(shape1.get());
    root->addDrawable(shape2.get());
    root->addDrawable(shape3.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    return viewer.run();
}
