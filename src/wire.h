#ifndef WIRE_H
#define WIRE_H

#include "logicelement.h"
#include <QString>
#include <QList>

class wire
{
public:
	wire();
	~wire();
	void initFromFile();
private:
	QString name;
	QList<QPair<logicElement,QString>> drivers;
	QList<QPair<logicElement,QString>> loads;
};

#endif // WIRE_H
