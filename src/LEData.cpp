#include <QFileDialog>
#include <QFile>
#include "defines.h"
#include "PortData.h"
#include "WireData.h"
#include "LEData.h"

QList<LEData> LEData::library;

LEData::LEData(){
	isBasic=false;
	shape=NULL;
}

LEData::LEData(LEData* _le){
    copy(_le);
	shape=NULL;
}

LEData::LEData(QString _type, QString _name){
	copyFromLibrary(_type, _name);
	shape=NULL;
}

LEData::~LEData(){
	int i;
	for (i=0;i<ports.size();i++) delete(ports[i]);
	for (i=0;i<wires.size();i++) delete(wires[i]);
    for (i=0;i<les.size();i++) delete(les[i]);
}

void LEData::clear(){
    name.clear();
    ports.clear();
    wires.clear();
    les.clear();
}

WireData* LEData::wireNamed(QString _name){
	for (int i=0; i<wires.size(); i++)
		if (wires[i]->name == _name) return wires[i];
	return NULL;
}
bool LEData::haveWire(QString _name){
    if (wireNamed(_name)==NULL) return false;
		else return true;
}

PortData* LEData::portNamed(QString _name){
	for (int i=0; i<ports.size(); i++)
		if (ports[i]->name == _name) return ports[i];
	return NULL;
}
bool LEData::havePort(QString _name){
    if (portNamed(_name)==NULL) return false;
		else return true;
}

int LEData::leIndex(PortData* _port){
	for (int i=0; i<ports.size();i++)
		if (ports[i] == _port) return i;
	return -1;
}
LEData* LEData::leNamed(QString _name){
    for (int i=0; i<les.size(); i++)
        if (les[i]->name == _name) return les[i];
    return NULL;
}
bool LEData::haveLE(QString _name){
    if (leNamed(_name)==NULL) return false;
        else return true;
}

bool LEData::nameIs(QString _name){
    if (name == _name) return true;
    return false;
}

int LEData::compareNames(const void* le1, const void* le2){
	LEData* _le1 = *(LEData**)le1;
	LEData* _le2 = *(LEData**)le2;
	return QString::compare(_le1->name, _le2->name);
}
void LEData::nameSort(QList<LEData*>& leList){ //qsort q-контейнеры не принимает
	QVector<LEData*> _leList = leList.toVector();
	qsort(&_leList,_leList.size(),sizeof(LEData*),compareNames);
}

bool LEData::copy(LEData* _le){
	int i,j;
    WireData* wire;
    PortData *port, *_port;
    LEData *iLE, *_iLE;

	clear();
	name=_le->name;
	type=_le->type;
	isBasic=_le->isBasic;

	for (i=0; i<_le->ports.size(); i++){
		_port=_le->ports[i];
        port=new PortData(this,_port->name,_port->isOutput);
		ports.append(port);
		if (port->isOutput) outPorts.append(port);
			else inPorts.append(port);
	}

	if (isBasic) return RESULT_SUCCESS;

	for (i=0; i<_le->wires.size(); i++)
        wires.append(new WireData(_le->wires[i]->name));

    for (i=0; i<_le->les.size(); i++){
        _iLE=_le->les[i];
        iLE = new LEData();
		iLE->copyFromLibrary(_iLE->type,_iLE->name);
        les.append(iLE);
		for (j=0; j<_iLE->ports.size(); j++){
			_port=_iLE->ports[j];
			port=portNamed(_port->name);
			wire=wireNamed(_port->outsideWire->name);
			port->outsideWire=wire;
			if (port->isOutput) wire->drivers.append(port);
				else wire->loads.append(port);
		}
	}

	for (i=0; i<ports.size(); i++)
		ports[i]->insideWire=wireNamed(_le->ports[i]->insideWire->name);

	return RESULT_SUCCESS;
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

    int l, r;

    l=0;
    while((r = line.indexOf('\n', l)) != -1){
        line[r]=' ';
        l=r+1;
    }
    l=0;
    while((r = line.indexOf('\t', l)) != -1){
        line[r]=' ';
        l=r+1;
    }

    l=0;
    while((r = line.indexOf(" ", l)) != -1)
        if (r == line.indexOf(QRegExp("\\b( )\\b"), r))
            l=r+1;
        else
            line.remove(r,1);

}

