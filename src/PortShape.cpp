#include "PortData.h"
#include "PortShape.h"

PortShape::PortShape(PortData* _port) : QGraphicsItem(){
    data = _port;
    data->shape=this;
    shownLabels=true;
    setPos(0,0);

    if (data->isOutput){
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
	for (int i=0; i<4; i++) delete(body[i]);
	data->shape=NULL;
}


QRectF PortShape::boundingRect() const{
	return QRectF(-0.1*GRID_SZ,-0.9*GRID_SZ,2.2*GRID_SZ,3.0*GRID_SZ);
}

void PortShape::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {

    if (shownLabels){
		painter->setPen(QPen(QColor(DARK_RED,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->setFont(QFont("Calibri", 11, QFont::DemiBold));
        painter->drawText(QRectF(0, -1*GRID_SZ, 2*GRID_SZ, 1*GRID_SZ),0,data->name);
    }

	QPen pen(QColor(DARK_GREEN,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
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
	for (int i=0; i < 4; i++) painter->drawLine(*body[i]);

	pen.setWidth(pen.width()+4);
	painter->setPen(pen);
	painter->drawPoint(*ending);

    return;
}

void PortShape::setState(State _state){
    state=_state;
    update();
}
