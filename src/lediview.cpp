#include "lediview.h"
#include "lediscene.h"
#include "logicelement.h"
#include "leshape.h"
#include "portshape.h"
#include "wire.h"
#include "wireshape.h"

LEdiView::LEdiView(LEdiScene *scene, QWidget *parent) : QGraphicsView(scene, parent){
	sceneLE = scene;
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
	sceneLE->addItem(hWire);
    state = DrawingWire;
}
void LEdiView::slotAct2(){
	hLE = new LEShape(new LogicElement("al_ao21","U1"));
	hLE->setState(LEShape::State::Moved);
	sceneLE->addItem(hLE);
    state = PlacingLE;
}


QPoint LEdiView::btg(QPointF point){
    return {qRound(point.x()/GRID_SZ)*GRID_SZ,qRound(point.y()/GRID_SZ)*GRID_SZ};
}

void LEdiView::forgetHolded(){
	if (hWire!=NULL) {hWire = NULL;}
    if (hRect!=NULL) {hRect = NULL;}
	if (hLE!=NULL) {hLE->setState(LEShape::State::Default); hLE = NULL;}
	if (hPort!=NULL) {hPort->setState(PortShape::State::Default); hPort = NULL;}
}

void LEdiView::mousePressEvent(QMouseEvent *mouseEvent){
    hPos1=btg(mapToScene(mouseEvent->pos()));
    switch (mouseEvent->button()){
    default:
        break;

    case Qt::LeftButton:
        switch (state){
		default:
            forgetHolded();
            hItem = sceneLE->itemAt(mouseEvent->pos(),transform());
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
			sceneLE->addItem(hWire);
            break;

        case PlacingLE:
            forgetHolded();
			hLE = new LEShape(new LogicElement("al_ao21","U1"));
			hLE->setState(LEShape::State::Moved);
			sceneLE->addItem(hLE);
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

void LEdiView::mouseMoveEvent(QMouseEvent *mouseEvent){
    hPos2=btg(mapToScene(mouseEvent->pos()));
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

void LEdiView::keyPressEvent(QKeyEvent *keyEvent){
    switch (keyEvent->key()){
    default:
        break;

	case Qt::Key_Minus:
		hScale*=0.8;
		scale(0.8,0.8);
		break;

	case Qt::Key_Equal:
		hScale*=1.25;
		scale(1.25,1.25);
		break;
    }
}
