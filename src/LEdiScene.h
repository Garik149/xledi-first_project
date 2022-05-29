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
    QHash<LEData*, int> rank;
    void setRank(LEData* _le, int r);
public:
    void layout(LEData* le);

    //tracing
private:
    int iter;
	WireShape* hWireShape;
    QLineF* makeHLine(QPointF _point);
    QLineF* makeVLine(QPointF _point);
    QLineF* lineWithPoint(QPointF _point, QList<QLineF*> ll);
    QList<QLineF*> makeHNormalsToVLines(QList<QLineF*> parent, QList<QLineF*> restrictLines);
    QList<QLineF*> makeVNormalsToHLines(QList<QLineF*> parent, QList<QLineF*> restrictLines);
    QPointF findCrossLvsL(QLineF* l1, QLineF* l2);
    QPointF findCrossLvsLL(QLineF* l, QList<QLineF*> ll);
    QPointF findCrossLLvsLL(QList<QLineF*> ll1, QList<QLineF*> ll2);
    QPointF findCrossLLvsHoldedWire(QList<QLineF*> ll);
    QPair<QPointF, QPointF> bothSideTraceStep(QList<QLineF*> bLL, QList<QLineF*> eLL, QList<QLineF*> _bLLPrev, QList<QLineF*> _eLLPrev);
    QPointF oneSideTraceStep(QList<QLineF*>, QList<QLineF*>);
public:
    void tracing(LEData* le);

    Q_OBJECT
private slots:
    //void slotNameChanged(QString oldName, QString newName);
signals:
	//void tranferItem(ItemLEdi* item, QGraphicsLineItem *line);

};

#endif // LEDISCENE_H
