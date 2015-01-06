#include "mainwindow.hpp"

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
    AutofuncsDelegate *autofDelegate = new AutofuncsDelegate(tableView);
    tableView->setItemDelegateForColumn(IndAutoJump, autofDelegate);
    tableView->setItemDelegateForColumn(IndDuckTap, autofDelegate);
    tableView->setItemDelegateForColumn(IndLgagst, autofDelegate);
    tableView->setItemDelegateForColumn(IndJumpBug, autofDelegate);
    tableView->setItemDelegateForColumn(IndDB4C, autofDelegate);
    tableView->setItemDelegateForColumn(IndDB4G, autofDelegate);
    tableView->setItemDelegateForColumn(IndDWJ, autofDelegate);
    YawDelegate *yawDelegate = new YawDelegate(tableView);
    tableView->setItemDelegateForColumn(IndYaw, yawDelegate);
    PitchDelegate *pitchDelegate = new PitchDelegate(tableView);
    tableView->setItemDelegateForColumn(IndPitch, pitchDelegate);
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

    propsWindow = new PropsWindow(this);

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
    actProperties = menuFile->addAction(
        "&Properties...", this, SLOT(openProperties()),
        QKeySequence("Ctrl+P"));
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
    actSwitchBuffer = menuView->addAction(
        "&Switch to work buffer", this, SLOT(switchBuffer()),
        QKeySequence("F2")
        );

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

    if (!((FrameModel *)tableView->model())->openProject(fileName))
        return;

    tableView->resizeColumnsToContents();
    setWindowTitle(QString("%1 (%2)")
                   .arg(APP_NAME)
                   .arg(getCurrentBufName()));
    actProperties->setEnabled(true);
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
    ((FrameModel *)tableView->model())->saveProject();
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

    ((FrameModel *)tableView->model())->saveProject(fileName);
}

void RMainWindow::switchBuffer()
{
    if (tableView->model() == mainFrameModel) {
        tableView->setModel(workFrameModel);
        actSwitchBuffer->setText("&Switch to main buffer");
    } else {
        tableView->setModel(mainFrameModel);
        actSwitchBuffer->setText("&Switch to work buffer");
    }
    setWindowTitle(QString("%1 (%2)")
                   .arg(APP_NAME)
                   .arg(getCurrentBufName()));
    actProperties->setDisabled(
        ((FrameModel *)tableView->model())->fileName().isEmpty());
}

QString RMainWindow::getCurrentBufName() const
{
    QFileInfo fileInfo(((FrameModel *)tableView->model())->fileName());
    return fileInfo.fileName();
}

void RMainWindow::openProperties()
{
    FrameModel *model = (FrameModel *)tableView->model();
    propsWindow->setDemoName(model->demoName());
    propsWindow->setSaveName(model->saveName());
    unsigned int SSeed;
    unsigned int NSSeed;
    if (model->seeds(SSeed, NSSeed)) {
        propsWindow->setSSeed(SSeed);
        propsWindow->setNSSeed(NSSeed);
    } else
        propsWindow->clearSeeds();

    if (!propsWindow->exec())
        return;

    model->setDemoName(propsWindow->demoName());
    model->setSaveName(propsWindow->saveName());
    model->setSeeds(propsWindow->SSeed(), propsWindow->NSSeed());
}
