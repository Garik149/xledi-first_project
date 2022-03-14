#include "lediscene.h"
#include "leshape.h"

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


	//painter->setPen(QColor(Qt::white));
	//painter->setFont(font);
	//painter->translate(QPoint(600, 600));
	//painter->drawText(30, 0, "mMm");
}

void LEdiScene::addShape(LEShape* leShape){
	addItem(leShape->type);
	addItem(leShape->name);
	addItem(leShape->body);
	for (int i = 0; i < leShape->ports.size(); i +=1)
		addItem(leShape->ports[i]);
}
