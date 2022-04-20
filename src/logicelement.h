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
    static QList<LogicElement> library;

    Wire* wireNamed(QString _name);
     bool haveWire(QString _name);
    Port* portNamed(QString _name);
     bool havePort(QString _name);
    LogicElement* leNamed(QString _name);
     bool haveLE(QString _name);
    bool nameIs(QString _name);
    bool initLEFromFile(const QString &path);
public:
	LogicElement();
     LogicElement(LogicElement* _le);
     ~LogicElement();
    static bool readLibrary(const QString& path);
    static LogicElement* copyFromLibrary(QString _type, QString _name);
	void clear();
    bool initMainLEFromFile(const QString &path);

    friend class LEShape;
	friend class LEdiScene;
};

#endif // LOGICELEMENT_H
