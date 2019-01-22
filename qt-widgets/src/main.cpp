#include    "main.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QOSGApplication osgApp(argc, argv);

    return osgApp.exec();
}
