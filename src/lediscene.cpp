#include "lediscene.h"

//#include <QKeyEvent>
#include <QPainter>


LEdiScene::LEdiScene(const QRectF &sceneRect, QObject *parent) : QGraphicsScene(sceneRect, parent)
{
    //lineWire1 = nullptr;
    //lineWire2 = nullptr;
    //firstPin = nullptr;
    //endPin = nullptr;
    //wire = nullptr;
    //currentItem = nullptr;
    //locationWire = true;
}

QPoint LEdiScene::bindedToGrid(QPointF point)
{
    int xV = qRound(point.x()/gridSize)*gridSize;
    int yV = qRound(point.y()/gridSize)*gridSize;
    return QPoint{xV, yV};
}

void LEdiScene::createItem(LogicElement* le)
{
    //if(currentItem)
    //{
    //    if(currentItem->insertFlag)
    //    {
    //        type = currentItem->typeItem();
    //        currentItem->insertFlag = false;
    //        currentItem = nullptr;
    //    }
    //}
    currentLESymbol = new LESymbol(le);
    //appendLESymbol(currentLESymbol);
    //currentItem -> insertFlag = true;

    //emit tranferItem(currentItem, nullptr);
}

void LEdiScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(Qt::black);
    painter->setPen({Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    painter->drawRect(rect);

    painter->setPen({Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    for(int i = gridSize; i < rect.right(); i += gridSize)
        for(int j = gridSize; j < rect.bottom(); j += gridSize)
            painter->drawPoint(i, j);

}
