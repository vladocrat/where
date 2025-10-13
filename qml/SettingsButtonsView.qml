import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Item {
    id: root

    readonly property alias buttonGroup: group
    property alias currentIndex: list.currentIndex

    ListModel {
        id: settingsModel

        ListElement {
            text: "Backends"
            iconSource: "qrc:/icons/server.svg"
        }

        ListElement {
            text: "Hotkeys"
            iconSource: "qrc:/icons/keyboard.svg"
        }

        ListElement {
            text: "Palette"
            iconSource: "qrc:/icons/palette.svg"
        }
    }

    ListView {
        id: list

        anchors.fill: parent

        ButtonGroup {
            id: group
        }

        model: settingsModel
        interactive: false

        delegate: WhereRadioButton {
            width: root.width
            height: 40

            text: model.text
            iconSource: model.iconSource
            ButtonGroup.group: group

            onCheckedChanged: {
                if (checked) {
                    root.currentIndex = index;
                }
            }
        }

        states: [
            State {
                name: "hidden"
                when: !root.visible
                PropertyChanges {
                    target: list
                    opacity: 0
                    scale: 0.7
                    currentIndex: 0
                }
            },
            State {
                name: "shown"
                when: root.visible
                PropertyChanges {
                    target: list
                    opacity: 1
                    scale: 1
                }
            }
        ]

        transitions: [
            Transition {
                from: "*"; to: "*"

                NumberAnimation {
                    target: list
                    property: "opacity"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
                SpringAnimation {
                    target: list
                    property: "scale"
                    spring: 2
                    damping: 0.3
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        ]
    }
}
