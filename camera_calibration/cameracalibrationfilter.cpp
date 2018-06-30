#include "cameracalibrationfilter.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <optional>
#include <iostream>

std::optional<cv::Mat> mapFrom2Mat(QVideoFrame& frame)
{
    const auto width = frame.width();
    const auto height = frame.height();
    const auto data = frame.bits();
    const auto bytesPerLine = static_cast<size_t>(frame.bytesPerLine());

    switch (frame.pixelFormat()) {
    case QVideoFrame::Format_RGB32:
        return cv::Mat{height, width, CV_8UC4, data, bytesPerLine};

//    case QVideoFrame::Format_RGB24:
//        std::cout << "QVideoFrame::Format_RGB24" << std::endl;
//        return cv::Mat{height, width, CV_8UC3, data};

//    case QVideoFrame::Format_YUV420P:
//    {
//        std::cout << "QVideoFrame::Format_YUV420P" << std::endl;
//        cv::Mat temp{ height + height / 2, width, CV_8UC1, data};
//        cv::Mat res;
//        cv::cvtColor(temp, res, cv::COLOR_YUV2BGR_I420);
//        return res;
//    }

    default:
        return {};
    }
}

CameraCalibrationFilter::CameraCalibrationFilter()
{
}

QVideoFilterRunnable* CameraCalibrationFilter::createFilterRunnable()
{
    return new CameraCalibrationRunnable(*this);
}

CameraCalibrationRunnable::CameraCalibrationRunnable(CameraCalibrationFilter& filter) noexcept
    : m_filter{filter}
{
}

QVideoFrame CameraCalibrationRunnable::run(QVideoFrame* frame, const QVideoSurfaceFormat&, QVideoFilterRunnable::RunFlags)
{
    if (!frame->isValid())
        return *frame;

    if (frame->handleType() != QAbstractVideoBuffer::NoHandle)
        return *frame;

    if (!frame->map(QAbstractVideoBuffer::ReadWrite))
        return *frame;

    auto mat = mapFrom2Mat(*frame);

    if (!mat)
        return *frame;

    if (m_calibrator.findChessboard(*mat))
    {
//        const auto chessboard = m_calibrator.lastChessboardImage();
//        QImage img{chessboard.data, chessboard.cols, chessboard.rows, QImage::Format_RGB32};
//        emit m_filter.chessboardFound(img);
        emit m_filter.chessboardFound();
    }

    frame->unmap();

    return *frame;
}
