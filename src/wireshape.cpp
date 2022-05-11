#include "wireshape.h"
#include "wire.h"

WireShape::WireShape(Wire* _wire) : QGraphicsLineItem(){
    wire=_wire;
    setPos(0,0);

    setState(Default);
}


void WireShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    switch(state){
    default:
        painter->setPen(QPen(QColor(255,0,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;

    case State::Bolded:
        painter->setPen(QPen(QColor(255,0,0,255), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;

    case State::Moved:
        painter->setPen(QPen(QColor(255,0,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;
    }

    painter->drawLine(line());

    return;
}

void WireShape::setState(State _state){
    state=_state;
    update();
}