#ifndef MAINGLWINDOW_H
#define MAINGLWINDOW_H

#include <QGLWidget>

#include <QtGui/QMatrix4x4>
#include <QVector2D>

#include <string>

#include <QMediaPlayer>
#include "videotextureplayer.h"

class Mesh;
class QImage;

class MainGLWindow : public QGLWidget
{
	Q_OBJECT
public:
	explicit MainGLWindow(QWidget *parent = 0);
	~MainGLWindow();

	void initializeVideo(const std::string& fileName);

	void setTexture(QImage &img);

signals:

public slots:

protected:
	virtual void paintGL();

	virtual void initializeGL();

	virtual void resizeGL(int width, int height);

	virtual void mouseMoveEvent(QMouseEvent* e);

	virtual void keyPressEvent(QKeyEvent* e);

private:

	QMatrix4x4 m_view;

	float m_viewRadius = 2;
	QVector2D m_mousePos = QVector2D(0.5, 0.5);
	bool m_viewFromInside = false;

	void updateView();

	QMatrix4x4 m_model;

	QMatrix4x4 m_proj;

	Mesh* m_sphere;

	GLuint m_texture;

	QMediaPlayer* m_mediaPlayer;
	VideoTexturePlayer* m_texturePlayer;

	QImage m_textureImage;
	bool m_textureUpdated;

	void loadTexture();

	void updateTexture();
};

#endif // MAINGLWINDOW_H
