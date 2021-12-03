#ifndef SCENELEDI_H
#define SCENELEDI_H

#include <QGraphicsScene>
//#include <QGraphicsSceneMouseEvent>
//#include <QDebug>
#include <QString>
//#include <QMap>

#include "port.h"
#include "logicelement.h"
#include "wire.h"

class SceneLEdi : public QGraphicsScene
{

    Q_OBJECT
public:
    explicit SceneLEdi(const QRectF &sceneRect, QObject *parent = nullptr);
    //~SceneLEdi();

    //void createItem(ItemLEdi::TypeItem type  = ItemLEdi::Null);
    //void createWire(QPointF mousePos);
    //void moveWire(QPointF mousePos);
    //void moveItem(QPointF mousePos);
    //void clearItem();
    //void setLocationWire(){locationWire = !locationWire;}
    //void deleteSelectItem();
    //inline const ItemLEdi* findItem(QString nameElement) const {return mapItems.value(nameElement);}
    //void addItemToMap(QGraphicsItem* ptrItem);

private:
    //QMap<QString, ItemLEdi*> mapItems{};
    //QPoint binding(QPointF point);
    //QGraphicsRectItem *seletionRect;
    const int gridSize = 20;
    //QGraphicsLineItem *lineWire1, *lineWire2;
    //ItemLEdi *currentItem;
    //Wire *wire;
    //Pin *firstPin, *endPin;
    //bool locationWire;

private slots:
    //void slotNameChanged(QString oldName, QString newName);

signals:
    //void tranferItem(ItemLEdi* item, QGraphicsLineItem *line);

public:
    virtual void drawBackground(QPainter *painter, const QRectF &rect);

};

#endif // SCENECAD_H
