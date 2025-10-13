import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    property alias backendsModel: settingsActionView.backendsListModel

    states: [
        State {
            name: "hidden"
            when: !root.visible
            PropertyChanges {
                target: divider
                height: 0
            }
        },
        State {
            name: "visible"
            when: root.visible
            PropertyChanges {
                target: divider
                height: root.height
            }
        }

    ]

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true

            SettingsButtonsView {
                id: settingsNav

                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                Layout.preferredHeight: root.height
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        Rectangle {
            id: divider

            Layout.fillHeight: true
            Layout.maximumWidth: 1
            Layout.minimumWidth: 1
            height: parent.height;

            border.width: 1

            Behavior on height {
                NumberAnimation {
                    duration: 500
                    easing.type: Easing.OutCubic
                }
            }
        }

        SettingsActionView {
            id: settingsActionView

            Layout.fillHeight: true
            Layout.minimumWidth: root.width * 0.75
            Layout.maximumWidth: root.width * 0.75

            group: settingsNav.buttonGroup
            currentIndex: settingsNav.currentIndex
        }
    }
}
