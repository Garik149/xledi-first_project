#include "leshape.h"
#include "logicelement.h"
//#include "wire.h"
#include "port.h"

LEShape::LEShape(LogicElement* _le) : QGraphicsItem(){
    le=_le;
	le->shape=this;
	shownLabels = true;
    setPos(0,0);

    int h = qMax(le->inPorts.size(),le->outPorts.size());

    body = new QRectF(0, 0, 2*GRID_SZ, (h+1)*GRID_SZ);

    int ody=0, idy=0;
    for (int i=0; i < le->ports.size(); i++)
        if (le->ports[i]->isOutput){
            ody += GRID_SZ;
            ports.append(new QPointF(2*GRID_SZ,ody));
        }
        else{
            idy += GRID_SZ;
            ports.append(new QPointF(0,idy));
        }

    setState(Default);
}

LEShape::~LEShape(){
	delete(body);
	for (int i=0; i<ports.size(); i++)
		delete(ports[i]);
}


QRectF LEShape::boundingRect() const{
    return QRectF(-1*GRID_SZ,-1*GRID_SZ,3*GRID_SZ,body->height()+1*GRID_SZ);
}

void LEShape::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {

	if (shownLabels){
        painter->setPen(QPen(QColor(RED,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter->setFont(QFont("Calibri", 11, QFont::DemiBold));
		painter->drawText(QRectF(-1*GRID_SZ, -1*GRID_SZ, 4*GRID_SZ, 1*GRID_SZ),0,le->name);
		painter->drawText(QRectF(-1*GRID_SZ, body->height(), 4*GRID_SZ, 1*GRID_SZ),0,le->type);

		painter->setFont(QFont("Calibri", 8, QFont::DemiBold));
		for (int i=0; i < ports.size(); i++)
			painter->drawText(QRectF(ports[i]->x()-0.5*GRID_SZ, ports[i]->y(), 1*GRID_SZ, 0.75*GRID_SZ),0,le->ports[i]->name);
	}

    QPen pen(QColor(GREEN,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    switch(state){
    default:
        break;

    case State::Bolded:
        pen.setWidth(pen.width()+1);
        break;

    case State::Moved:
        pen.setColor(QColor(pen.color().red(),pen.color().green(),pen.color().blue(),128));
        break;
    }
    painter->setPen(pen);
    painter->drawRect(*body);

    pen.setWidth(pen.width()+4);
    painter->setPen(pen);
    for (int i=0; i < ports.size(); i++)
		painter->drawPoint(*ports[i]);

    return;
}

void LEShape::setState(State _state){
    state=_state;
    update();
}

/*bool LEShape::initLEFromFile(QString &path){
	bool flag;


	flag=le->initLEFromFile(path);
	return flag;
}*/