bool LEData::readLibrary(const QString& _path){

    /*for(int i=1; i<=19; i++){
        LEData le;
        le.isBasic = true;
        switch(i){
        case 1:
            le.type = "not";
            le.ports.append(new PortData(NULL,"a",false));
            le.ports.append(new PortData(NULL,"y",true));
            break;
        case 2:
            le.type = "and";
            le.ports.append(new PortData(NULL,"a",false));
            le.ports.append(new PortData(NULL,"b",false));
            le.ports.append(new PortData(NULL,"y",true));
            break;
        case 3:
            le.type = "or";
            le.ports.append(new PortData(NULL,"a",false));
            le.ports.append(new PortData(NULL,"b",false));
            le.ports.append(new PortData(NULL,"y",true));
            break;
        case 4:
            le.type = "xor";
            le.ports.append(new PortData(NULL,"a",false));
            le.ports.append(new PortData(NULL,"b",false));
            le.ports.append(new PortData(NULL,"y",true));
            break;
        case 5:
            le.type = "buf";
            le.ports.append(new PortData(NULL,"a",false));
            le.ports.append(new PortData(NULL,"y",true));
            break;
        }
        library.append(le);
    }*/

    QFile file(_path);
    if (!file.open(QIODevice::ReadOnly)) return RESULT_ERROR;
	QString line = file.readAll();

	int k, i, p;
    QString str1, str2;
    LEData* le;

    prepareCode(line);

	while (line.contains(QRegExp("\\b(module)\\b"))){
        le = new LEData();
		p = line.indexOf(QRegExp("\\b(module )\\b"));
		str1 = cutLine(p, line, ';');
		str1.remove(0,7);
		p = str1.indexOf('(');
        le->type = str1.mid(0,p);
		str1.remove(0,p+1); str1.chop(2);

        PortData* port;

		k = str1.count(',')+1;
		for (i=0; i<k; i++){
			str2 = str1.section(',',i,i);
			if (str2 == "") return RESULT_ERROR;

            port = new PortData(NULL, str2);
            le->ports.append(port);

			if (str2.contains(' ')){
				if (str2.mid(0,6) == "input "){
					str2.remove(0,6);
                    port->isOutput=false;
				}
				else if (str2.mid(0,7) == "output "){
					str2.remove(0,7);
                    port->isOutput=true;
				}
				else return RESULT_ERROR;
			}
		}

        if (line.contains(QRegExp("\\b(input)\\b"))){
            p = line.indexOf(QRegExp("\\b(input)\\b"));
            str1 = cutLine(p, line, ';');
            str1.remove(0,6); str1.chop(1);
            k = str1.count(',')+1;
            for (i=0; i<k; i++){
                str2 = str1.section(',',i,i);
                if (str2 == "") return RESULT_ERROR;
                le->portNamed(str2)->isOutput=false;
            }
        }
        else return RESULT_ERROR;

        if (line.contains(QRegExp("\\b(output)\\b"))){
            p = line.indexOf(QRegExp("\\b(output)\\b"));
            str1 = cutLine(p, line, ';');
            str1.remove(0,7); str1.chop(1);
            k = str1.count(',')+1;
            for (i=0; i<k; i++){
                str2 = str1.section(',',i,i);
                if (str2 == "") return RESULT_ERROR;
                le->portNamed(str2)->isOutput=true;
            }
        }
        else return RESULT_ERROR;

        le->isBasic=true;
        library.append(*le);
	}
    return RESULT_SUCCESS;
}

bool LEData::initLEFromFile(const QString& _path){

	QFile file(_path);
	if (!file.open(QIODevice::ReadOnly)) return RESULT_ERROR;
	QString line = file.readAll();

	int k, i, p;
	QString str1, str2, str3;

	prepareCode(line);

	if (line.contains(QRegExp("\\b(module)\\b"))){
        PortData* port;

		p = line.indexOf(QRegExp("\\b(module )\\b"));
		str1 = cutLine(p, line, ';');
		str1.remove(0,7);
		p = str1.indexOf('(');
		type = str1.mid(0,p);
		str1.remove(0,p+1); str1.chop(2);

		k = str1.count(',')+1;
        bool outputFlag=false;
        for (i=0; i<k; i++){
            str2 = str1.section(',',i,i);

            if (str2.contains(' ')){
                if (str2.mid(0,6) == "input "){
                    str2.remove(0,6);
                    outputFlag=false;
                }
                else if (str2.mid(0,7) == "output "){
                    str2.remove(0,7);
                    outputFlag=true;
                }
                else return RESULT_ERROR;
            }

			if (str2 == "") return RESULT_ERROR;

            port = new PortData(this, str2);
            ports.append(port);
            port->le=this;
            port->isOutput=outputFlag;
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
            portNamed(str2)->isOutput=false;
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
            portNamed(str2)->isOutput=true;
		}
	}

    for (i=0; i<ports.size(); i++){
        WireData* wire;
        wire = new WireData(ports[i]->name);
        wires.append(wire);
        ports[i]->insideWire=wire;
        if (!ports[i]->isOutput){
            inPorts.append(ports[i]);
            wire->drivers.append(ports[i]);
        }
        else{
            outPorts.append(ports[i]);
            wire->loads.append(ports[i]);
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

            wires.append(new WireData(str2));
		}
	}

	while (line.contains(QRegExp("\\b(assign)\\b"))){
		p = line.indexOf(QRegExp("\\b(assign)\\b"));
		str1 = cutLine(p, line, ';');
		str1.remove(0,7); str1.chop(1);
		str2 = str1.section('=',0,0);
        str3 = str1.section('=',1,1);
	}

	while (line.contains(QRegExp("\\b"))){
        LEData* le;

		p = line.indexOf(QRegExp("\\b"));

		if ((str1 = cutLine(p, line, ';')) == "") break;

		p = str1.indexOf(' ');
		str2 = str1.mid(0,p); str1.remove(0,p);

		p = str1.indexOf('(');
		str3 = str1.mid(0,p); str1.remove(0,p);

        le = new LEData(str2,str3);
        les.append(le);

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
			 if (le->portNamed(str3)->isOutput)
				wireNamed(str2)->drivers.append(le->portNamed(str3));
				else
				wireNamed(str2)->loads.append(le->portNamed(str3));
				le->portNamed(str3)->outsideWire=wireNamed(str2);
			}
			else{
				if (le->ports[i]->isOutput)
					wireNamed(str2)->drivers.append(le->portNamed(str3));
				else
					wireNamed(str2)->loads.append(le->portNamed(str3));
				le->ports[i]->outsideWire=wireNamed(str2);
			}
		}
	}

	return RESULT_SUCCESS;
}

