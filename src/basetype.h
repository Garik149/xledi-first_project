#ifndef BASETYPE_H
#define BASETYPE_H

#include <QString>
#include <QList>

class baseType
{
public:
	baseType();
	~baseType();
	void initBaseTypes();
private:
	QString name;
	QList<QString> ports;
};

#endif // BASETYPE_H
