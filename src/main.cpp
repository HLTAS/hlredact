#include <QApplication>
#include <QLocale>
#include <locale>
#include "mainwindow.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    std::locale::global(std::locale("C"));
    QLocale::setDefault(QLocale::c());
    RMainWindow mainwin;
    mainwin.show();
    return app.exec();
}
