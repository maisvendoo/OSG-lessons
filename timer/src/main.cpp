#include	"main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct TimerInfo : public osg::Referenced
{
    TimerInfo(unsigned int c) : _count(c) {}
    unsigned int _count;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class TimerHandler : public osgGA::GUIEventHandler
{
public:

    TimerHandler(osg::Switch *sw, unsigned int interval = 1000)
        : _switch(sw)
        , _count(0)
        , _startTime(0.0)
        , _interval(interval)
        , _time(0)
    {

    }

    virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

protected:

    osg::ref_ptr<osg::Switch> _switch;
    unsigned int _count;
    double _startTime;
    unsigned int _interval;
    unsigned int _time;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool TimerHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    switch (ea.getEventType())
    {
    case osgGA::GUIEventAdapter::FRAME:
    {

        osgViewer::Viewer *viewer = dynamic_cast<osgViewer::Viewer *>(&aa);

        if (!viewer)
            break;

        double time = viewer->getFrameStamp()->getReferenceTime();
        unsigned int delta = static_cast<unsigned int>( (time - _startTime) * 1000.0);
        _startTime = time;

        if ( (_count >= _interval) || (_time == 0) )
        {
            viewer->getEventQueue()->userEvent(new TimerInfo(_time));
            _count = 0;
        }

        _count += delta;
        _time += delta;

        break;
    }

    case osgGA::GUIEventAdapter::USER:

        if (_switch.valid())
        {
            const TimerInfo *ti = dynamic_cast<const TimerInfo *>(ea.getUserData());

            std::cout << "Timer event at: " << ti->_count << std::endl;

            _switch->setValue(0, !_switch->getValue(0));
            _switch->setValue(1, !_switch->getValue(1));
        }

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

    osg::ref_ptr<osg::Node> model1 = osgDB::readNodeFile("../data/cessna.osg");
    osg::ref_ptr<osg::Node> model2 = osgDB::readNodeFile("../data/cessnafire.osg");

    osg::ref_ptr<osg::Switch> root = new osg::Switch;
    root->addChild(model1.get(), true);
    root->addChild(model2.get(), false);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.addEventHandler(new TimerHandler(root.get(), 1000));
    
    return viewer.run();
}
