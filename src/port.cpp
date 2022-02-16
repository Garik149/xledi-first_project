#include "port.h"

Port::Port() {}
Port::Port(QString _name, bool _isOutput) {name=_name; isOutput=_isOutput;}
Port::Port(QString _name) {name=_name;}
Port::~Port() {name.clear();}
