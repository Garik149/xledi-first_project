#include <QTextStream>
#include "MainWindow.h"
#include "Locale.h"
#include "LEdiScene.h"
#include "LEdiView.h"
#include "LEData.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, true);
    mainLE = NULL;

	initActions();
    resize(1200,700);
    createScene();
    createMenu();
}

void MainWindow::initActions(){
    saveSchemeAction = new QAction(QIcon{":/images/Save.png"}, "&Save As...", this);
	saveSchemeAction->setShortcut(tr("CTRL+S"));
	connect(saveSchemeAction, &QAction::triggered, this, &MainWindow::slotSaveScheme);

    loadSchemeAction = new QAction(QIcon{":/images/Open.png"}, "&Open...", this);
	connect(loadSchemeAction, &QAction::triggered, this, &MainWindow::slotLoadScheme);

    quitAction = new QAction(QIcon{":/images/Quit.png"}, "&Exit", this);
    quitAction->setShortcut(tr("CTRL+Q"));
    connect(quitAction, &QAction::triggered, this, &MainWindow::slotQuit);


    addRAction = new QAction("resistor", this);
    connect(addRAction, &QAction::triggered, this, &MainWindow::slotAddR);

    addNPNAction = new QAction("npn BJT", this);
    connect(addRAction, &QAction::triggered, this, &MainWindow::slotAddNPN);

    addCSAction = new QAction("current source", this);
    connect(addRAction, &QAction::triggered, this, &MainWindow::slotAddCS);
}

void MainWindow::createScene(){
	scene = new LEdiScene(QRect(0,0,80*GRID_SZ,60*GRID_SZ));

	view = new LEdiView(scene, NULL);
    view->show();

	setCentralWidget(view);
}

void MainWindow::createMenu(){

    QMenu* fileMenu = new QMenu("&File");
	menuBar()->addMenu(fileMenu);
    fileMenu->addAction(loadSchemeAction);
    fileMenu->addAction(saveSchemeAction);
	fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    QMenu* elementMenu = new QMenu("&Element");
    menuBar()->addMenu(elementMenu);
    elementMenu->addAction(addRAction);
    elementMenu->addAction(addNPNAction);
    elementMenu->addAction(addCSAction);
}

void MainWindow::slotSaveScheme(){
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

void MainWindow::slotLoadScheme(){
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

void MainWindow::slotQuit(){
    if (QMessageBox::question(this, "Exit request", "Are you sure?"))
        close();
}

void MainWindow::slotAddR(){
    QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

void MainWindow::slotAddNPN(){
    QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

void MainWindow::slotAddCS(){
    QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}
