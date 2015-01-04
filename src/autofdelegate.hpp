#ifndef AUTOFDELEGATE_HPP
#define AUTOFDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QIntValidator>
#include <QKeyEvent>

class AutofuncsDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    AutofuncsDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

protected:
    bool eventFilter(QObject *editor, QEvent *event);
};

#endif
