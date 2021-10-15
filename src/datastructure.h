#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QString>
#include <QList>

class LogicElement
{
private:
    QString name;
    QList<QString> ports;
};

class Wire
{
private:
    QList<QPair<LogicElement,QString>> Drivers;
    QList<QPair<LogicElement,QString>> Loads;
};

#endif // DATASTRUCTURE_H
