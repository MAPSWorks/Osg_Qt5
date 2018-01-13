#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "mainWindow.h"


int main ( int argc, char** argv ) {
    QApplication app(argc, argv);
    QWidget* widget0 = new QWidget;
    QVBoxLayout* vLayout = new QVBoxLayout;

    MainWindow* mw = new MainWindow(widget0);
    vLayout->addWidget(mw);
    widget0->setLayout(vLayout);
    widget0->show();

    return app.exec();
}
