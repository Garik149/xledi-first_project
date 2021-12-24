#ifndef WIRE_H
#define WIRE_H

#include <QString>
#include <QList>
#include "port.h"

class Wire
{
    QString name;
    QList<Port*> drivers;
    QList<Port*> loads;
    QList<Wire*> assigns;

    //Графика
    //QList<QLine*> arms;

public:
    Wire();
    Wire(QString _name);
    ~Wire();

    void assign(Wire _wire);
    bool nameIs(QString _name);
    void addDriver(Port* _pt_port);
    void addLoad(Port* _pt_port);
};

#endif // WIRE_H
