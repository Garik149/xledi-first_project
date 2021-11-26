#include "wire.h"
#include "logicelement.h"

QList<LogicElement> library;

#define NofBLE 4


LogicElement::LEPort::LEPort(QString _name, bool _outPort) {name=_name; outPort=_outPort;}
LogicElement::LEPort::~LEPort() {};

LogicElement::LogicElement() {basic = false;}
LogicElement::LogicElement(QString _name) { name = _name; basic = false;}
LogicElement::~LogicElement() {}

Wire& LogicElement::LEwire(QString _name)
{
    int i;

    for (i=0; i<wires.size(); i++)
        if (wires[i].nameIs(_name)) break;
    return wires[i];
}

bool LogicElement::havePort(QString _name, bool _outPort)
{
    int i;

    for (i=0; i<ports.size(); i++)
        if ((ports[i].name == _name) && (ports[i].outPort == _outPort)) return true;
    return false;
}

bool LogicElement::nameIs(QString _name)
{
    if (name == _name) return true;
    return false;
}

void LogicElement::addBasicElements(QList<LogicElement> &library)
{
    int i;
    for(i=1; i<=NofBLE; i++)
    {
        LogicElement le;
        le.basic = true;
        switch(i)
        {
        case 1:
            le.name = "al_ao21";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("c",0));
            le.ports.append(LEPort("y",1));
            break;
        case 2:
            le.name = "al_aoi21ttf";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("c",0));
            le.ports.append(LEPort("y",1));
            break;
        case 3:
            le.name = "al_oa21";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("c",0));
            le.ports.append(LEPort("y",1));
            break;
        case 4:
            le.name = "al_nand2";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("y",1));
            break;
        case 5:
            le.name = "";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("c",0));
            le.ports.append(LEPort("y",1));
            break;
        case 6:
            le.name = "al_ao21";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("c",0));
            le.ports.append(LEPort("y",1));
            break;
        case 7:
            le.name = "al_ao21";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("c",0));
            le.ports.append(LEPort("y",1));
            break;
        case 8:
            le.name = "al_ao21";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("c",0));
            le.ports.append(LEPort("y",1));
            break;
        case 9:
            le.name = "al_ao21";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("c",0));
            le.ports.append(LEPort("y",1));
            break;
        case 10:
            le.name = "al_ao21";
            le.ports.append(LEPort("a",0));
            le.ports.append(LEPort("b",0));
            le.ports.append(LEPort("c",0));
            le.ports.append(LEPort("y",1));
            break;
        }
        library.append(le);
    }
}

QString cutLine(int p, QString& line, QChar c)
{
    int l=p, r=p;

    while (r <= line.size()-1)
    {
        if (line[r] == c)
        {
            QString s = line.mid(l,r-l+1);
            line.remove(l,r-l+1);
            return s;
        }
        r++;
    }

    return NULL;
}

void deleteComments(QString& line)
{
    int l=0, r;

    while ((l = line.indexOf(QRegExp("//"))) != -1)
    {
        r=l;
        while (r <= line.size()-1)
        {
            if(line[r] == '\n') break;
            r++;
        }
        line.remove(l, r-l);
    }
    while ((l = line.indexOf(QRegExp("/\\*"))) != -1)
    {
        r = line.indexOf(QRegExp("\\*/"));
        line.remove(l, r-l+2);
    }
}

//bool LogicElement::initLEFromFile(QString& path)
//{
//    QFile file(path);
//    if (!file.open(QIODevice::ReadOnly)) return 1;
//    QString line = file.readAll();
//
//    addBasicElements(library);
//
//
//
//    return 0;
//}

