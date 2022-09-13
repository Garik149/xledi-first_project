#ifndef LEDATA_H
#define LEDATA_H

#include <QString>
#include <QList>
#include "defines.h"

class LEData{
private:
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
private:
    WireData* wireNamed(QString _name);
	bool haveWire(QString _name);
    PortData* portNamed(QString _name);
	bool havePort(QString _name);
    int leIndex(PortData* _port);
    LEData* leNamed(QString _name);
	bool haveLE(QString _name);
    bool nameIs(QString _name);
    bool copy(LEData* _le);
	static bool compareNames(const LEData*, const LEData*);


    friend class LEShape;
	friend class LEdiScene;
	friend class MainWindow;
};

#endif // LEDATA_H
