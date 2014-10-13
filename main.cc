#include "mainwindow.h"
#include "mainglwindow.h"
#include <QApplication>

#if 0

#include <QDebug>
#include <QApplication>
#include <QMediaPlayer>
#include <QGLWidget>
#include <QVBoxLayout>
#include <QFile>

#include "videotextureplayer.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	QGLWidget *widget = new QGLWidget;
	widget->resize(400, 300);

	QVBoxLayout *layout = new QVBoxLayout;
	QMediaPlayer* player = new QMediaPlayer;

	widget->setLayout(layout);

	VideoTexturePlayer* vtp = new VideoTexturePlayer;

	player->setVideoOutput(vtp);
	QFile file("/Developer/projects/visyon360-test/media/reel360.mp4");
	if(!file.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";
	player->setMedia(QUrl::fromLocalFile("/Developer/projects/visyon360-test/media/reel360.mp4"));
	player->play();
	widget->show();
	qDebug() << player->availableMetaData() << player->currentMedia().canonicalUrl();
	return app.exec();
}

#else
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainGLWindow w;
	//MainWindow w;
	//w.setWidth(800);
	//w.setHeight(600);
	w.resize(800, 600);

	w.setMinimumSize(QSize(w.width(), w.height()));
	w.setMaximumSize(QSize(w.width(), w.height()));
	//w.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	//w.setAnimating(true);

	w.initializeVideo();

	w.show();

	return a.exec();
}
#endif
