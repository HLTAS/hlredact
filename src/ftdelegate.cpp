#include "ftdelegate.hpp"
#include <QDebug>

FTDelegate::FTDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *FTDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                                  const QModelIndex &) const
{
    QLineEdit *lineEdit = new QLineEdit(parent);
    lineEdit->setFrame(false);
    lineEdit->setValidator(new QDoubleValidator(0, 0.05, 40, lineEdit));
    return lineEdit;
}

bool FTDelegate::eventFilter(QObject *obj, QEvent *event)
{
    QLineEdit *editor = (QLineEdit *)obj;
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        if (keyEvent->modifiers() == Qt::NoModifier) {
            if (keyEvent->key() == Qt::Key_Tab)
                return true;
            else if (keyEvent->key() == Qt::Key_Space) {
                emit commitData(editor);
                emit closeEditor(editor);
                return true;
            } else if (keyEvent->key() == Qt::Key_Minus) {
                editor->setText("-");
                emit commitData(editor);
                emit closeEditor(editor);
                return true;
            }
        }
    } else if (event->type() == QEvent::FocusIn)
        editor->end(false);
    return QStyledItemDelegate::eventFilter(obj, event);
}
