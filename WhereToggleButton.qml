import QtQuick 2.15
import QtQuick.Controls

WhereButton {
    id: root

    property bool toggled: false

    onClicked: {
        root.toggled = !root.toggled;
    }

    backgroundComponent.color: {
        if (root.toggled) {
            return "#eba9a9";
        }

        if (backgroundComponent.containsMouse) {
            return "#d6b6b6";
        } else {
            return "white";
        }
    }
}
