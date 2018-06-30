#pragma once

#include "cameracalibrator.h"
#include <opencv2/opencv.hpp>
#include <QAbstractVideoFilter>

class CameraCalibrationFilter : public QAbstractVideoFilter {
    Q_OBJECT

public:
    CameraCalibrationFilter();

    QVideoFilterRunnable* createFilterRunnable() override;

signals:
    void chessboardFound();
    void calibrationCompleted();

    friend class CameraCalibrationRunnable;
};

class CameraCalibrationRunnable : public QVideoFilterRunnable  {
public:
    CameraCalibrationRunnable(CameraCalibrationFilter& filter) noexcept;
    QVideoFrame run(QVideoFrame* input, const QVideoSurfaceFormat& surfaceFormat, RunFlags flags) override;

private:
    CameraCalibrator m_calibrator;
    CameraCalibrationFilter& m_filter;
};
