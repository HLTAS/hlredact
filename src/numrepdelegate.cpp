#include "numrepdelegate.hpp"

static const int SINGLE_STEP = 5;
static const int SHIFT_STEP = 20;

NumRepDelegate::NumRepDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *NumRepDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &,
                                      const QModelIndex &) const
{
    QLineEdit *lineEdit = new QLineEdit(parent);
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setFrame(false);
    return lineEdit;
}

bool NumRepDelegate::eventFilter(QObject *editor, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QLineEdit *lineEdit = (QLineEdit *)editor;
        QKeyEvent *keyEvent = (QKeyEvent *)event;

        if (keyEvent->modifiers() == Qt::NoModifier) {
            if (keyEvent->key() == Qt::Key_Space) {
                emit commitData(lineEdit);
                emit closeEditor(lineEdit);
                return true;
            } else if (keyEvent->key() == Qt::Key_Equal) {
                return true;
            } else if (keyEvent->key() == Qt::Key_Minus) {
                return true;
            } else if (keyEvent->key() == Qt::Key_Backspace) {
                lineEdit->end(false);
                return true;
            }
        } else if (keyEvent->modifiers() == Qt::ShiftModifier) {
            if (keyEvent->key() == Qt::Key_Plus) {
                return true;
            } else if (keyEvent->key() == Qt::Key_Underscore) {
                return true;
            }
        } else if (keyEvent->modifiers() == Qt::AltModifier) {
            if (keyEvent->key() == Qt::Key_Equal) {
                return true;
            } else if (keyEvent->key() == Qt::Key_Minus) {
                return true;
            }
        }
    } else if (event->type() == QEvent::FocusIn) {
        ((QLineEdit *)editor)->end(false);
        return true;
    }

    return QStyledItemDelegate::eventFilter(editor, event);
}
