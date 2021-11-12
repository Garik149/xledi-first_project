#ifndef MODULE_H
#define MODULE_H

#include "wire.h"
#include "logicelement.h"
#include <QList>

class module
{
public:
	module();
	~module();
    void initFromFile(QFile file);
private:
	QString name;
	QList<QString> ports;
	QList<wire> wires;
	QList<logicElement> logicElements;
};

#endif // MODULE_H
