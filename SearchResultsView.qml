import QtQuick 2.15
import QtQuick.Controls

Item {
    id: root

    property alias view: view
    required property Component delegate

    signal loseFocus();
    signal open(var currentItem);

    onFocusChanged: {
        if (root.focus) {
            root.focus = false;
            view.focus = true;
            return;
        }

        view.currentIndex = 0;
    }

    ListView {
        id: view

        anchors.fill: parent

        flickDeceleration: 1000
        keyNavigationEnabled: true
        keyNavigationWraps: true

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

        highlight: Rectangle {
            width: view.implicitHeight
            height: view.implicitWidth
            color: "#ed7b7b"
        }

        Keys.onPressed: function(event) {
            switch (event.key) {
            case Qt.Key_Up:
                if (view.currentIndex >= 0) {
                    view.currentIndex--;

                    if (view.currentIndex < 0) {
                        root.loseFocus();
                    }
                }

                break;

            case Qt.Key_Down:
                if (view.currentIndex < view.count - 1) {
                    view.incrementCurrentIndex();
                }

                break;

            case Qt.Key_Return:
                root.open(view.currentItem);
                break;

            case Qt.Key_Tab:
                root.loseFocus();
                break;

            default:
                break;
            }

           event.accepted = true;
        }
    }
}
