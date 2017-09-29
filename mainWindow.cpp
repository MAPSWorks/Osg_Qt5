#include "mainWindow.h"
#include "controlView.h"
#include <QWidget>
#include <QMainWindow>

#include <QSettings>
#include <QApplication>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _controlView( new ControlView( this ) )
{
    setUpdatesEnabled( false );

    setCentralWidget(_controlView );
    //TODO: Set an icon
//     setWindowIcon(QIcon(QStringLiteral(":/icons/SOMEICON.png")));
    setWindowFlags(Qt::Widget);

    QList<QAction*> const panelActions = _controlView->setupDockWidgets( this );
    createMenus( panelActions );

    setupStatusBar();
    setUpdatesEnabled( true );
}

MainWindow::~MainWindow()
{
}


void MainWindow::setupStatusBar() {
    statusBar()->showMessage("Ready");
    statusBar()->hide();
}

void MainWindow::createMenus( const QList<QAction*> &panelActions )
{
    _panelMenu = new QMenu(tr("&Panels"), this);
    for( QAction* action: panelActions ) {
        _panelMenu->addAction( action );
    }
}

