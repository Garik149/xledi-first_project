#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include <QString>
#include <QList>
#include <QPoint>
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

//Графическое представление
class G_LogicElement
{
    LogicElement* le;
    QPoint place;

public:
    G_LogicElement();
    ~G_LogicElement();

    bool initG_MainLE(LogicElement* le);
};

#endif // LOGICELEMENT_H
