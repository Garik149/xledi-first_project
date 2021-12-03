#include "port.h"

Port::Port() {}
Port::Port(QString _name, bool _outPort) {name=_name; outPort=_outPort;}
Port::Port(QString _name) {name=_name;}
Port::~Port() {name.clear();}
