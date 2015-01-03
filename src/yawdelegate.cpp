#include "yawdelegate.hpp"

YawDelegate::YawDelegate(QObject *parent)
    : QStyledItemDelegate(parent), readState(0)
{
}

QWidget *YawDelegate::createEditor(QWidget *parent,
                                   const QStyleOptionViewItem &,
                                   const QModelIndex &) const
{
    QLineEdit *lineEdit = new QLineEdit(parent);
    lineEdit->setFrame(false);
    lineEdit->setAlignment(Qt::AlignCenter);
    lineEdit->setValidator(new QDoubleValidator(-360, 360, 5, lineEdit));
    return lineEdit;
}

void YawDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                               const QModelIndex &index) const
{
    if (isPointRequired())
        model->setData(index, point);
    else
        model->setData(index, ((QLineEdit *)editor)->text());
}

bool YawDelegate::eventFilter(QObject *editor, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        QLineEdit *lineEdit = (QLineEdit *)editor;

        if (keyEvent->key() == Qt::Key_Space &&
            keyEvent->modifiers() == Qt::NoModifier) {
            if (!isPointRequired()) {
                emit commitData(lineEdit);
                emit closeEditor(lineEdit);
                return true;
            }

            if (readState == 0) {
                point.setX(lineEdit->text().toDouble());
                lineEdit->setText(QString());
                readState++;
            } else {
                point.setY(lineEdit->text().toDouble());
                emit commitData(lineEdit);
                emit closeEditor(lineEdit);
                readState = 0;
            }

            return true;
        }
    } else if (event->type() == QEvent::FocusIn && !isPointRequired())
        ((QLineEdit *)editor)->end(false);

    return QStyledItemDelegate::eventFilter(editor, event);
}

bool YawDelegate::isPointRequired() const
{
    QTableView *view = (QTableView *)parent();
    QAbstractItemModel *model = view->model();
    QModelIndex indStrafe = model->index(view->currentIndex().row(),
                                         IndStrafeInfo);
    return indStrafe.data().toString()[1] == 'P';
}
