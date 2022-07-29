#ifndef PORTSHAPE_H
#define PORTSHAPE_H

#include <QGraphicsItem>
#include <QPainter>
#include "defines.h"

class PortShape : public QGraphicsItem{
public:
    enum {Type = UserType+1};
private:
	State state;
    PortData* data;
    QLineF* body[4];
	QPointF* ending;
    bool shownLabels;


public:
    PortShape(PortData* _port);
	~PortShape();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    int type() const override {return Type;}
    void setState(State _state);


	friend class LEdiScene;
};

#endif // PORTSHAPE_H
