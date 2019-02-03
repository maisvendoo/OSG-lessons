QT += core
QT += gui
QT += opengl

TEMPLATE = app

TARGET = osgviewerQt

DESTDIR = ../../bin

win32 {

    OSG_LIB_DIRECTORY = $$(OSG_BIN_PATH)
    OSG_INCLUDE_DIRECTORY = $$(OSG_INCLUDE_PATH)


    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

        LIBS += -L$$OSG_LIB_DIRECTORY -losgd
        LIBS += -L$$OSG_LIB_DIRECTORY -losgViewerd
        LIBS += -L$$OSG_LIB_DIRECTORY -losgDBd
        LIBS += -L$$OSG_LIB_DIRECTORY -losgGAd
        LIBS += -L$$OSG_LIB_DIRECTORY -lOpenThreadsd
        LIBS += -L$$OSG_LIB_DIRECTORY -losgQt5d

    } else {

        LIBS += -L$$OSG_LIB_DIRECTORY -losg
        LIBS += -L$$OSG_LIB_DIRECTORY -losgViewer
        LIBS += -L$$OSG_LIB_DIRECTORY -losgDB
        LIBS += -L$$OSG_LIB_DIRECTORY -losgGA
        LIBS += -L$$OSG_LIB_DIRECTORY -lOpenThreads
        LIBS += -L$$OSG_LIB_DIRECTORY -losgQt5

    }

    INCLUDEPATH += $$OSG_INCLUDE_DIRECTORY
}

unix {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

        LIBS += -losgd
        LIBS += -losgViewerd
        LIBS += -losgDBd
        LIBS += -losgGAd
        LIBS += -lOpenThreadsd
        LIBS += -losgAnimationd
        LIBS += -losgQt5d

    } else {

        LIBS += -losg
        LIBS += -losgViewer
        LIBS += -losgDB
        LIBS += -losgGA
        LIBS += -lOpenThreads
        LIBS += -losgAnimation
        LIBS += -losgQt5
    }
}

INCLUDEPATH += ./include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
