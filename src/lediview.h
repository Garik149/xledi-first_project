#ifndef LEDIVIEW_H
#define LEDIVIEW_H

//#include "codeeditor.h"
#include "lediscene.h"
#include "logicelement.h"

#include <QGraphicsView>

class LEdiView : public QGraphicsView
{
    Q_OBJECT
public:
    LEdiView();
    explicit LEdiView(LEdiScene *scene, QWidget *parent = nullptr);
    ~LEdiView(){};

    LEdiScene* getSceneLE() {return sceneLE;};


    //enum Mode{MoveItem, InsertItem, InsertWire};
    //Mode myMode;
    //void setItemType(ItemLEdi::TypeItem type) { sceneLE->createItem(type);};

private:

    LEdiScene *sceneLE;
    //CodeEditor *editor;
    //QGraphicsItem *selectEditorItem;
    //ItemLEdi *currentItem;
    //QGraphicsLineItem *currentWire;
    //QPointF movePos{};
protected:
    //virtual void mousePressEvent(QMouseEvent *mouseEvent) override;
    //virtual void mouseDoubleClickEvent(QMouseEvent *mouseEvent) override;
    //virtual void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    //void mouseReleaseEvent(QMouseEvent *mouseEvent);
    //virtual void keyPressEvent(QKeyEvent *event) override;
    //virtual void wheelEvent(QWheelEvent *event) override;

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
