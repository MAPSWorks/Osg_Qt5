#include "controlView.h"
#include "viewerWidget.h"
#include "scene.h"

#include <QAction>
#include <QMainWindow>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
// #include <QComboBox>
#include <QKeySequence>

ControlView::ControlView( QWidget* parent )
     : QWidget( parent ),
       _togglePanelVisibilityAction( 0 ),
       _isPanelVisible( true ),
       _everything( new Scene( this ) ) {

     setWindowTitle( tr( "Virtual Globe" ) );

//     setMinimumSize( 1400, 1300 );
     _viewerWidget = new ViewerWidget( _everything->scene(), this );


     QVBoxLayout* layout = new QVBoxLayout();
     layout->addWidget( _viewerWidget );
     layout->setMargin( 0 );
     setLayout( layout );
     setAcceptDrops( true );
}

ControlView::~ControlView() {
     // nothing to do
}


QList<QAction*> ControlView::setupDockWidgets( QMainWindow* mainWindow ) {
     mainWindow->setTabPosition( Qt::LeftDockWidgetArea, QTabWidget::North );
     mainWindow->setTabPosition( Qt::RightDockWidgetArea, QTabWidget::North );

     //TODO: Bring back with another usage
//     QDockWidget *mapViewDock = new QDockWidget( tr( "Map Settings" ), this );
//     mapViewDock->setObjectName( "mapViewDock" );
//     mapViewDock->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
// //TODO: Add extra control panel/settings/etc widgets to this
// //     mapViewDock->setWidget( WIDGET TO BE WRITTEN);
//     mainWindow->addDockWidget( Qt::LeftDockWidgetArea, mapViewDock );

//     //TODO:General framework for adding further panels to the mainWindow:
//     QDockWidget* dockW = new QDockWidget(tr( "SOME_NAME"), this);
//     dockW->setObjectName("Some_Name");
//     dockW->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | OR SOMEOTHER AREA);
//     QWidget* someW = new QWidget(this);
//     QVBoxLayout* someLayout = new QVBoxLayout(someW); //probably someW is unneccessary here.
//     someW->setLayout(someLayout);
//     //Create some Widget-derived object, e.g. QPushButton or QCheckBox, etc.
//     class QWidgetDrivenObject;
//     QWidgetDrivenObject* qwdo = new QWidgetDrivenObject();
//     someLayout->addWidget(qwdo);
//     MoreQWidgetDrivenObject* moreqwdo = new MoreQWidgetDrivenObject();
//     someLayout->addWidget(moreqwdo);
//     dockW->setWidget(someW);
//     mainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockW);



     //TODO:General framework for adding further panels to the mainWindow:
     QDockWidget* settingsDock = new QDockWidget( tr( "&Settings" ), this );
     settingsDock->setObjectName( "Settings_Dock" );
     settingsDock->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
     QWidget* settingsWidget = new QWidget( this );
     QVBoxLayout* settingsLayout = new QVBoxLayout( settingsDock ); //probably someW is unneccessary here.
     settingsWidget->setLayout( settingsLayout );

     QCheckBox* showEventsLayer = new QCheckBox();
     showEventsLayer->setText( "Sample Layer" );
     showEventsLayer->setChecked( true );
//     showEventsLayer->setShortcut( QKeySequence(Qt::CTRL + Qt::Key_E) );
     showEventsLayer->setShortcut( QKeySequence( Qt::Key_E ) );
     connect( showEventsLayer, &QCheckBox::clicked, _everything, &Scene::showSampleLayer );
     settingsLayout->addWidget( showEventsLayer );

     QCheckBox* showWireFrame = new QCheckBox();
     showWireFrame->setText( "Wire Frame" );
     showWireFrame->setChecked( false );
     showWireFrame->setShortcut( QKeySequence( Qt::Key_W ) );
     connect( showWireFrame, &QCheckBox::clicked, _everything, &Scene::showWireFrame );
     settingsLayout->addWidget( showWireFrame );
     
     settingsDock->setWidget( settingsWidget );
     mainWindow->addDockWidget( Qt::LeftDockWidgetArea, settingsDock );

     // Create Settings->Panels Menu
     // Toggle All Panels action
     _togglePanelVisibilityAction = new QAction( tr( "Hide &All Panels" ), this );
     _togglePanelVisibilityAction->setShortcut( Qt::Key_F9 );
     _togglePanelVisibilityAction->setStatusTip( tr( "Show or hide all panels." ) );
     connect( _togglePanelVisibilityAction, &QAction::triggered, this, &ControlView::togglePanelVisibility );

     // Include a Separator in the List
     QAction* panelSeparatorAct = new QAction( this );
     panelSeparatorAct->setSeparator( true );

     // Return a list of panel view actions for Marble Menu including show/hide all
     QList<QAction*> panelMenuActions;
     panelMenuActions << _togglePanelVisibilityAction;
     panelMenuActions << panelSeparatorAct;

     for ( QAction* action : _panelActions ) {
               panelMenuActions << action;
          }

     return panelMenuActions;
}


void ControlView::togglePanelVisibility() {
     Q_ASSERT( _panelVisibility.size() == _panelActions.size() );

     if ( _isPanelVisible ) {
               for ( int p = 0; p < _panelActions.size(); ++p ) {
                         // Save state of individual dock visibility
                         _panelVisibility[p] = _panelActions.at( p )->isChecked();

                         // hide panel if it is showing
                         if ( _panelActions.at( p )->isChecked() ) {
                                   _panelActions.at( p )->activate( QAction::Trigger );
                              }
                    }

               // Change Menu Item Text
               _togglePanelVisibilityAction->setText( tr( "Show &All Panels" ) );
               _isPanelVisible = false;
          }
     else {
               for ( int p = 0; p < _panelActions.size(); ++p ) {
                         // show panel if it was showing before all panels were hidden
                         if ( _panelVisibility.at( p ) && !_panelActions.at( p )->isChecked() ) {
                                   _panelActions.at( p )->activate( QAction::Trigger );
                              }
                    }

               // Change Menu Item Text
               _togglePanelVisibilityAction->setText( tr( "Hide &All Panels" ) );
               _isPanelVisible = true;
          }
}

QString ControlView::applicationVersion() {
     return "0.1 roozbehDev0";
}




