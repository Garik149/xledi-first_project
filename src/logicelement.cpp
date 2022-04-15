#include <QFileDialog>
#include <QFile>
#include "defines.h"
#include "port.h"
#include "wire.h"
#include "logicelement.h"

QList<LogicElement> LogicElement::library;

LogicElement::LogicElement(){isBasic=false;}

LogicElement::LogicElement(LogicElement* _le, QString _name){
	int i;

	name=_name;
	type=_le->type;
	isBasic=_le->isBasic;

	for (i=0; i<_le->ports.size(); i++){
		ports.append(new Port(this,_le->ports[i]->name,_le->ports[i]->isOutput));
		if (ports[i]->isOutput) outPorts.append(ports[i]);
			else inPorts.append(ports[i]);
	}

	if (isBasic) return;

	for (i=0; i<_le->wires.size(); i++)
		wires.append(new Wire(_le->wires[i]->name));

	for (i=0; i<_le->logicElements.size(); i++)
		logicElements.append(new LogicElement(_le->logicElements[i]->type,_le->logicElements[i]->name));



}

//!!
LogicElement::LogicElement(QString _type, QString _name){
	for (int i=0; i<library.size(); i++)
		if (_type == library[i].type){
			*this=library[i];
			name = _name;
			return;
		}
}

LogicElement::~LogicElement(){
	int i;
	for (i=0;i<ports.size();i++) delete(ports[i]);
	for (i=0;i<wires.size();i++) delete(wires[i]);
	for (i=0;i<logicElements.size();i++) delete(logicElements[i]);
}

void LogicElement::clear(){
    name.clear();
    ports.clear();
    wires.clear();
	logicElements.clear();
}

Wire* LogicElement::leWire(QString _name){
    int i;

    for (i=0; i<wires.size(); i++)
		if (wires[i]->name == _name) return wires[i];
	return NULL;
}
bool LogicElement::haveWire(QString _name){
	if (leWire(_name)==NULL) return false;
		else return true;
}

Port* LogicElement::lePort(QString _name){
    int i;

    for (i=0; i<ports.size(); i++)
		if (ports[i]->name == _name) return ports[i];
	return NULL;
}
bool LogicElement::havePort(QString _name){
	if (lePort(_name)==NULL) return false;
		else return true;
}

bool LogicElement::nameIs(QString _name){
    if (name == _name) return true;
    return false;
}

void LogicElement::addBasicElements(){
    int i;
	LogicElement* le;
    for(i=1; i<=NofBLE; i++){
		le = new LogicElement();
		le->isBasic = true;
        switch(i){
        case 1:
			le->type = "al_ao21";
			le->ports.append(new Port(le,"a",false));
			le->ports.append(new Port(le,"b",false));
			le->ports.append(new Port(le,"c",false));
			le->ports.append(new Port(le,"y",true));
			break;
		case 2:
			le->type = "al_aoi21ttf";
			le->ports.append(new Port(le,"a",false));
			le->ports.append(new Port(le,"b",false));
			le->ports.append(new Port(le,"c",false));
			le->ports.append(new Port(le,"y",true));
            break;
		case 3:
			le->type = "al_oa21";
			le->ports.append(new Port(le,"a",false));
			le->ports.append(new Port(le,"b",false));
			le->ports.append(new Port(le,"c",false));
			le->ports.append(new Port(le,"y",true));
            break;
        case 4:
			le->type = "al_nand2";
			le->ports.append(new Port(le,"a",false));
			le->ports.append(new Port(le,"b",false));
			le->ports.append(new Port(le,"y",true));
            break;
        case 5:
			le->type = "al_dffl";
			le->ports.append(new Port(le,"d",false));
			le->ports.append(new Port(le,"clk",false));
			le->ports.append(new Port(le,"q",true));
            break;
        case 6:
			le->type = "al_dffi";
			le->ports.append(new Port(le,"d",false));
			le->ports.append(new Port(le,"clk",false));
			le->ports.append(new Port(le,"q",true));
            break;
        case 7:
			le->type = "al_oa21ttf";
			le->ports.append(new Port(le,"a",false));
			le->ports.append(new Port(le,"b",false));
			le->ports.append(new Port(le,"c",false));
			le->ports.append(new Port(le,"y",true));
            break;
        case 8:
			le->type = "al_and2";
			le->ports.append(new Port(le,"a",false));
			le->ports.append(new Port(le,"b",false));
			le->ports.append(new Port(le,"y",true));
            break;
        case 9:
			le->type = "al_nand3fft";
			le->ports.append(new Port(le,"a",false));
			le->ports.append(new Port(le,"b",false));
			le->ports.append(new Port(le,"c",false));
			le->ports.append(new Port(le,"y",true));
            break;
		case 10:
			le->type = "al_nand2ft";
			le->ports.append(new Port(le,"a",false));
			le->ports.append(new Port(le,"b",false));
			le->ports.append(new Port(le,"y",true));
			break;
        }
		library.append(*le);
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
		type = str1.mid(0,p);
        str1.remove(0,p+1); str1.chop(2);

		Port* port;
		Wire* wire;

        k = str1.count(',')+1;
		for (i=0; i<k; i++){
            str2 = str1.section(',',i,i);
            if (str2 == "") return RESULT_ERROR;

			port = new Port(this, str2);
			wire = new Wire(str2);
			ports.append(port);
			wires.append(wire);
			port->insideWire=wire;
			port->le=this;

			if (str2.contains(' ')){
				if (str2.mid(0,6) == "input "){
					str2.remove(0,6);
					port->isOutput=false;
					wire->drivers.append(port);
				}
				else if (str2.mid(0,7) == "output "){
					str2.remove(0,7);
					port->isOutput=true;
					wire->loads.append(port);
				}
				else return RESULT_ERROR;
			}
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
			leWire(str2)->drivers.append(lePort(str2));
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
			leWire(str2)->loads.append(lePort(str2));
        }
    }

    while (line.contains(QRegExp("\\b(wire)\\b"))){
        p = line.indexOf(QRegExp("\\b(wire)\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,5); str1.chop(1);
        k = str1.count(',')+1;
        for (i=0; i<k; i++){
            str2 = str1.section(',',i,i).trimmed();
            if (str2 == "") continue;

			wires.append(new Wire(str2));
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

		LogicElement* le;
		for (int i=0; i<library.size(); i++)
			if (str2 == library[i].type){
				le = new LogicElement(&library[i],str3);
				break;
			}
		logicElements.append(le);

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

				if (!le->havePort(str3)) return RESULT_ERROR;
				if (le->lePort(str3)->isOutput)
					leWire(str2)->drivers.append(le->lePort(str3));
                else
					leWire(str2)->loads.append(le->lePort(str3));
				le->lePort(str3)->outsideWire=leWire(str2);
            }
            else{
				if (le->ports[i]->isOutput)
					leWire(str2)->drivers.append(le->lePort(str3));
                else
					leWire(str2)->loads.append(le->lePort(str3));
				le->ports[i]->outsideWire=leWire(str2);
            }
        }
    }

    return RESULT_SUCCESS;
}

bool LogicElement::initMainLEFromFile(QString& path){
    this->initLEFromFile(path);
	name = "main";

	delete(this);

    return 0;
}
