#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include "wire.h"
#include <QString>
#include <QList>

class logicElement
{
public:
	logicElement();
	~logicElement();
	void initFromFile();
private:
	QString function;
	QString name;
	QList<logicElement> logicElements;
	QList<QString> ports;
	QList<wire> wires;
};

#endif // LOGICELEMENT_H
