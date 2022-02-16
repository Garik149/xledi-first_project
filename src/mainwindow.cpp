#include <QTextStream>
#include "mainwindow.h"
#include "locale.h"
#include "lediscene.h"
#include "lediview.h"
#include "logicelement.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, true);
    initActions();

    LogicElement::addBasicElements();

    msg = new Locale();
    //msg->setLocale("Eng");

    resize(1200,700);
    createScene();
    createMenu();
    createToolBar();
    createStatusBar();
    //tabWidget = nullptr;

    //QWidget *widget = new QWidget{};
    //QHBoxLayout *layout = new QHBoxLayout{};
    //layout->addWidget(toolBox);

    //layout->addWidget(tabWidget);

    //widget->setLayout(layout);

    //setCentralWidget(widget);

    //slotOpenFile();
}

MainWindow::~MainWindow(){}

void MainWindow::initActions(){
    AnewFile = new QAction(QIcon{":/images/New.png"}, msg->get1(), this);
    connect(AnewFile, &QAction::triggered, this, &MainWindow::slotNewFile);

    AopenFile = new QAction(QIcon{":/images/Open.png"}, msg->get2(), this);
    connect(AopenFile, &QAction::triggered, this, &MainWindow::slotOpenFile);

    AsaveFile = new QAction(QIcon{":/images/Save.png"}, msg->get3(), this);
	AsaveFile->setShortcut(tr("CTRL+S"));
    connect(AsaveFile, &QAction::triggered, this, &MainWindow::slotSaveFile);

    Aquit = new QAction(QIcon{":/images/Quit.png"}, msg->get4(), this);
	Aquit->setShortcut(tr("CTRL+Q"));
    connect(Aquit, &QAction::triggered, this, &MainWindow::slotQuit);
}

void MainWindow::createScene(){
    scene = new LEdiScene(QRectF(0,0,2500,1500));

    view = new LEdiView(scene);
	view->show();

	setCentralWidget(view);
}

void MainWindow::createMenu(){
    fileMenu = new QMenu(msg->get0());
	menuBar()->addMenu(fileMenu);

	fileMenu->addAction(AnewFile);
	fileMenu->addAction(AopenFile);
	fileMenu->addAction(AsaveFile);
	fileMenu->addSeparator();
	fileMenu->addAction(Aquit);
}

void MainWindow::createToolBar(){
	toolBar = new QToolBar(this);

	toolBar->addAction(AnewFile);
	toolBar->addAction(AopenFile);
	toolBar->addAction(AsaveFile);
	toolBar->setMovable(true);

	addToolBar(Qt::TopToolBarArea, toolBar);
}

void MainWindow::createStatusBar(){
	statusBar = new QStatusBar(this);
	setStatusBar(statusBar);
	statusBar->showMessage("Запуск");
	statusBar->setStatusTip("Пока тут нечего смотреть...");
}

//Empty
void MainWindow::slotNewFile(){
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

//
void MainWindow::slotOpenFile(){
    QString path;
    path = QFileDialog::getOpenFileName(this, "Select", "", "Verilog (*.syn_dc.v)");
    //path = "C:/Users/goris/_Stuff/Study/Practical_work/examples/input_files/c17.syn_dc.v";

    mainLE = new LogicElement();
    if (mainLE->initMainLEFromFile(path) == RESULT_ERROR) qWarning("Module read failure");
}

//Empty
void MainWindow::slotSaveFile(){
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

//
void MainWindow::slotQuit(){
	QMessageBox::information(this, "Запрос на выход", "Ну идите...");
    close();
}
