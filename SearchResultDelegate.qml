import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: root

    required property string fileName
    required property string filePath

    signal openRequested(var filePath);
    signal copyPath(var filePath);

    Rectangle {
        anchors.fill: parent

        color: mouseArea.containsMouse ? "#d6b6b6" : "white"
        radius: 10

        RowLayout {
            anchors.fill: parent

            spacing: 7

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
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    horizontalAlignment: Text.AlignLeft

                    text: root.fileName
                    font.pointSize: 10
                }

                Text {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    horizontalAlignment: Text.AlignLeft

                    text: root.filePath
                    font.pointSize: 8
                }
            }
        }
    }

    Menu {
        id: contextMenu

        MenuItem {
            text: "Open file location"

            background: Rectangle {
                required property bool hovered

                color: parent.highlighted ? "#d6b6b6" : "white"
            }

            onTriggered: {
                root.openRequested(root.filePath);
            }
        }

        MenuItem {
            text: "Copy file path"

            background: Rectangle {
                required property bool hovered

                color: parent.highlighted ? "#d6b6b6" : "white"
            }

            onTriggered: {
                root.copyPath(root.filePath + "/" + root.fileName);
            }
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onClicked: function(mouse) {
            if (mouse.button === Qt.RightButton) {
                contextMenu.popup(mouse.x, mouse.y);
                return;
            }

            root.openRequested(root.filePath + "/" + root.fileName);
        }
    }
}


