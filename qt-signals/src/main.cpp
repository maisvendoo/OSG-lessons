#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    osg::ref_ptr<osg::Node> scene = osgDB::readNodeFile("../data/cessnafire.osg");

    osgViewer::Viewer viewer;
    viewer.setSceneData(scene.get());    
    viewer.addEventHandler(new QtEventsHandler);
    viewer.setUpViewInWindow(0, 0, 1024, 768);

    KeyboardHandler *keyboardHandler = new KeyboardHandler;
    Receiver *receiver = new Receiver;

    QObject::connect(keyboardHandler, &KeyboardHandler::sendMessage,
                     receiver, &Receiver::printMessage);

    viewer.addEventHandler(keyboardHandler);

    return viewer.run();
}
