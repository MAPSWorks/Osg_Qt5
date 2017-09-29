#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QStatusBar>
#include <QMenu>

#include "controlView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow() override;

protected:
    void setupStatusBar();
    void setupMenus();


private:
    void  createMenus( const QList<QAction*> &panelActions );

    ControlView*            _controlView;
    QMenu*                  _panelMenu;

private slots:

};

