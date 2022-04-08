#ifndef PORT_H
#define PORT_H

#include <QString>
#include "defines.h"
#include "wire.h"

struct Port
{
	LogicElement* le;
	QString name;
	Wire* insideWire;
	Wire* outsideWire;
    bool isOutput;

     Port();
	 Port(LogicElement* _le ,QString _name);
	 Port(LogicElement* _le ,QString _name, bool _isOutput);
     ~Port();
};

////Графическое представление
//class G_Port
//{
//    Port* port;
//    QPoint place;
//
//public:
//     G_Port();
//     ~G_Port();
//};

#endif // PORT_H
