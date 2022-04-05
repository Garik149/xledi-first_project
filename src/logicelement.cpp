#include <QFileDialog>
#include <QFile>
#include "defines.h"
#include "port.h"
#include "wire.h"
#include "logicelement.h"

QList<LogicElement> LogicElement::library;

LogicElement::LogicElement(){};
//!!
LogicElement::LogicElement(QString _type, QString _name){
	for (int i=0; i<library.size(); i++)
		if (_type == library[i].name){
			*this=library[i];
			name = _name;
			resetLists();
			return;
		}
}

LogicElement::~LogicElement() {name.clear(); ports.clear(); wires.clear(); logicElements.clear(); basic = false;}

void LogicElement::clear(){
    name.clear();
    ports.clear();
    wires.clear();
    logicElements.clear();
    basic = false;
}

Wire* LogicElement::leWire(QString _name){
    int i;

    for (i=0; i<wires.size(); i++)
		if (wires[i].name == _name) return &wires[i];
	return NULL;
}
bool LogicElement::haveWire(QString _name){
	if (leWire(_name)==NULL) return false;
		else return true;
}

Port* LogicElement::lePort(QString _name){
    int i;

    for (i=0; i<ports.size(); i++)
		if (ports[i].name == _name) return &ports[i];
	return NULL;
}
bool LogicElement::havePort(QString _name){
	if (lePort(_name)==NULL) return false;
		else return true;
}

void LogicElement::resetLists(){
	inPorts.clear(); outPorts.clear();
	for (int i=0; i<ports.size(); i++)
		if (ports[i].isOutput) outPorts.append(&ports[i]);
			else inPorts.append(&ports[i]);
}

bool LogicElement::nameIs(QString _name){
    if (name == _name) return true;
    return false;
}

void LogicElement::addBasicElements(){
    int i;
    for(i=1; i<=NofBLE; i++){
        LogicElement le;
        le.basic = true;
        switch(i){
        case 1:
            le.name = "al_ao21";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 2:
            le.name = "al_aoi21ttf";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 3:
            le.name = "al_oa21";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 4:
            le.name = "al_nand2";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("y",1));
            break;
        case 5:
            le.name = "al_dffl";
			le.ports.append(Port("d",0));
			le.ports.append(Port("clk",0));
			le.ports.append(Port("q",1));
            break;
        case 6:
            le.name = "al_dffi";
			le.ports.append(Port("d",0));
			le.ports.append(Port("clk",0));
			le.ports.append(Port("q",1));
            break;
        case 7:
            le.name = "al_oa21ttf";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 8:
            le.name = "al_and2";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("y",1));
            break;
        case 9:
            le.name = "al_nand3fft";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
		case 10:
            le.name = "al_nand2ft";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("y",1));
            break;
        case 11:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 12:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 13:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 14:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("y",1));
            break;
        case 15:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 16:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 17:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 18:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 19:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        case 20:
            le.name = "";
			le.ports.append(Port("a",0));
			le.ports.append(Port("b",0));
			le.ports.append(Port("c",0));
			le.ports.append(Port("y",1));
            break;
        }
        library.append(le);
    }
}

