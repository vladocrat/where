import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    width: 600
    height: 60
    visible: true
    color: "transparent"

    flags: Qt.Tool | Qt.FramelessWindowHint

    x: Math.round((Screen.width - width) / 2)
    y: Math.round((Screen.height - height) / 2)

    Component.onCompleted: {
        console.log(Screen.width, Screen.height)
    }

    Rectangle {
        anchors.fill: parent

        border.width: 1
        radius: 30

        RowLayout {
            anchors.fill: parent

            Image {
                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.maximumWidth: 50
                Layout.minimumWidth: 50


                onStatusChanged: {
                    console.log("Ready:", paintedWidth, paintedHeight)
                    console.log(status)
                }
                Component.onCompleted: {
                    console.log(status)
                    console.log(progress)
                    console.log(paintedHeight, height)
                    console.log(paintedWidth, width)
                }

                height: 10
                width: 10

                source: ":/icons/apple.jpg"
            }

            TextField {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.margins: 10

                placeholderText: "Where is..."

                background: Rectangle {
                    anchors.fill: parent
                    anchors.margins: 10
                    radius: 30
                }
            }
        }
    }
}
