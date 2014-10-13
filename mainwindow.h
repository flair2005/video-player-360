#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "openglwindow.h"

#include <string>

#include <qopengl.h>
#include <QtGui/QMatrix4x4>

#include <QMediaPlayer>
#include "videotextureplayer.h"

namespace Ui {
class MainWindow;
}

class Mesh;

class MainWindow : public OpenGLWindow
{
	Q_OBJECT

public:
	explicit MainWindow();
	~MainWindow();

	void initialize();

	void update();

	void render();

	void initializeVideo();

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

#endif // MAINWINDOW_H