bool LEData::copyFromLibrary(QString _type, QString _name){
	for (int i=0; i<library.size(); i++)
		if (_type == library[i].type){
			copy(&library[i]);
			name = _name;
			return RESULT_SUCCESS;
		}
	return RESULT_ERROR;
}

/*QString LEData::addLEFromFileToLibrary(const QString& _path){

    LEData* le = new LEData();

    QFile file(_path);
	if (!file.open(QIODevice::ReadOnly)) return NULL;
    QString line = file.readAll();

    int k, i, p;
	QString str1, str2, str3, path;

    prepareCode(line);

    while (line.contains('`')){
        p = line.indexOf('`');
        if (line.mid(p,8) == "`include"){
            str1 = cutLine(p, line, '\n');
            str1.remove(0,9);
            str1.chop(2);

            path = path.left(path.lastIndexOf('/'));
			path += '/' + str1;
			if (addLEFromFileToLibrary(path) == RESULT_ERROR) return NULL;
        }
		else return NULL;
	}

    if (line.contains(QRegExp("\\b(module)\\b"))){
        p = line.indexOf(QRegExp("\\b(module )\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,7);
        p = str1.indexOf('(');
		le->type = str1.mid(0,p);
        str1.remove(0,p+1); str1.chop(2);

        PortData* port;
        WireData* wire;

        k = str1.count(',')+1;
		for (i=0; i<k; i++){
            str2 = str1.section(',',i,i);
			if (str2 == "") return NULL;

            port = new PortData(le, str2);
            wire = new WireData(str2);
			le->ports.append(port);
			le->wires.append(wire);
			port->insideWire=wire;
			port->le=le;

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
				else return NULL;
			}
        }
    }
	else return NULL;

    while (line.contains(QRegExp("\\b(input)\\b"))){
        p = line.indexOf(QRegExp("\\b(input)\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,6); str1.chop(1);
        k = str1.count(',')+1;
        for (i=0; i<k; i++){
            str2 = str1.section(',',i,i);
			if (str2 == "") return NULL;

			le->portNamed(str2)->isOutput=false;
			le->wireNamed(str2)->drivers.append(le->portNamed(str2));
        }
    }

    while (line.contains(QRegExp("\\b(output)\\b"))){
        p = line.indexOf(QRegExp("\\b(output)\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,7); str1.chop(1);
        k = str1.count(',')+1;
        for (i=0; i<k; i++){
            str2 = str1.section(',',i,i);
			if (str2 == "") return NULL;

			le->portNamed(str2)->isOutput=true;
			le->wireNamed(str2)->loads.append(le->portNamed(str2));
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

            le->wires.append(new WireData(str2));
        }
    }

    while (line.contains(QRegExp("\\b(assign)\\b"))){
        p = line.indexOf(QRegExp("\\b(assign)\\b"));
        str1 = cutLine(p, line, ';');
        str1.remove(0,7); str1.chop(1);
        str2 = str1.section('=',0,0);
        str3 = str1.section('=',1,1);
		le->wireNamed(str3)->assigns.append(le->wireNamed(str2));
		le->wireNamed(str2)->assigns.append(le->wireNamed(str3));
    }

	while (line.contains(QRegExp("\\b"))){
        p = line.indexOf(QRegExp("\\b"));

        if ((str1 = cutLine(p, line, ';')) == "") break;

        p = str1.indexOf(' ');
        str2 = str1.mid(0,p); str1.remove(0,p);

        p = str1.indexOf('(');
        str3 = str1.mid(0,p); str1.remove(0,p);

        LEData* _le;
        le = copyFromLibrary(str2,str3);
        les.append(le);

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

			 if (!le->havePort(str3)) return NULL;
             if (le->portNamed(str3)->isOutput)
                wireNamed(str2)->drivers.append(le->portNamed(str3));
                else
                wireNamed(str2)->loads.append(le->portNamed(str3));
                le->portNamed(str3)->outsideWire=wireNamed(str2);
            }
            else{
				if (le->ports[i]->isOutput)
                    wireNamed(str2)->drivers.append(le->portNamed(str3));
                else
                    wireNamed(str2)->loads.append(le->portNamed(str3));
                le->ports[i]->outsideWire=wireNamed(str2);
            }
        }
    }

	library.append(le);

	return le->type;
}*/
