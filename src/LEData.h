#ifndef LEDATA_H
#define LEDATA_H

#include <QString>
#include <QList>
#include "defines.h"

class LEData{
    QString name;
	QString type;
    QList<PortData*> ports;
     QList<PortData*> inPorts;
     QList<PortData*> outPorts;
    QList<WireData*> wires;
    QList<LEData*> les;
	bool isBasic:1;
	LEShape* shape;
    static QList<LEData> library;

    WireData* wireNamed(QString _name);
     bool haveWire(QString _name);
    PortData* portNamed(QString _name);
     bool havePort(QString _name);
    int leIndex(PortData* _port);
    LEData* leNamed(QString _name);
     bool haveLE(QString _name);
    bool nameIs(QString _name);
    bool copy(LEData* _le);
	static int compareNames(const void*, const void*);
public:
    LEData();
     LEData(LEData* _le);
     LEData(QString _type, QString _name);
     ~LEData();

	static void nameSort(QList<LEData*>&);
    static bool readLibrary(const QString& path);
	bool initLEFromFile(const QString &path);
	bool copyFromLibrary(const QString _type, const QString _name);
	void clear();

    friend class LEShape;
	friend class LEdiScene;
};

#endif // LEDATA_H
