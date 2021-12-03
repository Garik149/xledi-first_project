#include "sceneledi.h"

//#include <QKeyEvent>
#include <QPainter>

SceneLEdi::SceneLEdi(const QRectF &sceneRect, QObject *parent) : QGraphicsScene(sceneRect, parent)
{
    //lineWire1 = nullptr;
    //lineWire2 = nullptr;
    //firstPin = nullptr;
    //endPin = nullptr;
    //wire = nullptr;
    //currentItem = nullptr;
    //locationWire = true;
}

void SceneLEdi::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPen pen{Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin};
    painter->setPen(pen);
    for(int i = gridSize; i < rect.right(); i += gridSize)
        for(int j = gridSize; j < rect.bottom(); j += gridSize)
            painter->drawPoint(i, j);

}
