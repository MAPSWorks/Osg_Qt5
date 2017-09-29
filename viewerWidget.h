#pragma once


#include <osgViewer/GraphicsWindow>

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMutex>
#include <QEvent>
#include <QQueue>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>

#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>
#include <osg/Camera>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osg/Material>
#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>
#include <osg/Group>
#include <osg/Node>


class ViewerWidget : public QOpenGLWidget {
Q_OBJECT

public:
    ViewerWidget(osg::Group* scene, QWidget* parent = 0);
//     ViewerWidget(QWidget* parent = 0);

    virtual ~ViewerWidget() {
//         _graphicsWindow->close();
// //         _graphicsWindow->_widget = NULL;
//         _graphicsWindow = NULL;
    }



protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


    virtual bool event(QEvent* event) override
    {
        bool handled = QOpenGLWidget::event(event);
        this->update();
        return handled;
    }

    virtual void mouseMoveEvent(QMouseEvent* event) override
    {
        this->getEventQueue()->mouseMotion(event->x(), event->y());
    }


    virtual void mousePressEvent(QMouseEvent* event) override
    {
        unsigned int button = 0;
        switch (event->button()) {
        case Qt::LeftButton:
            button = 1;
            break;
        case Qt::MiddleButton:
            button = 2;
            break;
        case Qt::RightButton:
            button = 3;
            break;
        default:
            break;
        }
        this->getEventQueue()->mouseButtonPress(event->x(), event->y(), button);
    }


    virtual void mouseReleaseEvent(QMouseEvent* event) override
    {
        unsigned int button = 0;
        switch (event->button()) {
        case Qt::LeftButton:
            button = 1;
            break;
        case Qt::MiddleButton:
            button = 2;
            break;
        case Qt::RightButton:
            button = 3;
            break;
        default:
            break;
        }
        this->getEventQueue()->mouseButtonRelease(event->x(), event->y(), button);
    }

    virtual void wheelEvent(QWheelEvent* event) override
    {
        int delta = event->delta();
        osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?
                osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
        this->getEventQueue()->mouseScroll(motion);
    }


private:
    // private method to manage GUI events
    osgGA::EventQueue* getEventQueue() const {
        osgGA::EventQueue* eventQueue = _graphicsWindow->getEventQueue();
        return eventQueue;
    }
    
    void startTimer(int interval);
    QTimer* _timer;

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded>         _graphicsWindow;
    osg::ref_ptr<osgViewer::Viewer>                         _viewer;
    osg::Group*                                             _scene;

};
