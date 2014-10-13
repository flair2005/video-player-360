#ifndef VIDEOTEXTUREPLAYER_H
#define VIDEOTEXTUREPLAYER_H

#include <QAbstractVideoSurface>

class MainGLWindow;

class VideoTexturePlayer : public QAbstractVideoSurface
{
public:
	VideoTexturePlayer(MainGLWindow* toUpdate = 0);

	QList<QVideoFrame::PixelFormat> supportedPixelFormats(
			QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;

	bool present(const QVideoFrame &frame);

private:
	MainGLWindow* m_toUpdate;
};

#endif // VIDEOTEXTUREPLAYER_H
