#ifndef WIRE_H
#define WIRE_H

#include <QString>
#include <QList>

class LogicElement;

class Wire
{
    QString name;
    QList<QPair<LogicElement*,QString>> drivers;
    QList<QPair<LogicElement*,QString>> loads;

public:
    Wire();
    Wire(QString _name);
    ~Wire();

    bool nameIs(QString _name);
    void addDriver(LogicElement* pt_LE, QString port);
    void addLoad(LogicElement* pt_LE, QString port);
};

#endif // WIRE_H
