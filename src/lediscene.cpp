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

void LEdiScene::check(QHash<LogicElement*, int>* map, LogicElement* _le, int _r){
	int& r = map->find(_le).value();
	if (r < _r+1) r=_r+1;

	Port* port;
	Wire* wire;
	for (int i=0; i < _le->outPorts.size(); i++){
		port=_le->outPorts[i];
		for (int j=0; j < port->outsideWire->loads.size(); j++){
			wire=port->outsideWire;
			if (wire == wire->loads[j]->outsideWire)
				check(map, wire->loads[j]->le,r);
		}
	}
}
void LEdiScene::layout(LogicElement* le){
    int i, j;

	QHash<LogicElement*, int>* map = new QHash<LogicElement*, int>;
    for (i=0; i<le->logicElements.size(); i++)
		map->insert(le->logicElements[i],1);

	for (i=0; i<le->inPorts.size(); i++)
        for (j=0; j<le->inPorts[i]->insideWire->loads.size(); j++)
			check(map, le->inPorts[i]->insideWire->loads[j]->le,0);

	int maxRank = 1;
	for (i=0; i<le->logicElements.size(); i++){
		int r=map->find(le->logicElements[i]).value();
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
		leList=map->keys(i);
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

    delete (map);
}

void LEdiScene::tracing(LogicElement* le){

    enum {Empty, Block, HLine, VLine};
    int i, j, k;
    QPointF point;
    QGraphicsItem* item;
    WireShape* wireShape;
    short int M[H][W];

    for (i=0; i<H; i++)
        for (j=0; j<W; j++){
            point=QPointF(j*GRID_SZ,i*GRID_SZ);
            item = itemAt(point,views().back()->transform());
            if (item!=NULL)
                switch(item->type()-QGraphicsItem::UserType){
                default:
                    M[i][j]=Empty;
                    break;

                case 0: //LEShape
                    M[i][j]=Block;
                    break;

                case 1: //PortShape
                    M[i][j]=Block;
                    break;

                case 2: //WireShape
                    wireShape=(WireShape*)item;
                    if ((point != wireShape->line().p1())&&(point != wireShape->line().p2()))
                        if (wireShape->line().p1().x() == wireShape->line().p2().x())
                            M[i][j]=HLine;
                        else
                            M[i][j]=VLine;
                    else
                        M[i][j]=Block;
                    break;
                }
            else
                M[i][j]=Empty;
        }

    Wire* wire;
    QList<QGraphicsLineItem*> U1;
    QList<QGraphicsLineItem*> U2;

    for (i=0; i<le->wires.size(); i++){
        wire=le->wires[i];
        for (j=0; j<wire->drivers.size(); j++)
            for (k=0; k<wire->loads.size(); k++){
                wireShape = new WireShape(wire);

            }
    }
}
