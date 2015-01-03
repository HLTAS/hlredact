#include "strafedelegate.hpp"

StrafeDelegate::StrafeDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *StrafeDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &,
                                      const QModelIndex &) const
{
    QLineEdit *strafeEdit = new QLineEdit(parent);
    strafeEdit->setFrame(false);
    QRegExp regExp("[-AaDdCcGg][NnYyPpLlRr]");
    strafeEdit->setValidator(new QRegExpValidator(regExp, strafeEdit));
    strafeEdit->setAlignment(Qt::AlignCenter);
    connect(strafeEdit, SIGNAL(textEdited(const QString &)), this,
            SLOT(textEdited(const QString &)));
    return strafeEdit;
}

void StrafeDelegate::textEdited(const QString &text)
{
    QLineEdit *editor = (QLineEdit *)sender();
    if (text == "-") {
        emit commitData(editor);
        emit closeEditor(editor);
    } else if (text.length() == 2) {
        editor->setText(text.toUpper());
        emit commitData(editor);
        emit closeEditor(editor);
    }
}
