#include    "main.h"

class MonitoringTarget : public osg::Referenced
{
public:

    MonitoringTarget(int id) : _id(id)
    {
        std::cout << "Constructing target " << _id << std::endl;
    }

protected:

    virtual ~MonitoringTarget()
    {
        std::cout << "Dsetroying target " << _id << std::endl;
    }

    int _id;
};

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    osg::ref_ptr<MonitoringTarget> target = new MonitoringTarget(0);
    std::cout << "Referenced count before referring: " << target->referenceCount() << std::endl;
    osg::ref_ptr<MonitoringTarget> anotherTarget = target;
    std::cout << "Referenced count after referring: " << target->referenceCount() << std::endl;

    for (int i = 1; i < 5; i++)
    {
        osg::ref_ptr<MonitoringTarget> subTarget = new MonitoringTarget(i);
    }

    return 0;
}
