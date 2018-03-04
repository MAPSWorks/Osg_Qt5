#include "scene.h"

#include <QDebug>
#include <QWidget>
#include <QString>

#include <osg/Node>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/PolygonMode>

#include <osg/Program>
#include <osg/Shader>

Scene::Scene( QWidget* parent ):
     QWidget( parent ),
     _scene( new osg::Group ),
     _visEventsLayer( new osg::Group ) {
     _scene->addChild( addCube() );

     _visEventsLayer->addChild( addSphere() );
     _scene->addChild( addMonkeyHead() );
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

void Scene::showWireFrame( bool wireFrame ) {
     osg::ref_ptr<osg::PolygonMode> pm = new osg::PolygonMode;
     pm->setMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE );

     if ( wireFrame ) {
               _scene->getOrCreateStateSet()->setAttribute( pm.get() );
          }
    else{
        //TODO: I'm not sure this is correct. I'm afraid that it clears all attribs, which is not what I want. Check it! but it works for current silly tests
        _scene->getOrCreateStateSet()->clear();
    }
        
}


osg::ref_ptr<osg::Node> Scene::addCube() {
     osg::ref_ptr<osg::Geode> cube = new osg::Geode();
     cube->setName( "Cube" );
     cube->addDrawable( new osg::ShapeDrawable( new osg::Box() ) );
     osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
     transform->setMatrix( osg::Matrix::translate( osg::Vec3( 0.0f, 1.0f, 0.0f ) ) *
                           osg::Matrix::rotate( 37.0f, osg::Vec3( 1.0f, 0.0f, 1.0f ) ) );
     transform->addChild( cube );
     osg::ref_ptr<osg::Group> temp = new osg::Group;
     temp->addChild( transform.get() );

     return temp;
}

osg::ref_ptr<osg::Geode> Scene::addSphere() {

     osg::ref_ptr<osg::Geode> sphere = new osg::Geode();
     sphere->setName( "Sphere" );
     sphere->addDrawable( new osg::ShapeDrawable( new osg::Sphere() ) );
     return sphere;
}

osg::ref_ptr<osg::Node> Scene::addMonkeyHead() {
     osg::ref_ptr<osg::Node> monkey = osgDB::readNodeFile( "data/monkeyHead.osg" );
     
     osg::ref_ptr<osg::Program> program = new osg::Program;
     osg::ref_ptr<osg::Shader> monkeyVert = osgDB::readShaderFile("monkey.vert");
     osg::ref_ptr<osg::Shader> monkeyFrag = osgDB::readShaderFile("monkey.frag");
//      osg::ref_ptr<osg::Shader> monkeyGeom = osgDB::readShaderFile("monkey.vert");
     
     program->addShader(monkeyVert);
     program->addShader(monkeyFrag);
     
     monkey->getOrCreateStateSet()->setAttributeAndModes(program.get());

     return monkey;
}
