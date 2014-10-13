#include "mainwindow.h"

#include "meshutils.h"

#include "timer.h"

#include <QGLWidget>
#include <QImage>

#include <iostream>
#include <cassert>


MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
	delete m_sphere;
}


void MainWindow::initialize()
{
	OpenGLWindow::initialize();

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

void MainWindow::update()
{
	Timer::update();

	m_model.rotate(Timer::deltaTime()*10, QVector3D(0, 1, 0));

}

void MainWindow::render()
{
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


void MainWindow::loadTexture()
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
