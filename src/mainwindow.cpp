#include "mainwindow.h"
#include <QTextStream>
#include "locale.h"

#include "wire.h"
#include "logicelement.h"

Locale msg;
LogicElement mainLE;

//
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, true);
    initActions();

    //msg.setLocale("Eng");


    resize(1200,700);
    createScene();
    createMenu();
    createToolBar();
    createStatusBar();
}

//
void MainWindow::initActions()
{
    AnewFile = new QAction(QIcon{":/images/New.png"}, msg.get1(), this);
	connect(AnewFile, &QAction::triggered, this, &MainWindow::SLnewFile);

    AopenFile = new QAction(QIcon{":/images/Open.png"}, msg.get2(), this);
	connect(AopenFile, &QAction::triggered, this, &MainWindow::SLopenFile);

    AsaveFile = new QAction(QIcon{":/images/Save.png"}, msg.get3(), this);
	AsaveFile->setShortcut(tr("CTRL+S"));
	connect(AsaveFile, &QAction::triggered, this, &MainWindow::SLsaveFile);

    Aquit = new QAction(QIcon{":/images/Quit.png"}, msg.get4(), this);
	Aquit->setShortcut(tr("CTRL+Q"));
	connect(Aquit, &QAction::triggered, this, &MainWindow::SLquit);
}

//
void MainWindow::createScene()
{
	scene = new QGraphicsScene();
	scene->addText("Hello, world!");

	view = new QGraphicsView(scene);
	view->show();

	setCentralWidget(view);
}

//
void MainWindow::createMenu()
{
    fileMenu = new QMenu(msg.get0());
	menuBar()->addMenu(fileMenu);

	fileMenu->addAction(AnewFile);
	fileMenu->addAction(AopenFile);
	fileMenu->addAction(AsaveFile);
	fileMenu->addSeparator();
	fileMenu->addAction(Aquit);
}

//
void MainWindow::createToolBar()
{
	toolBar = new QToolBar(this);

	toolBar->addAction(AnewFile);
	toolBar->addAction(AopenFile);
	toolBar->addAction(AsaveFile);
	toolBar->setMovable(true);

	addToolBar(Qt::TopToolBarArea, toolBar);
}

//
void MainWindow::createStatusBar()
{
	statusBar = new QStatusBar(this);
	setStatusBar(statusBar);
	statusBar->showMessage("Запуск");
	statusBar->setStatusTip("Пока тут нечего смотреть...");
}

//Empty
void MainWindow::SLnewFile()
{
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

//
void MainWindow::SLopenFile()
{
	QString filename = QFileDialog::getOpenFileName(this, "Select", "", "Verilog (*.syn_dc.v)");

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning("Cannot open file for reading");
        return;
    }

    mainLE.initMainFromFile(file.readAll());
}

//Empty
void MainWindow::SLsaveFile()
{
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

//
void MainWindow::SLquit()
{
	QMessageBox::information(this, "Запрос на выход", "Ну идите...");
    close();
}

//
MainWindow::~MainWindow()
{}
