#include "port.h"

Port::Port() {le=NULL; insideWire=NULL; outsideWire=NULL; isOutput=false; shape=NULL;}
Port::Port(LogicElement* _le ,QString _name) {name=_name; le=_le; insideWire=NULL; outsideWire=NULL; isOutput=false; shape=NULL;}
Port::Port(LogicElement* _le ,QString _name, bool _isOutput) {name=_name; le=_le; insideWire=NULL; outsideWire=NULL; isOutput=_isOutput; shape=NULL;}
Port::~Port() {name.clear();}
