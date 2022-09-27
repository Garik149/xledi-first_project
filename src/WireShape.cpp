#include "WireData.h"
#include "WireShape.h"

//WireShape
WireShape::WireShape(WireData* _wire, LEdiScene* _scene){
	_wire->shape=this;
    scene=_scene;
	data=_wire;

    setState(Default);
}

WireShape::~WireShape(){
    erase();
	data->shape=NULL;
}

void WireShape::erase(){
	for (int i=0; i<seg.size(); i++) delete(seg[i]);
	for (int i=0; i<nodes.size(); i++) delete(nodes[i]);
}

void WireShape::addNode(QPointF _point){
    WireNode* hWireNode= new WireNode(this, _point);
    scene->addItem(hWireNode);
}

WireSeg* WireShape::addSeg(QLineF line){
    WireSeg* hWireSeg=new WireSeg(this, QLineF(qMin(line.x1(),line.x2()),qMin(line.y1(),line.y2()),qMax(line.x1(),line.x2()),qMax(line.y1(),line.y2())));
	scene->addItem(hWireSeg);
    return hWireSeg;
}

void WireShape::setState(State _state){
    state=_state;
    for (int i=0; i<seg.size(); i++)
		seg[i]->update();
}


//WireSeg
WireSeg::WireSeg(WireShape* _shape, QLineF _line) : QGraphicsLineItem(_line){
	whole=_shape;
	whole->seg.append(this);
}

WireSeg::~WireSeg() {
	whole->seg.removeAll(this);
}

void WireSeg::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {

	QPen hPen(QColor(LIGHT_BLUE,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    switch(whole->state){
    default:
        break;

	case State::Bolded:
        hPen.setWidth(hPen.width()+1);
		hPen.setColor(QColor(BLUE));
        break;

	case State::Moved:
        hPen.setColor(QColor(hPen.color().red(),hPen.color().green(),hPen.color().blue(),128));
        break;
	}

    painter->setPen(hPen);
    painter->drawLine(line());

	return;
}

void WireSeg::shiftHrz(int shift){
    QLineF _line = line();
    for (int i=0; i<whole->seg.size(); i++){
        WireSeg* seg = whole->seg[i];
        if ((seg->line().p1() == _line.p1())||(seg->line().p1() == _line.p2())){
            seg->setLine(seg->line().x1()+shift,seg->line().y1(),seg->line().x2(),seg->line().y2());
        }
        if ((seg->line().p2() == _line.p1())||(seg->line().p2() == _line.p2())){
            seg->setLine(seg->line().x1(),seg->line().y1(),seg->line().x2()+shift,seg->line().y2());
        }
    }
}

void WireSeg::shiftVrt(int shift){
    QLineF _line = line();
    for (int i=0; i<whole->seg.size(); i++){
        WireSeg* seg = whole->seg[i];
        if ((seg->line().p1() == _line.p1())||(seg->line().p1() == _line.p2())){
            seg->setLine(seg->line().x1(),seg->line().y1()+shift,seg->line().x2(),seg->line().y2());
        }
        if ((seg->line().p2() == _line.p1())||(seg->line().p2() == _line.p2())){
            seg->setLine(seg->line().x1(),seg->line().y1(),seg->line().x2(),seg->line().y2()+shift);
        }
    }
}


//WireNode
WireNode::WireNode(WireShape* _shape, QPointF _point) : QGraphicsItem(){
    whole=_shape;
	whole->nodes.append(this);
    setPos(_point);
}

WireNode::~WireNode(){
	whole->nodes.removeAll(this);
}

QRectF WireNode::boundingRect() const{
    return QRectF(-10,-10,20,20);
}

void WireNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {

	QPen hPen(QColor(LIGHT_BLUE,255), 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    switch(whole->state){
    default:
        break;

    case State::Bolded:
        hPen.setWidth(hPen.width()+2);
		hPen.setColor(QColor(BLUE));
        break;

    case State::Moved:
        hPen.setColor(QColor(hPen.color().red(),hPen.color().green(),hPen.color().blue(),128));
        break;
    }

    painter->setPen(hPen);
    painter->drawPoint(0,0);

    return;
}
