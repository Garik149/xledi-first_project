#ifndef WIREDATA_H
#define WIREDATA_H

#include <QString>
#include <QList>
#include "defines.h"

struct WireData
{
    QString name;
    QList<PortData*> drivers;
    QList<PortData*> loads;
    //QList<WireData*> assigns;
	WireShape* shape;


	WireData();
	WireData(QString _name);
	~WireData();
};

#endif // WIREDATA_H
