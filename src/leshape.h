#ifndef LESHAPE_H
#define LESHAPE_H

#include <QGraphicsItem>
#include <QPainter>
#include "defines.h"

class LEShape : public QGraphicsItem{
public:
    enum {Type = UserType};
	enum State {Default, Bolded, Moved};
private:
	State state;
    LogicElement* le;
    QRectF* body;
    QList<QLineF*> ports;

public:
	 LEShape(LogicElement* _le);
     ~LEShape();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    int type() const override {return Type;}
    void setState(State state);

	friend class LEdiScene;
};

#endif // LESHAPE_H
