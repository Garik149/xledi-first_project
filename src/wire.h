#ifndef WIRE_H
#define WIRE_H

#include <QString>
#include <QList>

class LogicElement;

class Wire
{
public:
    Wire();
    Wire(QString _name);
    ~Wire();
private:
    QString name;
    QList<QPair<LogicElement*,QString>> drivers;
    QList<QPair<LogicElement*,QString>> loads;
};

#endif // WIRE_H
