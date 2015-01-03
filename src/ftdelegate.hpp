#ifndef FTDELEGATE_HPP
#define FTDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QKeyEvent>

class FTDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    FTDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif
