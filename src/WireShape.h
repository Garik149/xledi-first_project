#ifndef WIRESHAPE_H
#define WIRESHAPE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QPainter>
#include "defines.h"
#include "LEdiScene.h"

class WireShape{
private:
    State state;
    LEdiScene* scene;
    WireData* data;
    QList <QGraphicsEllipseItem*> nodes;
	QList <WireSeg*> seg;

public:
    WireShape(WireData* _wire, LEdiScene* _scene);
    ~WireShape();

    void erase();
    void addNode(QPointF);
    WireSeg* addSeg(QLineF line);
    void setState(State _state);

    friend class LEdiScene;
    friend class WireSeg;
};


class WireSeg : public QGraphicsLineItem{
public:
    enum {Type = UserType + 2};
public:
	WireShape* whole;

public:
	WireSeg(WireShape* _whole, QLineF _line);
    ~WireSeg() {};
	void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    int type() const override {return Type;}
    void shiftLeft();

    friend class LEdiScene;
    friend class WireShape;
};

/*class WireNode : public QGraphicsEllipseItem{
public:
    enum {Type = UserType + 2};
private:
    State state;
    WireShape* whole;

public:
    WireSeg(WireShape* _whole, QLineF _line);
    ~WireSeg() {};
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    int type() const override {return Type;}
    void setState(State state);

    friend class LEdiScene;
};*/

#endif // WIRESHAPE_H
