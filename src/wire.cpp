#include "wire.h"
#include "port.h"

Wire::Wire() {}
Wire::Wire(QString _name) {name = _name;}
Wire::~Wire() {name.clear(); drivers.clear(); loads.clear(); assigns.clear();}
