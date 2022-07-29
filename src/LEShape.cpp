#include "LEData.h"
#include "LEShape.h"
#include "PortData.h"

LEShape::LEShape(LEData* _le) : QGraphicsItem(){
    data =_le;
    data->shape=this;
	shownLabels = true;
    setPos(0,0);

    int h = qMax(data->inPorts.size(),data->outPorts.size());

    body = new QRectF(0, 0, 2*GRID_SZ, (h+1)*GRID_SZ);

    int ody=0, idy=0;
    for (int i=0; i < data->ports.size(); i++)
        if (data->ports[i]->isOutput){
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
	data->shape=NULL;
}


QRectF LEShape::boundingRect() const{
    return QRectF(-0.9*GRID_SZ,-0.9*GRID_SZ,3.8*GRID_SZ,body->height()+1.8*GRID_SZ);
}

void LEShape::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {

	if (shownLabels){
		painter->setPen(QPen(QColor(DARK_RED,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		painter->setFont(QFont("Calibri", 11, QFont::DemiBold));
        painter->drawText(QRectF(-0.9*GRID_SZ, -0.9*GRID_SZ, 3.8*GRID_SZ, 0.9*GRID_SZ),0,data->name);
        painter->drawText(QRectF(-0.9*GRID_SZ, body->height(), 3.8*GRID_SZ, 0.9*GRID_SZ),0,data->type);

		painter->setFont(QFont("Calibri", 8, QFont::DemiBold));
		for (int i=0; i < ports.size(); i++)
            painter->drawText(QRectF(ports[i]->x()+0.1*GRID_SZ, ports[i]->y()+0.1*GRID_SZ, 0.8*GRID_SZ, 0.8*GRID_SZ),0,data->ports[i]->name);
	}

	QPen pen(QColor(DARK_GREEN,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
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
	for (int i=0; i < ports.size(); i++) painter->drawPoint(*ports[i]);

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
