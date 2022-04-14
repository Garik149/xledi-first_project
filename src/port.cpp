#include "port.h"

Port::Port() {}
Port::Port(LogicElement* _le ,QString _name, bool _isOutput) {le=_le; name=_name; isOutput=_isOutput;}
Port::Port(LogicElement* _le ,QString _name) {le=_le; name=_name;}
Port::~Port() {name.clear();}
