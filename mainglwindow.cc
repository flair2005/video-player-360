#include "mainglwindow.h"

#include "meshutils.h"

#include "timer.h"

#include <QImage>

#include <iostream>
#include <cassert>

#include <QDebug>
#include <QMediaPlaylist>
#include <QFile>

#include <QMouseEvent>

#include <cmath>

MainGLWindow::MainGLWindow(QWidget *parent) :
    QGLWidget(parent)
{
	m_mediaPlayer = new QMediaPlayer;
	m_texturePlayer = new VideoTexturePlayer(this);
}


MainGLWindow::~MainGLWindow()
{
	delete m_sphere;
	delete m_mediaPlayer;
}

void MainGLWindow::initializeGL()
{
	setMouseTracking(true);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	resizeGL(width(), height());

	updateView();

	m_model.setToIdentity();

	m_sphere = MeshUtils::CreateSphere(30, 30);

	glEnable(GL_TEXTURE_2D);

	loadTexture();
}

void MainGLWindow::mouseMoveEvent(QMouseEvent* e)
{
	float x = ((float)e->x()) / width();
	float y = ((float)e->y()) / height();
	if(x <= 0 || x >= 1 || y <= 0 || y >= 1)
		return;

	m_mousePos = QVector2D(x, y);
	updateView();
}

void MainGLWindow::updateView()
{
	float r = m_viewRadius;
	float x = m_mousePos.x() * 2 * M_PI;
	float y = m_mousePos.y() * M_PI;

	m_view.setToIdentity();

	QVector3D eye(
				r*sin(y)*sin(x),
				r*cos(y),
				r*sin(y)*cos(x)
				);

	if(m_viewFromInside)
	{
		m_view.lookAt(QVector3D(0, 0, 0), eye, QVector3D(0, 1, 0));
		makeCurrent();
		glFrontFace(GL_CW);
	}
	else
	{
		m_view.lookAt(eye, QVector3D(0, 0, 0), QVector3D(0, 1, 0));
		makeCurrent();
		glFrontFace(GL_CCW);
	}
}

void MainGLWindow::keyPressEvent(QKeyEvent* e)
{
	if(e->key() == Qt::Key_Space)
	{
		m_viewFromInside = ! m_viewFromInside;
		updateView();
	}
	else if(e->key() == Qt::Key_Escape)
	{
		close();
	}
}

void MainGLWindow::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	m_proj.setToIdentity();
	m_proj.perspective(60, ((float)width)/height, 0.1, 1000);

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_proj.constData());
	glMatrixMode(GL_MODELVIEW);
}

void MainGLWindow::paintGL()
{
	updateTexture();

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
}

void MainGLWindow::initializeVideo(const std::string& fileName)
{
	// Initialize the Video Player

	m_mediaPlayer->setVideoOutput(m_texturePlayer);

	QFile file(fileName.c_str());
	if(!file.open(QIODevice::ReadOnly))
		qDebug() << "Could not open file";

	m_mediaPlayer->setMedia(QUrl::fromLocalFile(fileName.c_str()));
	m_mediaPlayer->play();
}

void MainGLWindow::setTexture(QImage& img)
{
	m_textureImage = img;
	m_textureUpdated = true;
}

void MainGLWindow::updateTexture()
{
	if(!m_textureUpdated) return;
	m_textureUpdated = false;

	QImage t;
	t = QGLWidget::convertToGLFormat( m_textureImage );

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, t.width(), t.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, t.bits() );

	assert(glGetError() == GL_NO_ERROR);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

void MainGLWindow::loadTexture()
{
	QImage b;

	if ( !b.load( "003.jpg" ) )
	{
		b = QImage( 16, 16, QImage::Format_RGBA8888 );
		b.fill( Qt::green );
		b.setPixel(8, 8, Qt::red);
	}

	m_texture = 0;
	glGenTextures(1, &m_texture);
	setTexture(b);
	updateTexture();
}
