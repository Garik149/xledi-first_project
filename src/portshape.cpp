#include "portshape.h"
#include "port.h"

PortShape::PortShape(){}
PortShape::PortShape(Port* _port){
	port = _port;
	place = QPoint(0,0);

	name = new QGraphicsSimpleTextItem();
	name->setFont(QFont("Calibri", 10, QFont::DemiBold));
	name->setBrush(Qt::red);
	name->setText(port->name);
	name->setPos(QPoint(place.x(),place.y()-GRID_SZ));

	if (port->isOutput){
		body[0] = new QGraphicsLineItem(QLineF(QPoint(place.x(),place.y()+GRID_SZ),QPoint(place.x()+GRID_SZ,place.y()+GRID_SZ)));
		body[1] = new QGraphicsLineItem(QLineF(QPoint(place.x()+GRID_SZ,place.y()),QPoint(place.x()+GRID_SZ,place.y()+2*GRID_SZ)));
		body[2] = new QGraphicsLineItem(QLineF(QPoint(place.x()+GRID_SZ,place.y()),QPoint(place.x()+2*GRID_SZ,place.y()+GRID_SZ)));
		body[3] = new QGraphicsLineItem(QLineF(QPoint(place.x()+GRID_SZ,place.y()+2*GRID_SZ),QPoint(place.x()+2*GRID_SZ,place.y()+GRID_SZ)));
	}
	else{
		body[0] = new QGraphicsLineItem(QLineF(QPoint(place.x(),place.y()),QPoint(place.x(),place.y()+2*GRID_SZ)));
		body[1] = new QGraphicsLineItem(QLineF(QPoint(place.x(),place.y()),QPoint(place.x()+GRID_SZ,place.y()+GRID_SZ)));
		body[2] = new QGraphicsLineItem(QLineF(QPoint(place.x(),place.y()+2*GRID_SZ),QPoint(place.x()+GRID_SZ,place.y()+GRID_SZ)));
		body[3] = new QGraphicsLineItem(QLineF(QPoint(place.x()+GRID_SZ,place.y()+GRID_SZ),QPoint(place.x()+2*GRID_SZ,place.y()+GRID_SZ)));
	}
	setState(State::Default);
}

void PortShape::setState(State _state){
	switch(_state){
	default:
		for (int i=0; i < 4; i++)
			body[i]->setPen(QPen(QColor(0,255,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		state=_state;
		break;

	case State::Bolded:
		for (int i=0; i < 4; i++)
			body[i]->setPen(QPen(QColor(0,255,0,255), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		state=_state;
		break;

	case State::Moved:
		for (int i=0; i < 4; i++)
			body[i]->setPen(QPen(QColor(0,255,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		state=_state;
		break;
	}
}

void PortShape::moveTo(QPoint _place){
	int dx=_place.x()-place.x(), dy=_place.y()-place.y();
	place=_place;
	name->moveBy(dx,dy);
	for (int i=0; i < 4; i++)
		body[i]->moveBy(dx,dy);
}
