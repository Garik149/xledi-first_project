#ifndef LEDIVIEW_H
#define LEDIVIEW_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTreeWidget>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include "defines.h"

class LEdiView : public QGraphicsView{
private:
    State state;
    LEdiScene* scene;
	//QGraphicsItem *selectEditorItem;

	//LEData* mainLE;
    QPoint hPos1, hPos2; // - holded position
	QGraphicsItem* hItem;
    WireSeg* hWireSeg;
	LEShape* hLE;
	PortShape* hPort;
    float hScale;

	/*QMenu* contextMenu;
	QAction* drawWire;
	QAction* addLE;*/
    //CodeEditor *editor;


public:
	LEdiView();
	explicit LEdiView(LEdiScene *scene, QWidget *parent = nullptr);
	~LEdiView(){};
	void addLibraryTreeLE(QTreeWidgetItem* current, QTreeWidgetItem* previous);
	void reset();
protected:
	void mousePressEvent(QMouseEvent *mouseEvent) override;
	//virtual void mouseDoubleClickEvent(QMouseEvent *mouseEvent) override;
	void mouseMoveEvent(QMouseEvent *mouseEvent) override;
	//void mouseReleaseEvent(QMouseEvent *mouseEvent);
	void keyPressEvent(QKeyEvent *keyEvent) override;
	//virtual void wheelEvent(QWheelEvent *event) override;
private:
    QPoint btg(QPointF point); //BindedToGrid
    void forgetHolded();
    //void setItemType(ItemLEdi::TypeItem type) { sceneLE->createItem(type);};


    Q_OBJECT
public slots:
	//void slotOnCustomContextMenu(const QPoint&);
	void drawWire();
signals:
};

#endif // LEDIVIEW_H
