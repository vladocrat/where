import QtQuick 2.15
import QtQuick.Controls

Item {
    id: root

    property alias view: view
    required property Component delegate

    ListView {
        id: view

        anchors.fill: parent

        flickDeceleration: 1000

        clip: true
        spacing: 10

        ScrollBar.vertical: ScrollBar {
            parent: parent
            anchors.right: parent.right
        }

        delegate: root.delegate

        add: Transition {
            NumberAnimation {
                property: "opacity"
                from: 0.8
                to: 1.0
                duration: 75
                easing.type: Easing.OutInExpo
            }
        }
    }
}
