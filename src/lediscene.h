#ifndef LEDISCENE_H
#define LEDISCENE_H

#include <QGraphicsScene>
#include <QString>
#include <QPainter>
#include "defines.h"

class LEdiScene : public QGraphicsScene{
	//int gridSz;
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
	void check(QHash<LogicElement*, int>* map, LogicElement* _le, int r);

public:
	LEdiScene(const QRect &sceneRect, QObject *parent = nullptr);
	~LEdiScene(){};
	void addShape(LEShape* leShape);//?
	void addShape(PortShape* portShape);
	void layout(LogicElement* le);
    Q_OBJECT
private slots:
    //void slotNameChanged(QString oldName, QString newName);
signals:
	//void tranferItem(ItemLEdi* item, QGraphicsLineItem *line);

    friend class LEShape;
	friend class PortShape;
};

#endif // LEDISCENE_H
