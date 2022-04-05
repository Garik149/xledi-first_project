#include <QMap>

#include "lediscene.h"
#include "leshape.h"
#include "logicelement.h"

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

void LEdiScene::layout(LogicElement* le){

	//QMap<LogicElement*, int> map;
	//for (int i=0; i<le->logicElements.size(); i++)
	//	map.insert(&le->logicElements[i],0);
	//
	//for (int i=0; i<le->inPorts.size(); i++){
	//	for (int i=0; i<le->inPorts.size(); i++)
	//		;
	//}
}
