#include "cameracalibrator.h"
#include <opencv2/core/types_c.h>
#include <iostream>

using namespace std;

bool CameraCalibrator::findChessboard(const cv::Mat& image)
{
    if (!m_enable)
        return false;

    m_lastCorners.clear();

    if (cv::findChessboardCorners(image, m_boardSize, m_lastCorners, cv::CALIB_CB_FAST_CHECK))
    {
        return true;
//        cv::Mat grayscale;
//        cv::cvtColor(image, grayscale, cv::COLOR_RGBA2GRAY);

//        cv::cornerSubPix(
//                    grayscale, m_lastCorners, cv::Size{11, 11},
//                    cv::Size(-1, -1),
//                    cv::TermCriteria{
//                        CV_TERMCRIT_EPS + CV_TERMCRIT_ITER,
//                        300, 0.01}
//                    );

//        if (static_cast<int>(m_lastCorners.size()) == m_boardSize.area())
//        {
//            m_lastChessboardImage = image.clone();

//            cv::drawChessboardCorners(
//                        m_lastChessboardImage,
//                        m_boardSize,
//                        m_lastCorners,
//                        true
//                        );

//            cv::bitwise_not(m_lastChessboardImage, m_lastChessboardImage);

//            appendCornerPoints(m_lastCorners);
//            return true;
//        }
    }

    return false;
}

void CameraCalibrator::appendCornerPoints(const std::vector<cv::Point2f>& imageCorners)
{
    vector<cv::Point3f> objectCorners;

    for (auto y = 0; y < m_boardSize.height; ++y)
        for (auto x = 0; x < m_boardSize.width; ++x)
            objectCorners.push_back(
                        cv::Point3f(static_cast<float>(y),
                                    static_cast<float>(x),
                                    0.0f
                                    )
                        );

    m_worldObjectPoints.push_back(objectCorners);
    m_imagePoints.push_back(imageCorners);
}

double CameraCalibrator::calibrate(cv::Size& imageSize)
{
    m_mustInitUndistort = true;

    // start calibration
    auto res = cv::calibrateCamera(
                m_worldObjectPoints,
                m_imagePoints,
                imageSize,
                m_cameraMatrix,
                m_distCoeffs,
                m_rotationVecs,
                m_translationtVecs
                );

    cout << "Camera matrix: " << m_cameraMatrix << '\n'
         << "Camera distortion: " << m_distCoeffs << '\n'
         << endl;

    return res;
}

cv::Mat CameraCalibrator::CameraCalibrator::remap(const cv::Mat& image)
{
    if (m_mustInitUndistort)
    {
        cv::initUndistortRectifyMap(
                    m_cameraMatrix,     // computed camera matrix
                    m_distCoeffs,       // computed distortion matrix
                    cv::Mat(),          // optional rectification (none)
                    cv::Mat(),          // camera matrix to generate undistorted
                    image.size(),       // size of undistorted
                    CV_32FC1,           // type of output map
                    m_mapX, m_mapY      // the x and y mapping functions
                    );
        m_mustInitUndistort = false;
    }

    // Apply mapping functions
    cv::Mat outImage;
    cv::remap(image, outImage, m_mapX, m_mapY, cv::INTER_LINEAR);
    return outImage;
}

const std::vector<cv::Point2f> &CameraCalibrator::lastChessboardCorner() const noexcept
{
    return m_lastCorners;
}

const cv::Mat CameraCalibrator::lastChessboardImage() const noexcept
{
    return m_lastChessboardImage;
}

const cv::Mat &CameraCalibrator::chessboardImage() const noexcept
{
    return m_lastChessboardImage;
}