QString cutLine(int p, QString& line, QChar c){
    int pi = line.indexOf(c,p);
    if (pi == -1) return NULL;
    QString str = line.mid(p,pi-p+1);
    line.remove(p,pi-p+1);
    return str;
}
void deleteComments(QString& line){
    int l, r;

    while (line.contains("//")){
        l = line.indexOf("//");
        r = line.indexOf('\n',l);
        if (r == -1) r=line.size();
        line.remove(l, r-l);
    }
    while (line.contains("/*")){
        l = line.indexOf("/*");
        r = line.indexOf("*/");
        if (r == -1) r=line.size()-1;
        line.remove(l, r-l+2);
    }
}
void prepareCode(QString& line){
    deleteComments(line);

    int l=0, r;
    while((r = line.indexOf(" ", l)) != -1){
        if (r == line.indexOf(QRegExp("\\b( )\\b"), r))
            l=r+1;
        else
            line.remove(r,1);
    }
}
bool LogicElement::initLEFromFile(QString& path){
    clear();

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) return RESULT_ERROR;
    QString line = file.readAll();

    int k, i, p;
    QString str1, str2, str3;

    prepareCode(line);

    while (line.contains('`')){
        p = line.indexOf('`');
        if (line.mid(p,8) == "`include"){
            str1 = cutLine(p, line, '\n');
            str1.remove(0,9);
            str1.chop(2);

            path = path.left(path.lastIndexOf('/'));
            path += '/' + str1;
            LogicElement le;
            if (le.initLEFromFile(path) == RESULT_ERROR) return RESULT_ERROR;
            library.append(le);
        }
        else return RESULT_ERROR;
    }

	if (line.contains(QRegExp("\\b(module)\\b"))){
        p = line.indexOf(QRegExp("\\b(module )\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,7);
        p = str1.indexOf('(');
        name = str1.mid(0,p);
        str1.remove(0,p+1); str1.chop(2);

		bool isOutput=false;
        k = str1.count(',')+1;
		for (i=0; i<k; i++){
            str2 = str1.section(',',i,i);
            if (str2 == "") return RESULT_ERROR;

			if (str2.contains(' ')){
				if (str2.mid(0,6) == "input "){
					str2.remove(0,6);
					isOutput=false;
				}
				else if (str2.mid(0,7) == "output "){
					str2.remove(0,7);
					isOutput=true;
				}
				else return RESULT_ERROR;
			}

			Port port(str2,isOutput);
			Wire wire(str2);

			ports.append(port);
			port.insideWire=&wire;
			wires.append(wire);
			wire.loads.append(lePort(str2));
        }
    }
    else return RESULT_ERROR;

    while (line.contains(QRegExp("\\b(input)\\b"))){
        p = line.indexOf(QRegExp("\\b(input)\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,6); str1.chop(1);
        k = str1.count(',')+1;
        for (i=0; i<k; i++){
            str2 = str1.section(',',i,i);
			if (str2 == "") return RESULT_ERROR;

			lePort(str2)->isOutput=false;
			leWire(str2)->loads.append(lePort(str2));
        }
    }

    while (line.contains(QRegExp("\\b(output)\\b"))){
        p = line.indexOf(QRegExp("\\b(output)\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,7); str1.chop(1);
        k = str1.count(',')+1;
        for (i=0; i<k; i++){
            str2 = str1.section(',',i,i);
			if (str2 == "") return RESULT_ERROR;

			lePort(str2)->isOutput=true;
			leWire(str2)->drivers.append(lePort(str2));
        }
    }

	resetLists();

    while (line.contains(QRegExp("\\b(wire)\\b"))){
        p = line.indexOf(QRegExp("\\b(wire)\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,5); str1.chop(1);
        k = str1.count(',')+1;
        for (i=0; i<k; i++){
            str2 = str1.section(',',i,i).trimmed();
            if (str2 == "") continue;

            Wire wire(str2);
            wires.append(wire);
        }
    }

    while (line.contains(QRegExp("\\b(assign)\\b"))){
        p = line.indexOf(QRegExp("\\b(assign)\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,7); str1.chop(1);
        str2 = str1.section('=',0,0);
        str3 = str1.section('=',1,1);
		leWire(str3)->assigns.append(leWire(str2));
		leWire(str2)->assigns.append(leWire(str3));
    }

    while (line.contains(QRegExp("\\b"))){
        p = line.indexOf(QRegExp("\\b"));

        if ((str1 = cutLine(p, line, ';')) == "") break;

        p = str1.indexOf(' ');
        str2 = str1.mid(0,p); str1.remove(0,p);

        p = str1.indexOf('(');
        str3 = str1.mid(0,p); str1.remove(0,p);

        for (i=0; i<library.size(); i++)
            if (library[i].nameIs(str2)) break;
        if (i == library.size()) return RESULT_ERROR;
        logicElements.append(library[i]);
        LogicElement& le = logicElements.back();
        le.name = str3;

        str1.remove(0,1);
        str1.chop(2);
        k = str1.count(',')+1;
        for (i=0; i<k; i++){
            str2 = str1.section(',',i,i);
            if (str2 == "")
                continue;
            if (str2[0] == '.'){
                str2.remove(0,1);
                str2.chop(1);
                p = str2.indexOf('(');
                str3 = str2.left(p);
                str2.remove(0,p+1);

				if (!le.havePort(str3)) return RESULT_ERROR;
				if (le.lePort(str3)->isOutput)
					leWire(str2)->drivers.append(le.lePort(str3));
                else
					leWire(str2)->loads.append(le.lePort(str3));
            }
            else{
                if (le.ports[i].isOutput)
					leWire(str2)->drivers.append(le.lePort(str3));
                else
					leWire(str2)->loads.append(le.lePort(str3));
            }
        }
    }

    return RESULT_SUCCESS;
}

bool LogicElement::initMainLEFromFile(QString& path){
    this->initLEFromFile(path);
	name = "main";


    return 0;
}
