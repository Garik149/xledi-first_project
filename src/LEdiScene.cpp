#include <QMap>
#include "LEdiScene.h"
#include "LEdiView.h"
#include "LEShape.h"
#include "PortShape.h"
#include "WireShape.h"
#include "LEData.h"
#include "PortData.h"
#include "WireData.h"

void LEdiScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->setBrush(Qt::black);
    painter->setPen({Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    painter->drawRect(rect);

    painter->setPen({Qt::gray, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    for (int i = GRID_SZ; i < rect.right(); i += GRID_SZ)
        for (int j = GRID_SZ; j < rect.bottom(); j += GRID_SZ)
			painter->drawPoint(i, j);
}

void LEdiScene::scaleUpdate(float scale){
    LEShape* le;
    PortShape* port;
    QList<QGraphicsItem*> item = items();

    for (int i=0; i<item.size(); i++)
    if (scale < 0.6)
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
    else
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


void LEdiScene::setRank(LEData* _le, int _r){
    int& r = rank.find(_le).value();
	if (r < _r+1) r=_r+1;

    PortData* port;
    WireData* wire;
	for (int i=0; i < _le->outPorts.size(); i++){
		port=_le->outPorts[i];
		for (int j=0; j < port->outsideWire->loads.size(); j++){
			wire=port->outsideWire;
			if (wire == wire->loads[j]->outsideWire)
                setRank(wire->loads[j]->le,r);
		}
	}
}
void LEdiScene::layout(LEData* le){
    int i, j;

    for (i=0; i<le->les.size(); i++)
        rank.insert(le->les[i],1);

	for (i=0; i<le->inPorts.size(); i++)
        for (j=0; j<le->inPorts[i]->insideWire->loads.size(); j++)
            setRank(le->inPorts[i]->insideWire->loads[j]->le,0);

	int maxRank = 1;
    for (i=0; i<le->les.size(); i++){
        int r=rank.find(le->les[i]).value();
		if (maxRank<r) maxRank=r;
	}

	for (i=0; i<le->inPorts.size(); i++){
		PortShape* sh;
		sh = new PortShape(le->inPorts[i]);
        addItem(sh);
        sh->setPos(QPoint(GRID_SZ*10,GRID_SZ*(10+4*i)));
    }

    QList<LEData*> leList;
	for (i=1; i<=maxRank; i++){
        leList=rank.keys(i);
		int Height=0;
		for (j=0; j<leList.size(); j++){
			LEShape* sh;
			sh = new LEShape(leList[j]);
            addItem(sh);
            sh->setPos(QPoint(GRID_SZ*(10+10*i),GRID_SZ*(10+Height)));
            Height+=sh->body->height()/GRID_SZ+2;
        }
    }

	for (i=0; i<le->outPorts.size(); i++){
		PortShape* sh;
		sh = new PortShape(le->outPorts[i]);
        addItem(sh);
        sh->setPos(QPoint(GRID_SZ*(20+10*maxRank),GRID_SZ*(10+4*i)));
	}

    rank.clear();
}



QLineF* LEdiScene::makeHLine(QPointF _point){

    QGraphicsItem* item;
    WireSeg* wireSeg;

    QPointF point = _point;
    bool end;
	int x, xl, xr;

    //Left direction
	xl=_point.x();
	x=xl-GRID_SZ;
    end=false;
	while((!end) && (x>0)){
        point.setX(x);
		item = itemAt(point,QTransform());
        if (item!=NULL)
			switch(item->type()-QGraphicsItem::UserType){
            default:
                xl=x;
                break;

			case 0: //LEShape
                end=true;
                break;

			case 1: //PortShape
				end=true;
				break;

            case 2: //WireSeg
                wireSeg=(WireSeg*)item;
                if ((point == wireSeg->line().p1())||(point == wireSeg->line().p2()))
                    end=true;
                break;
            }
        else
            xl=x;
		x-=GRID_SZ;
	}

    //Right direction
	xr=_point.x();
	x=xr+GRID_SZ;
    end=false;
	while((!end) && (x<W*GRID_SZ)){
        point.setX(x);
        item = itemAt(point,QTransform());
        if (item!=NULL)
            switch(item->type()-QGraphicsItem::UserType){
            default:
                xr=x;
                break;

			case 0: //LEShape
				end=true;
				break;

			case 1: //PortShape
				end=true;
				break;

            case 2: //WireSeg
                wireSeg=(WireSeg*)item;
                if ((point == wireSeg->line().p1())||(point == wireSeg->line().p2()))
                    end=true;
                break;
            }
        else
            xr=x;
		x+=GRID_SZ;
    }

	if (xl==xr) return NULL;
	else return new QLineF(QPointF(xl,_point.y()),QPointF(xr,_point.y()));
}
QLineF* LEdiScene::makeVLine(QPointF _point){

    QGraphicsItem* item;
    WireSeg* wireSeg;

    QPointF point=_point;
    bool end;
	int y, yt, yb;

    //Up direction
	yt=_point.y();
	y=yt-GRID_SZ;
    end=false;
    while((!end) && (y>0)){

        point.setY(y);
        item = itemAt(point,QTransform());
        if (item!=NULL)
            switch(item->type()-QGraphicsItem::UserType){
            default:
                yt=y;
                break;

			case 0: //LEShape
				end=true;
				break;

			case 1: //PortShape
				end=true;
				break;

            case 2: //WireSeg
                wireSeg=(WireSeg*)item;
                if ((point == wireSeg->line().p1())||(point == wireSeg->line().p2()))
                    end=true;
                break;
            }
        else
            yt=y;
		y-=GRID_SZ;
    }

    //Down direction
	yb=_point.y();
	y=yb+GRID_SZ;
    end=false;
    while((!end) && (y<H*GRID_SZ)){
        point.setY(y);
        item = itemAt(point,QTransform());
        if (item!=NULL)
            switch(item->type()-QGraphicsItem::UserType){
            default:
                yb=y;
                break;

			case 0: //LEShape
				end=true;
				break;

			case 1: //PortShape
				end=true;
				break;

            case 2: //WireSeg
				wireSeg=(WireSeg*)item;
                if ((point == wireSeg->line().p1())||(point == wireSeg->line().p2()))
                    end=true;
                break;
            }
        else
            yb=y;
		y+=GRID_SZ;
    }

	if (yt==yb) return NULL;
	else return new QLineF(QPointF(_point.x(),yt),QPointF(_point.x(),yb));
}
QLineF* LEdiScene::lineWithPoint(QPointF point, QList<QLineF*> ll){
    for (int i=0; i<ll.size(); i++)
        if (((point.y() == ll[i]->y1())&&(point.x() >= ll[i]->x1())&&(point.x() <= ll[i]->x2()))||((point.x() == ll[i]->x1())&&(point.y() >= ll[i]->y1())&&(point.y() <= ll[i]->y2()))) return ll[i];
    return NULL;
}
QList<QLineF*> LEdiScene::makeHNormalsToVLines(QList<QLineF*> parents, QList<QLineF*> restrictLines){
    QLineF* line;
	QPointF p;
	int i;

    QList<QLineF*> childs;
    for (i=0; i<parents.size(); i++){
		p.setX(parents[i]->x1());
		for (p.ry()=parents[i]->y1(); p.ry()<=parents[i]->y2(); p.ry()+=GRID_SZ)
        if ((lineWithPoint(p, childs) == NULL)&&(lineWithPoint(p, restrictLines) == NULL)){
			line = makeHLine(p);
            if (line != NULL) childs.append(line);
        }
    }
    return childs;
}
QList<QLineF*> LEdiScene::makeVNormalsToHLines(QList<QLineF*> parents, QList<QLineF*> restrictLines){
    QLineF* line;
	QPointF p;
	int i;

    QList<QLineF*> childs;
    for (i=0; i<parents.size(); i++){
		p.setY(parents[i]->y1());
		for (p.rx()=parents[i]->x1(); p.rx()<=parents[i]->x2(); p.rx()+=GRID_SZ)
        if ((lineWithPoint(p, childs) == NULL)&&(lineWithPoint(p, restrictLines) == NULL)){
			line = makeVLine(p);
            if (line != NULL) childs.append(line);
        }
    }
    return childs;
}
QPointF LEdiScene::findCrossLvsL(QLineF* l1, QLineF* l2){

    if (l1->y1() == l1->y2()){
        if ((l1->y1() >= l2->y1()) && (l1->y1() <= l2->y2()) &&	(l2->x1() >= l1->x1()) && (l2->x1() <= l1->x2()))
            return QPointF(l2->x1(),l1->y1());
    }
    else{
        if ((l2->y1() >= l1->y1()) && (l2->y1() <= l1->y2()) &&	(l1->x1() >= l2->x1()) && (l1->x1() <= l2->x2()))
            return QPointF(l1->x1(),l2->y1());
    }

    return QPointF(-1,-1);
}
QPointF LEdiScene::findCrossLvsLL(QLineF* l, QList<QLineF*> ll){
    QPointF point(-1,-1);

    for (int i=0; i<ll.size(); i++){
        point = findCrossLvsL(l,ll[i]);
        if (point != QPoint(-1,-1))
            break;
    }

    return point;
}
QPointF LEdiScene::findCrossLLvsLL(QList<QLineF*> ll1, QList<QLineF*> ll2){
    QPointF point(-1,-1);

    for (int i=0; i<ll1.size(); i++){
        point = findCrossLvsLL(ll1[i],ll2);
        if (point != QPointF(-1,-1))
            break;
    }

    return point;
}
QPointF LEdiScene::findCrossLLvsHoldedWire(QList<QLineF*> ll){
    QPointF point(-1,-1);

    for (int i=0; i< hWireShape->seg.size(); i++){
        QLineF l = QLineF(hWireShape->seg[i]->line());
        point=findCrossLvsLL(&l,ll);
        if (point != QPoint(-1,-1)){
            break;
        }
    }

    return point;
}

QPair<QPointF, QPointF> LEdiScene::bothSideTraceStep(QList<QLineF*> _bLL, QList<QLineF*> _eLL, QList<QLineF*> _bLLPrev, QList<QLineF*> _eLLPrev){
    iter++;
    QPair<QPointF, QPointF> pointPair(QPointF(-1,-1),QPointF(-1,-1));
    QPair<QPointF, QPointF> pointPair2(QPointF(-1,-1),QPointF(-1,-1));
    QList<QLineF*> bLL, eLL;

    if (iter%2 == 0){
        bLL = makeHNormalsToVLines(_bLL, _bLLPrev);
        eLL = makeHNormalsToVLines(_eLL, _eLLPrev);
    }
    else{
        bLL = makeVNormalsToHLines(_bLL, _bLLPrev);
        eLL = makeVNormalsToHLines(_eLL, _eLLPrev);
    }

    if (bLL.isEmpty()||eLL.isEmpty()){
        for (int i=0; i<bLL.size(); i++)
            delete(bLL[i]);
        for (int i=0; i<eLL.size(); i++)
            delete(eLL[i]);
        return pointPair;
    }

    pointPair.second = findCrossLLvsLL(bLL, _eLL);
    if (pointPair.second != QPointF(-1,-1)){
        QLineF* midLine = lineWithPoint(pointPair.second, bLL);
        pointPair.first = findCrossLvsLL(midLine, _bLL);
        hWireShape->addSeg(QLineF(pointPair.second, pointPair.first));
        return pointPair;
    }

    pointPair = bothSideTraceStep(bLL, eLL, _bLLPrev, _eLLPrev);
    QLineF* bl = lineWithPoint(pointPair.first, bLL);
    pointPair2.first = findCrossLvsLL(bl, _bLL);
    QLineF* el = lineWithPoint(pointPair.second, eLL);
    pointPair2.second = findCrossLvsLL(el, _eLL);
    hWireShape->addSeg(QLineF(pointPair.first, pointPair2.first));
    hWireShape->addSeg(QLineF(pointPair.second, pointPair2.second));

    for (int i=0; i<bLL.size(); i++)
        delete(bLL[i]);
    for (int i=0; i<eLL.size(); i++)
        delete(eLL[i]);
    return pointPair2;

}
QPointF LEdiScene::oneSideTraceStep(QList<QLineF*> _ll, QList<QLineF*> _llPrev){
    iter++;
    QPointF point1(QPointF(-1,-1));
    QPointF point2(QPointF(-1,-1));
    QList<QLineF*> ll;

    if (iter%2 == 0)
        ll = makeHNormalsToVLines(_ll, _llPrev);
    else
        ll = makeVNormalsToHLines(_ll, _llPrev);

    if (ll.isEmpty()) return point1;

    point1 = findCrossLLvsHoldedWire(ll);
    if (point1 != QPoint(-1,-1)){
        //hWireShape->nodes.append(new QGraphicsEllipseItem(point1.x()-5,point1.y()-5,10,10));
        QLineF* lastLine = lineWithPoint(point1, ll);
        point2 = findCrossLvsLL(lastLine, _ll);
        hWireShape->addSeg(QLineF(point1, point2));
        return point2;
    }

    point1 = oneSideTraceStep(ll, _llPrev);
    QLineF* l = lineWithPoint(point1, ll);
    point2 = findCrossLvsLL(l, _ll);
    hWireShape->addSeg(QLineF(point1, point2));

    for (int i=0; i<ll.size(); i++)
        delete(ll[i]);
    return point2;

}
void LEdiScene::tracing(LEData* _le){

    QPointF begin, end;
    WireData* wire;
    PortData* port;

    for (int i=0; i<_le->wires.size(); i++){
        wire = _le->wires[i];
        hWireShape = new WireShape(wire,this);
        for (int j=0; j<wire->drivers.size(); j++){
            port=wire->drivers[j];
            if (_le->havePort(port->name))
                begin=port->shape->pos() + *(port->shape->ending);
            else
                begin=port->le->shape->pos() + *(port->le->shape->ports[port->le->leIndex(port)]);
            for (int k=0; k<wire->loads.size(); k++){
                port=wire->loads[k];
                if (_le->havePort(port->name))
                    end=port->shape->pos() + *(port->shape->ending);
                else
                    end=port->le->shape->pos() + *(port->le->shape->ports[port->le->leIndex(port)]);

                iter=0;
                if (k == 0){
                    QList<QLineF*> bLL, eLL;
                    bLL.append(makeHLine(begin));
                    if (bLL.first() != NULL){
                        if (bLL.first()->p2() == end)
                            hWireShape->addSeg(QLineF(begin, end));
                        else{
                            eLL.append(makeHLine(end));
                            if (eLL.first() != NULL){
                                QPair<QPointF, QPointF> pointPair = bothSideTraceStep(bLL, eLL, QList<QLineF*>(), QList<QLineF*>());
                                if (pointPair.first != QPointF(-1,-1)){
                                    hWireShape->addSeg(QLineF(begin, pointPair.first));
                                    hWireShape->addSeg(QLineF(pointPair.second, end));
                                }
                                else
                                    hWireShape->addSeg(QLineF(begin, end));
                                delete(eLL.first());
                            }
                            else
                                hWireShape->addSeg(QLineF(begin, end));
                        }
                        delete(bLL.first());
                    }
                    else
                        hWireShape->addSeg(QLineF(begin, end));
                }
                else{
                    QList<QLineF*> ll;
                    ll.append(makeHLine(end));
                    if (ll.first() != NULL){
                        QPointF point = findCrossLLvsHoldedWire(ll);
                        if (point != QPoint(-1,-1))
                            hWireShape->addSeg(QLineF(point, end));
                        else{
                            point = oneSideTraceStep(ll, QList<QLineF*>());
                            if (point != QPointF(-1,-1))
                                hWireShape->addSeg(QLineF(point, end));
                            else
                                hWireShape->addSeg(QLineF(begin, end));
                        }
                        delete(ll.first());
                    }
                    else
                        hWireShape->addSeg(QLineF(begin, end));
                }

            }
        }
    }

    /*iter=0;
    QList<QLineF*> bLL, eLL;
    bLL.append(makeHLine(begin));
    if (bLL.first()->p2() == end)
        hWireShape->addSeg(QLineF(begin, end));
    else{
        eLL.append(makeHLine(end));
        QPair<QPointF, QPointF> pointPair = bothSideTraceStep(bLL, eLL);
        if (pointPair.first == QPointF(-1,-1)){pointPair = QPair<QPointF, QPointF>(begin,end);};
        hWireShape->addSeg(QLineF(begin, pointPair.first));
        hWireShape->addSeg(QLineF(pointPair.second, end));
    }

    for (int i=0; i<_le->wires.size(); i++){
		wire=_le->wires[i];
        hWireShape = new WireShape(wire, this);
		for (j=0; j<wire->drivers.size(); j++){
			port=wire->drivers[j];
			if (_le->havePort(port->name))
				begin=port->shape->pos() + *(port->shape->ending);
			else
				begin=port->le->shape->pos() + *(port->le->shape->ports[port->le->leIndex(port)]);
			for (k=0; k<wire->loads.size(); k++){
				port=wire->loads[k];
				if (_le->havePort(port->name))
					end=port->shape->pos() + *(port->shape->ending);
				else
					end=port->le->shape->pos() + *(port->le->shape->ports[port->le->leIndex(port)]);

				hWireShape->addSeg(QLineF(begin, end));

                iter=0;
				QList<QLineF*> bLs;
				QList<QLineF*> eLs;
				bLs.append(makeHLine(begin));
				eLs.append(makeHLine(end));
				if (bLs.back()->p2() == eLs.back()->p2())
					hWireShape->addSeg(QLineF(begin, end));
				else
                    trace(bLs, eLs);

            }
        }
    }*/
}
