#ifndef LESHAPE_H
#define LESHAPE_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include "defines.h"

class LEShape{
public:
	enum State {Default, Bolded, Moved};
private:
	State state;
    LogicElement* le;
	QPoint place;
	QGraphicsRectItem* body;
	QList<QGraphicsLineItem*> ports;

public:
     LEShape(LogicElement* _le);
     ~LEShape();
	void setState(State state);
	void moveTo(QPoint _place);

	friend class LEdiScene;
};

#endif // LESHAPE_H
