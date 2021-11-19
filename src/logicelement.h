#ifndef LOGICELEMENT_H
#define LOGICELEMENT_H

#include <QString>
#include <QList>

class Module;

class LogicElement
{
public:
    LogicElement();
    LogicElement(QString _name, const Module* _type);
    ~LogicElement();
private:
    QString name;
    const Module* type;
};

#endif // LOGICELEMENT_H
