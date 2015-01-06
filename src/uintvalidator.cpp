#include "uintvalidator.hpp"

UIntValidator::UIntValidator(unsigned int minimum, unsigned int maximum,
                             QObject *parent)
    : QValidator(parent), lowerbd(minimum), upperbd(maximum)
{
}

QValidator::State UIntValidator::validate(QString &input, int &) const
{
    if (input.isEmpty())
        return QValidator::Intermediate;
    bool ok;
    unsigned int val = input.toUInt(&ok);
    if (!ok)
        return QValidator::Invalid;
    if (val < lowerbd)
        return QValidator::Intermediate;
    return QValidator::Acceptable;
}
