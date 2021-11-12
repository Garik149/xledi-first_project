#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include "basetype.h"
#include <QString>
#include <QList>

class logicElement
{
public:
	logicElement();
	~logicElement();
	void initFromFile();
private:
	baseType* type;
	QString name;
};

#endif // LOGICELEMENT_H
