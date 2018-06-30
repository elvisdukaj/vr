import QtQuick.Controls 2.2
import QtQuick.Window 2.10

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Camera Calibration")

    SwipeView {
        id: swipeView
        anchors.fill: parent

        Page {
            AcquisitionImage {
                id: acquisition;
                anchors.fill:  parent

                camera.imageCapture.onImageCaptured:
                {
                    console.debug("image captured");
                    candidateImage.source = preview;
                    swipeView.setCurrentIndex(1);
                }
            }
        }

        Page {
            ValidateImage {
                id: candidateImage
                anchors.fill: parent

                camera: acquisition.camera

                onAccepted: {
                    swipeView.setCurrentIndex(0);
                    acquisition.activateFilter();
                }

                onRejected: {
                    swipeView.setCurrentIndex(0);
                    acquisition.activateFilter();
                }
            }
        }
    }
}
