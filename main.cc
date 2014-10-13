#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setWidth(800);
	w.setHeight(600);

	w.setMinimumSize(QSize(w.width(), w.height()));
	w.setMaximumSize(QSize(w.width(), w.height()));

	w.setAnimating(true);

	w.show();

	return a.exec();
}
