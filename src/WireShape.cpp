#include "WireShape.h"
#include "WireData.h"

//WireShape
WireShape::WireShape(WireData* _wire, LEdiScene* _scene){
	_wire->shape=this;
    scene=_scene;
	data=_wire;
}

WireShape::~WireShape(){
    erase();
}

void WireShape::erase(){
	data->shape=NULL;
    for (int i=0; i<seg.size(); i++) delete(seg[i]);
    seg.clear();
    for (int i=0; i<nodes.size(); i++) delete(nodes[i]);
    nodes.clear();
}

void WireShape::addNode(QPointF _point){
    QGraphicsEllipseItem* hEllipse= new QGraphicsEllipseItem(_point.x()-3,_point.y()-3,6,6);
    hEllipse->setPen(QPen(QColor(BLUE,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    hEllipse->setBrush(QBrush(QColor(BLUE,255)));
    nodes.append(hEllipse);
    scene->addItem(hEllipse);
	hEllipse->hide();
}

WireSeg* WireShape::addSeg(QLineF line){
    WireSeg* hWireSeg=new WireSeg(this, QLineF(qMin(line.x1(),line.x2()),qMin(line.y1(),line.y2()),qMax(line.x1(),line.x2()),qMax(line.y1(),line.y2())));
	hWireSeg->setPen(QPen(QColor(WHITE,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    seg.append(hWireSeg);
    scene->addItem(hWireSeg);
    return hWireSeg;
}


//WireSeg
WireSeg::WireSeg(WireShape* _shape, QLineF _line) : QGraphicsLineItem(_line){
	whole=_shape;
	setPos(0,0);

	setState(Default);
}

void WireSeg::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {

    QPen hPen = pen();
    switch(state){
	default:
        break;

	case State::Bolded:
        hPen.setWidth(hPen.width()+1);
        break;

	case State::Moved:
        hPen.setColor(QColor(hPen.color().red(),hPen.color().green(),hPen.color().blue(),128));
        break;
	}

    painter->setPen(hPen);
	painter->drawLine(line());

	return;
}

void WireSeg::setState(State _state){
	state=_state;
	update();
}

void WireSeg::shiftLeft(){
    /*QLineF segLine = line();
    for (int i=0; i<whole->seg.size(); i++){
        WireSeg* seg = whole->seg[i];
        if (segLine.p1() == seg->line().p1()){
            seg->line().setP1(segLine.p1());
        }
        if (segLine.p2() == seg->line().p2()){
            seg->line().setP1(segLine.p2());
        }
    }*/
}
