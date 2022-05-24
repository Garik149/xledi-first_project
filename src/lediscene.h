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
    QList<QList<QLineF*>> H1;
    QList<QList<QLineF*>> H2;
    QList<QList<QLineF*>> V1;
    QList<QList<QLineF*>> V2;
    QLineF* makeHLine(QPointF _point);
    QLineF* makeVLine(QPointF _point);
    QList<QLineF*> makeHNormalsToVLines(QList<QLineF*> parent);
    QList<QLineF*> makeVNormalsToHLines(QList<QLineF*> parent);
    QLineF* findMidLine();
    QPointF findOverlap(QLineF* l1, QLineF* l2);
    QPair<QPointF, QLineF*> findOverlapWithList(QLineF* line, QList<QLineF*> lineList);
    bool trace();
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
