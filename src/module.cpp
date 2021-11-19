#include "wire.h"
#include "module.h"
#include "logicelement.h"

#include "QString"
#include "QRegularExpression"

QList<LogicElement> logicElementList;
QList<Wire> wireList;

Module::Module()
{
}

Module::~Module()
{
}

//Empty
void Module::addToList()
{
    //moduleList.back();
}

//!Не обходит в файле "пустые ;" и комментарии
void Module::initFromFile(QString line, QList<Module>* pt_moduleList)
{
    QString str, str2;
    int k, i, j, p;
    p = line.indexOf("module "); line.remove(0, p+6);
    p = line.indexOf('('); str = line.left(p); name = str.trimmed();

    p = line.indexOf("input "); line.remove(0, p+5);
    p = line.indexOf(';'); str = line.left(p);
    k = str.count(',')+1;
    for (i=0; i<k; i++)
    {
        str2 = str.section(',',i,i).trimmed();
        QPair<QString, bool> pair(str2, 0);
        ports.append(pair);
        Wire wire(str2);
        wireList.append(wire);
        wires.append(&wireList.back());
    }

    p = line.indexOf("output "); line.remove(0, p+6);
    p = line.indexOf(';'); str = line.left(p);
    k = str.count(',')+1;
    for (i=0; i<k; i++)
    {
        str2 = str.section(',',i,i).trimmed();
        QPair<QString, bool> pair(str2, 1);
        ports.append(pair);
        Wire wire(str2);
        wireList.append(wire);
        wires.append(&wireList.back());
    }

    p = line.indexOf("wire "); line.remove(0, p+4);
    p = line.indexOf(';'); str = line.left(p); line.remove(0, p+1);
    k = str.count(',')+1;
    for (i=0; i<k; i++)
    {
        str2 = str.section(',',i,i).trimmed();
        Wire wire(str2);
        wireList.append(wire);
        wires.append(&wireList.back());
    }

    p = line.indexOf("endmodule"); str = line.left(p);
    k = str.count(';');
    for (i=0; i<k; i++)
    {
        str = str.trimmed();
        p = str.indexOf(' ');
        str2 = str.left(p);
        j=-1;
        do
        {
            j++;
            if (j == pt_moduleList->size()) break; ///Обработать ошибку
        }
        while (pt_moduleList->at(j).name != str2);
        str.remove(0, p); str = str.trimmed();
        p = str.indexOf(' ');
        LogicElement le(str.left(p), &pt_moduleList->at(j));
        logicElementList.append(le);
        logicElements.append(&logicElementList.back());
    }


}
