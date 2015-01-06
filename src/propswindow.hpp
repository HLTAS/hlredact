#ifndef PROSPWINDOW_HPP
#define PROSPWINDOW_HPP

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QRegExpValidator>
#include "uintvalidator.hpp"

class PropsWindow : public QDialog
{
    Q_OBJECT

public:
    PropsWindow(QWidget *parent = nullptr, Qt::WindowFlags f = 0);

private slots:
    
};

#endif
