#include "lediview.h"
#include "lediscene.h"
#include "logicelement.h"
#include "leshape.h"
#include "portshape.h"
#include "wire.h"
#include "wireshape.h"

LEdiView::LEdiView(LEdiScene *_scene, QWidget *_parent) : QGraphicsView(_scene, _parent){
    scene = _scene;
	{
        setContextMenuPolicy(Qt::CustomContextMenu);

        contextMenu = new QMenu(this);

        act1 = new QAction("Draw wire", this);
        act2 = new QAction("Place logic element", this);

        contextMenu->addAction(act1);
        contextMenu->addAction(act2);

		connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slotOnCustomContextMenu(const QPoint&)));

		connect(act1, SIGNAL(triggered()), SLOT(slotAct1()));
		connect(act2, SIGNAL(triggered()), SLOT(slotAct2()));
    }

    hPos1 = QPoint(0,0); hPos2 = QPoint(0,0);
	hWire = NULL;
    hRect = NULL;
	hLE = NULL;
	hPort = NULL;
	hScale = 1;
    state = Default;
    setMouseTracking(true);
    //setDragMode(QGraphicsView::RubberBandDrag);
    //connect(sceneLE, &LEdiScene::tranferItem, this, &ViewLEdi::transferItem);
}

void LEdiView::slotOnCustomContextMenu(const QPoint&){}
void LEdiView::slotAct1(){
	hWire = new WireShape(new Wire());
	hWire->setPen(QPen(QColor(255,0,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    scene->addItem(hWire);
    state = DrawingWire;
}
void LEdiView::slotAct2(){
	hLE = new LEShape(new LogicElement("al_ao21","U1"));
	hLE->setState(LEShape::State::Moved);
    scene->addItem(hLE);
    state = PlacingLE;
}


QPoint LEdiView::btg(QPointF _point){
    return {qRound(_point.x()/GRID_SZ)*GRID_SZ,qRound(_point.y()/GRID_SZ)*GRID_SZ};
}

void LEdiView::forgetHolded(){
    if (hRect!=NULL) {hRect = NULL;}
	if (hLE!=NULL) {hLE->setState(LEShape::State::Default); hLE = NULL;}
	if (hPort!=NULL) {hPort->setState(PortShape::State::Default); hPort = NULL;}
    if (hWire!=NULL) {hWire->setState(WireShape::State::Default); hWire = NULL;}
}

void LEdiView::mousePressEvent(QMouseEvent *_mouseEvent){
    hPos1=btg(mapToScene(_mouseEvent->pos()));
    switch (_mouseEvent->button()){
    default:
        break;

    case Qt::LeftButton:
        switch (state){
		default:
            forgetHolded();
            hItem = scene->itemAt(mapToScene(_mouseEvent->pos()),QTransform());
            if (hItem!=NULL)
                switch(hItem->type()-QGraphicsItem::UserType){
                default:
                    break;

                case 0:
					hLE = (LEShape*)hItem;
					hLE->setState(LEShape::State::Bolded);
                    break;

                case 1:
					hPort = (PortShape*)hItem;
					hPort->setState(PortShape::State::Bolded);
                    break;

                case 2:
					hWire = (WireShape*)hItem;
					hWire->setState(WireShape::State::Bolded);
                    break;
                }
            break;

        case DrawingWire:
			hWire->setPen(QPen(QColor(255,0,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            hPos1=hPos2;
			hWire = new WireShape(new Wire());
			hWire->setPen(QPen(QColor(255,0,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            scene->addItem(hWire);
            break;

        case PlacingLE:
            forgetHolded();
			hLE = new LEShape(new LogicElement("al_ao21","U1"));
			hLE->setState(LEShape::State::Moved);
            scene->addItem(hLE);
            break;
        }
        break;

    case Qt::RightButton:
        switch (state){
        default:
            forgetHolded();
            contextMenu->exec(QCursor::pos());
            break;

        case DrawingWire:
			delete(hWire); hWire=NULL;
            state = Default;
            break;

        case PlacingLE:
			delete(hLE); hLE=NULL;
            state = Default;
            break;
        }
        break;
    }
}

void LEdiView::mouseMoveEvent(QMouseEvent *_mouseEvent){
    hPos2=btg(mapToScene(_mouseEvent->pos()));
    switch (state){
    default:
        break;

    case DrawingWire:
        if (abs(hPos2.x()-hPos1.x()) < abs(hPos2.y()-hPos1.y())) hPos2.rx()=hPos1.x();
            else hPos2.ry()=hPos1.y();
		hWire->setLine(QLine(hPos2,hPos1));
        break;

    case PlacingLE:
		hLE->setPos(hPos2);
        break;
    }
}

void LEdiView::keyPressEvent(QKeyEvent *_keyEvent){
    switch (_keyEvent->key()){
    default:
        break;

	case Qt::Key_Minus:
        if (hScale > 0.5){
            hScale*=0.8;
            scale(0.8,0.8);
            scene->scaleUpdate(hScale);
        }
		break;

	case Qt::Key_Equal:
        if (hScale < 2){
            hScale*=1.25;
            scale(1.25,1.25);
            scene->scaleUpdate(hScale);
        }
        break;
    }
}
