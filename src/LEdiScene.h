#ifndef LEDISCENE_H
#define LEDISCENE_H

#include <QGraphicsScene>
#include <QString>
#include <QPainter>
#include "defines.h"

class LEdiScene : public QGraphicsScene{
public:
	const QColor bcgndColor;
private:
	bool largeGrid;
	bool shownLabels;
	int colorMap;


public:
	LEdiScene(const QRect &sceneRect, QObject *parent = nullptr);
	 ~LEdiScene(){};
	void reset();
	void scaleUpdate(float scale);
private:
	void drawBackground(QPainter*, const QRectF&) override;


    //placing
private:
    QHash<LEData*, int> rank;
    QList<PortData*> restrictedPorts;
    QList<LEData*> passedLE;
    void rankingStep(LEData* _le, int r);
public:
	QRectF layoutLE(LEData* le);


    //tracing
private:
    QLineF const nullLine{-1,-1,-1,-1};
    QPointF const nullPoint{-1,-1};
    int iter;
    LEData* hLE;
    WireData* hWire;
    WireShape* hWireShapeToDelete;
	QList<WireData*> wiresToTrace;
    QList<WireShape*> wireShapeList;

	short int positionState(QPointF _point);
    int orthDist(QPointF _point1, QPointF _point2);
    QLineF makeHLine(QPointF _point);
    QLineF makeVLine(QPointF _point);
    QLineF const& lineWithPoint(QPointF _point, QList<QLineF> const& ll);
    void makeHNormalsToVLines(QPair<QList<QLineF>,QList<QPointF>>& childs, QPair<QList<QLineF>,QList<QPointF>> const& parents, QList<QLineF> const& restrictLines);
    void makeVNormalsToHLines(QPair<QList<QLineF>,QList<QPointF>>& childs, QPair<QList<QLineF>,QList<QPointF>> const& parents, QList<QLineF> const& restrictLines);
    QPointF findCrossLvsL(QLineF l1, QLineF l2);
    QPointF findCrossLvsLL(QLineF l, QList<QLineF> const& ll);
    QPointF findCrossLLvsLL(QList<QLineF> const& ll1, QList<QLineF> const& ll2);
    QPointF findCrossLLvsHoldedWire(QPair<QList<QLineF>,QList<QPointF>> const& lPair);
    QPair<QPointF, QPointF> bothSideTraceStep(QPair<QList<QLineF>,QList<QPointF>> const& _bLPair, QPair<QList<QLineF>,QList<QPointF>> const& _eLPair, QList<QLineF> const& _bLLPrev, QList<QLineF> const& _eLLPrev);
    QPointF oneSideTraceStep(QPair<QList<QLineF>,QList<QPointF>> const& _lPair, QList<QLineF> const& _llPrev);
    bool traceHoldedWire();
public:
    void traceLE(LEData* le);


    Q_OBJECT
public slots:
    //void slotNameChanged(QString oldName, QString newName);
signals:
	//void tranferItem(ItemLEdi* item, QGraphicsLineItem *line);

};

#endif // LEDISCENE_H
