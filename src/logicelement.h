#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include <QString>
#include <QList>

class Wire;

class LogicElement
{
    struct LEPort
    {
        QString name;
        bool outPort;

        LEPort(QString _name, bool _outPort);
        ~LEPort();
    };

    QString name;
    QList<LEPort> ports;
    QList<Wire> wires;
    QList<LogicElement> logicElements;
    bool basic;

public:
    LogicElement();
    LogicElement(QString _name);
    ~LogicElement();

    Wire& LEwire(QString _name);
    QString& LEinPort(QString _name);

    void addBasicElements(QList<LogicElement> &library);
    bool havePort(QString _name, bool _outPort);
    bool nameIs(QString _name);
    bool initMainLEFromFile(QString& path);
    bool initLEFromFile(QString& path);
};

#endif // LOGICELEMENT_H
