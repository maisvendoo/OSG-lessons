#include    "mainwindow.h"
#include    "ui_mainwindow.h"

#include    <QGridLayout>
#include    <QFileDialog>

#include    <osg/Group>
#include    <osgDB/ReadFile>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , qviewer(Q_NULLPTR)
{
    ui->setupUi(this);

    QGridLayout *layout = new QGridLayout;
    qviewer = new QViewerWidget(QRect(0, 0, ui->frame->width(), ui->frame->height()));
    layout->addWidget(qviewer);
    ui->frame->setLayout(layout);
    this->setCentralWidget(ui->frame);

    connect(&timer, &QTimer::timeout, this, &MainWindow::update);
    timer.start(40);

    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quit);
    connect(ui->actionClean, &QAction::triggered, this, &MainWindow::clean);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);

    this->setWindowTitle("QViewerWidget example");
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::paintEvent(QPaintEvent *)
{
    ui->frame->update();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::update()
{
    QMainWindow::update(this->geometry());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::open()
{
    osg::Group *scene = qviewer->getScene();

    if (scene == nullptr)
        return;

    QString path = QFileDialog::getOpenFileName(Q_NULLPTR,
                                                tr("Open model file"),
                                                "./",
                                                tr("OpenSceneGraph (*.osg *.osgt *.osgb *.ivi)"));

    if (path.isEmpty())
        return;

    scene->removeChildren(0, scene->getNumChildren());

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(path.toStdString());
    scene->addChild(model.get());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::clean()
{
    osg::Group *scene = qviewer->getScene();

    if (scene == nullptr)
        return;

    scene->removeChildren(0, scene->getNumChildren());
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void MainWindow::quit()
{
    QApplication::quit();
}
