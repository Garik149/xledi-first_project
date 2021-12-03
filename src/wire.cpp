#include "wire.h"

Wire::Wire() {}
Wire::Wire(QString _name) {name = _name;}
Wire::~Wire() {name.clear(); drivers.clear(); loads.clear(); assigns.clear();}

void Wire::addDriver(Port* _pt_port)
{
    drivers.append(_pt_port);
}

void Wire::addLoad(Port* _pt_port)
{
    loads.append(_pt_port);
}

bool Wire::nameIs(QString _name)
{
    if (name == _name)
        return true;
    else return false;
}

void Wire::assign(Wire wire)
{
    assigns.append(&wire);
}
