#include "lediview.h"
#include "lediscene.h"
#include "logicelement.h"
#include "leshape.h"

LEdiView::LEdiView(LEdiScene *scene, QWidget *parent) : QGraphicsView(scene, parent), sceneLE(scene){
	{
		setContextMenuPolicy(Qt::CustomContextMenu);

		contextMenu = new QMenu(this);

		act1 = new QAction("Draw wire", this);
		act2 = new QAction("Place logic element", this);

		contextMenu->addAction(act1);
		contextMenu->addAction(act2);

		connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slotOnCustomContextMenu(const QPoint&)));

		connect(act1,	SIGNAL(triggered()), SLOT(slotAct1()));
		connect(act2,	SIGNAL(triggered()), SLOT(slotAct2()));
	}

	reset();
    //setDragMode(QGraphicsView::RubberBandDrag);
    //connect(sceneLE, &LEdiScene::tranferItem, this, &ViewLEdi::transferItem);
}

void LEdiView::slotAct1(){
	hLine = new QGraphicsLineItem();
	hLine->setPen(QPen(QColor(255,0,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	sceneLE->addItem(hLine);
	state = DrawingWire;
}
void LEdiView::slotAct2(){
	hShape = new LEShape("al_ao21","U1");
	sceneLE->addShape(hShape);
	state = PlacingLE;
}


QPoint LEdiView::btg(QPointF point){
    return {qRound(point.x()/GRID_SZ)*GRID_SZ,qRound(point.y()/GRID_SZ)*GRID_SZ};
}

void LEdiView::reset(){
//    if (hLine != nullptr) {delete(hLine); hLine = nullptr;}
//    if (hRect != nullptr) {delete(hRect); hRect = nullptr;}
	hPos1 = QPoint(0,0); hPos2 = QPoint(0,0);
    state = Default;
    setMouseTracking(true);
}

void LEdiView::mousePressEvent(QMouseEvent *mouseEvent){
	hPos1=btg(mapToScene(mouseEvent->pos()));
    switch (mouseEvent->button()){
    default:
        break;

    case Qt::LeftButton:
        switch (state){
		default:
            break;

        case DrawingWire:
			hLine->setPen(QPen(QColor(255,0,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            hLine = new QGraphicsLineItem();
			hLine->setPen(QPen(QColor(255,0,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            sceneLE->addItem(hLine);
            break;

        case PlacingLE:
			hShape->setState(LEShape::State::Default);
			hShape = new LEShape("al_ao21","U1");
			sceneLE->addShape(hShape);
            break;
        }
        break;

    case Qt::RightButton:
        switch (state){
        default:
            break;

        case DrawingWire:
			delete(hLine);
            state = Default;
            break;

        case PlacingLE:
			delete(hShape);
            state = Default;
            break;
        }
        break;
    }
}

void LEdiView::mouseMoveEvent(QMouseEvent *mouseEvent){
	hPos2=btg(mapToScene(mouseEvent->pos()));
    switch (state){
	default:
        break;

	case DrawingWire:
        if (abs(hPos2.x()-hPos1.x()) < abs(hPos2.y()-hPos1.y())) hPos2.rx()=hPos1.x();
            else hPos2.ry()=hPos1.y();
		hLine->setLine(QLine(hPos2,hPos1));
        break;

    case PlacingLE:
		hShape->moveTo(hPos1);
        break;
    }
}

void LEdiView::keyPressEvent(QKeyEvent *keyEvent){
    switch (keyEvent->key()){
    default:
		break;
    }
}
