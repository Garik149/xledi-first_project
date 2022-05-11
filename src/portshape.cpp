#include "portshape.h"
#include "port.h"

PortShape::PortShape(Port* _port) : QGraphicsItem(){
	port = _port;
    setPos(0,0);

	if (port->isOutput){
        body[0] = new QLineF(QPoint(x(),y()+GRID_SZ),QPoint(x()+GRID_SZ,y()+GRID_SZ));
        body[1] = new QLineF(QPoint(x()+GRID_SZ,y()),QPoint(x()+GRID_SZ,y()+2*GRID_SZ));
        body[2] = new QLineF(QPoint(x()+GRID_SZ,y()),QPoint(x()+2*GRID_SZ,y()+GRID_SZ));
        body[3] = new QLineF(QPoint(x()+GRID_SZ,y()+2*GRID_SZ),QPoint(x()+2*GRID_SZ,y()+GRID_SZ));
	}
	else{
        body[0] = new QLineF(QPoint(x(),y()),QPoint(x(),y()+2*GRID_SZ));
        body[1] = new QLineF(QPoint(x(),y()),QPoint(x()+GRID_SZ,y()+GRID_SZ));
        body[2] = new QLineF(QPoint(x(),y()+2*GRID_SZ),QPoint(x()+GRID_SZ,y()+GRID_SZ));
        body[3] = new QLineF(QPoint(x()+GRID_SZ,y()+GRID_SZ),QPoint(x()+2*GRID_SZ,y()+GRID_SZ));
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

void PortShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setPen(QPen(QColor(255,0,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setFont(QFont("Calibri", 11, QFont::DemiBold));
    painter->drawText(QRectF(0, -1*GRID_SZ, 2*GRID_SZ, 1*GRID_SZ),0,port->name);

    switch(state){
    default:
        painter->setPen(QPen(QColor(0,255,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;

    case State::Bolded:
        painter->setPen(QPen(QColor(0,255,0,255), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;

    case State::Moved:
        painter->setPen(QPen(QColor(0,255,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;
    }
    for (int i=0; i < 4; i++) painter->drawLine(*body[i]);

    return;
}

void PortShape::setState(State _state){
    state=_state;
    update();
}
