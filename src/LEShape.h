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
    LEData* data;
    QRectF* body;
	QList<QPointF*> ports;
	bool shownLabels;

public:
     LEShape(LEData* _le);
     ~LEShape();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    int type() const override {return Type;}
    void setState(State state);

	friend class LEdiScene;
};

#endif // LESHAPE_H