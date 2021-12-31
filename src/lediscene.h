#ifndef LEDISCENE_H
#define LEDISCENE_H

#include <QGraphicsScene>
//#include <QGraphicsSceneMouseEvent>
//#include <QDebug>
#include <QString>
//#include <QMap>

#include "lesymbol.h"
#include "port.h"
#include "logicelement.h"
#include "wire.h"

class LEdiScene : public QGraphicsScene
{

    Q_OBJECT
public:
    explicit LEdiScene(const QRectF &sceneRect, QObject *parent = nullptr);
    ~LEdiScene(){};

    void addLE(G_LogicElement* le);
    //void createWire(QPointF mousePos);
    //void moveWire(QPointF mousePos);
    //void moveItem(QPointF mousePos);
    //void clearItem();
    //void setLocationWire(){locationWire = !locationWire;}
    //void deleteSelectItem();
    //inline const ItemLEdi* findItem(QString nameElement) const {return mapItems.value(nameElement);}
    //void appendLESymbol(LESymbol* pt_lESymbol);

private:
    //QMap<QString, ItemLEdi*> mapItems{};
    QPoint bindToGrid(QPointF point);
    //QGraphicsRectItem *selectionRect;
    const int gridSize = 20;
    //QGraphicsLineItem *lineWire1, *lineWire2;
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

#endif // LEDISCENE_H
