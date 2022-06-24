#include "WireShape.h"
#include "WireData.h"

//WireShape
WireShape::WireShape(WireData* _wire, LEdiScene* _scene){
	_wire->shape=this;
    scene=_scene;
	data=_wire;

    setState(Default);
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
    WireNode* hWireNode= new WireNode(this, _point);
    nodes.append(hWireNode);
    scene->addItem(hWireNode);
}

WireSeg* WireShape::addSeg(QLineF line){
    WireSeg* hWireSeg=new WireSeg(this, QLineF(qMin(line.x1(),line.x2()),qMin(line.y1(),line.y2()),qMax(line.x1(),line.x2()),qMax(line.y1(),line.y2())));
    seg.append(hWireSeg);
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
    setPos(0,0);
}

void WireSeg::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {

	QPen hPen(QColor(BLUE,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    switch(whole->state){
    default:
        break;

	case State::Bolded:
        hPen.setWidth(hPen.width()+1);
        hPen.setColor(QColor(LIGHT_BLUE));
        break;

	case State::Moved:
        hPen.setColor(QColor(hPen.color().red(),hPen.color().green(),hPen.color().blue(),128));
        break;
	}

    painter->setPen(hPen);
    painter->drawLine(line());

	return;
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

//WireNode
WireNode::WireNode(WireShape* _shape, QPointF _point) : QGraphicsItem(){
    whole=_shape;
    setPos(_point);
}

QRectF WireNode::boundingRect() const{
    return QRectF(-10,-10,20,20);
}

void WireNode::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {

    QPen hPen(QColor(BLUE,255), 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    switch(whole->state){
    default:
        break;

    case State::Bolded:
        hPen.setWidth(hPen.width()+2);
        hPen.setColor(QColor(LIGHT_BLUE));
        break;

    case State::Moved:
        hPen.setColor(QColor(hPen.color().red(),hPen.color().green(),hPen.color().blue(),128));
        break;
    }

    painter->setPen(hPen);
    painter->drawPoint(0,0);

    return;
}
