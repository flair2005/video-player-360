#ifndef VIDEOTEXTUREPLAYER_H
#define VIDEOTEXTUREPLAYER_H

#include <QAbstractVideoSurface>

class VideoTexturePlayer : public QAbstractVideoSurface
{
public:
	VideoTexturePlayer();

	QList<QVideoFrame::PixelFormat> supportedPixelFormats(
			QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const;

	bool present(const QVideoFrame &frame);
};

#endif // VIDEOTEXTUREPLAYER_H
