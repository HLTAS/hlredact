#include "toggledelegate.hpp"

ToggleDelegate::ToggleDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

bool ToggleDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick) {
        setModelData(nullptr, model, index);
        return true;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

void ToggleDelegate::setModelData(QWidget *, QAbstractItemModel *model,
                                  const QModelIndex &index) const
{
    model->setData(index, 1);
}
