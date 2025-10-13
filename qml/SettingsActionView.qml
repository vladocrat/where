import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    property alias backendsListModel: backendsList.model
    required property ButtonGroup group
    property int currentIndex: -1

    StackLayout {
        anchors.fill: parent

        visible: root.currentIndex !== -1
        currentIndex: root.currentIndex

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            visible: false

            RowLayout {
                Layout.fillWidth: true
                Layout.maximumHeight: 20
                Layout.minimumHeight: 20

                Text {
                    text: "Current backend: "
                }

                ComboBox {
                    id: backendsList

                    delegate: Text {
                        text: name
                    }
                }
            }
        }

        HotkeySettingsView {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        Text {
            Layout.fillHeight: true
            Layout.fillWidth: true

            text: "TBD"
        }
    }
}
