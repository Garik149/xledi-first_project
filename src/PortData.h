#ifndef PORTDATA_H
#define PORTDATA_H

#include <QString>
#include "defines.h"

struct PortData
{
	QString name;
    LEData* le;
    WireData* insideWire;
    WireData* outsideWire;
	bool isOutput:1;
	PortShape* shape;


	PortData();
	PortData(LEData* _le ,QString _name);
	PortData(LEData* _le ,QString _name, bool _isOutput);
	~PortData();
};

#endif // PORTDATA_H
