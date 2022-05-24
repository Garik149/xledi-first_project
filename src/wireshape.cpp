#include "wireshape.h"
#include "wire.h"

//WireShape
WireShape::WireShape(Wire* _wire, LEdiScene* _scene){
	_wire->shape=this;
    scene=_scene;
	data=_wire;
}

WireSeg* WireShape::addSeg(QLineF line){
    WireSeg* hWireSeg=new WireSeg(this, line);
    seg.append(hWireSeg);
    scene->addItem(hWireSeg);
    return hWireSeg;
}


//WireSeg
WireSeg::WireSeg(WireShape* _shape, QLineF _line) : QGraphicsLineItem(_line){
	whole=_shape;
	setPos(0,0);

	setState(Default);
}


void WireSeg::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {

    QPen pen(QPen(QColor(BLUE,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    switch(state){
	default:
        break;

	case State::Bolded:
        pen.setWidth(pen.width()+1);
        break;

	case State::Moved:
        pen.setColor(QColor(pen.color().red(),pen.color().green(),pen.color().blue(),128));
        break;
	}

    painter->setPen(pen);
	painter->drawLine(line());

	return;
}

void WireSeg::setState(State _state){
	state=_state;
	update();
}
