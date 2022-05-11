#ifndef WIRE_H
#define WIRE_H

#include <QString>
#include <QList>
#include "defines.h"

struct Wire
{
    QString name;
    QList<Port*> drivers;
    QList<Port*> loads;
    QList<Wire*> assigns;

     Wire();
     Wire(QString _name);
     ~Wire();
};

#endif // WIRE_H
