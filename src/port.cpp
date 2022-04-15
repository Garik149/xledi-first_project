#include "port.h"

Port::Port() {le=NULL; insideWire=NULL; outsideWire=NULL; isOutput=false;}
Port::Port(LogicElement* _le ,QString _name) {name=_name; le=_le; insideWire=NULL; outsideWire=NULL; isOutput=false;}
Port::Port(LogicElement* _le ,QString _name, bool _isOutput) {name=_name; le=_le; insideWire=NULL; outsideWire=NULL; isOutput=_isOutput;}
Port::~Port() {name.clear();}
