import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Item {
    id: root

    property alias backendsModel: backendsList.model

    RowLayout {
        anchors.fill: parent

        ColumnLayout {
            id: column

            Layout.fillWidth: true
            Layout.fillHeight: true

            ButtonGroup {
                id: settingsGroup

                buttons: column.children
            }

            RadioButton {
                id: backends

                text: "Backends"
            }

            RadioButton {
                id: palette

                text: "Palette"
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: parent.implicitWidth * 0.7

            visible: backends.checked

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

        Text {
            Layout.fillWidth: true
            Layout.fillHeight: true

            text: "TBD"

            visible: palette.checked
        }
    }
}
