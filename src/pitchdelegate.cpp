#include "pitchdelegate.hpp"

PitchDelegate::PitchDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *PitchDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    QLineEdit *lineEdit = new QLineEdit(parent);
    lineEdit->setFrame(false);
    lineEdit->setAlignment(Qt::AlignCenter);
    lineEdit->setValidator(new QDoubleValidator(-90, 90, 5, lineEdit));
    return lineEdit;
}
