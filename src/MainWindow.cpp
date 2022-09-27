#include <QTextStream>
#include "MainWindow.h"
#include "Locale.h"
#include "LEdiScene.h"
#include "LEdiView.h"
#include "LEData.h"


/*class WorkerThread : public QThread
{
	Q_OBJECT
public:
	WorkerThread(QObject* obj):QThread(obj){};
	void run() override {
		QString result;
		emit resultReady(result);
	}
signals:
	void resultReady(const QString &s);
};

void MainWindow::startWorkInAThread()
{
	//WorkerThread *workerThread = new WorkerThread(this);
	//connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResults);
	//connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
	//workerThread->start();
}*/

//int iter;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, true);
	mainLE = NULL;
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
	/*for (iter=0; iter<3; iter++)
		slotSynthScheme();*/

	//close();
}

void MainWindow::initActions(){
	newSchemeAction = new QAction(QIcon{":/images/New.png"}, msg->get1(), this);
	connect(newSchemeAction, &QAction::triggered, this, &MainWindow::slotNewScheme);

	loadLibraryAction = new QAction(QIcon{":/images/Open.png"}, "Load library", this);
	connect(loadLibraryAction, &QAction::triggered, this, &MainWindow::slotLoadLibrary);

	synthSchemeAction = new QAction(QIcon{":/images/Open.png"}, "Synthesize scheme", this);
	connect(synthSchemeAction, &QAction::triggered, this, &MainWindow::slotSynthScheme);

	saveSchemeAction = new QAction(QIcon{":/images/Save.png"}, msg->get3(), this);
	saveSchemeAction->setShortcut(tr("CTRL+S"));
	connect(saveSchemeAction, &QAction::triggered, this, &MainWindow::slotSaveScheme);

	loadSchemeAction = new QAction(QIcon{":/images/Open.png"}, "Load scheme", this);
	connect(loadSchemeAction, &QAction::triggered, this, &MainWindow::slotLoadScheme);

    quitAction = new QAction(QIcon{":/images/Quit.png"}, msg->get4(), this);
    quitAction->setShortcut(tr("CTRL+Q"));
    connect(quitAction, &QAction::triggered, this, &MainWindow::slotQuit);
}

void MainWindow::createScene(){
	scene = new LEdiScene(QRect(0,0,80*GRID_SZ,60*GRID_SZ));

	view = new LEdiView(scene, NULL);
	view->show();

	//QThread myThread(view);
	//connect(myThread, &QThread::finished, myThread, &QObject::deleteLater);
	//myThread.start();

	setCentralWidget(view);
}

void MainWindow::createMenu(){
    fileMenu = new QMenu(msg->get0());
	menuBar()->addMenu(fileMenu);

	//fileMenu->addAction(newSchemeAction);
	fileMenu->addAction(loadLibraryAction);
	fileMenu->addAction(synthSchemeAction);
	//fileMenu->addAction(loadSchemeAction);
	//fileMenu->addAction(saveSchemeAction);
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
	libraryTree = new QTreeWidget();
	QStringList headers;
	headers << "Library LE";
	libraryTree->setHeaderLabels(headers);
	libraryTree->setRootIsDecorated(0);
	dockWidget->setWidget(libraryTree);
	addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
	connect(libraryTree, &QTreeWidget::currentItemChanged, view, &LEdiView::addLibraryTreeLE);
}

//Empty
void MainWindow::slotNewScheme(){
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

void MainWindow::slotLoadLibrary(){
	QString path;
	//path = QFileDialog::getOpenFileName(this, "Select", "", "Verilog (*.v)");
    //path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC_libs/XD_LE_PtcV1.80T25.v";
    path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/library/XD_LE_PtcV1.80T25.v";

	LEData::readLibrary(path);

	libraryTree->clear();
	QTreeWidgetItem* item;
	for (int i=0;i<LEData::library.size();i++){
		item = new QTreeWidgetItem(libraryTree);
		item->setText(0,LEData::library[i].type);
	}
}

//
void MainWindow::slotSynthScheme(){
	QString path;
	/*switch(iter){
		case 0: path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/s510.syn_dc.v"; break;
		case 1: path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/s838.syn_dc.v"; break;
		case 2: path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/c1908.syn_dc.v"; break;
	}*/
    path = QFileDialog::getOpenFileName(this, "Select", "", "Verilog (*.v)");
	//path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/s27.syn_dc.v";
	//path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/input_files/s27.syn_dc.v";

    //path = "s27.syn_dc.v";
    LEData* newLE = new LEData();
	if (newLE->initLEFromFile(path) == RESULT_ERROR)
		qWarning("Module read failure");
	else{

		scene->reset();
		view->reset();
		if (mainLE!=NULL) delete(mainLE);
		mainLE=newLE;
		//startWorkInAThread();
		scene->synth(mainLE);
	}
}

//Empty
void MainWindow::slotSaveScheme(){
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

//Empty
void MainWindow::slotLoadScheme(){
	QMessageBox::information(this, "Информация", "Эта функция не разблокирована");
}

//
void MainWindow::slotQuit(){
	QMessageBox::information(this, "Запрос на выход", "Ну идите...");
    close();
}
