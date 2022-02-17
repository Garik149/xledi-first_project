#include "leshape.h"
#include "logicelement.h"
//#include "wire.h"
#include "port.h"

LEShape::LEShape(LogicElement* _le){
    le = _le;
    place = QPoint(0,0);

    int mkOut=0, mkIn=0, h, dy;
	QGraphicsLineItem* line;

    for (int i=0; i < le->ports.size(); i++)
        if ((le->ports[i].isOutput)) mkOut++; else mkIn++;
    if (mkOut>mkIn) h=mkOut; else h=mkIn;

	body = new QGraphicsRectItem();
	body->setPen(QPen(QColor(0,255,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	body->setRect(QRectF(place.x(), place.y(), 2*GRID_SZ, (h+1)*GRID_SZ));

    for (int i=0; i < le->outPorts.size(); i++){
		line = new QGraphicsLineItem();
		line->setPen(QPen(QColor(0,255,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		dy = (i+1)*GRID_SZ;
        line->setLine(QLineF(QPoint(place.x()+2*GRID_SZ,place.y()+dy),QPoint(place.x()+3*GRID_SZ,place.y()+dy)));
		ports.append(line);
    }
	for (int i=0; i < le->inPorts.size(); i++){
		line = new QGraphicsLineItem();
		line->setPen(QPen(QColor(0,255,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		dy = (i+1)*GRID_SZ;
		line->setLine(QLineF(QPoint(place.x(),place.y()+dy),QPoint(place.x()-GRID_SZ,place.y()+dy)));
		ports.append(line);
	}
}

LEShape::~LEShape() {}

void LEShape::moveTo(QPointF _place){
	place=_place;
}
