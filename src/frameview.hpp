#ifndef FRAMEVIEW_HPP
#define FRAMEVIEW_HPP

#include <QTableView>
#include <QHeaderView>
#include <QKeyEvent>
#include <QLineEdit>
#include <QAbstractItemDelegate>
#include <QShortcut>
#include <QInputDialog>
#include "common.hpp"
#include "framemodel.hpp"

class FrameView : public QTableView
{
    Q_OBJECT

public:
    FrameView(QWidget *parent);
    void setModel(QAbstractItemModel *model);

private:
    enum EditMode
    {
        IdleMode,
        StrafeMode,
    };

    EditMode editMode;
    QString keyInputBuffer;

    void toggleButton(int column);
    QModelIndex getIndexByColumn(int column) const;
    void updateSaveColumns(int startRow, int endRow);
    void removeSelectedFrames();

protected:
    void keyPressEvent(QKeyEvent *event);
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>());

private slots:
    void editCmds();
    void toggleUse();
    void toggleDuck();
    void toggleJump();
    void toggleAttack();
    void toggleAttack2();
    void toggleReload();
    void toggleForward();
    void toggleBack();
    void toggleMoveLeft();
    void toggleMoveRight();
    void toggleMoveUp();
    void toggleMoveDown();
    void addSegment();
};

#endif
