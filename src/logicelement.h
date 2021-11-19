#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include <QString>
#include <QList>

class Wire;

class LogicElement
{
    QString name;
    QList<QPair<QString, bool>> ports;
    QList<Wire> wires;
    QList<LogicElement> logicElements;
    bool basic;

public:
    LogicElement();
    LogicElement(QString _name);
    ~LogicElement();

    void initBasicLE(QString type);
    void initMainFromFile(QString line);
};

#endif // LOGICELEMENT_H
