#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QGraphicsView>
#include "defines.h"

class MainWindow : public QMainWindow{
private:
	QAction* saveSchemeAction;
	QAction* loadSchemeAction;
	QAction* quitAction;

    QAction* addRAction;
    QAction* addNPNAction;
    QAction* addCSAction;

	LEdiScene* scene;
    LEdiView* view;

	LEData* mainLE;


public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow() {};

private:
	void initActions();
	void createScene();
    void createMenu();


Q_OBJECT
private slots:
    void slotLoadScheme();
    void slotSaveScheme();
	void slotQuit();

    void slotAddR();
    void slotAddNPN();
    void slotAddCS();
};
#endif // MAINWINDOW_H
