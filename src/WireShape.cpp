#include "WireShape.h"
#include "WireData.h"

//WireShape
WireShape::WireShape(WireData* _wire, LEdiScene* _scene){
	_wire->shape=this;
    scene=_scene;
	data=_wire;
}

WireShape::~WireShape(){
    for (int i=0; i<seg.size(); i++) delete(seg[i]);
    for (int i=0; i<nodes.size(); i++) delete(nodes[i]);
}

WireSeg* WireShape::addSeg(QLineF line){
    WireSeg* hWireSeg=new WireSeg(this, QLineF(qMin(line.x1(),line.x2()),qMin(line.y1(),line.y2()),qMax(line.x1(),line.x2()),qMax(line.y1(),line.y2())));
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

    QPen pen(QPen(QColor(BLUE,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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
	painter->drawLine(line());

	return;
}

void WireSeg::setState(State _state){
	state=_state;
	update();
}

void WireSeg::shiftLeft(){
    QLineF segLine = line();
    for (int i=0; i<whole->seg.size(); i++){
        WireSeg* seg = whole->seg[i];
        if (segLine.p1() == seg->line().p1()){
            seg->line().setP1(segLine.p1());
        }
        if (segLine.p2() == seg->line().p2()){
            seg->line().setP1(segLine.p2());
        }
    }
}
