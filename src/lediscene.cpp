#include <QMap>
#include "lediscene.h"
#include "lediview.h"
#include "leshape.h"
#include "portshape.h"
#include "wireshape.h"
#include "logicelement.h"
#include "port.h"
#include "wire.h"

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


void LEdiScene::setRank(LogicElement* _le, int _r){
    int& r = rank.find(_le).value();
	if (r < _r+1) r=_r+1;

	Port* port;
	Wire* wire;
	for (int i=0; i < _le->outPorts.size(); i++){
		port=_le->outPorts[i];
		for (int j=0; j < port->outsideWire->loads.size(); j++){
			wire=port->outsideWire;
			if (wire == wire->loads[j]->outsideWire)
                setRank(wire->loads[j]->le,r);
		}
	}
}
void LEdiScene::layout(LogicElement* le){
    int i, j;

    for (i=0; i<le->logicElements.size(); i++)
        rank.insert(le->logicElements[i],1);

	for (i=0; i<le->inPorts.size(); i++)
        for (j=0; j<le->inPorts[i]->insideWire->loads.size(); j++)
            setRank(le->inPorts[i]->insideWire->loads[j]->le,0);

	int maxRank = 1;
	for (i=0; i<le->logicElements.size(); i++){
        int r=rank.find(le->logicElements[i]).value();
		if (maxRank<r) maxRank=r;
	}

	for (i=0; i<le->inPorts.size(); i++){
		PortShape* sh;
		sh = new PortShape(le->inPorts[i]);
        addItem(sh);
        sh->setPos(QPoint(GRID_SZ*10,GRID_SZ*(10+4*i)));
    }

	QList<LogicElement*> leList;
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
bool LEdiScene::pointIsOnHLines(QPointF _point, QList<QLineF*> h){
	for (int i=0; i<h.size(); i++)
		if ((_point.y() == h[i]->y1())&&(_point.x() > h[i]->x1())&&(_point.x() < h[i]->x2())) return true;
	return false;
}
bool LEdiScene::pointIsOnVLines(QPointF _point, QList<QLineF*> v){
	for (int i=0; i<v.size(); i++)
		if ((_point.x() == v[i]->x1())&&(_point.y() > v[i]->y1())&&(_point.y() < v[i]->y2())) return true;
	return false;
}
QList<QLineF*> LEdiScene::makeHNormalsToVLines(QList<QLineF*> parents){
    QLineF* line;
	QPointF p;
	int i;

    QList<QLineF*> childs;
    for (i=0; i<parents.size(); i++){
		p.setX(parents[i]->x1());
		for (p.ry()=parents[i]->y1(); p.ry()<=parents[i]->y2(); p.ry()+=GRID_SZ)
		if (!pointIsOnHLines(p, childs)){
			line = makeHLine(p);
            if (line != NULL) childs.append(line);
        }
    }
    return childs;
}
QList<QLineF*> LEdiScene::makeVNormalsToHLines(QList<QLineF*> parents){
    QLineF* line;
	QPointF p;
	int i;

    QList<QLineF*> childs;
    for (i=0; i<parents.size(); i++){
		p.setY(parents[i]->y1());
		for (p.rx()=parents[i]->x1(); p.rx()<=parents[i]->x2(); p.rx()+=GRID_SZ)
		if (!pointIsOnVLines(p, childs)){
			line = makeVLine(p);
            if (line != NULL) childs.append(line);
        }
    }
    return childs;
}
QLineF* LEdiScene::findMidLine(){
    int i, j;
    QList<QLineF*> h;
    QList<QLineF*> v;

    if (flagH){
        h = H1.back();
        v = V2.back();
    }
    else{
        v = V1.back();
        h = H2.back();
    }

    for (i=0; i<h.size(); i++)
        for (j=0; j<v.size(); j++)
            if ((h[i]->y1() > v[j]->y1()) && (h[i]->y1() < v[j]->y2()) &&
            (v[j]->x1() > h[i]->x1()) && (v[j]->x1() < h[i]->x2())){
                if (flagH) return h[i];
                else return v[j];
            }

    return NULL;
}
QPair<QPointF, QLineF*> LEdiScene::findOverlapWithList(QLineF* line, QList<QLineF*> lineList){

    QPair<QPointF, QLineF*> pair;

    for (int i=0; i<lineList.size(); i++){
        pair.first = findOverlap(line, lineList[i]);
        if (pair.first != QPoint(-1,-1)){
            pair.second = lineList[i];
            return pair;
        }
    }

    pair.second = NULL;
    return pair;
}
QPointF LEdiScene::findOverlap(QLineF* l1, QLineF* l2){

    QLineF* h; QLineF* v;
	if (l1->y1() == l1->y2()) {h=l1; v=l2;}
    else {h=l2; v=l1;}

	if ((h->y1() >= v->y1()) && (h->y1() <= v->y2()) &&
	(v->x1() >= h->x1()) && (v->x1() <= h->x2()))
        return QPointF(v->x1(),h->y1());

    return QPointF(-1,-1);
}
bool LEdiScene::trace(){
    iter++;

    if (iter%2 == 0) flagH=true;
    else flagH=false;

    QList<QLineF*> lines;

    if (flagH){
        lines = makeHNormalsToVLines(V1.back());
        if (lines.isEmpty()) return false;
        H1.append(lines);
    }
    else{
        lines = makeVNormalsToHLines(H1.back());
        if (lines.isEmpty()) return false;
        V1.append(lines);
    }
    lines.clear();

    QLineF* midLine = findMidLine();
    if (midLine != NULL){
        makePath(midLine);
        return true;
    }

    if (flagH){
        lines = makeHNormalsToVLines(V2.back());
        if (lines.isEmpty()) return false;
        H2.append(lines);
    }
    else{
        lines = makeVNormalsToHLines(H2.back());
        if (lines.isEmpty()) return false;
        V2.append(lines);
    }
    lines.clear();

    if (!trace()) return false;
    return true;
}
void LEdiScene::makePath(QLineF* midLine){

    QPointF beginPoint, endPoint;
    QPair<QPointF, QLineF*> beginPair, endPair;

    if (iter%2 == 0){
        beginPair = findOverlapWithList(midLine, V1[(iter-1)/2]);
        endPair = findOverlapWithList(midLine, V2[(iter-1)/2]);
    }
    else{
        beginPair = findOverlapWithList(midLine, H1[iter/2]);
        endPair = findOverlapWithList(midLine, H2[iter/2]);
    }
    hWireShape->addSeg(QLineF(beginPair.first, endPair.first));
    iter--;

    while (iter != 0){
        beginPoint = beginPair.first; endPoint = endPair.first;
        if (iter%2 == 0){
			beginPair = findOverlapWithList(beginPair.second, V1[(iter-2)/2]);
			endPair = findOverlapWithList(endPair.second, V2[(iter-2)/2]);
        }
        else{
			beginPair = findOverlapWithList(beginPair.second, H1[(iter-1)/2]);
			endPair = findOverlapWithList(endPair.second, H2[(iter-1)/2]);
        }
        hWireShape->addSeg(QLineF(beginPoint, beginPair.first));
        hWireShape->addSeg(QLineF(endPoint, endPair.first));
        iter--;
    }

    hWireShape->addSeg(QLineF(beginPair.first, H1[0][0]->p1()));
    hWireShape->addSeg(QLineF(endPair.first, H2[0][0]->p2()));
}
void LEdiScene::tracing(LogicElement* _le){

	int i, j, k;
    QPointF begin, end;

	Wire* wire;
	Port* port;

	LEShape* leShape;
	leShape=_le->logicElements[3]->shape;
	begin = leShape->pos()+*leShape->ports[0];
	leShape=_le->logicElements[0]->shape;
	end = leShape->pos()+*leShape->ports[2];

	hWireShape = new WireShape(new Wire(), this);

    iter=0;
    H1.append(QList<QLineF*>());
	H1.back().append(makeHLine(begin));
	H2.append(QList<QLineF*>());
    H2.back().append(makeHLine(end));
    if (H1.back().back()->p2() == end)
        hWireShape->addSeg(QLineF(begin, end));
    else
		trace();

	/*for (i=0; i<_le->wires.size(); i++){
		wire=_le->wires[1];
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

				iter=0;
				H1.append(QList<QLineF*>());
				H1.back().append(makeHLine(begin));
				H2.append(QList<QLineF*>());
				H2.back().append(makeHLine(end));
				if (H1.back().back()->p2() == end)
					hWireShape->addSeg(QLineF(begin, end));
				else
					trace();

            }
		}
	}*/
}
