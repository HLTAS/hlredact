#ifndef TOGGLEDELEGATE_HPP
#define TOGGLEDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QEvent>

class ToggleDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ToggleDelegate(QObject *parent = nullptr);
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index);
};

#endif
