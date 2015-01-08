#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <limits>
#include <QApplication>
#include <QMainWindow>
#include <QTableView>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include "common.hpp"
#include "frameview.hpp"
#include "framemodel.hpp"
#include "strafedelegate.hpp"
#include "toggledelegate.hpp"
#include "numrepdelegate.hpp"
#include "ftdelegate.hpp"
#include "yawdelegate.hpp"
#include "pitchdelegate.hpp"
#include "autofdelegate.hpp"
#include "propswindow.hpp"

class RMainWindow : public QMainWindow
{
     Q_OBJECT

public:
    FrameView *tableView;
    FrameModel *mainFrameModel;
    FrameModel *workFrameModel;

    RMainWindow();

private slots:
    void openProperties();
    void openProject();
    void showAbout();
    void save();
    void saveAs();
    void saveACopy();
    void switchBuffer();
    void switchCumulativeDisp();
    void joinFramesToOther();
    void jumpToPosition();

private:
    QAction *actJumpToPosition;
    QAction *actJoinFramesToOther;
    QAction *actSwitchCumulative;
    QAction *actSwitchBuffer;
    QAction *actProperties;
    PropsWindow *propsWindow;

    QString getCurrentBufName() const;
};

#endif
