#include <QTextStream>
#include "MainWindow.h"
#include "Locale.h"
#include "LEdiScene.h"
#include "LEdiView.h"
#include "LEData.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, true);
	msg = new Locale();
	//msg->setLocale("Eng");

	initActions();
    resize(1200,700);
    createScene();
    createMenu();
    createToolBar();
    createStatusBar();
	createLibraryWidget();

	slotLoadLibrary();
	slotLoadScheme();
}

void MainWindow::initActions(){
	newFileAction = new QAction(QIcon{":/images/New.png"}, msg->get1(), this);
	connect(newFileAction, &QAction::triggered, this, &MainWindow::slotNewFile);

	loadLibraryAction = new QAction(QIcon{":/images/Open.png"}, "Load library", this);
	connect(loadLibraryAction, &QAction::triggered, this, &MainWindow::slotLoadLibrary);

	loadSchemeAction = new QAction(QIcon{":/images/Open.png"}, "Load scheme", this);
	connect(loadSchemeAction, &QAction::triggered, this, &MainWindow::slotLoadScheme);

	saveFileAction = new QAction(QIcon{":/images/Save.png"}, msg->get3(), this);
	saveFileAction->setShortcut(tr("CTRL+S"));
	connect(saveFileAction, &QAction::triggered, this, &MainWindow::slotSaveFile);

    quitAction = new QAction(QIcon{":/images/Quit.png"}, msg->get4(), this);
    quitAction->setShortcut(tr("CTRL+Q"));
    connect(quitAction, &QAction::triggered, this, &MainWindow::slotQuit);
}

void MainWindow::createScene(){
    scene = new LEdiScene(QRect(0,0,80*GRID_SZ,60*GRID_SZ));

	view = new LEdiView(scene, NULL);
	view->show();

	setCentralWidget(view);
}

void MainWindow::createMenu(){
    fileMenu = new QMenu(msg->get0());
	menuBar()->addMenu(fileMenu);

    //fileMenu->addAction(newFileAction);
	fileMenu->addAction(loadLibraryAction);
	fileMenu->addAction(loadSchemeAction);
	//fileMenu->addAction(saveFileAction);
	fileMenu->addSeparator();
    fileMenu->addAction(quitAction);
}

void MainWindow::createToolBar(){
	toolBar = new QToolBar(this);

	//toolBar->addAction(newFileAction);
	toolBar->addAction(loadSchemeAction);
	//toolBar->addAction(saveFileAction);
	toolBar->setMovable(true);

	addToolBar(Qt::TopToolBarArea, toolBar);
}

void MainWindow::createStatusBar(){
	statusBar = new QStatusBar(this);
	setStatusBar(statusBar);
	statusBar->showMessage("Запуск");
	statusBar->setStatusTip("Пока тут нечего смотреть...");
}

void MainWindow::createLibraryWidget(){
	QDockWidget* dockWidget = new QDockWidget();
	QTreeWidget* treeWidget = new QTreeWidget();
	QStringList headers;
	headers << "Library LE";
	treeWidget->setHeaderLabels(headers);
	treeWidget->setRootIsDecorated(0);
	dockWidget->setWidget(treeWidget);
	addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

	QTreeWidgetItem* item = new QTreeWidgetItem(treeWidget);
	item->setText(0,"jj");

	//connect(treeWidget, &QTreeWidget::currentItemChanged, this, &LEdiView::slotAct2);
}

//Empty
void MainWindow::slotNewFile(){
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

void MainWindow::slotLoadLibrary(){
	QString path;
	//path = QFileDialog::getOpenFileName(this, "Select", "", "Verilog (*.v)");
	path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC_libs/XD_LE_PtcV1.80T25.v";
	//path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/library/XD_LE_PtcV1.80T25.v";

	LEData::readLibrary(path);
}

//
void MainWindow::slotLoadScheme(){
	QString path;
    //path = QFileDialog::getOpenFileName(this, "Select", "", "Verilog (*.v)");
	path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/s27.syn_dc.v";
    //path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/c432.syn_dc.v";
	//path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/input_files/s27.syn_dc.v";
    //path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/input_files/c432.syn_dc.v";

    mainLE = new LEData();
	if (mainLE->initLEFromFile(path) == RESULT_ERROR)
		qWarning("Module read failure");
    else{
        scene->clear();
        scene->setSceneRect(scene->layoutLE(mainLE));
		scene->traceLE(mainLE);
    }
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
