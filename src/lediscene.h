#ifndef LEDISCENE_H
#define LEDISCENE_H

#include <QGraphicsScene>
#include <QString>
#include <QPainter>
#include "defines.h"

class LEdiScene : public QGraphicsScene{

private:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
public:
    LEdiScene(const QRect &sceneRect, QObject *parent = nullptr) : QGraphicsScene(sceneRect,parent){};
     ~LEdiScene(){};
    void scaleUpdate(float scale);

    //placing
private:
    QHash<LogicElement*, int> rank;
    void setRank(LogicElement* _le, int r);
public:
    void layout(LogicElement* le);

    //tracing
private:
	int iter;
	bool flagH;
	WireShape* hWireShape;
    QLineF* makeHLine(QPointF _point);
    QLineF* makeVLine(QPointF _point);
	bool pointIsOnHLines(QPointF _point, QList<QLineF*> h);
	bool pointIsOnVLines(QPointF _point, QList<QLineF*> v);
    QList<QLineF*> makeHNormalsToVLines(QList<QLineF*> parent);
    QList<QLineF*> makeVNormalsToHLines(QList<QLineF*> parent);
	QLineF* findMidLine(QList<QLineF*> _bLL, QList<QLineF*> _eLL);
    QPointF findOverlap(QLineF* l1, QLineF* l2);
	QLineF* findOverlapWithList(QLineF* l, QList<QLineF*> lL);
	bool trace(QList<QLineF*> bLL, QList<QLineF*> eLL);
    void makePath(QLineF* midLine);
public:
    void tracing(LogicElement* le);

    Q_OBJECT
private slots:
    //void slotNameChanged(QString oldName, QString newName);
signals:
	//void tranferItem(ItemLEdi* item, QGraphicsLineItem *line);

};

#endif // LEDISCENE_H
