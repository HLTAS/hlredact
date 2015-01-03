#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    RMainWindow mainwin;
    mainwin.show();
    return app.exec();
}
