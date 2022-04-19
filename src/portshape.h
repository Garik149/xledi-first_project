#ifndef PORTSHAPE_H
#define PORTSHAPE_H

#include <QGraphicsItem>
#include <QTextItem>
#include "defines.h"

class PortShape{
public:
	enum State {Default, Bolded, Moved};
private:
	State state;
	Port* port;
	QPoint place;
	QGraphicsSimpleTextItem* name;
	QGraphicsLineItem* body[4];

public:
	PortShape();
	 PortShape(Port* _port);
	void setState(State _state);
	void moveTo(QPoint _place);

	friend class LEdiScene;
};

#endif // PORTSHAPE_H
