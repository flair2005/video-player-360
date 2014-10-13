#include "videotextureplayer.h"
#include "mainglwindow.h"

#include <QImage>

#include <QDebug>

VideoTexturePlayer::VideoTexturePlayer(MainGLWindow* toUpdate)
	: m_toUpdate(toUpdate)
{
}

QList<QVideoFrame::PixelFormat> VideoTexturePlayer::supportedPixelFormats(
		QAbstractVideoBuffer::HandleType handleType) const
{
	if (handleType == QAbstractVideoBuffer::NoHandle) {
			 return QList<QVideoFrame::PixelFormat>()
					 << QVideoFrame::Format_RGB32
					 << QVideoFrame::Format_ARGB32
					 << QVideoFrame::Format_ARGB32_Premultiplied
					 << QVideoFrame::Format_RGB565
					 << QVideoFrame::Format_RGB555;
	 } else {
		 return QList<QVideoFrame::PixelFormat>();
	 }
	/*
	Q_UNUSED(handleType);

	// Return the formats you will support
	return QList<QVideoFrame::PixelFormat>()
					 << QVideoFrame::Format_RGB32
					 << QVideoFrame::Format_ARGB32
					 << QVideoFrame::Format_ARGB32_Premultiplied
					 << QVideoFrame::Format_RGB565
					 << QVideoFrame::Format_RGB555;
					 */
}

bool VideoTexturePlayer::present(const QVideoFrame &frame)
{
	// Handle the frame and do your processing

	if(m_toUpdate)
	{
		QVideoFrame f2(frame);

		f2.map(QAbstractVideoBuffer::ReadOnly);
		QImage img(f2.bits(), f2.width(), f2.height(),
				   QVideoFrame::imageFormatFromPixelFormat(f2.pixelFormat()));
//		QImage img(frame.bits(), frame.width(), frame.height(),
//				   QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
		m_toUpdate->setTexture(img);
		f2.unmap();
		m_toUpdate->update();
	}

	return true;
}
