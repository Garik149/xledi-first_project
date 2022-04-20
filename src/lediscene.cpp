#include <QMap>

#include "lediscene.h"
#include "leshape.h"
#include "portshape.h"
#include "logicelement.h"
#include "port.h"
#include "wire.h"

LEdiScene::LEdiScene(const QRect &sceneRect, QObject *parent) : QGraphicsScene(sceneRect, parent)
{
	//gridSz=20;
}

void LEdiScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(Qt::black);
    painter->setPen({Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    painter->drawRect(rect);

    painter->setPen({Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    for (int i = GRID_SZ; i < rect.right(); i += GRID_SZ)
        for (int j = GRID_SZ; j < rect.bottom(); j += GRID_SZ)
			painter->drawPoint(i, j);
}

void LEdiScene::addShape(LEShape* leShape){
	addItem(leShape->type);
	addItem(leShape->name);
	addItem(leShape->body);
	for (int i = 0; i < leShape->ports.size(); i +=1)
		addItem(leShape->ports[i]);
}

void LEdiScene::addShape(PortShape* portShape){
	addItem(portShape->name);
	for (int i = 0; i < 4; i +=1)
		addItem(portShape->body[i]);
}

void LEdiScene::check(QHash<LogicElement*, int>* map, LogicElement* _le, int _r){
	int& r = map->find(_le).value();
	if (r < _r+1) r=_r+1;

	Port* port;
	Wire* wire;
	for (int i=0; i < _le->outPorts.size(); i++){
		port=_le->outPorts[i];
		for (int j=0; j < port->outsideWire->loads.size(); j++){
			wire=port->outsideWire;
			if (wire == wire->loads[j]->outsideWire)
				check(map, wire->loads[j]->le,r);
		}
	}
}
void LEdiScene::layout(LogicElement* le){
    int i, j;

	QHash<LogicElement*, int>* map = new QHash<LogicElement*, int>;
    for (i=0; i<le->logicElements.size(); i++)
		map->insert(le->logicElements[i],1);

	for (i=0; i<le->inPorts.size(); i++)
        for (j=0; j<le->inPorts[i]->insideWire->loads.size(); j++)
			check(map, le->inPorts[i]->insideWire->loads[j]->le,0);

	int maxRank = 1;
	for (i=0; i<le->logicElements.size(); i++){
		int r=map->find(le->logicElements[i]).value();
		if (maxRank<r) maxRank=r;
	}

	for (i=0; i<le->inPorts.size(); i++){
		PortShape* sh;
		sh = new PortShape(le->inPorts[i]);
		addShape(sh);
		sh->moveTo(QPoint(GRID_SZ*10,GRID_SZ*(10+4*i)));
	}

	QList<LogicElement*> leList;
	for (i=1; i<=maxRank; i++){
		leList=map->keys(i);
		int Height=0;
		for (j=0; j<leList.size(); j++){
			LEShape* sh;
			sh = new LEShape(leList[j]);
            addShape(sh);
			sh->moveTo(QPoint(GRID_SZ*(10+10*i),GRID_SZ*(10+Height)));
			Height+=sh->body->rect().height()/GRID_SZ+2;
        }
    }

	for (i=0; i<le->outPorts.size(); i++){
		PortShape* sh;
		sh = new PortShape(le->outPorts[i]);
		addShape(sh);
		sh->moveTo(QPoint(GRID_SZ*(20+10*maxRank),GRID_SZ*(10+4*i)));
	}

    delete (map);
}
