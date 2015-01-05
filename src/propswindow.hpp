#ifndef PROSPWINDOW_HPP
#define PROSPWINDOW_HPP

#include <QDialog>

class PropsWindow : public QDialog
{
    Q_OBJECT

public:
    PropsWindow(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
};

#endif
