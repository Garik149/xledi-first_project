#ifndef MODULE_H
#define MODULE_H

#include <QString>
#include <QList>

class LogicElement;
class Wire;

class Module
{
public:
    Module();
    ~Module();
    void initFromFile(QString line, QList<Module>* moduleList);
    void addToList();

private:
	QString name;
    QList<QPair<QString, bool>> ports;
    QList<Wire*> wires;
    QList<LogicElement*> logicElements;
};

#endif // MODULE_H
