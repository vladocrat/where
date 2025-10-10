import QtQuick 2.15
import QtQuick.Controls

Button {    
    id: root

    property alias imgSource: img.source

    contentItem: Image {
        id: img

        anchors.fill: parent

        sourceSize.height: 512
        sourceSize.width: 512
        antialiasing: true

        fillMode: Image.PreserveAspectFit
        smooth: true
    }

    background: Rectangle {
        anchors.fill: parent
        anchors.topMargin: 10
        anchors.bottomMargin: 10

        radius: 10

        color: mouseArea.containsMouse ? "#d6b6b6" : "white"

        MouseArea {
            id: mouseArea

            anchors.fill: parent

            hoverEnabled: true
            propagateComposedEvents: true
            cursorShape: Qt.PointingHandCursor
        }
    }
}
