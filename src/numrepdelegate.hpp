#ifndef NUMREPDELEGATE_HPP
#define NUMREPDELEGATE_HPP

#include <limits>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QKeyEvent>

class NumRepDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    NumRepDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    bool eventFilter(QObject *editor, QEvent *event);
};

#endif
