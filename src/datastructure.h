#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QString>
#include <QList>

class Wire;
class LogicElement;

class LogicElementType
{
private:
    QString typeName;
    QList<QString> ports;
    QList<QPair<Wire,QString>> wires;
};

class LogicElement
{
private:
    QString name;
    QString typeName;
};

class Wire
{
private:
    QList<QPair<LogicElement,QString>> Drivers;
    QList<QPair<LogicElement,QString>> Loads;
};

#endif // DATASTRUCTURE_H
