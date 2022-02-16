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

////Графическое представление
//class G_Wire
//{
//    Wire* wire;
//    QList<QPoint> segments;
//
//public:
//     G_Wire();
//     ~G_Wire();
//};

#endif // WIRE_H
