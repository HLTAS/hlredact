#include "mainwindow.hpp"
#include "common.hpp"

RMainWindow::RMainWindow()
    : QMainWindow(nullptr)
{
    setWindowTitle(APP_NAME);
    resize(800, 600);

    tableView = new FrameView(this);
    setCentralWidget(tableView);
    mainFrameModel = new FrameModel(tableView);
    workFrameModel = new FrameModel(tableView);
    tableView->setModel(mainFrameModel);
    tableView->resizeColumnsToContents();

    NumRepDelegate *numRepDelegate = new NumRepDelegate(tableView);
    tableView->setItemDelegateForColumn(IndNumRepeat, numRepDelegate);
    StrafeDelegate *strafeDelegate = new StrafeDelegate(tableView);
    tableView->setItemDelegateForColumn(IndStrafeInfo, strafeDelegate);
    YawDelegate *yawDelegate = new YawDelegate(tableView);
    tableView->setItemDelegateForColumn(IndYaw, yawDelegate);
    FTDelegate *ftDelegate = new FTDelegate(tableView);
    tableView->setItemDelegateForColumn(IndFrameTime, ftDelegate);
    ToggleDelegate *toggleDelegate = new ToggleDelegate(tableView);
    tableView->setItemDelegateForColumn(IndUse, toggleDelegate);
    tableView->setItemDelegateForColumn(IndDuck, toggleDelegate);
    tableView->setItemDelegateForColumn(IndJump, toggleDelegate);
    tableView->setItemDelegateForColumn(IndAttack, toggleDelegate);
    tableView->setItemDelegateForColumn(IndAttack2, toggleDelegate);
    tableView->setItemDelegateForColumn(IndReload, toggleDelegate);
    tableView->setItemDelegateForColumn(IndForward, toggleDelegate);
    tableView->setItemDelegateForColumn(IndBack, toggleDelegate);
    tableView->setItemDelegateForColumn(IndMoveLeft, toggleDelegate);
    tableView->setItemDelegateForColumn(IndMoveRight, toggleDelegate);
    tableView->setItemDelegateForColumn(IndMoveUp, toggleDelegate);
    tableView->setItemDelegateForColumn(IndMoveDown, toggleDelegate);

    statusBar();

    QMenu *menuFile = menuBar()->addMenu("&File");
    menuFile->addAction("&New Project...");
    menuFile->addAction(
        "&Open Project...",
        this, SLOT(openProject()),
        QKeySequence("Ctrl+O"));
    menuFile->addSeparator();
    menuFile->addAction("&Save", this, SLOT(save()), QKeySequence("Ctrl+S"));
    menuFile->addAction("Save &As...", this, SLOT(saveAs()));
    menuFile->addAction("Save a &Copy...", this, SLOT(saveACopy()));
    menuFile->addSeparator();
    QAction *actProperties = menuFile->addAction("&Properties...");
    actProperties->setEnabled(false);
    menuFile->addSeparator();
    menuFile->addAction("&Quit");

    QMenu *menuEdit = menuBar()->addMenu("&Edit");
    menuEdit->addAction("&Undo");
    menuEdit->addAction("&Redo");
    menuEdit->addSeparator();
    menuEdit->addAction("&Find...");
    menuEdit->addSeparator();
    menuEdit->addAction("&Preferences...");

    QMenu *menuView = menuBar()->addMenu("&View");
    menuView->addAction("Show");

    QMenu *menuHelp = menuBar()->addMenu("&Help");
    menuHelp->addAction("&About...", this, SLOT(showAbout()));
    menuHelp->addAction("About &Qt...", qApp, SLOT(aboutQt()));
}

void RMainWindow::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(
        this, "Open Project", QString(),
        "HLTAS scripts (*.hltas);;All files (*.*)"
        );

    if (fileName.isEmpty())
        return;

    if (!mainFrameModel->openProject(fileName))
        return;

    tableView->resizeColumnsToContents();
    mainFileName = fileName;

    QFileInfo fileInfo(fileName);
    setWindowTitle(QString("%1 (%2)")
                   .arg(windowTitle())
                   .arg(fileInfo.fileName()));
}

void RMainWindow::showAbout()
{
    QMessageBox::about(
        this, APP_NAME,
        "A HLTAS script editor by Chong Jiang Wei (aka Matherunner).\n\n"
        "libHLTAS by Ivan Molodetskikh (aka YaLTeR)."
        );
}

void RMainWindow::save()
{
    mainFrameModel->saveProject(mainFileName);
}

void RMainWindow::saveAs()
{
}

void RMainWindow::saveACopy()
{
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save a Copy", QString(),
        "HLTAS scripts (*.hltas);;All files (*.*)"
        );

    if (fileName.isEmpty())
        return;

    mainFrameModel->saveProject(fileName);
}
