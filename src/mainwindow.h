#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void SLnewFile();
	void SLopenFile();
	void SLsaveFile();
	void SLquit();

private:
	void initActions();
	void createScene();
	void createMenu();
	void createToolBar();
	void createStatusBar();

	QAction* AnewFile;
	QAction* AopenFile;
	QAction* AsaveFile;
	QAction* Aquit;

	QMenu* fileMenu;
	QToolBar* toolBar;
	QStatusBar* statusBar;
	QTextEdit* textEditor;
	QGraphicsScene* scene;
	QGraphicsView* view;

};
#endif // MAINWINDOW_H
