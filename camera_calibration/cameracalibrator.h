#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

class CameraCalibrator {
public:
    CameraCalibrator(const cv::Size boardSize = cv::Size{8, 6})
        : m_boardSize{boardSize} {}

    bool findChessboard(const cv::Mat& mat);
    double calibrate(cv::Size& imageSize);
    cv::Mat remap(const cv::Mat& image);

    const std::vector<cv::Point2f>& lastChessboardCorner() const noexcept;
    const cv::Mat lastChessboardImage() const noexcept;

    const cv::Size boardSize() const noexcept { return m_boardSize; }
    const cv::Mat& cameraMatrix() const noexcept { return m_cameraMatrix; }
    const cv::Mat& distortion() const noexcept { return m_distCoeffs; }

    const cv::Mat& chessboardImage() const noexcept;

private:
    void appendCornerPoints(const std::vector<cv::Point2f>& imageCorners);

private:
    bool m_enable = true;
    cv::Size m_boardSize;

    std::vector<cv::Point2f> m_lastCorners;
    std::vector<std::vector<cv::Point3f>> m_worldObjectPoints;
    std::vector<std::vector<cv::Point2f>> m_imagePoints;

    cv::Mat m_cameraMatrix;
    cv::Mat m_distCoeffs;
    std::vector<cv::Mat> m_rotationVecs;
    std::vector<cv::Mat> m_translationtVecs;
    cv::Mat m_mapX, m_mapY;
    cv::Mat m_lastChessboardImage;
    bool m_mustInitUndistort;
};
