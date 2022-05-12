#include "leshape.h"
#include "logicelement.h"
//#include "wire.h"
#include "port.h"

LEShape::LEShape(LogicElement* _le) : QGraphicsItem(){
    le=_le;
	le->shape=this;
    setPos(0,0);

    int h = qMax(le->inPorts.size(),le->outPorts.size());

    body = new QRectF(0, 0, 2*GRID_SZ, (h+1)*GRID_SZ);

    int ody=0, idy=0;
    for (int i=0; i < le->ports.size(); i++)
        if (le->ports[i]->isOutput){
            ody += GRID_SZ;
			ports.append(new QLineF(QPoint(2*GRID_SZ,ody),QPoint(3*GRID_SZ,ody)));
        }
        else{
            idy += GRID_SZ;
			ports.append(new QLineF(QPoint(-1*GRID_SZ,idy),QPoint(0,idy)));
        }

    setState(Default);
}

LEShape::~LEShape(){
	delete(body);
	for (int i=0; i<ports.size(); i++)
		delete(ports[i]);
}


QRectF LEShape::boundingRect() const{
    return QRectF(-1*GRID_SZ,-1*GRID_SZ,4*GRID_SZ,body->height()+2*GRID_SZ);
}

void LEShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->setPen(QPen(QColor(255,0,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setFont(QFont("Calibri", 11, QFont::DemiBold));
    painter->drawText(QRectF(-1*GRID_SZ, -1*GRID_SZ, 4*GRID_SZ, 1*GRID_SZ),0,le->name);
    painter->drawText(QRectF(-1*GRID_SZ, body->height(), 4*GRID_SZ, 1*GRID_SZ),0,le->type);

    painter->setFont(QFont("Calibri", 8, QFont::DemiBold));
    for (int i=0; i < ports.size(); i++)
        painter->drawText(QRectF(ports[i]->p1().x()+0.25*GRID_SZ, ports[i]->p1().y(), 0.5*GRID_SZ, 1*GRID_SZ),0,le->ports[i]->name);


    switch(state){
    default:
        painter->setPen(QPen(QColor(0,255,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;

    case State::Bolded:
        painter->setPen(QPen(QColor(0,255,0,255), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;

    case State::Moved:
        painter->setPen(QPen(QColor(0,255,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        break;
    }
    painter->drawRect(*body);
    for (int i=0; i < ports.size(); i++)
        painter->drawLine(*ports[i]);

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
