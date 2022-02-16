#include "lediview.h"
#include "lediscene.h"
#include "logicelement.h"
#include "leshape.h"

LEdiView::LEdiView(LEdiScene *scene, QWidget *parent) : QGraphicsView(scene, parent), sceneLE(scene){
    reset();
    //setDragMode(QGraphicsView::RubberBandDrag);
    //connect(sceneLE, &LEdiScene::tranferItem, this, &ViewLEdi::transferItem);
}

QPoint LEdiView::btg(QPointF point){
    return {qRound(point.x()/GRID_SZ)*GRID_SZ,qRound(point.y()/GRID_SZ)*GRID_SZ};
}

void LEdiView::reset(){
//    if (hLine != nullptr) {delete(hLine); hLine = nullptr;}
//    if (hRect != nullptr) {delete(hRect); hRect = nullptr;}
    hPos1 = QPointF(0,0); hPos2 = QPointF(0,0);
    state = Default;
    setMouseTracking(true);
}

void LEdiView::mousePressEvent(QMouseEvent *mouseEvent){
    switch (mouseEvent->button()){
    default:
        break;

    case Qt::LeftButton:
        switch (state){
        default:
            hPos1 = btg(mapToScene(mouseEvent->pos()));
            hLine = new QGraphicsLineItem();
            hLine->setPen(QPen(QColor(130,0,0), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            sceneLE->addItem(hLine);
            state = DrawingWire;
            break;

        case DrawingWire:
            hLine->setPen(QPen(QColor(255,0,0), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            hPos1=hPos2;
            hPos2 = btg(mapToScene(mouseEvent->pos()));
            hLine = new QGraphicsLineItem();
            hLine->setPen(QPen(QColor(130,0,0), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            sceneLE->addItem(hLine);
            break;

        case PlacingLE:
            hRect->setPen(QPen(QColor(0,255,0), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            hRect = new QGraphicsRectItem();
            hRect->setPen(QPen(QColor(0,130,0), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            sceneLE->addItem(hRect);
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
            delete(hRect);
            state = Default;
            break;
        }
        break;
    }
}

void LEdiView::mouseMoveEvent(QMouseEvent *mouseEvent){
    switch (state){
    default:
        hPos1 = btg(mapToScene(mouseEvent->pos()));
        break;

    case DrawingWire:
        hPos2 = btg(mapToScene(mouseEvent->pos()));
        if (abs(hPos2.x()-hPos1.x()) < abs(hPos2.y()-hPos1.y())) hPos2.rx()=hPos1.x();
            else hPos2.ry()=hPos1.y();
        hLine->setLine(QLineF(hPos1,hPos2));
        break;

    case PlacingLE:
        hPos1 = btg(mapToScene(mouseEvent->pos()));
        hRect->setRect(QRectF(hPos1.x()-20,hPos1.y()-30,40,60));
        break;
    }
}

void LEdiView::keyPressEvent(QKeyEvent *keyEvent){
    switch (keyEvent->key()){
    default:
        break;

    //case Qt::Key_L:
    //    switch (state){
    //    default:
    //        LogicElement;
    //        hShape = new LEShape();
    //        sceneLE->addShape(hShape);
    //        state = PlacingLE;
    //        break;
    //
    //    case DrawingWire:
    //        delete(hLine);
    //        hRect = new QGraphicsRectItem();
    //        sceneLE->addItem(hRect);
    //        state = PlacingLE;
    //        break;
    //
    //    case PlacingLE:
    //        delete(hRect);
    //        state = Default;
    //        break;
    //    }
    //    break;
    }
}