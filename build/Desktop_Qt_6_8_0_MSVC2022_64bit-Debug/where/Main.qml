import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: root
    width: 600
    height: 400
    visible: true
    color: "transparent"

    flags: Qt.Tool | Qt.FramelessWindowHint

    x: Math.round((Screen.width - width) / 2)
    y: Math.round((Screen.height - height) / 2)

    Component.onCompleted: {
        console.log(Screen.width, Screen.height)
    }

    property int revealIndex: 0

    function startReveal() {
        for (var i = 0; i < lm.count; ++i) {
            lm.set(i, {"shown": false})
        }
        revealIndex = 0
        if (revealTimer.running) revealTimer.stop()
        revealTimer.start()
    }

    function resetReveal() {
        revealTimer.stop()
        revealIndex = 0
        for (var i = 0; i < lm.count; ++i) lm.set(i, {"shown": false})
    }

    Rectangle {
        radius: 30
        width: parent.width
        height: column.implicitHeight
        //color: "transparent"

        Behavior on height {
            NumberAnimation {
                duration: 400
                easing.type: Easing.InOutQuad
            }
        }

        ColumnLayout {
            id: column
            anchors.margins: 10
            spacing: 0

            RowLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.minimumHeight: 60
                Layout.maximumHeight: 60
                Layout.alignment: Qt.AlignTop

                Image {
                    Layout.alignment: Qt.AlignCenter
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.maximumWidth: 50
                    Layout.minimumWidth: 50

                    height: 10
                    width: 10

                    source: ":/icons/apple.jpg"
                }

                TextField {
                    id: searchbar

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.margins: 10

                    placeholderText: "Where is..."

                    background: Rectangle {
                        anchors.fill: parent
                        anchors.margins: 10
                        radius: 30
                    }

                    onTextEdited: {
                        if (text !== "") {
                            startReveal()
                        } else {
                            resetReveal()
                        }
                    }
                }
            }

            Rectangle {
                Layout.minimumWidth: root.width - 20
                Layout.maximumHeight: 1
                Layout.minimumHeight: 1
                Layout.leftMargin: 10
                Layout.rightMargin: 10

                visible: searchbar.text !== ""

                onVisibleChanged: {
                    if (visible) {
                        width = root.width - 20;
                    } else {
                        width = 0;
                    }
                }

                Behavior on width {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }

                color: "black"
            }

            ListModel {
                id: lm

                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
                ListElement { text: "text"; shown: false }
            }

            Timer {
                id: revealTimer
                interval: 120
                repeat: true
                running: false
                onTriggered: {
                    if (revealIndex < lm.count) {
                        lm.set(revealIndex, {"shown": true})
                        revealIndex++
                    } else {
                        revealTimer.stop()
                    }
                }
            }


            ListView {
                Layout.preferredHeight: 200
                Layout.minimumWidth: root.width - 20
                Layout.leftMargin: 10
                Layout.rightMargin: 10
                Layout.topMargin: 10

                visible: searchbar.text !== ""
                flickDeceleration: 2000

                model: lm
                clip: true
                spacing: 10

                ScrollBar.vertical: ScrollBar {
                    parent: parent
                    anchors.right: parent.right
                }

                delegate: Rectangle {
                    implicitWidth: root.width
                    implicitHeight: 20
                    color: "red"
                    opacity: model.shown ? 1.0 : 0.0
                    scale: model.shown ? 1.0 : 0.5

                    Behavior on opacity { NumberAnimation { duration: 200; easing.type: Easing.InOutQuad } }
                    Behavior on scale { NumberAnimation { duration: 120; easing.type: Easing.OutQuad } }
                }
            }
        }
    }
}

