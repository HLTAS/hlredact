#ifndef PITCHDELEGATE_HPP
#define PITCHDELEGATE_HPP

#include <QStyledItemDelegate>
#include <QDoubleValidator>
#include <QLineEdit>

class PitchDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    PitchDelegate(QObject *parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
};

#endif
