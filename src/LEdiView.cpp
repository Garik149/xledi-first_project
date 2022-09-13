#include "LEdiView.h"
#include "LEdiScene.h"
#include "LEData.h"
#include "LEShape.h"
#include "PortShape.h"
#include "WireData.h"
#include "WireShape.h"

LEdiView::LEdiView(LEdiScene *_scene, QWidget *_parent) : QGraphicsView(_scene, _parent){
    scene = _scene;
	/*{
        setContextMenuPolicy(Qt::CustomContextMenu);

		contextMenu = new QMenu(this);

		act1 = new QAction("Draw wire", this);
		act2 = new QAction("Place logic element", this);

        contextMenu->addAction(act1);
		contextMenu->addAction(act2);

		connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(slotOnCustomContextMenu(const QPoint&)));

		connect(act1, SIGNAL(triggered()), SLOT(slotAct1()));
		connect(act2, SIGNAL(triggered()), SLOT(slotAct2()));
	}*/

	reset();
}

void LEdiView::reset(){

	hPos1 = QPoint(0,0); hPos2 = QPoint(0,0);
	//hWire = NULL;
	//mainLE = NULL;
	hLE = NULL;
	hPort = NULL;
	hWireSeg = NULL;
	hScale = 1;
	state = Default;
	setMouseTracking(true);
}

//void LEdiView::slotOnCustomContextMenu(const QPoint&){}

void LEdiView::drawWire(){
	forgetHolded();
	WireShape* hWire = new WireShape(new WireData("neWire"),scene);
    hWireSeg = hWire->addSeg(QLineF());
    hWire->setState(Moved);
    state = DrawingWire;
}

void LEdiView::addLibraryTreeLE(QTreeWidgetItem* current, QTreeWidgetItem*){
	forgetHolded();
	hLE = new LEShape(new LEData(current->text(0),"newLE"));
	hLE->setState(Moved);
	scene->addItem(hLE);
	state = PlacingLE;
}

QPoint LEdiView::btg(QPointF _point){
    return {qRound(_point.x()/GRID_SZ)*GRID_SZ,qRound(_point.y()/GRID_SZ)*GRID_SZ};
}

void LEdiView::forgetHolded(){
	if (hLE!=NULL){
		if (hLE->state == Moved) DELETE(hLE)
		else {hLE->setState(Default); hLE = NULL;}
	}
	if (hPort!=NULL){
		//if (hPort->state == Moved) DELETE(hPort)
		{hPort->setState(Default); hPort = NULL;}
	}
	if (hWireSeg!=NULL){
		if (hWireSeg->whole->state == Moved){
			hWireSeg->whole->setState(Default);
			delete(hWireSeg);
		}
		else
			hWireSeg->whole->setState(Default);
		hWireSeg = NULL;
	}
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
                    hLE->setState(Bolded);
                    break;

                case 1:
					hPort = (PortShape*)hItem;
                    hPort->setState(Bolded);
                    break;

                case 2:
                    hWireSeg = (WireSeg*)hItem;
                    hWireSeg->whole->setState(Bolded);
                    break;
                }
            break;

		case DrawingWire:
			hPos1=hPos2;
			hWireSeg = hWireSeg->whole->addSeg(QLineF());
			//hWire->setState(Moved);
            break;

        case PlacingLE:
			hLE->setState(Default);
			hLE = new LEShape(hLE->data);
            hLE->setState(Moved);
            scene->addItem(hLE);
            break;
        }
        break;

    case Qt::RightButton:
        switch (state){
        default:
            forgetHolded();
			drawWire();
            break;

		case DrawingWire:
			forgetHolded();
            state = Default;
            break;

		case PlacingLE:
			forgetHolded();
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
        hWireSeg->setLine(QLine(hPos2,hPos1));
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
        if (hScale > 0.2){
            hScale*=0.8;
            scale(0.8,0.8);
            scene->scaleUpdate(hScale);
        }
		break;

	case Qt::Key_Equal:
        if (hScale < 5){
            hScale*=1.25;
            scale(1.25,1.25);
            scene->scaleUpdate(hScale);
        }
        break;

	case Qt::Key_T:
		break;
    }
}
