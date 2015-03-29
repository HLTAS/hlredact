#include <QtWidgets>
#include "mainwindow.hpp"
#include "timelinescene.hpp"

MainWindow::MainWindow()
    : QMainWindow()
{
    setWindowTitle("hlredact");

    timeLineScene = new TimeLineScene(this);
    timeLineView = new TimeLineView(timeLineScene, this);
    setCentralWidget(timeLineView);
}
