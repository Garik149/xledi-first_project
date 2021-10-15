#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, true);
    initActions();

    resize(1200,700);
    createScene();
    createMenu();
    createToolBar();
    createStatusBar();
}

//
void MainWindow::initActions()
{
    AnewFile = new QAction(QIcon{":/images/New.png"}, "&New file", this);
    connect(AnewFile, &QAction::triggered, this, &MainWindow::SLnewFile);

    AopenFile = new QAction(QIcon{":/images/Open.png"}, "&Open file", this);
    connect(AopenFile, &QAction::triggered, this, &MainWindow::SLopenFile);

    AsaveFile = new QAction(QIcon{":/images/Save.png"}, "&Save file", this);
    AsaveFile->setShortcut(tr("CTRL+S"));
    connect(AsaveFile, &QAction::triggered, this, &MainWindow::SLsaveFile);

    Aquit = new QAction(QIcon{":/images/Quit.png"}, "&Quit", this);
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
    fileMenu = new QMenu("&File");
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

//Empty
void MainWindow::SLopenFile()
{

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

MainWindow::~MainWindow()
{}
