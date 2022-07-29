#include "WireData.h"
#include "WireShape.h"
#include "PortData.h"

WireData::WireData() {shape=NULL;}
WireData::WireData(QString _name) {name = _name; shape=NULL;}
WireData::~WireData(){
	if (shape != NULL) delete(shape);
}
