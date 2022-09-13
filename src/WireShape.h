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
    QList <WireNode*> nodes;
	QList <WireSeg*> seg;


public:
    WireShape(WireData* _wire, LEdiScene* _scene);
    ~WireShape();

    void erase();
    void addNode(QPointF);
	WireSeg* addSeg(QLineF);
	void setState(State);


    friend class LEdiScene;
	friend class LEdiView;
    friend class WireSeg;
	friend class WireNode;
};



class WireSeg : public QGraphicsLineItem{
public:
	enum {Type = UserType + 2};
	WireShape* whole;


public:
	WireSeg(WireShape* _whole, QLineF _line);
	~WireSeg();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    int type() const override {return Type;}
    void shiftLeft();


    friend class LEdiScene;
    friend class WireShape;
};



class WireNode : public QGraphicsItem{
public:
	enum {Type = UserType + 3};
    WireShape* whole;


public:
    WireNode(WireShape* _whole, QPointF _point);
	~WireNode();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    QRectF boundingRect() const override;
    int type() const override {return Type;}


	friend class LEdiScene;
};

#endif // WIRESHAPE_H
