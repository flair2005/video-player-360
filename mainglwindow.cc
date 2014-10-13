#include "mainglwindow.h"

#include "meshutils.h"

#include "timer.h"

#include <QImage>

#include <iostream>
#include <cassert>

#include <QDebug>
#include <QMediaPlaylist>
#include <QFile>

MainGLWindow::MainGLWindow(QWidget *parent) :
    QGLWidget(parent)
{
	m_mediaPlayer = new QMediaPlayer;
	m_texturePlayer = new VideoTexturePlayer;
}


MainGLWindow::~MainGLWindow()
{
	delete m_sphere;
	delete m_mediaPlayer;
}

void MainGLWindow::initializeGL()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, width(), height());

	m_proj.setToIdentity();
	m_proj.perspective(60, ((float)width())/height(), 0.1, 1000);

	m_view.setToIdentity();
	m_view.lookAt(QVector3D(1.5,0,1.5), QVector3D(0,0,0), QVector3D(0, 1, 0));

	m_model.setToIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_proj.constData());
	glMatrixMode(GL_MODELVIEW);

	m_sphere = MeshUtils::CreateSphere(30, 30);

	glEnable(GL_TEXTURE_2D);

	loadTexture();
}

void MainGLWindow::paintGL()
{
	Timer::update();

	m_model.rotate(Timer::deltaTime()*10, QVector3D(0, 1, 0));


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glLoadMatrixf(m_view.constData());
	glMultMatrixf(m_model.constData());

	glBindTexture(GL_TEXTURE_2D, m_texture);

	m_sphere->render();

	glBindTexture(GL_TEXTURE_2D, 0);

	//update();
}

void MainGLWindow::initializeVideo()
{
	// Initialize the Video Player

	m_mediaPlayer->setVideoOutput(m_texturePlayer);
	QFile file("/Developer/projects/visyon360-test/media/reel360.mp4");
	if(!file.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";
	m_mediaPlayer->setMedia(QUrl::fromLocalFile("/Developer/projects/visyon360-test/media/reel360.mp4"));
	m_mediaPlayer->play();
	std::cout << m_mediaPlayer->duration() << std::endl;
}

void MainGLWindow::loadTexture()
{
	QImage t;
	QImage b;

	if ( !b.load( "003.jpg" ) )
	{
		b = QImage( 16, 16, QImage::Format_RGBA8888 );
		b.fill( Qt::green );
		b.setPixel(8, 8, Qt::red);
	}

	t = QGLWidget::convertToGLFormat( b );

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}
