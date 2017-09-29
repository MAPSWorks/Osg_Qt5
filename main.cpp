#include <QApplication>
#include <QWidget>
#include <QDockWidget>
#include <QMainWindow>
#include <QMenu>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include "mainWindow.h"

#include <X11/Xlib.h>


int main (int argc, char** argv) {
    QApplication app(argc, argv);
    QWidget* widget0 = new QWidget;
    QVBoxLayout* vLayout = new QVBoxLayout;

    MainWindow* mw = new MainWindow(widget0);
    vLayout->addWidget(mw);
    widget0->setLayout(vLayout);
    widget0->show();

    return app.exec();
}
