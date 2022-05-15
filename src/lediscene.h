#ifndef LEDISCENE_H
#define LEDISCENE_H

#include <QGraphicsScene>
#include <QString>
#include <QPainter>
#include "defines.h"

class LEdiScene : public QGraphicsScene{
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void setRank(QHash<LogicElement*, int>* map, LogicElement* _le, int r);

public:
    LEdiScene(const QRect &sceneRect, QObject *parent = nullptr) : QGraphicsScene(sceneRect,parent){};
     ~LEdiScene(){};
    void scaleUpdate(float scale);

	void layout(LogicElement* le);
    void tracing(LogicElement* le);

    Q_OBJECT
private slots:
    //void slotNameChanged(QString oldName, QString newName);
signals:
	//void tranferItem(ItemLEdi* item, QGraphicsLineItem *line);

};

#endif // LEDISCENE_H
