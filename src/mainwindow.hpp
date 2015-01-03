#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include "frameview.hpp"
#include "framemodel.hpp"
#include "strafedelegate.hpp"
#include "toggledelegate.hpp"
#include "numrepdelegate.hpp"
#include "ftdelegate.hpp"
#include "yawdelegate.hpp"

class RMainWindow : public QMainWindow
{
     Q_OBJECT

public:
    FrameView *tableView;
    FrameModel *mainFrameModel;
    FrameModel *workFrameModel;

    RMainWindow();
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void openProject();
    void showAbout();
    void save();
    void saveAs();
    void saveACopy();

private:
    QString mainFileName;
};

#endif
