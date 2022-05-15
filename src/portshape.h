#ifndef PORTSHAPE_H
#define PORTSHAPE_H

#include <QGraphicsItem>
#include <QPainter>
#include "defines.h"

class PortShape : public QGraphicsItem{
public:
	enum {Type = UserType+1};
	enum State {Default, Bolded, Moved};
private:
	State state;
    Port* port;
    QLineF* body[4];
	QPointF* ending;
    bool shownLabels;

public:
    PortShape(Port* _port);
     ~PortShape();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    int type() const override {return Type;}
    void setState(State _state);

	friend class LEdiScene;
};

#endif // PORTSHAPE_H
