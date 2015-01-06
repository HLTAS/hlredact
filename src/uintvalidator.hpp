#ifndef UINTVALIDATOR_HPP
#define UINTVALIDATOR_HPP

#include <QValidator>

class UIntValidator : public QValidator
{
public:
    UIntValidator(unsigned int minimum, unsigned int maximum,
                  QObject *parent = nullptr);
    QValidator::State validate(QString &input, int &pos) const;

private:
    unsigned int lowerbd;
    unsigned int upperbd;
};

#endif
