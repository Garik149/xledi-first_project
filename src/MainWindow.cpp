#include <QTextStream>
#include "MainWindow.h"
#include "Locale.h"
#include "LEdiScene.h"
#include "LEdiView.h"
#include "LEData.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    qApp->setAttribute(Qt::AA_DontShowIconsInMenus, true);
	msg = new Locale();
	initActions();

	QString path;
	//path = QFileDialog::getOpenFileName(this, "Select", "", "Verilog (*.v)");
    path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC_libs/XD_LE_PtcV1.80T25.v";
    //path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/library/XD_LE_PtcV1.80T25.v";
    LEData::readLibrary(path);

    //msg->setLocale("Eng");

    resize(1200,700);
    createScene();
    createMenu();
    createToolBar();
    createStatusBar();

    slotOpenFile();
}

void MainWindow::initActions(){
    //newFileAction = new QAction(QIcon{":/images/New.png"}, msg->get1(), this);
    //connect(newFileAction, &QAction::triggered, this, &MainWindow::slotNewFile);

    openFileAction = new QAction(QIcon{":/images/Open.png"}, msg->get2(), this);
    connect(openFileAction, &QAction::triggered, this, &MainWindow::slotOpenFile);

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
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(saveFileAction);
	fileMenu->addSeparator();
    fileMenu->addAction(quitAction);
}

void MainWindow::createToolBar(){
	toolBar = new QToolBar(this);

    //toolBar->addAction(newFileAction);
    toolBar->addAction(openFileAction);
    toolBar->addAction(saveFileAction);
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
    //path = QFileDialog::getOpenFileName(this, "Select", "", "Verilog (*.v)");
<<<<<<< HEAD
    path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/s27.syn_dc.v";
	//path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/s344.syn_dc.v";
    //path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/input_files/c17.syn_dc.v";
    //path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/input_files/c432.syn_dc.v";
=======
	//path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/s27.syn_dc.v";
	path = "D:/Gorislav/Projects/X-LEdi/InputExamples/Syn_DC/c432.syn_dc.v";
	//path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/input_files/c17.syn_dc.v";
	//path = "C:/Users/goris/_Stuff/Study/Practical_work/X-LEdi/examples/input_files/c432.syn_dc.v";
>>>>>>> 897ee37b166e8100e466a8c05c0fb96ef4145a38

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
