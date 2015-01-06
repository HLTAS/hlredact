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

    void setDemoName(const QString &name);
    void setSaveName(const QString &name);
    void clearSeeds();
    void setNSSeed(unsigned int seed);
    void setSSeed(unsigned int seed);

    QString demoName() const;
    QString saveName() const;
    unsigned int NSSeed() const;
    unsigned int SSeed() const;

private:
    QLineEdit *editDemo;
    QLineEdit *editSave;
    QLineEdit *editNSSeed;
    QLineEdit *editSSeed;
};

#endif
