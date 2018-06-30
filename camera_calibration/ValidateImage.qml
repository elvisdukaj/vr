import QtQuick 2.10
import QtQuick.Window 2.10
import QtMultimedia 5.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Rectangle {
    property alias source: preview.source

    signal accepted()
    signal rejected()

    Image {
        anchors.fill: parent
        id: preview
    }

    RowLayout {
        id: layout

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40

        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "Accept"

            onClicked: {
                accepted()
            }
        }

        Button {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "Reject"

            onClicked: {
                rejected()
            }
        }
    }
}
