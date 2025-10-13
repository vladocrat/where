import QtQuick
import QtQuick.Controls

RadioDelegate {
    id: root

    property alias iconSource: icon.source

    indicator: Image {
        id: icon

        width: 26
        height: 26

        x: root.leftPadding
        y: root.height / 2 - height / 2

        sourceSize.height: 512
        sourceSize.width: 512
        antialiasing: true

        fillMode: Image.PreserveAspectFit
    }

    background: Rectangle {
        anchors.fill: parent

        color: {
            if (root.checked) {
                return "#eba9a9";
            } else if (mouseArea.containsMouse) {
                return "#d6b6b6";
            } else {
                return "white";
            }
        }
        radius: 15

        MouseArea {
            id: mouseArea

            anchors.fill: parent

            hoverEnabled: true
            cursorShape: Qt.PointingHandCursor
        }
    }

    contentItem: Text {
        text: root.text
        font: root.font

        verticalAlignment: Text.AlignVCenter

        leftPadding: root.indicator.width + root.spacing
    }
}
