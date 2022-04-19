#include <QMap>

#include "lediscene.h"
#include "leshape.h"
#include "portshape.h"
#include "logicelement.h"
#include "port.h"
#include "wire.h"

LEdiScene::LEdiScene(const QRect &sceneRect, QObject *parent) : QGraphicsScene(sceneRect, parent)
{
    gridSz=20;
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

void LEdiScene::check(QHash<LogicElement*, int>* map, Port* _port, int r){
	if (map->find(_port->le).value() <= r) map->find(_port->le).value()=r;

	Port* port;
	Wire* wire;
	for (int i=0; i < _port->le->outPorts.size(); i++){
		port=_port->le->outPorts[i];
		for (int j=0; j < port->outsideWire->loads.size(); j++){
			wire=port->outsideWire;
			if (wire == wire->loads[j]->outsideWire)
				check(map, wire->loads[j],r+1);
		}
	}
}
void LEdiScene::layout(LogicElement* le){
    int i, j;

	QHash<LogicElement*, int>* map = new QHash<LogicElement*, int>;
    for (i=0; i<le->logicElements.size(); i++)
        map->insert(le->logicElements[i],0);

	for (i=0; i<le->inPorts.size(); i++)
        for (j=0; j<le->inPorts[i]->insideWire->loads.size(); j++)
			check(map, le->inPorts[i]->insideWire->loads[j],1);

    QList<int> rank; QList<int> ql= map->values();
    for (i=0; i<ql.size(); i++)
        if (!rank.contains(ql[i])) rank.append(ql[i]);
    QList<LogicElement*> leList;
	int maxRank = 1;

    for (i=0; i<rank.size(); i++){
		if (maxRank<rank[i]) maxRank=rank[i];
        leList=map->keys(rank[i]);
		int prevLEHeight=0;
		for (j=0; j<leList.size(); j++){
			LEShape* sh;
			sh = new LEShape(leList[j]);
            addShape(sh);
			sh->moveTo(QPoint(gridSz*(10+10*rank[i]),gridSz*(10+(prevLEHeight+2)*j)));
            prevLEHeight=sh->body->rect().height()/gridSz;
        }
    }

	for (i=0; i<le->inPorts.size(); i++){
		PortShape* sh;
		sh = new PortShape(le->inPorts[i]);
		addShape(sh);
		sh->moveTo(QPoint(gridSz*10,gridSz*(10+4*i)));
	}

	for (i=0; i<le->outPorts.size(); i++){
		PortShape* sh;
		sh = new PortShape(le->outPorts[i]);
		addShape(sh);
		sh->moveTo(QPoint(gridSz*(20+10*maxRank),gridSz*(10+4*i)));
	}

    delete (map);
}
