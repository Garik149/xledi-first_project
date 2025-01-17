#include <stdio.h>
#include <stdlib.h>

#include <QMap>

#include "LEdiScene.h"
#include "LEdiView.h"
#include "LEData.h"
#include "LEShape.h"
#include "PortData.h"
#include "PortShape.h"
#include "WireData.h"
#include "WireShape.h"


LEdiScene::LEdiScene(const QRect &sceneRect, QObject *parent) : QGraphicsScene(sceneRect,parent){
	reset();
}

void LEdiScene::reset(){
	largeGrid=false;
	iter=0;
	hLE=NULL;
	hWire=NULL;
	hWireShapeToDelete=NULL;
	wiresToTrace.clear();
	wireShapeList.clear();
	rank.clear();
	restrictedPorts.clear();
	passedLE.clear();

	QList<QGraphicsItem*> itemList=items();
	for (int i=itemList.size()-1; i>=0; i--)
		removeItem(itemList[i]);
}

void LEdiScene::scaleUpdate(float scale){
	LEShape* le;
	PortShape* port;
	QList<QGraphicsItem*> item = items();

	for (int i=0; i<item.size(); i++)
	if (scale < 0.6){
		largeGrid = true;
		switch(item[i]->type()-QGraphicsItem::UserType){
		default:
			break;

		case 0:
			le = (LEShape*)item[i];
			le->shownLabels=false;
			break;

		case 1:
			port = (PortShape*)item[i];
			port->shownLabels=false;
			break;
		}
	}
	else{
		largeGrid = false;
		switch(item[i]->type()-QGraphicsItem::UserType){
		default:
			break;

		case 0:
			le = (LEShape*)item[i];
			le->shownLabels=true;
			break;

		case 1:
			port = (PortShape*)item[i];
			port->shownLabels=true;
			break;
		}
	}
}

void LEdiScene::synth(LEData* le){
	mainLE=le;
	setSceneRect(layoutMainLE());
	traceMainLE();
}

