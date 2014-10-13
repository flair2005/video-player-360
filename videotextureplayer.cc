#include "videotextureplayer.h"

#include <iostream>

VideoTexturePlayer::VideoTexturePlayer()
{
}

QList<QVideoFrame::PixelFormat> VideoTexturePlayer::supportedPixelFormats(
		QAbstractVideoBuffer::HandleType handleType) const
{
	//Q_UNUSED(handleType);

	// Return the formats you will support
	return QList<QVideoFrame::PixelFormat>()
					 << QVideoFrame::Format_RGB32
					 << QVideoFrame::Format_ARGB32
					 << QVideoFrame::Format_ARGB32_Premultiplied
					 << QVideoFrame::Format_RGB565
					 << QVideoFrame::Format_RGB555;
}

bool VideoTexturePlayer::present(const QVideoFrame &frame)
{
	//Q_UNUSED(frame);
	// Handle the frame and do your processing

	std::cout << "hola" << std::endl;
	return true;
}
