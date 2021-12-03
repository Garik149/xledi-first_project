#ifndef PORT_H
#define PORT_H

#include <QString>

struct Port
{
    QString name;
    bool outPort;

    Port();
    Port(QString _name);
    Port(QString _name, bool _outPort);
    ~Port();
};

#endif // PORT_H
