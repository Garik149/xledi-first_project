#ifndef WIRE_H
#define WIRE_H

#include <QString>
#include <QList>

class LogicElement;

class Wire
{
    struct WirePort
    {
        QString name;
        LogicElement* pt_le;

        WirePort(LogicElement* _pt_le, QString _name);
        ~WirePort();
    };

    QString name;
    QList<WirePort> drivers;
    QList<WirePort> loads;
    QList<Wire*> assigns;

public:
    Wire();
    Wire(QString _name);
    ~Wire();

    void assign(Wire _wire);
    bool nameIs(QString _name);
    void addDriver(LogicElement* _pt_le, QString _name);
    void addLoad(LogicElement* _pt_le, QString _name);
};

#endif // WIRE_H
