#include "viewerWidget.h"

#include <QOpenGLWidget>
#include <QTimer>

#include <osg/Camera>
#include <osg/Group>
#include <osg/Node>
#include <osgDB/ReadFile>

#ifdef Q_WS_X11
#include <X11/Xlib.h>
#endif

ViewerWidget::ViewerWidget(osg::Group* scene, QWidget* parent) :
// ViewerWidget::ViewerWidget(QWidget* parent) :
    QOpenGLWidget(parent),
    _graphicsWindow(new osgViewer::GraphicsWindowEmbedded(this->x(), this->y(), this->width(), this->height()) ),
    _viewer(new osgViewer::Viewer),
    _timer(new QTimer(this) ),
    _scene(new osg::Group)
{

#ifdef Q_WS_X11
    XInitThreads();
#endif

    _scene->addChild(scene);
    // create a main camera and attach a graphics context to it
    osg::Camera* camera = new osg::Camera;
    camera->setViewport( 0, 0, this->width(), this->height() );
    camera->setClearColor( osg::Vec4( 0.9f, 0.9f, 1.f, 1.f ) );
    float aspectRatio = static_cast<float>( this->width()) / static_cast<float>( this->height() );
    camera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );
    camera->setGraphicsContext( _graphicsWindow );

    // attach a camera to the viewer
    _viewer->setCamera(camera);
    _viewer->setSceneData(_scene);
    osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;;
    manipulator->setAllowThrow( false );
    this->setMouseTracking(true);
    _viewer->setCameraManipulator(manipulator);
    _viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    _viewer->realize();

    // set a size of the widget
    this->setMinimumSize( 300, 300 );
    startTimer(0);
}


void ViewerWidget::initializeGL()
{
    osg::StateSet* stateSet = _scene->getOrCreateStateSet();
    stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );
    stateSet->setMode( GL_LIGHTING, osg::StateAttribute::ON );
}

void ViewerWidget::resizeGL(int width, int height)
{
    this->getEventQueue()->windowResize(this->x(), this->y(), width, height);
    _graphicsWindow->resized(this->x(), this->y(), width, height);
    osg::Camera* camera = _viewer->getCamera();
    camera->setViewport(0, 0, this->width(), this->height());
}

void ViewerWidget::paintGL()
{
    _viewer->frame();
}

void ViewerWidget::startTimer(int interval)
{
    connect(_timer,SIGNAL(timeout() ), this, SLOT(update() ));
    _timer->start(interval);
}
