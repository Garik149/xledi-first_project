#include "wireshape.h"
#include "wire.h"

//WireShape
WireShape::WireShape(Wire* _wire){
	_wire->shape=this;
	data=_wire;
}

void WireShape::addToScene(LEdiScene* _scene){
	for (int i=0; i<seg.size();i++) _scene->addItem(seg[i]);
}

void WireShape::addSeg(QLineF line){
	seg.append(new WireSeg(this, line));
}


//WireSeg
WireSeg::WireSeg(WireShape* _shape, QLineF _line) : QGraphicsLineItem(_line){
	whole=_shape;
	setPos(0,0);

	setState(Default);
}


void WireSeg::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {

	switch(state){
	default:
		painter->setPen(QPen(QColor(BLUE,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		break;

	case State::Bolded:
		painter->setPen(QPen(QColor(BLUE,255), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		break;

	case State::Moved:
		painter->setPen(QPen(QColor(BLUE,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		break;
	}

	painter->drawLine(line());

	return;
}

void WireSeg::setState(State _state){
	state=_state;
	update();
}
