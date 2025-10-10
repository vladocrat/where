import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    required property string fileName
    required property string filePath

    signal openRequested(var filePath);

    Rectangle {
        anchors.fill: parent

        opacity: visible ? 1.0 : 0.0
        scale: visible ? 1.0 : 0.5
        color: mouseArea.containsMouse ? "#d6b6b6" : "white"

        Behavior on opacity {
            NumberAnimation { duration: 200; easing.type: Easing.InOutQuad }
        }

        Behavior on scale {
            NumberAnimation { duration: 120; easing.type: Easing.OutQuad }
        }

        RowLayout {
            anchors.fill: parent

            Image {
                Layout.fillHeight: true
                Layout.maximumWidth: 30
                Layout.minimumWidth: 30
                Layout.margins: 2

                sourceSize.height: 512
                sourceSize.width: 512
                antialiasing: true

                fillMode: Image.PreserveAspectFit
                smooth: true

                source: "qrc:/icons/file.svg"
            }

            ColumnLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignLeft

                Text {
                    horizontalAlignment: Text.AlignLeft

                    text: root.fileName
                    font.pointSize: 10
                }

                Text {
                    horizontalAlignment: Text.AlignLeft

                    text: root.filePath
                    font.pointSize: 8
                }
            }
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true

        onClicked: {
            root.openRequested(root.filePath + "/" + root.fileName);
        }
    }
}


