import QtQuick 2.10
import QtQuick.Window 2.10
import QtMultimedia 5.9
import com.elvis.ar 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Camera Calibration")

    Camera {
        id: camera
    }

    CameraCalibrationFilter {
        id: cameraCalibrationFilter
        onChessboardFound:
        {
//            smallImg.source = image
        }
    }

    VideoOutput {
        source: camera

        filters: [cameraCalibrationFilter]
    }

    Image {
        id: smallImg
        width: 100;
        height: 100
        anchors.right: parent.left
        anchors.bottom: parent.bottom
    }
}
