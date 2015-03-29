#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "timelineview.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    TimeLineScene *timeLineScene;
    TimeLineView *timeLineView;
};

#endif
