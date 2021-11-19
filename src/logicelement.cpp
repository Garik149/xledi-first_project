#include "wire.h"
#include "logicelement.h"

LogicElement::LogicElement() {basic = false;}
LogicElement::LogicElement(QString _name) { name = _name; basic = false;}
LogicElement::~LogicElement() {}

///Не рассчитан на наличие комментариев и лишние ';'
///Не рассчитан на неявные подключения проводов к портам элементов
///Не обрабатывает assign
///Не рассчитан на включение логических элементов из других файлов
///Нужен нормальный изменяемый список базовых элементов
void LogicElement::initMainFromFile(QString line)
{
    QString str, str2, str3, str4;
    int k, k2, i, i2, i3, i4, p;

    name = "main";

    //p = line.indexOf("module "); line.remove(0, p+6);
    //p = line.indexOf('('); str = line.left(p); type = str.trimmed();

    p = line.indexOf("input "); line.remove(0, p+5);
    p = line.indexOf(';'); str = line.left(p);
    k = str.count(',')+1;
    for (i=0; i<k; i++)
    {
        str2 = str.section(',',i,i).trimmed();
        QPair<QString, bool> port(str2, 0);
        ports.append(port);
        Wire wire(str2);
        wire.addDriver(this, str2);
        wires.append(wire);
    }

    p = line.indexOf("output "); line.remove(0, p+6);
    p = line.indexOf(';'); str = line.left(p);
    k = str.count(',')+1;
    for (i=0; i<k; i++)
    {
        str2 = str.section(',',i,i).trimmed();
        QPair<QString, bool> port(str2, 1);
        ports.append(port);
        Wire wire(str2);
        wire.addLoad(this, str2);
        wires.append(wire);
    }

    p = line.indexOf("wire "); line.remove(0, p+4);
    p = line.indexOf(';'); str = line.left(p); line.remove(0, p+1);
    k = str.count(',')+1;
    for (i=0; i<k; i++)
    {
        str2 = str.section(',',i,i).trimmed();
        Wire wire(str2);
        wires.append(wire);
    }

    k = line.count(';');
    for (i=0; i<k; i++)
    {
        str = line.section(';',i,i).trimmed();
        p = str.indexOf(' '); str2 = str.left(p);
        str.remove(0, p); str = str.trimmed();
        p = str.indexOf(' '); str3 = str.left(p);
        str.remove(0, p); str = str.trimmed();
        LogicElement le(str3);
        le.initBasicLE(str2);
        logicElements.append(le);

        k2 = str.count(',')+1;
        for (i2=0; i2<k2; i2++)
        {
            str2 = str.section(',',i2,i2).trimmed();
            p = str2.indexOf('.'); str2.remove(0, p+1);
            p = str2.indexOf('('); str3 = str2.left(p); str2.remove(0, p+1);
            p = str2.indexOf(')'); str4 = str2.left(p); str2.remove(0, p+1);
            for (i3=0; i3<wires.size(); i3++)
                if (wires[i3].nameIs(str4))
                {
                    for (i4=0; i4<le.ports.size(); i4++)
                        if (le.ports[i4].first == str3) break; ///!
                    if (le.ports[i4].second == 0)
                        wires[i3].addLoad(&logicElements.back(), str3);
                    else
                        wires[i3].addDriver(&logicElements.back(), str3);
                    break;
                }

        }
    }

}

void LogicElement::initBasicLE(QString type)
{
    basic = true;

     if (type == "al_ao21")
    {
        QPair<QString, bool> port1("a",0);
        ports.append(port1);
        QPair<QString, bool> port2("b",0);
        ports.append(port2);
        QPair<QString, bool> port3("c",0);
        ports.append(port3);
        QPair<QString, bool> port4("y",1);
        ports.append(port4);
    }
else if (type == "al_aoi21ttf")
    {
         QPair<QString, bool> port1("a",0);
         ports.append(port1);
         QPair<QString, bool> port2("b",0);
         ports.append(port2);
         QPair<QString, bool> port3("c",0);
         ports.append(port3);
         QPair<QString, bool> port4("y",1);
         ports.append(port4);
    }
else if (type == "al_oa21")
    {
         QPair<QString, bool> port1("a",0);
         ports.append(port1);
         QPair<QString, bool> port2("b",0);
         ports.append(port2);
         QPair<QString, bool> port3("c",0);
         ports.append(port3);
         QPair<QString, bool> port4("y",1);
         ports.append(port4);
    }
else if (type == "al_nand2")
    {
         QPair<QString, bool> port1("a",0);
         ports.append(port1);
         QPair<QString, bool> port2("b",0);
         ports.append(port2);
         QPair<QString, bool> port4("y",1);
         ports.append(port4);
    }
}