void LEdiScene::drawBackground(QPainter* painter, const QRectF&)
{
	painter->setBrush(Qt::white);
	painter->setPen(QPen(Qt::darkGray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawRect(sceneRect());

    if (!largeGrid)
        for (int i = GRID_SZ; i < sceneRect().right(); i += GRID_SZ)
            for (int j = GRID_SZ; j < sceneRect().bottom(); j += GRID_SZ)
                painter->drawPoint(i, j);

	painter->setPen(QPen(Qt::darkGray, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = GRID_SZ*10; i < sceneRect().right(); i += GRID_SZ*10)
        for (int j = GRID_SZ*10; j < sceneRect().bottom(); j += GRID_SZ*10)
            painter->drawPoint(i, j);
}


void LEdiScene::rankingStep(LEData* _le, int _r){
    if (passedLE.contains(_le)) return;
    passedLE.append(_le);
    int& r = rank.find(_le).value();
	if (r < _r+1) r=_r+1;

    for (int i=0; i < _le->outPorts.size(); i++){
        WireData* wire;
        QList<LEData*> leToRank;
        wire=_le->outPorts[i]->outsideWire;
        for (int j=0; j < wire->loads.size(); j++)
            if ((wire == wire->loads[j]->outsideWire)&&(!restrictedPorts.contains(wire->loads[j]))){
                if (!passedLE.contains(wire->loads[j]->le))
                    leToRank.append(wire->loads[j]->le);
                else
                    restrictedPorts.append(wire->loads[j]);
    }
        for (int j=0; j < leToRank.size(); j++)
            rankingStep(leToRank[j],r);
        leToRank.clear();
    }

    passedLE.removeAll(_le);
}
QRectF LEdiScene::layoutMainLE(){
	int i, j;
	int dl;

	for (i=0; i<mainLE->les.size(); i++)
		rank.insert(mainLE->les[i],1);

	for (i=0; i < mainLE->inPorts.size(); i++){
        QList<LEData*> leToRank;
        WireData* wire;
		wire=mainLE->inPorts[i]->insideWire;
        for (int j=0; j < wire->loads.size(); j++)
            if (wire == wire->loads[j]->outsideWire)
				leToRank.append(wire->loads[j]->le);
        for (int j=0; j < leToRank.size(); j++)
            rankingStep(leToRank[j],0);
        leToRank.clear();
    }

	int maxH = 10+4*qMax(mainLE->outPorts.size(),mainLE->inPorts.size());
	int maxRank = 1;
	for (i=0; i<mainLE->les.size(); i++){
        int r;
		r=rank.find(mainLE->les[i]).value();
		maxRank=qMax(maxRank,r);
	}

	dl=10;
	for (i=0; i<mainLE->inPorts.size(); i++){
		PortShape* sh;
		sh = new PortShape(mainLE->inPorts[i]);
        addItem(sh);
		sh->setPos(QPoint(GRID_SZ*dl,GRID_SZ*(10+4*i)));
	}
	{
		int dh=0;
		QList<LEData*> leList;
		leList=rank.keys(1);
		for (i=0; i<leList.size(); i++)
			dh+=leList[i]->inPorts.size()+3;
		dl+=4+int((dh-3)/4);
	}

	for (i=1; i<=maxRank; i++){
		QList<LEData*> leList;
		QSet<WireData*> inWires, outWires;
        leList=rank.keys(i);
		LEData::nameSort(leList);
		int height=0;
		for (j=0; j<leList.size(); j++){
			for (int k=0; k<leList[j]->inPorts.size(); k++)
				inWires.insert(leList[j]->inPorts[k]->outsideWire);
			for (int k=0; k<leList[j]->outPorts.size(); k++)
				outWires.insert(leList[j]->inPorts[k]->outsideWire);
		}
		dl+=inWires.size(); inWires.clear();
		for (j=0; j<leList.size(); j++){
			LEShape* sh;
			sh = new LEShape(leList[j]);
            addItem(sh);
			sh->setPos(QPoint(GRID_SZ*dl,GRID_SZ*(10+height)));
			height+=sh->body->height()/GRID_SZ+2;
        }
		maxH = qMax(maxH,height);
		dl+=3+outWires.size(); outWires.clear();
    }

	dl+=mainLE->outPorts.size();
	for (i=0; i<mainLE->outPorts.size(); i++){
		PortShape* sh;
		sh = new PortShape(mainLE->outPorts[i]);
        addItem(sh);
		sh->setPos(QPoint(GRID_SZ*dl,GRID_SZ*(10+4*i)));
	}

	QList<WireData*> wireList=mainLE->wires;
	while(!wireList.isEmpty()){
		int k;
		k=1;
		for (i=0; i<wireList.size(); i++)
			k=qMax(k,wireList[i]->loads.size());
		for (i=0; i<wireList.size(); i++)
			if (wireList[i]->loads.size()==k){
				wiresToTrace.append(wireList[i]);
				wireList.removeAt(i);
			}
	}

	restrictedPorts.clear();
    rank.clear();
	passedLE.clear();
	return QRectF(0, 0, GRID_SZ*20+mainLE->outPorts.back()->shape->x(), GRID_SZ*(maxH+10));
}


short int LEdiScene::positionState(QPointF _point){ // 0-occupied place, 1-mid of wireSeg, 2-empty place
	WireSeg* wireSeg;
	WireNode* wireNode;
	QList<QGraphicsItem*> itemList(items(_point));
	short int type=2;

	for (int i=0; i<itemList.size(); i++)
		switch(itemList[i]->type()-QGraphicsItem::UserType){
		default:
			break;
		case 0: case 1: //LEShape, PortShape
			return 0;
			break;
		case 2: //WireSeg
			wireSeg=(WireSeg*)itemList[i];
			if ((wireSeg->whole != hWireShapeToDelete)&&(wireSeg->whole != hWire->shape)){
				if ((_point == wireSeg->line().p1())||(_point == wireSeg->line().p2()))
					return 0;
				else
					type=1;
			}
			break;
		case 3: //WireNode
			wireNode = (WireNode*)itemList[i];
			if ((wireNode->whole != hWireShapeToDelete)&&(wireNode->whole != hWire->shape))
				return 0;
			break;
	}
	return type;
}
int LEdiScene::orthDist(QPointF _point1, QPointF _point2){
    return abs(_point1.x()-_point2.x())+abs(_point1.y()-_point2.y());
}
QLineF LEdiScene::makeHLine(QPointF _point){
	QPointF point=_point;
	short int mode;
	int x, xl, xr;

    //Left direction
	xl=_point.x();
	x=xl;
	while(x>GRID_SZ){
		x-=GRID_SZ;
        point.setX(x);
		mode = positionState(point);

		if (mode == 0) break;
		if (mode == 2) xl=x;
	}

    //Right direction
	xr=_point.x();
	x=xr;
	while(x<width()-GRID_SZ){
		x+=GRID_SZ;
        point.setX(x);
		mode = positionState(point);

		if (mode == 0) break;
		if (mode == 2) xr=x;
    }

    if (xl==xr) return nullLine;
    else return QLineF(QPointF(xl,_point.y()),QPointF(xr,_point.y()));
}
QLineF LEdiScene::makeVLine(QPointF _point){
    QPointF point=_point;
	short int mode;
	int y, yt, yb;

    //Up direction
	yt=_point.y();
	y=yt;
	while(y>GRID_SZ){
		y-=GRID_SZ;
        point.setY(y);
		mode = positionState(point);

		if (mode == 0) break;
		if (mode == 2) yt=y;
    }

    //Down direction
	yb=_point.y();
	y=yb;
	while(y<height()-GRID_SZ){
		y+=GRID_SZ;
        point.setY(y);
		mode = positionState(point);

		if (mode == 0) break;
		if (mode == 2) yb=y;
    }

    if (yt==yb) return nullLine;
    else return QLineF(QPointF(_point.x(),yt),QPointF(_point.x(),yb));
}
QLineF const& LEdiScene::lineWithPoint(QPointF point, QList<QLineF> const& ll){
    for (int i=0; i<ll.size(); i++)
        if (((point.y() == ll[i].y1())&&(point.x() >= ll[i].x1())&&(point.x() <= ll[i].x2()))||((point.x() == ll[i].x1())&&(point.y() >= ll[i].y1())&&(point.y() <= ll[i].y2())))
            return ll[i];
    return nullLine;
}
void LEdiScene::makeHNormalsToVLines(QPair<QList<QLineF>,QList<QPointF>>& childs, QPair<QList<QLineF>,QList<QPointF>> const& parents, QList<QLineF> const& restrictLines){
    QPointF top, bottom;
    QLineF line;
    bool traceUp=true, traceDown=true;

    for (int i=0; i<parents.first.size(); i++){
        top = parents.second[i]; bottom = parents.second[i];
        traceUp=true; traceDown=true;
        while (traceUp || traceDown){

            if (traceUp){
                if ((lineWithPoint(top, childs.first) == nullLine)&&(lineWithPoint(top, restrictLines) == nullLine)){
                    line = makeHLine(top);
                    if (line != nullLine){
                        childs.first.append(line);
                        childs.second.append(top);
                    }
                }

                top.ry()-=GRID_SZ;
                if (top.y() < parents.first[i].y1()) traceUp=false;
            }

            if (traceDown){
                if ((lineWithPoint(bottom, childs.first) == nullLine)&&(lineWithPoint(bottom, restrictLines) == nullLine)){
                    line = makeHLine(bottom);
                    if (line != nullLine){
                        childs.first.append(line);
                        childs.second.append(bottom);
                    }
                }

                bottom.ry()+=GRID_SZ;
                if (bottom.y() > parents.first[i].y2()) traceDown=false;
            }
        }
    }
}
void LEdiScene::makeVNormalsToHLines(QPair<QList<QLineF>,QList<QPointF>>& childs, QPair<QList<QLineF>,QList<QPointF>> const& parents, QList<QLineF> const& restrictLines){
    QPointF left, right;
    QLineF line;
    bool traceLeft, traceRight;

    for (int i=0; i<parents.first.size(); i++){
        left = parents.second[i]; right = parents.second[i];
        traceLeft=true; traceRight=true;
        while (traceLeft || traceRight){

            if (traceLeft){
                if ((lineWithPoint(left, childs.first) == nullLine)&&(lineWithPoint(left, restrictLines) == nullLine)){
                    line = makeVLine(left);
                    if (line != nullLine){
                        childs.first.append(line);
                        childs.second.append(left);
                    }
                }

                left.rx()-=GRID_SZ;
                if (left.x() < parents.first[i].x1()) traceLeft=false;
            }

            if (traceRight){
                if ((lineWithPoint(right, childs.first) == nullLine)&&(lineWithPoint(right, restrictLines) == nullLine)){
                    line = makeVLine(right);
                    if (line != nullLine){
                        childs.first.append(line);
                        childs.second.append(right);
                    }
                }

                right.rx()+=GRID_SZ;
                if (right.x() > parents.first[i].x2()) traceRight=false;
            }
        }
    }
}
QPointF LEdiScene::findCrossLvsL(QLineF l1, QLineF l2){

    if (l1.y1() == l1.y2()){
        if ((l1.y1() >= l2.y1()) && (l1.y1() <= l2.y2()) &&	(l2.x1() >= l1.x1()) && (l2.x1() <= l1.x2()))
            return QPointF(l2.x1(),l1.y1());
    }
    else{
        if ((l2.y1() >= l1.y1()) && (l2.y1() <= l1.y2()) &&	(l1.x1() >= l2.x1()) && (l1.x1() <= l2.x2()))
            return QPointF(l1.x1(),l2.y1());
    }

    return nullPoint;
}
QPointF LEdiScene::findCrossLvsLL(QLineF l, QList<QLineF> const& ll){
    QPointF point = nullPoint;

    for (int i=0; i<ll.size(); i++){
        point = findCrossLvsL(l,ll[i]);
        if (point != nullPoint)
            break;
    }

    return point;
}
QPointF LEdiScene::findCrossLLvsLL(QList<QLineF> const& ll1, QList<QLineF> const& ll2){
    QPointF point = nullPoint;

    for (int i=0; i<ll1.size(); i++){
        point = findCrossLvsLL(ll1[i],ll2);
        if (point != nullPoint)
            break;
    }

    return point;
}
QPointF LEdiScene::findCrossLLvsHoldedWire(QPair<QList<QLineF>,QList<QPointF>> const& lPair){
    int dist;
    int minDist=this->height()+this->width();
    QPointF point;
    QPointF closestPoint = nullPoint;

    QList<QLineF> const& ll = lPair.first;
    QList<QPointF> const& pl = lPair.second;

    for (int i=0; i< hWire->shape->seg.size(); i++)
        for (int j=0; j< ll.size(); j++){
            point=findCrossLvsL(hWire->shape->seg[i]->line(),ll[j]);
            dist=orthDist(point,pl[j]);
            if (point != nullPoint && dist<minDist){
                minDist=dist;
                closestPoint=point;
                break;
            }
        }

    return closestPoint;
}

QPair<QPointF, QPointF> LEdiScene::bothSideTraceStep(QPair<QList<QLineF>,QList<QPointF>> const& _bLPair, QPair<QList<QLineF>,QList<QPointF>> const& _eLPair, QList<QLineF> const& _bLLPrev, QList<QLineF> const& _eLLPrev){
    iter++;
    QPair<QPointF, QPointF> pointPair(nullPoint,nullPoint);
    QPair<QPointF, QPointF> pointPair2(nullPoint,nullPoint);
    QPair<QList<QLineF>,QList<QPointF>> bLPair, eLPair;

    if (iter%2 == 0){
        makeHNormalsToVLines(bLPair, _bLPair, _bLLPrev);
        makeHNormalsToVLines(eLPair, _eLPair, _eLLPrev);
    }
    else{
        makeVNormalsToHLines(bLPair, _bLPair, _bLLPrev);
        makeVNormalsToHLines(eLPair, _eLPair, _eLLPrev);
    }

    QList<QLineF> const &bLL = bLPair.first, &eLL = eLPair.first, &_bLL = _bLPair.first, &_eLL = _eLPair.first;

    if (!bLL.isEmpty() && !eLL.isEmpty()){
        pointPair.second = findCrossLLvsLL(bLL, _eLL);
        if (pointPair.second != nullPoint){
            QLineF midLine = lineWithPoint(pointPair.second, bLL);
            pointPair.first = findCrossLvsLL(midLine, _bLL);
            hWire->shape->addSeg(QLineF(pointPair.second, pointPair.first));
            return pointPair;
        }

        pointPair = bothSideTraceStep(bLPair, eLPair, _bLLPrev, _eLLPrev);
        if (pointPair.first != nullPoint){
            QLineF bl = lineWithPoint(pointPair.first, bLL);
            pointPair2.first = findCrossLvsLL(bl, _bLL);
            QLineF el = lineWithPoint(pointPair.second, eLL);
            pointPair2.second = findCrossLvsLL(el, _eLL);
            hWire->shape->addSeg(QLineF(pointPair.first, pointPair2.first));
            hWire->shape->addSeg(QLineF(pointPair.second, pointPair2.second));
        }
    }

    return pointPair2;
}
QPointF LEdiScene::oneSideTraceStep(QPair<QList<QLineF>,QList<QPointF>> const& _lPair, QList<QLineF> const& _llPrev){
    iter++;
    QPointF point1(nullPoint);
    QPointF point2(nullPoint);
	QPair<QList<QLineF>,QList<QPointF>> lPair;

    if (iter%2 == 0)
        makeHNormalsToVLines(lPair, _lPair, _llPrev);
    else
		makeVNormalsToHLines(lPair, _lPair, _llPrev);

    QList<QLineF> const &ll = lPair.first, &_ll = _lPair.first;

    if (!ll.isEmpty()){
        point1 = findCrossLLvsHoldedWire(lPair);
        if (point1 != nullPoint){
			hWire->shape->addNode(point1);
            QLineF lastLine = lineWithPoint(point1, ll);
            point2 = findCrossLvsLL(lastLine, _ll);
            hWire->shape->addSeg(QLineF(point1, point2));
            return point2;
        }

        point1 = oneSideTraceStep(lPair, _ll);
        if (point1 != nullPoint){
            QLineF l = lineWithPoint(point1, ll);
            point2 = findCrossLvsLL(l, _ll);
            hWire->shape->addSeg(QLineF(point1, point2));
        }
    }

    return point2;

}
bool LEdiScene::traceHoldedWire(){

    QPointF begin, end;
    PortData* port;

    port=hWire->drivers.first();
    if (hLE->havePort(port->name))
        begin=port->shape->pos() + *(port->shape->ending);
    else
        begin=port->le->shape->pos() + *(port->le->shape->ports[port->le->leIndex(port)]);

    port=hWire->loads.first();
    if (hLE->havePort(port->name))
        end=port->shape->pos() + *(port->shape->ending);
    else
        end=port->le->shape->pos() + *(port->le->shape->ports[port->le->leIndex(port)]);

    iter=0;
    QPair<QList<QLineF>, QList<QPointF>> bLPair, eLPair;
    bLPair.first.append(makeHLine(begin));
    bLPair.second.append(begin);
	if (bLPair.first.first() == nullLine) {hWire->shape->erase(); return false;}
	if (bLPair.first.first().p2() == end+QPointF(-GRID_SZ,0))
		hWire->shape->addSeg(QLineF(begin, end));
	else{
		eLPair.first.append(makeHLine(end));
		eLPair.second.append(end);
		if (eLPair.first.first() == nullLine) {hWire->shape->erase(); return false;}
		QPair<QPointF, QPointF> pointPair = bothSideTraceStep(bLPair, eLPair, QList<QLineF>(), QList<QLineF>());
		if (pointPair.first == nullPoint) {hWire->shape->erase(); return false;}
		hWire->shape->addSeg(QLineF(begin, pointPair.first));
		hWire->shape->addSeg(QLineF(pointPair.second, end));
	}

    for (int i=1; i<hWire->loads.size(); i++){
        port=hWire->loads[i];
        if (hLE->havePort(port->name))
            end=port->shape->pos() + *(port->shape->ending);
        else
            end=port->le->shape->pos() + *(port->le->shape->ports[port->le->leIndex(port)]);

        iter=0;
        QPair<QList<QLineF>, QList<QPointF>> lPair;
        lPair.first.append(makeHLine(end));
        lPair.second.append(end);
		if (lPair.first.first() == nullLine) {hWire->shape->erase(); return false;}
		QPointF point = findCrossLLvsHoldedWire(lPair);
		if (point != nullPoint){
			hWire->shape->addNode(point);
			hWire->shape->addSeg(QLineF(point, end));
		}
		else{
			point = oneSideTraceStep(lPair, QList<QLineF>());
			if (point == nullPoint) {hWire->shape->erase(); return false;}
			hWire->shape->addSeg(QLineF(point, end));
		}
    }

    return true;
}
void LEdiScene::traceMainLE(){
	hLE=mainLE;
	if (wiresToTrace.isEmpty()) return;

	int k=1;
	int const maxK=7+wiresToTrace.size()/5;
	while((!wiresToTrace.isEmpty()) && k<=maxK){
        hWire=wiresToTrace.first();
		wiresToTrace.removeFirst();
        new WireShape(hWire,this);
		if (!traceHoldedWire()&&(k <= maxK)){
			int j;
			k++;
			for (j=0; j<wireShapeList.size(); j++){
                hWireShapeToDelete=wireShapeList[j];
				if (traceHoldedWire()){
					wiresToTrace.append(hWireShapeToDelete->data);
					wireShapeList.removeAll(hWireShapeToDelete); delete(hWireShapeToDelete);
					break;
				}
			}
			hWireShapeToDelete=NULL;
		}
		if (hWire->shape != NULL)
			wireShapeList.append(hWire->shape);
		hWire=NULL;

		switch (qRound(wireShapeList.size()*10.0/mainLE->wires.size())){
			case 1: qDebug("+---------"); break;
			case 2: qDebug("++--------"); break;
			case 3: qDebug("+++-------"); break;
			case 4: qDebug("++++------"); break;
			case 5: qDebug("+++++-----"); break;
			case 6: qDebug("++++++----"); break;
			case 7: qDebug("+++++++---"); break;
			case 8: qDebug("++++++++--"); break;
			case 9: qDebug("+++++++++-"); break;
		}
	}
    wiresToTrace.clear();

	if (wireShapeList.size() != mainLE->wires.size())
		qDebug("Only %d of %d wires was traced.", wireShapeList.size(), mainLE->wires.size());
	else
		qDebug("All %d wires was traced.", mainLE->wires.size());

	hLE=NULL;
}
