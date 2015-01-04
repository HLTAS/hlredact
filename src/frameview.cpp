#include "frameview.hpp"
#include <QDebug>

FrameView::FrameView(QWidget *parent = nullptr)
    : QTableView(parent)
{
    setTabKeyNavigation(false);
    horizontalHeader()->setSectionsMovable(true);
    // We will implement our own heavily customised triggers.
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    new QShortcut(QKeySequence("Ctrl+M"), this, SLOT(editCmds()));
    new QShortcut(QKeySequence("Ctrl+U"), this, SLOT(toggleUse()));
    new QShortcut(QKeySequence("Ctrl+D"), this, SLOT(toggleDuck()));
    new QShortcut(QKeySequence("Ctrl+J"), this, SLOT(toggleJump()));
    new QShortcut(QKeySequence("Ctrl+1"), this, SLOT(toggleAttack()));
    new QShortcut(QKeySequence("Ctrl+2"), this, SLOT(toggleAttack2()));
    new QShortcut(QKeySequence("Ctrl+R"), this, SLOT(toggleReload()));
    new QShortcut(QKeySequence("Ctrl+Up"), this, SLOT(toggleForward()));
    new QShortcut(QKeySequence("Ctrl+Down"), this, SLOT(toggleBack()));
    new QShortcut(QKeySequence("Ctrl+Left"), this, SLOT(toggleMoveLeft()));
    new QShortcut(QKeySequence("Ctrl+Right"), this, SLOT(toggleMoveRight()));
    new QShortcut(QKeySequence("Ctrl+Shift+Up"), this, SLOT(toggleMoveUp()));
    new QShortcut(QKeySequence("Ctrl+Shift+Down"), this, SLOT(toggleMoveDown()));
}

void FrameView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndAutoJump));
            return;
        }
        break;

    case Qt::Key_C:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndDB4C));
            return;
        }
        break;

    case Qt::Key_F:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndFrameTime));
            return;
        }
        break;

    case Qt::Key_G:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndDB4G));
            return;
        }
        break;

    case Qt::Key_I:
        if (event->modifiers() == Qt::NoModifier)
            ((FrameModel *)model())->insertEmptyRow(currentIndex().row());
        else if (event->modifiers() == Qt::ShiftModifier)
            ((FrameModel *)model())->insertDuplicateRow(currentIndex().row());
        return;

    case Qt::Key_J:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndJumpBug));
            return;
        }
        break;

    case Qt::Key_L:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndLgagst));
            return;
        }
        break;

    case Qt::Key_R:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndNumRepeat));
            return;
        }
        break;

    case Qt::Key_S:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndStrafeInfo));
            return;
        }
        break;

    case Qt::Key_T:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndDuckTap));
            return;
        }
        break;

    case Qt::Key_W:
        if (event->modifiers() == Qt::NoModifier) {
            edit(getIndexByColumn(IndDWJ));
            return;
        }
        break;

    case Qt::Key_Y:
        if (event->modifiers() == Qt::NoModifier) {
            QModelIndex targetIndex = getIndexByColumn(IndYaw);
            if (targetIndex.data() == "NA")
                break;
            edit(targetIndex);
            return;
        }
        break;

    case Qt::Key_Delete:
        if (event->modifiers() == Qt::NoModifier)
            ((FrameModel *)model())->removeRow(currentIndex().row());
        return;

    case Qt::Key_AsciiCircum:
        if (currentIndex().column() == IndDB4C)
            ((FrameModel *)model())->toggleDB4CCeil(currentIndex().row());
        else if (currentIndex().column() == IndLgagst)
            ((FrameModel *)model())->toggleLgagstFullM(currentIndex().row());
        break;
    }

    QTableView::keyPressEvent(event);
}

void FrameView::toggleUse()
{
    toggleButton(IndUse);
}

void FrameView::toggleDuck()
{
    toggleButton(IndDuck);
}

void FrameView::toggleJump()
{
    toggleButton(IndJump);
}

void FrameView::toggleAttack()
{
    toggleButton(IndAttack);
}

void FrameView::toggleAttack2()
{
    toggleButton(IndAttack2);
}

void FrameView::toggleReload()
{
    toggleButton(IndReload);
}

void FrameView::toggleForward()
{
    toggleButton(IndForward);
}

void FrameView::toggleBack()
{
    toggleButton(IndBack);
}

void FrameView::toggleMoveLeft()
{
    toggleButton(IndMoveLeft);
}

void FrameView::toggleMoveRight()
{
    toggleButton(IndMoveRight);
}

void FrameView::toggleMoveUp()
{
    toggleButton(IndMoveUp);
}

void FrameView::toggleMoveDown()
{
    toggleButton(IndMoveDown);
}

void FrameView::toggleButton(int column)
{
    QModelIndex targetIndex = model()->index(currentIndex().row(), column);
    model()->setData(targetIndex, 1);
}

void FrameView::editCmds()
{
    if (state() == QAbstractItemView::EditingState)
        return;
    edit(getIndexByColumn(IndCmds));
}

QModelIndex FrameView::getIndexByColumn(int column) const
{
    return model()->index(currentIndex().row(), column);
}

void FrameView::dataChanged(const QModelIndex &topLeft,
                            const QModelIndex &bottomRight,
                            const QVector<int> &roles)
{
    const FrameModel *frameModel = (FrameModel *)model();
    for (int i = topLeft.row(); i <= bottomRight.row(); i++) {
        if (frameModel->isSaveLine(i))
            setSpan(i, 0, 1, IndLength);
    }
    QTableView::dataChanged(topLeft, bottomRight, roles);
}
