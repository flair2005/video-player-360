#ifndef MAINGLWINDOW_H
#define MAINGLWINDOW_H

#include <QGLWidget>

#include <QtGui/QMatrix4x4>

#include <QMediaPlayer>
#include "videotextureplayer.h"

class Mesh;

class MainGLWindow : public QGLWidget
{
	Q_OBJECT
public:
	explicit MainGLWindow(QWidget *parent = 0);
	~MainGLWindow();

	void initializeVideo();

signals:

public slots:

protected:
	virtual void paintGL();

	virtual void initializeGL();

private:

	QMatrix4x4 m_view;

	QMatrix4x4 m_model;

	QMatrix4x4 m_proj;

	Mesh* m_sphere;

	GLuint m_texture;

	QMediaPlayer* m_mediaPlayer;
	VideoTexturePlayer* m_texturePlayer;

	void loadTexture();
};

#endif // MAINGLWINDOW_H
