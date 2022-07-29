#include "LEData.h"
#include "PortData.h"
#include "PortShape.h"

PortData::PortData() {le=NULL; insideWire=NULL; outsideWire=NULL; isOutput=false; shape=NULL;}
PortData::PortData(LEData* _le ,QString _name) {name=_name; le=_le; insideWire=NULL; outsideWire=NULL; isOutput=false; shape=NULL;}
PortData::PortData(LEData* _le ,QString _name, bool _isOutput) {name=_name; le=_le; insideWire=NULL; outsideWire=NULL; isOutput=_isOutput; shape=NULL;}
PortData::~PortData(){
	//le->portNamed
	if (shape != NULL) delete(shape);
}
