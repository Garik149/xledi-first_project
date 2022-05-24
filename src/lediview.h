#ifndef LEDIVIEW_H
#define LEDIVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include "defines.h"

class LEdiView : public QGraphicsView
{
    enum State {Default, DrawingWire, PlacingLE}; State state;
    LEdiScene* scene;
	//QGraphicsItem *selectEditorItem;

    QPoint hPos1, hPos2; // - holded position
	QGraphicsItem* hItem;
    WireSeg* hWireSeg;
	LEShape* hLE;
	PortShape* hPort;
	WireShape* hWire;
    float hScale;

	QMenu* contextMenu;
	QAction* act1;
	QAction* act2;
    //CodeEditor *editor;

    QPoint btg(QPointF point); //BindedToGrid
    void forgetHolded();
    //void setItemType(ItemLEdi::TypeItem type) { sceneLE->createItem(type);};
protected:
    void mousePressEvent(QMouseEvent *mouseEvent) override;
    //virtual void mouseDoubleClickEvent(QMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    //void mouseReleaseEvent(QMouseEvent *mouseEvent);
    void keyPressEvent(QKeyEvent *keyEvent) override;
    //virtual void wheelEvent(QWheelEvent *event) override;
public:
     LEdiView();
     explicit LEdiView(LEdiScene *scene, QWidget *parent = nullptr);
     ~LEdiView(){};

    Q_OBJECT
public slots:
     void slotOnCustomContextMenu(const QPoint&);
	 void slotAct1();
	 void slotAct2();
    //void closeEditor();
    //void transferItem(ItemLEdi *item , QGraphicsLineItem *line);
    //void deleteSelectItem(){sceneLE->deleteSelectItem();}
signals:
    //void mouseMove(QPointF mouseCoordinates);
    //void insertItem();
};

#endif // LEDIVIEW_H
