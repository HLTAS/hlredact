#ifndef STRAFEDELEGATE_HPP
#define STRAFEDELEGATE_HPP

#include <QLineEdit>
#include <QSpinBox>
#include <QStyledItemDelegate>

class StrafeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    StrafeDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

private slots:
    void textEdited(const QString &text);
};

#endif
