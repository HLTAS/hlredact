#include "numrepdelegate.hpp"

static const int SMALL_STEP = 1;
static const int NORMAL_STEP = 5;
static const int SHIFT_STEP = 50;

NumRepDelegate::NumRepDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *NumRepDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &,
                                      const QModelIndex &index) const
{
    QLineEdit *lineEdit = new QLineEdit(parent);
    lineEdit->setFrame(false);
    if (((FrameModel *)index.model())->isSaveLine(index.row())) {
        lineEdit->setProperty("saveedit", true);
        lineEdit->setAlignment(Qt::AlignLeft);
    } else {
        lineEdit->setProperty("saveedit", false);
        // int instead of unsigned int because QIntValidator only accepts int.
        QIntValidator *validator = new QIntValidator(
            1, std::numeric_limits<int>::max(), parent);
        lineEdit->setValidator(validator);
        lineEdit->setAlignment(Qt::AlignRight);
    }
    return lineEdit;
}

bool NumRepDelegate::eventFilter(QObject *editor, QEvent *event)
{
    if (editor->property("saveedit").toBool())
        return handleSaveEdit(editor, event);
    else
        return handleNumRep(editor, event);
}

void NumRepDelegate::stepBy(QLineEdit *editor, int count) const
{
    int val = editor->text().toInt();
    if (count > 0 && std::numeric_limits<int>::max() - val < count)
        val = std::numeric_limits<int>::max();
    else if (count < 0 && val <= std::abs(count))
        val = 1;
    else
        val += count;
    editor->setText(QString::number(val));
}

bool NumRepDelegate::handleNumRep(QObject *editor, QEvent *event)
{
    QLineEdit *lineEdit = (QLineEdit *)editor;

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = (QKeyEvent *)event;

        if (keyEvent->modifiers() == Qt::NoModifier) {
            if (keyEvent->key() == Qt::Key_Space) {
                emit commitData(lineEdit);
                emit closeEditor(lineEdit);
                return true;
            } else if (keyEvent->key() == Qt::Key_Equal) {
                stepBy(lineEdit, NORMAL_STEP);
                return true;
            } else if (keyEvent->key() == Qt::Key_Minus) {
                stepBy(lineEdit, -NORMAL_STEP);
                return true;
            } else if (keyEvent->key() == Qt::Key_Backspace)
                lineEdit->end(false);
        } else if (keyEvent->modifiers() == Qt::ShiftModifier) {
            if (keyEvent->key() == Qt::Key_Plus) {
                stepBy(lineEdit, SHIFT_STEP);
                return true;
            } else if (keyEvent->key() == Qt::Key_Underscore) {
                stepBy(lineEdit, -SHIFT_STEP);
                return true;
            }
        } else if (keyEvent->modifiers() == Qt::ControlModifier) {
            if (keyEvent->key() == Qt::Key_Equal) {
                stepBy(lineEdit, SMALL_STEP);
                return true;
            } else if (keyEvent->key() == Qt::Key_Minus) {
                stepBy(lineEdit, -SMALL_STEP);
                return true;
            }
        }
    } else if (event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = (QWheelEvent *)event;
        Qt::KeyboardModifiers keyMods = QGuiApplication::keyboardModifiers();

        if (keyMods == Qt::NoModifier) {
            stepBy(lineEdit, wheelEvent->angleDelta().y() > 0 ?
                   NORMAL_STEP : -NORMAL_STEP);
            return true;
        } else if (keyMods == Qt::ShiftModifier) {
            stepBy(lineEdit, wheelEvent->angleDelta().y() > 0 ?
                   SHIFT_STEP : -SHIFT_STEP);
            return true;
        } else if (keyMods == Qt::ControlModifier) {
            stepBy(lineEdit, wheelEvent->angleDelta().y() > 0 ?
                   SMALL_STEP : -SMALL_STEP);
            return true;
        }
    } else if (event->type() == QEvent::FocusIn) {
        ((QLineEdit *)editor)->end(false);
        return true;
    }

    return QStyledItemDelegate::eventFilter(editor, event);
}

bool NumRepDelegate::handleSaveEdit(QObject *editor, QEvent *event)
{
    QLineEdit *lineEdit = (QLineEdit *)editor;

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = (QKeyEvent *)event;
        if (keyEvent->modifiers() == Qt::NoModifier)
            if (keyEvent->key() == Qt::Key_Space)
                return true;
    }

    return QStyledItemDelegate::eventFilter(editor, event);
}
