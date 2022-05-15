#include "portshape.h"
#include "port.h"

PortShape::PortShape(Port* _port) : QGraphicsItem(){
	port = _port;
	port->shape=this;
    shownLabels=true;
    setPos(0,0);

	if (port->isOutput){
		body[0] = new QLineF(QPoint(0,GRID_SZ),QPoint(GRID_SZ,GRID_SZ));
		body[1] = new QLineF(QPoint(GRID_SZ,0),QPoint(GRID_SZ,2*GRID_SZ));
		body[2] = new QLineF(QPoint(GRID_SZ,0),QPoint(2*GRID_SZ,GRID_SZ));
		body[3] = new QLineF(QPoint(GRID_SZ,2*GRID_SZ),QPoint(2*GRID_SZ,GRID_SZ));
		ending = new QPointF(0,GRID_SZ);
	}
	else{
		body[0] = new QLineF(QPoint(0,0),QPoint(0,2*GRID_SZ));
		body[1] = new QLineF(QPoint(0,0),QPoint(GRID_SZ,GRID_SZ));
		body[2] = new QLineF(QPoint(0,2*GRID_SZ),QPoint(GRID_SZ,GRID_SZ));
		body[3] = new QLineF(QPoint(GRID_SZ,GRID_SZ),QPoint(2*GRID_SZ,GRID_SZ));
		ending = new QPointF(2*GRID_SZ,GRID_SZ);
	}
	setState(State::Default);
}

PortShape::~PortShape(){
    for (int i=0; i<4; i++)
        delete(body[i]);
}


QRectF PortShape::boundingRect() const{
    return QRectF(0,-1*GRID_SZ,2*GRID_SZ,3*GRID_SZ);
}

void PortShape::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {

    if (shownLabels){
        painter->setPen(QPen(QColor(RED,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setFont(QFont("Calibri", 11, QFont::DemiBold));
        painter->drawText(QRectF(0, -1*GRID_SZ, 2*GRID_SZ, 1*GRID_SZ),0,port->name);
    }

    switch(state){
    default:
        painter->setPen(QPen(QColor(GREEN,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;

    case State::Bolded:
        painter->setPen(QPen(QColor(GREEN,255), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;

    case State::Moved:
        painter->setPen(QPen(QColor(GREEN,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;
    }
    for (int i=0; i < 4; i++) painter->drawLine(*body[i]);

    painter->setPen(QPen(QColor(RED,255), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter->drawPoint(*ending);

    return;
}

void PortShape::setState(State _state){
    state=_state;
    update();
}
