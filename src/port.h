#ifndef PORT_H
#define PORT_H

#include <QString>
#include "defines.h"

struct Port
{
	QString name;
	LogicElement* le;
	Wire* insideWire;
	Wire* outsideWire;
	bool isOutput:1;

     Port();
	 Port(LogicElement* _le ,QString _name);
	 Port(LogicElement* _le ,QString _name, bool _isOutput);
     ~Port();
};

#endif // PORT_H
