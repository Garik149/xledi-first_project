#include "wire.h"

Wire::WirePort::WirePort(LogicElement* _pt_le, QString _name) {pt_le = _pt_le; name = _name;}
Wire::WirePort::~WirePort() {}

Wire::Wire() {}
Wire::Wire(QString _name) {name = _name;}
Wire::~Wire() {}

void Wire::addDriver(LogicElement* _pt_le, QString _name)
{
    drivers.append(WirePort(_pt_le, _name));
}

void Wire::addLoad(LogicElement* _pt_le, QString _name)
{
    loads.append(WirePort(_pt_le, _name));
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
