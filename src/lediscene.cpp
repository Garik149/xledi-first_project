#include <QMap>

#include "lediscene.h"
#include "leshape.h"
#include "logicelement.h"
#include "port.h"
#include "wire.h"

LEdiScene::LEdiScene(const QRect &sceneRect, QObject *parent) : QGraphicsScene(sceneRect, parent)
{
    //lineWire1 = nullptr;
    //lineWire2 = nullptr;
    //firstPin = nullptr;
    //endPin = nullptr;
    //wire = nullptr;
    //currentItem = nullptr;
    //locationWire = true;
}

void LEdiScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(Qt::black);
    painter->setPen({Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    painter->drawRect(rect);

    painter->setPen({Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    for (int i = GRID_SZ; i < rect.right(); i += GRID_SZ)
        for (int j = GRID_SZ; j < rect.bottom(); j += GRID_SZ)
			painter->drawPoint(i, j);;
}

void LEdiScene::addShape(LEShape* leShape){
	addItem(leShape->type);
	addItem(leShape->name);
	addItem(leShape->body);
	for (int i = 0; i < leShape->ports.size(); i +=1)
		addItem(leShape->ports[i]);
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

    for (i=0; i<map->size(); i++)
        LEShape(map->key(i));

    delete (map);

}
