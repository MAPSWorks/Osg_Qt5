#pragma once

#include <QWidget>

#include <osg/Group>


class Scene : public QWidget {
     Q_OBJECT
public:
     Scene( QWidget* parent = 0 );
     ~Scene() {}


     inline osg::Group* scene() {
          return _scene.get();
     }

public slots:
     void showSampleLayer( bool show );

private:
     void addCube();
     osg::ref_ptr<osg::Geode> sphere();

     osg::ref_ptr<osg::Group>    _scene;
     osg::ref_ptr<osg::Group>    _visEventsLayer;
};

