#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include <QString>
#include <QList>
#include "defines.h"

class LogicElement{
    QString name;
	QString type;
	QList<Port*> ports;
     QList<Port*> inPorts;
	 QList<Port*> outPorts;
	QList<Wire*> wires;
	QList<LogicElement*> logicElements;
	bool isBasic:1;
	LEShape* shape;
    static QList<LogicElement> library;

    Wire* wireNamed(QString _name);
     bool haveWire(QString _name);
    Port* portNamed(QString _name);
     bool havePort(QString _name);
	int leIndex(Port* _port);
	LogicElement* leNamed(QString _name);
     bool haveLE(QString _name);
    bool nameIs(QString _name);
	bool copy(LogicElement* _le);
public:
	LogicElement();
     LogicElement(LogicElement* _le);
	 LogicElement(QString _type, QString _name);
     ~LogicElement();
    static bool readLibrary(const QString& path);
	bool initLEFromFile(const QString &path);
	bool copyFromLibrary(const QString _type, const QString _name);
	void clear();

    friend class LEShape;
	friend class LEdiScene;
};

#endif // LOGICELEMENT_H
