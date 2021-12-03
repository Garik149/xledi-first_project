#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include <QString>
#include <QList>
#include "port.h"

class Wire;

class LogicElement
{
    QString name;
    QList<Port> ports;
    QList<Wire> wires;
    QList<LogicElement> logicElements;
    bool basic;

public:
    LogicElement();
    LogicElement(QString _name);
    ~LogicElement();

    Wire& leWire(QString _name);
    Port& lePort(QString _name);

    void clear();
    void addBasicElements(QList<LogicElement> &library);
    bool havePort(QString _name);
    bool nameIs(QString _name);
    bool initMainLEFromFile(QString &path);
    bool initLEFromFile(QString &path);
};

#endif // LOGICELEMENT_H
