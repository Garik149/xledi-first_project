#ifndef PORT_H
#define PORT_H

#include <QString>
#include <QPoint>

struct Port
{
    QString name;
    bool outPort;

    Port();
    Port(QString _name);
    Port(QString _name, bool _outPort);
    ~Port();
};

//Графическое представление
class G_Port
{
    Port* port;
    QPoint place;

public:
    G_Port();
    ~G_Port();
};

#endif // PORT_H
