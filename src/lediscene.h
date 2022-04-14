#ifndef LEDISCENE_H
#define LEDISCENE_H

#include <QGraphicsScene>
#include <QString>
#include <QPainter>
//#include <QMap>
#include "defines.h"

class LEdiScene : public QGraphicsScene{
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
	void check(QHash<LogicElement*, int>* map, Port* port, int r);

public:
	explicit LEdiScene(const QRect &sceneRect, QObject *parent = nullptr);
    ~LEdiScene(){};
	void addShape(LEShape* leShape);
	void layout(LogicElement* le);
    Q_OBJECT
private slots:
    //void slotNameChanged(QString oldName, QString newName);
signals:
	//void tranferItem(ItemLEdi* item, QGraphicsLineItem *line);
};

#endif // LEDISCENE_H
