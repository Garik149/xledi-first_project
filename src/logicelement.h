#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include <QString>
#include <QList>
#include "defines.h"

class LogicElement{
    QString name;
    QList<Port> ports;
     QList<Port*> inPorts;
     QList<Port*> outPorts;
    QList<Wire> wires;
    QList<LogicElement> logicElements;
    bool basic:1;
    static QList<LogicElement> library;

    Wire& leWire(QString _name);
    Port& lePort(QString _name);
	void resetLists();
    bool havePort(QString _name);
    bool nameIs(QString _name);
    bool initLEFromFile(QString &path);
public:
	LogicElement();
	 LogicElement(QString _type, QString _name);
     ~LogicElement();
    static void addBasicElements();
	void clear();
	bool initMainLEFromFile(QString &path);

    friend class LEShape;
};

#endif // LOGICELEMENT_H
