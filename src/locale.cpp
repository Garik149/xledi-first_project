#include "locale.h"

Locale::Locale() {locale = 0;}
Locale::~Locale() {}

QString Locale::get0()
{
    switch(locale)
    {
    default: return "&File";
    case 1: return "&Файл";
    }
}

QString Locale::get1()
{
    switch(locale)
    {
    default: return "&New file";
    case 1: return "&Новый Файл";
    }
}

QString Locale::get2()
{
    switch(locale)
    {
    default: return "&Open file";
    case 1: return "&Открыть";
    }
}

QString Locale::get3()
{
    switch(locale)
    {
    default: return "&Save file";
    case 1: return "&Сохранить";
    }
}

QString Locale::get4()
{
    switch(locale)
    {
    default: return "&Quit";
    case 1: return "&Выйти";
    }
}
