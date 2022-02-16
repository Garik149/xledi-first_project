#ifndef LEDIVIEW_H
#define LEDIVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include "defines.h"

class LEdiView : public QGraphicsView
{
    enum State {Default, DrawingWire, PlacingLE}; State state;
    QGraphicsLineItem* hLine;
    QPointF hPos1, hPos2; // - holded position
    QGraphicsRectItem* hRect;
    LEShape* hShape;
    LEdiScene *sceneLE;
    //CodeEditor *editor;
    //QGraphicsItem *selectEditorItem;

    QPoint btg(QPointF point); //BindedToGrid
    void reset();
    //void setItemType(ItemLEdi::TypeItem type) { sceneLE->createItem(type);};
protected:
    virtual void mousePressEvent(QMouseEvent *mouseEvent) override;
    //virtual void mouseDoubleClickEvent(QMouseEvent *mouseEvent) override;
    virtual void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    //void mouseReleaseEvent(QMouseEvent *mouseEvent);
    virtual void keyPressEvent(QKeyEvent *keyEvent) override;
    //virtual void wheelEvent(QWheelEvent *event) override;
public:
     LEdiView();
     explicit LEdiView(LEdiScene *scene, QWidget *parent = nullptr);
     ~LEdiView(){};

    Q_OBJECT
public slots:
    //void closeEditor();
    //void transferItem(ItemLEdi *item , QGraphicsLineItem *line);
    //void setMode(Mode mode) {myMode = mode;}
    //void deleteSelectItem(){sceneLE->deleteSelectItem();}
signals:
    //void mouseMove(QPointF mouseCoordinates);
    //void insertItem();
};

#endif // LEDIVIEW_H
