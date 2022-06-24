#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
//#include <QTabWidget>
#include <QGraphicsView>
#include "defines.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
     ~MainWindow() {};

private slots:
    void slotNewFile();
    void slotOpenFile();
    void slotSaveFile();
    void slotQuit();
	void slotChooseLibrary();

private:
	void initActions();
	void createScene();
	void createMenu();
	void createToolBar();
	void createStatusBar();
	void createLibraryWidget();

	//void createToolBox();
    //void buttonGroupClicked(QAbstractButton *button);
    //void pointerGroupCliced();
    //void insertItem();
    //void currentChangedTab(int indexTab);
	//void tabCloseRequested(int indexTab);

    QAction* newFileAction;
    QAction* openFileAction;
    QAction* saveFileAction;
    QAction* quitAction;

    //QPixmap createImage(ItemLEdi::TypeItem type);
    //QWidget *createCellWidget(const QString &text, ItemLEdi::TypeItem type);
    //QToolBox *toolBox;
    //QAction *deleteAction;
    //QToolBar *pointerToolBar;
    //QTabWidget *tabWidget;
    //QButtonGroup *buttonGroup;
    //QButtonGroup *pointerTypeGroup;

    //QList <ViewLEdi*> tabList{};

	QMenu* fileMenu;
	QToolBar* toolBar;
	QStatusBar* statusBar;
    QTextEdit* textEditor;
    LEdiScene* scene;
    LEdiView* view;

    Locale* msg;
    LEData* mainLE;
};
#endif // MAINWINDOW_H
