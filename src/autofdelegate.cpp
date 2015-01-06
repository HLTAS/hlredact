#include "autofdelegate.hpp"

AutofuncsDelegate::AutofuncsDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *AutofuncsDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &,
                                         const QModelIndex &) const
{
    QLineEdit *lineEdit = new QLineEdit(parent);
    UIntValidator *validator = new UIntValidator(
        0, std::numeric_limits<unsigned int>::max(), lineEdit);
    lineEdit->setValidator(validator);
    lineEdit->setAlignment(Qt::AlignCenter);
    lineEdit->setFrame(false);
    return lineEdit;
}

bool AutofuncsDelegate::eventFilter(QObject *editor, QEvent *event)
{
    QLineEdit *lineEdit = (QLineEdit *)editor;

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        if (keyEvent->key() == Qt::Key_Space &&
            keyEvent->modifiers() == Qt::NoModifier) {
            if (lineEdit->hasAcceptableInput() || lineEdit->text().isEmpty()) {
                emit commitData(lineEdit);
                emit closeEditor(lineEdit);
                return true;
            }
        }
    }

    return QStyledItemDelegate::eventFilter(editor, event);
}

void AutofuncsDelegate::setEditorData(QWidget *editor,
                                      const QModelIndex &index) const
{
    QLineEdit *lineEdit = (QLineEdit *)editor;
    QString strData = index.data(Qt::EditRole).toString();
    lineEdit->setText(strData == "∞" ? "0" : strData);
}
