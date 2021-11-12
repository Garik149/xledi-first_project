#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include "module.h"
#include <QString>
#include <QList>

class logicElement
{
public:
	logicElement();
	~logicElement();
	void initFromFile();
private:
    module* type;
	QString name;
};

#endif // LOGICELEMENT_H
