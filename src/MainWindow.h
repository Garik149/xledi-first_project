#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
//#include <QTabWidget>
#include <QGraphicsView>
#include "defines.h"

class MainWindow : public QMainWindow{
private:
	QAction* newSchemeAction;
	QAction* loadLibraryAction;
	QAction* synthSchemeAction;
	QAction* saveSchemeAction;
	QAction* loadSchemeAction;
	QAction* quitAction;

	QMenu* fileMenu;
	QToolBar* toolBar;
	QStatusBar* statusBar;
	QTextEdit* textEditor;
	LEdiScene* scene;
	LEdiView* view;

	Locale* msg;
	LEData* mainLE;


public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow() {};

private:
	void initActions();
	void createScene();
	void createMenu();
	void createToolBar();
	void createStatusBar();
	void createLibraryWidget();
	void startWorkInAThread();


Q_OBJECT
private slots:
	void handleResults(const QString &s) {};

	//void slotChangeColorMap();
	void slotNewScheme();
	void slotLoadLibrary();
	void slotSynthScheme();
	void slotSaveScheme();
	void slotLoadScheme();
	void slotQuit();
};
#endif // MAINWINDOW_H
