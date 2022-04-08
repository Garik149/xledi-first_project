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

void check(QHash<LogicElement*, int>* map, Port* port){
	for (int i=0; i<port->insideWire->drivers.size(); i++){
		//map()
		check(map, port->insideWire->drivers[i]);
	}
}
void LEdiScene::layout(LogicElement* le){

	QHash<LogicElement*, int>* map = new QHash<LogicElement*, int>;
	for (int i=0; i<le->logicElements.size(); i++)
		map->insert(le->logicElements[i],0);

	for (int i=0; i<le->inPorts.size(); i++)
		check(map, le->inPorts[i]);

	delete(map);
}
