#ifndef LESHAPE_H
#define LESHAPE_H

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTextItem>
#include "defines.h"

class LEShape{
public:
	enum State {Default, Bolded, Moved};
private:
	State state;
    LogicElement* le;
	QPoint place;
	QGraphicsSimpleTextItem* type;
	QGraphicsSimpleTextItem* name;
	QGraphicsRectItem* body;
	QList<QGraphicsLineItem*> ports;

public:
	 LEShape(LogicElement* _le);
     ~LEShape();
	void setState(State state);
	void moveTo(QPoint _place);
	bool initMainLEFromFile(QString &path);

	friend class LEdiScene;
};

#endif // LESHAPE_H
