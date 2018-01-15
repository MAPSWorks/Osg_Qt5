#include "scene.h"

#include <QDebug>
#include <QWidget>
#include <QString>

#include <osg/Node>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

Scene::Scene( QWidget* parent ):
     QWidget( parent ),
     _scene( new osg::Group ),
     _visEventsLayer( new osg::Group ) {
     addCube();
//     _scene->addChild(_mapNode);
     _visEventsLayer->addChild( sphere() );
     _scene->addChild( _visEventsLayer.get() );
//     addVisEvents(true);
}


void Scene::showSampleLayer( bool show ) {
     if ( show ) {
               _visEventsLayer->asNode()->setNodeMask( 0xffffffff );
          }
     else {
               _visEventsLayer->asNode()->setNodeMask( 0x0 );
          }
}


void Scene::addCube() {
     osg::ref_ptr<osg::Geode> cube = new osg::Geode();
     cube->setName( "Cube" );
     cube->addDrawable( new osg::ShapeDrawable( new osg::Box() ) );
     osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
     transform->setMatrix( osg::Matrix::translate( osg::Vec3( 0.0f, 1.0f, 0.0f ) ) *
                           osg::Matrix::rotate( 37.0f, osg::Vec3( 1.0f, 0.0f, 1.0f ) ) );
     transform->addChild( cube );
     _scene->addChild( transform.get() );
}

osg::ref_ptr<osg::Geode> Scene::sphere() {

     osg::ref_ptr<osg::Geode> sphere = new osg::Geode();
     sphere->setName( "Sphere" );
     sphere->addDrawable( new osg::ShapeDrawable( new osg::Sphere() ) );
     return sphere;
}
