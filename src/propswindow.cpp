#include "propswindow.hpp"

PropsWindow::PropsWindow(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    setWindowTitle("Properties");

    QGridLayout *gridLay = new QGridLayout(this);
    setLayout(gridLay);

    QLabel *lblDemo = new QLabel("&Demo", this);
    gridLay->addWidget(lblDemo, 0, 0);
    editDemo = new QLineEdit(this);
    lblDemo->setBuddy(editDemo);
    gridLay->addWidget(editDemo, 0, 1);

    QLabel *lblSave = new QLabel("&Save", this);
    gridLay->addWidget(lblSave, 1, 0);
    editSave = new QLineEdit(this);
    lblSave->setBuddy(editSave);
    gridLay->addWidget(editSave, 1, 1);

    QRegExp regExp("[a-zA-Z0-9_]*");
    QRegExpValidator *regExpValid = new QRegExpValidator(regExp, this);
    editDemo->setValidator(regExpValid);
    editSave->setValidator(regExpValid);

    QLabel *lblSSeed = new QLabel("S s&eed", this);
    gridLay->addWidget(lblSSeed, 2, 0);
    editSSeed = new QLineEdit(this);
    lblSSeed->setBuddy(editSSeed);
    gridLay->addWidget(editSSeed, 2, 1);

    QLabel *lblNSSeed = new QLabel("&NS seed", this);
    gridLay->addWidget(lblNSSeed, 3, 0);
    editNSSeed = new QLineEdit(this);
    lblNSSeed->setBuddy(editNSSeed);
    gridLay->addWidget(editNSSeed, 3, 1);

    UIntValidator *uintValid = new UIntValidator(
        0, std::numeric_limits<unsigned int>::max(),
        this);
    editNSSeed->setValidator(uintValid);
    editSSeed->setValidator(uintValid);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    gridLay->addWidget(buttonBox, 4, 0, 1, 2);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void PropsWindow::setDemoName(const QString &name)
{
    editDemo->setText(name);
}

void PropsWindow::setSaveName(const QString &name)
{
    editSave->setText(name);
}

void PropsWindow::setNSSeed(unsigned int seed)
{
    editNSSeed->setText(QString::number(seed));
}

void PropsWindow::setSSeed(unsigned int seed)
{
    editSSeed->setText(QString::number(seed));
}

QString PropsWindow::demoName() const
{
    return editDemo->text();
}

QString PropsWindow::saveName() const
{
    return editSave->text();
}

unsigned int PropsWindow::NSSeed() const
{
    return editNSSeed->text().toUInt();
}

unsigned int PropsWindow::SSeed() const
{
    return editSSeed->text().toUInt();
}

void PropsWindow::clearSeeds()
{
    editNSSeed->setText(QString());
    editSSeed->setText(QString());
}
