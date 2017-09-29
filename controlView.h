#pragma once

#include "viewerWidget.h"
#include "scene.h"

#include <QWidget>
#include <QMainWindow>

// #include <osgViewer/CompositeViewer>

#ifdef Q_WS_X11
#include <X11/Xlib.h>
#endif

class ControlView : public QWidget
{
    Q_OBJECT

public:
    ControlView(QWidget* parent = 0);
    ~ControlView() override;

    static QString applicationVersion();

    QList<QAction*> setupDockWidgets( QMainWindow* mainWindow );


public slots:
    /**
     *  Toggles all of the docking panels on or off
     */
    void togglePanelVisibility();
//     void createEvents();

signals:
    //

protected:
    //
private slots:
//     void addEvent();

private:    
    QList<QAction*>     _panelActions;
    QAction*            _togglePanelVisibilityAction;
    QList<bool>         _panelVisibility;
    bool                _isPanelVisible;
    ViewerWidget*       _viewerWidget;
    Scene*              _everything;
};
