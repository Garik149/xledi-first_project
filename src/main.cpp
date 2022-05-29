#include <QApplication>

#include "MainWindow.h"

QPalette plainStyle()
{
    QPalette plainPalette;
    plainPalette.setColor(QPalette::Window, Qt::white);
    plainPalette.setColor(QPalette::WindowText, Qt::black);
    plainPalette.setColor(QPalette::Base, Qt::white);
    plainPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    plainPalette.setColor(QPalette::ToolTipBase, Qt::white);
    plainPalette.setColor(QPalette::ToolTipText, Qt::white);
    plainPalette.setColor(QPalette::Text, Qt::black);
    plainPalette.setColor(QPalette::Button, QColor(46, 52, 57));
    plainPalette.setColor(QPalette::ButtonText, Qt::white);
    plainPalette.setColor(QPalette::BrightText, Qt::red);
    plainPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    plainPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    plainPalette.setColor(QPalette::HighlightedText, Qt::black);

    return plainPalette;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    app.setWindowIcon(QIcon{":/images/Icon.png"});
    //app.setPalette(plainStyle());

	MainWindow window{};
	window.show();

	return app.exec();
}
