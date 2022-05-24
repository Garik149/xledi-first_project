#ifndef WIRESHAPE_H
#define WIRESHAPE_H

#include <QGraphicsLineItem>
#include <QPainter>
#include "defines.h"
#include "lediscene.h"

class WireShape{
    LEdiScene* scene;
	Wire* data;
	QList <WireSeg*> seg;

public:
    WireShape(Wire* _wire, LEdiScene* _scene);
    ~WireShape() {};

    WireSeg* addSeg(QLineF line);
};


class WireSeg : public QGraphicsLineItem{
public:
	enum {Type = UserType + 2};
	enum State {Default, Bolded, Moved};
private:
	State state;
	WireShape* whole;

public:
	WireSeg(WireShape* _whole, QLineF _line);
	~WireSeg() {};
	void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
	int type() const override {return Type;}
	void setState(State state);
};

#endif // WIRESHAPE_H
