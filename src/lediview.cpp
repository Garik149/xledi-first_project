#include "lediview.h"
#include "lediscene.h"
#include "logicelement.h"
#include "leshape.h"
#include "portshape.h"
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

        connect(act1,	SIGNAL(triggered()), SLOT(slotAct1()));
        connect(act2,	SIGNAL(triggered()), SLOT(slotAct2()));
    }

    hPos1 = QPoint(0,0); hPos2 = QPoint(0,0);
    hLine = NULL;
    hRect = NULL;
    hLEShape = NULL;
    hPortShape = NULL;
    state = Default;
    setMouseTracking(true);
    //setDragMode(QGraphicsView::RubberBandDrag);
    //connect(sceneLE, &LEdiScene::tranferItem, this, &ViewLEdi::transferItem);
}

void LEdiView::slotOnCustomContextMenu(const QPoint&){}
void LEdiView::slotAct1(){
    hLine = new QGraphicsLineItem();
    hLine->setPen(QPen(QColor(255,0,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    sceneLE->addItem(hLine);
    state = DrawingWire;
}
void LEdiView::slotAct2(){
	hLEShape = new LEShape(new LogicElement("al_ao21","U1"));
    hLEShape->setState(LEShape::State::Moved);
    sceneLE->addItem(hLEShape);
    state = PlacingLE;
}


QPoint LEdiView::btg(QPointF point){
    return {qRound(point.x()/GRID_SZ)*GRID_SZ,qRound(point.y()/GRID_SZ)*GRID_SZ};
}

void LEdiView::forgetHolded(){
    if (hLine!=NULL) {hLine = NULL;}
    if (hRect!=NULL) {hRect = NULL;}
    if (hLEShape!=NULL) {hLEShape->setState(LEShape::State::Default); hLEShape = NULL;}
    if (hPortShape!=NULL) {hPortShape->setState(PortShape::State::Default); hPortShape = NULL;}
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
                    hLEShape = (LEShape*)hItem;
                    hLEShape->setState(LEShape::State::Bolded);
                    break;

                case 1:
                    hPortShape = (PortShape*)hItem;
                    hPortShape->setState(PortShape::State::Bolded);
                    break;

                case 2:
                    hWireShape = (WireShape*)hItem;
                    hWireShape->setState(WireShape::State::Bolded);
                    break;
                }
            break;

        case DrawingWire:
            hLine->setPen(QPen(QColor(255,0,0,255), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            hPos1=hPos2;
			hLine = new QGraphicsLineItem();
            hLine->setPen(QPen(QColor(255,0,0,128), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            sceneLE->addItem(hLine);
            break;

        case PlacingLE:
            forgetHolded();
			hLEShape = new LEShape(new LogicElement("al_ao21","U1"));
            hLEShape->setState(LEShape::State::Moved);
            sceneLE->addItem(hLEShape);
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
            delete(hLine); hLine=NULL;
            state = Default;
            break;

        case PlacingLE:
            delete(hLEShape); hLEShape=NULL;
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
        hLEShape->setPos(hPos2);
        break;
    }
}

void LEdiView::keyPressEvent(QKeyEvent *keyEvent){
    switch (keyEvent->key()){
    default:
        break;
    }
}
