cmake_minimum_required(VERSION 3.11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick Multimedia REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(camera_calibration
    "main.cpp"
    "cameracalibrationfilter.h"
    "cameracalibrationfilter.cpp"
    "cameracalibrator.h"
    "cameracalibrator.cpp"
    "timer.hpp"
    "qml.qrc"
    )

target_compile_features(camera_calibration PRIVATE cxx_std_17)

target_link_libraries(camera_calibration
PRIVATE
    Qt5::Core Qt5::Quick Qt5::Multimedia
    ${OpenCV_LIBS}
)
