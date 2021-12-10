#include "lediview.h"

LEdiView::LEdiView(LEdiScene *scene, QWidget *parent) : QGraphicsView(scene, parent), sceneLE(scene)
{
    //editor = nullptr;
    //currentItem = nullptr;
    //currentWire = nullptr;
    //selectEditorItem = nullptr;
    //setMouseTracking(true);
    //myMode = MoveItem;
    //setDragMode(QGraphicsView::RubberBandDrag);
    //connect(sceneLE, &LEdiScene::tranferItem, this, &ViewLEdi::transferItem);
}
