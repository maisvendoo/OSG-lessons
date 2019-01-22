#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("../data/Kranchik395-7.osgb");


    if (!model.valid())
        return -1;

    osgAnimation::BasicAnimationManager *manager = dynamic_cast<osgAnimation::BasicAnimationManager *>(model->getUpdateCallback());

    if (manager)
    {

        const osgAnimation::AnimationList &animations = manager->getAnimationList();

        for (auto it = animations.begin(); it != animations.end(); ++it)
        {
            manager->playAnimation((*it).get());
        }
    }

    osgViewer::Viewer viewer;
    viewer.setSceneData(model.get());
    viewer.setUpViewInWindow(100, 100, 1280, 720);

    return viewer.run();
}
