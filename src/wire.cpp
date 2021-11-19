#include "wire.h"

Wire::Wire() {}
Wire::Wire(QString _name) {name = _name;}
Wire::~Wire() {}

void Wire::addDriver(LogicElement* pt_LE, QString port)
{
    QPair<LogicElement*,QString> driver(pt_LE, port);
    drivers.append(driver);
}

void Wire::addLoad(LogicElement* pt_LE, QString port)
{
    QPair<LogicElement*,QString> load(pt_LE, port);
    loads.append(load);
}

bool Wire::nameIs(QString _name)
{
    if (name == _name)
        return true;
    else return false;
}
