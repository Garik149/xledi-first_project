#ifndef LESHAPE_H
#define LESHAPE_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include "defines.h"

class LEShape{
    LogicElement* le;
    QPoint place;
    QGraphicsRectItem body;
    QList<QGraphicsLineItem> ports;

public:
     LEShape(LogicElement* _le);
     ~LEShape();
     void moveTo(QPoint _place);

     friend class LEdiScene;
};

#endif // LESHAPE_H
