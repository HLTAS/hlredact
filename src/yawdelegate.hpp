#ifndef YAWDELEGATE_HPP
#define YAWDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QKeyEvent>
#include <QTableView>
#include "common.hpp"

class YawDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    YawDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

protected:
    bool eventFilter(QObject *editor, QEvent *event);

private:
    QPointF point;
    int readState;

    bool isPointRequired() const;
};

#endif
