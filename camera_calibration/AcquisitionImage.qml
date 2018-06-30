import QtQuick 2.10
import QtMultimedia 5.9
import com.elvis.ar 1.0

Rectangle {
    property alias camera: camera
    property bool isCapturing: false

    function activateFilter()
    {
        cameraCalibrationFilter.active = true;
    }

    Camera {
        id: camera
        captureMode: Camera.CaptureStillImage
    }

    CameraCalibrationFilter {
        id: cameraCalibrationFilter

        onChessboardFound:
        {
            console.debug("chessboard found!");
            camera.imageCapture.cancelCapture();

            isCapturing = true;
            cameraCalibrationFilter.active = false;
            camera.imageCapture.capture();
        }
    }

    VideoOutput {
        anchors.fill: parent
        source: camera

        filters: [cameraCalibrationFilter]
    }
}
