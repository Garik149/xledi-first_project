#ifndef PORT_H
#define PORT_H

#include <QString>
#include "defines.h"

struct Port
{
    QString name;
    bool isOutput;

     Port();
     Port(QString _name);
     Port(QString _name, bool _isOutput);
     ~Port();
};

////Графическое представление
//class G_Port
//{
//    Port* port;
//    QPoint place;
//
//public:
//     G_Port();
//     ~G_Port();
//};

#endif // PORT_H