///Нужно сохранять порядок портов
///Не рассчитан на включение логических элементов из других файлов
bool LogicElement::initMainLEFromFile(QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return 1;
    QString line = file.readAll();

    int k, i, p;
    QString str1, str2, str3;
    QList<QString> includes;
    addBasicElements(library);

    name = "main";

    deleteComments(line);

    while ((p = line.indexOf(QRegExp("\\b(`include)\\b"))) != -1)
    {
        str1 = cutLine(p, line, '\n');
        str1.remove(0,8); str1 = str1.trimmed();
        str1.remove(0,1);
        str1.chop(1);
        includes.append(str1);

        //str1 = cutLine(p, line);
        //str1.remove(p,6); str1 = str1.trimmed();
        //p = str1.indexOf(' ');
        //str1.left(p);
    }

    p = line.indexOf(QRegExp("\\b(module)\\b"));
    if (p == -1) return 1;
    cutLine(p, line, ';');

    p = line.indexOf(QRegExp("\\b(endmodule)\\b"));
    if (p == -1) return 1;
    line.remove(p,9);

    while ((p = line.indexOf(QRegExp("\\b(input)\\b"))) != -1)
    {
        str1 = cutLine(p, line, ';');
        str1.remove(0,5); str1.chop(1);
        k = str1.count(',')+1;
        for (i=0; i<k; i++)
        {
            str2 = str1.section(',',i,i).trimmed();
            if (str2 == "") continue;

            ports.append(LEPort(str2,0));
            Wire wire(str2);
            wire.addDriver(this, str2);
            wires.append(wire);
        }
    }

    while ((p = line.indexOf(QRegExp("\\b(output)\\b"))) != -1)
    {
        str1 = cutLine(p, line, ';');
        str1.remove(0,6); str1.chop(1);
        k = str1.count(',')+1;
        for (i=0; i<k; i++)
        {
            str2 = str1.section(',',i,i).trimmed();
            if (str2 == "") continue;

            ports.append(LEPort(str2,1));
            Wire wire(str2);
            wire.addLoad(this, str2);
            wires.append(wire);
        }
    }

    while ((p = line.indexOf(QRegExp("\\b(wire)\\b"))) != -1)
    {
        str1 = cutLine(p, line, ';');
        str1.remove(0,4); str1.chop(1);
        k = str1.count(',')+1;
        for (i=0; i<k; i++)
        {
            str2 = str1.section(',',i,i).trimmed();
            if (str2 == "") continue;

            Wire wire(str2);
            wires.append(wire);
        }
    }

    while ((p = line.indexOf(QRegExp("\\b(assign)\\b"))) != -1)
    {
        str1 = cutLine(p, line, ';');
        str1.remove(0,6); str1.chop(1);
        str2 = str1.section('=',0,0).trimmed();
        LEwire(str1).assign(LEwire(str2));
        str3 = str1.section('=',1,1).trimmed();
        LEwire(str2).assign(LEwire(str1));
    }

    while ((p = line.indexOf(QRegExp("\\b"))) != -1)
    {
        str1 = cutLine(p, line, ';');

        p = str1.indexOf(' ');
        str2 = str1.mid(0,p); str1.remove(0,p); str1 = str1.trimmed();

        p = str1.indexOf(' ');
        str3 = str1.mid(0,p); str1.remove(0,p); str1 = str1.trimmed();

        LogicElement le;
        for (i=0; i<library.size(); i++)
            if (library[i].nameIs(str2)) break;
        if (i == library.size()) return 1;
        le = library[i];
        le.name = str3;
        logicElements.append(le);

        str1.remove(0,1);
        str1.chop(2);
        k = str1.count(',')+1;
        for (i=0; i<k; i++)
        {
            str2 = str1.section(',',i,i).trimmed();
            if (str2 == "")
                continue;
            if (str2[0] == '.')
            {
                str2.remove(0,1);
                str2.chop(1);
                p = str2.indexOf('(');
                str3 = str2.left(p);
                str2.remove(0,p+1);
                if(le.havePort(str3,0))
                LEwire(str2).addLoad(&logicElements.back(), str3);
                else if(le.havePort(str3,1))
                LEwire(str2).addDriver(&logicElements.back(), str3);
                else return 1;
            }
            else
            {
                if(le.ports[i].outPort)
                    LEwire(str2).addLoad(&le, str3);
                else
                    LEwire(str2).addDriver(&le, str3);

            }
        }

    }

    return 0;
}
