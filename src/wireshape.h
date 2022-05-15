#ifndef WIRESHAPE_H
#define WIRESHAPE_H

#include <QGraphicsItem>
#include <QPainter>
#include "defines.h"

class WireShape : public QGraphicsLineItem{
public:
    enum {Type = UserType + 2};
    enum State {Default, Bolded, Moved};
private:
    State state;
    Wire* wire;

public:
    WireShape(Wire* _wire);
    ~WireShape() {};
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    int type() const override {return Type;}
    void setState(State state);
};

#endif // WIRESHAPE_H
