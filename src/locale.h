#ifndef LOCALE_H
#define LOCALE_H

#include "QString"

class Locale
{
    int locale;

public:
    Locale();

    //void setLocale(QString);

    QString get0();
    QString get1();
    QString get2();
    QString get3();
    QString get4();
};

#endif // LOCALE_H