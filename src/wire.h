#ifndef WIRE_H
#define WIRE_H

#include <QString>
#include <QList>
#include <QPoint>
#include "port.h"

class Wire
{
    QString name;
    QList<Port*> drivers;
    QList<Port*> loads;
    QList<Wire*> assigns;

public:
    Wire();
    Wire(QString _name);
    ~Wire();

    void assign(Wire _wire);
    bool nameIs(QString _name);
    void addDriver(Port* _pt_port);
    void addLoad(Port* _pt_port);
};

//Графическое представление
class G_Wire
{
    Wire* wire;
    QList<QPoint> segments;

public:
    G_Wire();
    ~G_Wire();
};

#endif // WIRE_H
