import QtQuick 2.15
import QtQuick.Controls

Item {
    id: root

    property alias view: view
    required property Component delegate

    QtObject {
        id: internal

        property int revealIndex: 0
        property var revealedIndices: []
    }

    Timer {
        id: revealTimer

        interval: 120
        repeat: true
        running: false

        onTriggered: {
            if (internal.revealIndex < view.model.count) {
                internal.revealedIndices.push(internal.revealIndex)
                internal.revealIndex++
            } else {
                revealTimer.stop()
            }
        }
    }

    function startReveal() {
        for (var i = 0; i < view.model.count; ++i) {
            view.model.set(i, {"shown": false})
        }

        internal.revealIndex = 0

        if (revealTimer.running) {
            revealTimer.stop()
        }

        revealTimer.start()
    }

    function resetReveal() {
        revealTimer.stop()
        internal.revealIndex = 0

        for (var i = 0; i < view.model.count; ++i) {
            view.model.set(i, {"shown": false})
        }
    }

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
    }
}
