#include "leshape.h"
#include "logicelement.h"
//#include "wire.h"
#include "port.h"

LEShape::LEShape(LogicElement* _le){
	le=_le;
    place = QPoint(0,0);

    int h = qMax(le->inPorts.size(),le->outPorts.size());

	body = new QGraphicsRectItem(QRectF(place.x(), place.y(), 2*GRID_SZ, (h+1)*GRID_SZ));

	type = new QGraphicsSimpleTextItem();
	type->setFont(QFont("Calibri", 10, QFont::DemiBold));
	type->setBrush(Qt::red);
	type->setText(le->type);
	type->setPos(QPoint(place.x(),place.y()+(h+1)*GRID_SZ));

	name = new QGraphicsSimpleTextItem();
	name->setFont(QFont("Calibri", 10, QFont::DemiBold));
	name->setBrush(Qt::red);
	name->setText(le->name);
	name->setPos(QPoint(place.x(),place.y()-GRID_SZ));

    int dy;
    QGraphicsLineItem* line;
    for (int i=0; i < le->outPorts.size(); i++){
		line = new QGraphicsLineItem();
		dy = (i+1)*GRID_SZ;
        line->setLine(QLineF(QPoint(place.x()+2*GRID_SZ,place.y()+dy),QPoint(place.x()+3*GRID_SZ,place.y()+dy)));
		ports.append(line);
    }
	for (int i=0; i < le->inPorts.size(); i++){
		line = new QGraphicsLineItem();
		dy = (i+1)*GRID_SZ;
		line->setLine(QLineF(QPoint(place.x(),place.y()+dy),QPoint(place.x()-GRID_SZ,place.y()+dy)));
		ports.append(line);
	}
    setState(State::Default);
}

LEShape::~LEShape(){
	delete(le);
	delete(type);
	delete(name);
	delete(body);
	for (int i=0; i<ports.size(); i++)
		delete(ports[i]);
}

void LEShape::setState(State _state){
	switch(_state){
	default:
		body->setPen(QPen(QColor(0,255,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		for (int i=0; i < ports.size(); i++)
			ports[i]->setPen(QPen(QColor(0,255,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		state=_state;
		break;

	case State::Bolded:
		body->setPen(QPen(QColor(0,255,0,255), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		for (int i=0; i < ports.size(); i++)
			ports[i]->setPen(QPen(QColor(0,255,0,255), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		state=_state;
		break;

	case State::Moved:
		body->setPen(QPen(QColor(0,255,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		for (int i=0; i < ports.size(); i++)
			ports[i]->setPen(QPen(QColor(0,255,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		state=_state;
		break;
	}
}

void LEShape::moveTo(QPoint _place){
	int dx=_place.x()-place.x(), dy=_place.y()-place.y();
	place=_place;
	type->moveBy(dx,dy);
	name->moveBy(dx,dy);
	body->moveBy(dx,dy);
	for (int i=0; i < ports.size(); i++)
		ports[i]->moveBy(dx,dy);
}

bool LEShape::initLEFromFile(QString &path){
	bool flag;


	flag=le->initLEFromFile(path);
	return flag;
}
