#include "PortData.h"

PortData::PortData() {le=NULL; insideWire=NULL; outsideWire=NULL; isOutput=false; shape=NULL;}
PortData::PortData(LEData* _le ,QString _name) {name=_name; le=_le; insideWire=NULL; outsideWire=NULL; isOutput=false; shape=NULL;}
PortData::PortData(LEData* _le ,QString _name, bool _isOutput) {name=_name; le=_le; insideWire=NULL; outsideWire=NULL; isOutput=_isOutput; shape=NULL;}
PortData::~PortData() {name.clear();}
